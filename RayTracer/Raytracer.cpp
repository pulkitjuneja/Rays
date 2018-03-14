#pragma once 

#include "global.h"
#include <vector>
#include <fstream>
#include "Vector3.cpp"
#include <math.h>
#include "RenderOptions.cpp"
#include "Light.cpp"
#include "renderable.cpp"
#include <algorithm>

#define PI 3.14159265


using namespace std;

class RayTracer {
protected:
	const int MAX_DEPTH = 5;
	vector<Renderable*> sceneObjects;
	vector<Light*> lights;
	Vector3f trace(Vector3f &rayOrigin, Vector3f &raydirection, int depth) {
		Renderable* hitObject = NULL;
		Vector3f hitColor = Vector3f(0.5f, 0.5f, 0.5f);
		float tnear = INT_MAX;
		if (checkRayCollision(rayOrigin, raydirection, &hitObject, tnear)) {
			Vector3f phit = rayOrigin + raydirection*tnear;
			Vector3f nhit, uv;
			int index;
			hitObject->getProperties(phit, raydirection, index, uv, nhit);
			float bias = 1e-4;
			switch (hitObject->surfaceProperties.type) {
			case DIFFUSE_AND_GLOSSY:
				Vector3f lightAmt(0, 0, 0), specularAmount(0, 0, 0);
				Vector3f shadowPointOrig = (raydirection.dot(nhit) < 0) ?
					phit + nhit *bias :
					phit - nhit *bias;
				for (vector<Light*>::iterator lt = lights.begin(); lt != lights.end(); lt++) {
					Vector3f lightDir = ((*lt)->position - phit).normalize();
					float distanceToLight = ((*lt)->position - phit).lengthSquared();
					float LdotN = std::max(0.0f, lightDir.dot(nhit));
					Renderable * shadowHitObject = NULL;
					float tnearShadow = INT_MAX;
					bool isInShadow = checkRayCollision(shadowPointOrig, lightDir, &shadowHitObject, tnearShadow) && (tnearShadow*tnearShadow < distanceToLight);
					lightAmt = lightAmt + (*lt)->intensity*LdotN*(1 - isInShadow);
					Vector3f reflectionDir = reflect(-lightDir, nhit);
					specularAmount = specularAmount + (*lt)->intensity*pow(max(0.0f, -reflectionDir.dot(raydirection)), hitObject->surfaceProperties.specularExponent);
				}
				hitColor = hitObject->surfaceProperties.diffuseColor*lightAmt*hitObject->surfaceProperties.Kd + specularAmount*hitObject->surfaceProperties.Ks;
			}

		}

		return hitColor;

	}

	Vector3f reflect(const Vector3f &I, const Vector3f &N)
	{
		float IdotN = I.dot(N);
		return N * IdotN * 2;
	}


	bool checkRayCollision(Vector3f &origin, Vector3f &dir, Renderable **hitObject, float &tnear) {
		for (vector<Renderable*>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
			float distance;
			if ((*it)->intersects(origin, dir, distance)) {
				if (distance < tnear) {
					tnear = distance;
					*(hitObject) = *it;
					return true;
				}
			}
		}
		return false;
	}

	float clamp(float lo, float hi, float v)
	{
		return std::max(lo, std::min(hi, v));
	}
public:
	void render(RenderOptions* options) {
		Vector3f* frameBuffer = new Vector3f[options->height * options->width];
		float scale = tan(options->fov * 0.5 *PI / 180.0);
		Vector3f origin(0, 0, 0);
		int count = 0;
		for (int j = 0; j < options->height; j++) {
			for (int i = 0; i < options->width; i++) {
				float x = (2 * ((i + 0.5) / (float)options->width) - 1)*options->aspectRatio*scale;
				float y = (1 - 2 * ((j + 0.5) / (float)options->height))*scale;
				Vector3f dir(x, y, -1);
				dir = dir.normalize();
				//std::cout << "( " << dir.x << " , " << dir.y << " )\n";
				Vector3f result = trace(origin, dir, options->maxDepth);
				frameBuffer[count++] = result;
			}
		}
		ofstream ofs("finalImage.ppm", ios::out);
		ofs << "P6\n" << options->width << " " << options->height << "\n255\n";
		for (uint32_t i = 0; i < options->height * options->width; ++i) {
			char r = (char)(255 * clamp(0, 1, frameBuffer[i].x));
			char g = (char)(255 * clamp(0, 1, frameBuffer[i].y));
			char b = (char)(255 * clamp(0, 1, frameBuffer[i].z));
			ofs << r << g << b;
		}

		ofs.close();

		delete[] frameBuffer;
	}

	void addObjectToScene(Renderable *object) {
		sceneObjects.push_back(object);
	}

	void addLightToScene(Light * light) {
		lights.push_back(light);
	}

};