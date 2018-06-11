#pragma once

#include <math.h>
#include <algorithm>
#include <fstream>
#include <vector>
#include "Light.cpp"
#include "RenderOptions.cpp"
#include "Vector3.cpp"
#include "global.h"
#include "renderable.cpp"

#define PI 3.14159265

using namespace std;

class RayTracer
{
  protected:
	int MAX_DEPTH = 5;
	vector<Renderable *> sceneObjects;
	vector<Light *> lights;
	Vector3f trace(Vector3f &rayOrigin, Vector3f &raydirection, int depth)
	{
		Vector3f hitColor = Vector3f(0.235294f, 0.67451f, 0.843137f);
		if (depth > MAX_DEPTH)
		{
			return hitColor;
		}
		Renderable *hitObject = NULL;
		float tnear = INT32_MAX;
		if (checkRayCollision(rayOrigin, raydirection, &hitObject, tnear))
		{
			Vector3f phit = rayOrigin + raydirection * tnear;
			Vector3f nhit, uv;
			int index;
			hitObject->getProperties(phit, raydirection, index, uv, nhit);
			float bias = 1e-4;
			float inside = false;
			//std::cout<<tnear<<"\n";
			if (raydirection.dot(nhit))
			{
				switch (hitObject->surfaceProperties.type)
				{
				case DIFFUSE_AND_GLOSSY:
				{
					Vector3f lightAmt(0, 0, 0), specularAmount(0, 0, 0);
					Vector3f shadowPointOrig = phit + nhit * bias;
					for (vector<Light *>::iterator lt = lights.begin(); lt != lights.end(); lt++)
					{
						Vector3f distanceToLightVector = ((*lt)->position - phit);
						float distanceToLight = distanceToLightVector.lengthSquared();
						Vector3f lightDir = ((*lt)->position - phit).normalize();
						float LdotN = std::max(0.0f, lightDir.dot(nhit));
						Renderable *shadowHitObject = NULL;
						float tnearShadow = INT32_MAX;
						bool isInShadow = checkRayCollision(shadowPointOrig, lightDir, &shadowHitObject, tnearShadow) && (tnearShadow * tnearShadow < distanceToLight);
						//std::cout<<distanceToLight<<"\n";
						lightAmt = lightAmt + (*lt)->intensity * LdotN * (1 - isInShadow);
						Vector3f reflectionDir = reflect(-lightDir, nhit);
						specularAmount = specularAmount + (*lt)->intensity * pow(max(0.0f, -(reflectionDir.dot(raydirection))), hitObject->surfaceProperties.specularExponent);
					}
					hitColor = hitObject->surfaceProperties.diffuseColor * lightAmt * hitObject->surfaceProperties.Kd;
					break;
				}
				case REFLECTION:
				{
					float kr;
					fresnel(rayOrigin, raydirection, hitObject->surfaceProperties.ior, kr);
					Vector3f reflectionDir = reflect(raydirection, nhit);
					Vector3f reflectionOrigion = phit + nhit * bias;
					hitColor = trace(reflectionOrigion, reflectionDir, depth + 1) * kr;
					break;
				}
				}
			}
		}

		return hitColor;
	}

	Vector3f reflect(const Vector3f &I, const Vector3f &N)
	{
		float IdotN = I.dot(N);
		return N * IdotN * 2;
	}

	bool checkRayCollision(Vector3f &origin, Vector3f &dir, Renderable **hitObject, float &tnear)
	{
		for (vector<Renderable *>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); ++it)
		{
			float distance;
			if ((*it)->intersects(origin, dir, distance))
			{
				if (distance < tnear)
				{
					tnear = distance;
					*(hitObject) = *it;
					return true;
				}
			}
		}
		return false;
	}

	void fresnel(const Vector3f &I, const Vector3f &N, const float &ior, float &kr)
	{
		float cosi = clamp(-1, 1, I.dot(N));
		float etai = 1, etat = ior;
		if (cosi > 0)
		{
			std::swap(etai, etat);
		}
		// Compute sini using Snell's law
		float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
		// Total internal reflection
		if (sint >= 1)
		{
			kr = 1;
		}
		else
		{
			float cost = sqrtf(std::max(0.f, 1 - sint * sint));
			cosi = fabsf(cosi);
			float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
			float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
			kr = (Rs * Rs + Rp * Rp) / 2;
		}
		// As a consequence of the conservation of energy, transmittance is given by:
		// kt = 1 - kr;
	}

	float clamp(float lo, float hi, float v)
	{
		return std::max(lo, std::min(hi, v));
	}

  public:
	void render(RenderOptions *options)
	{
		Vector3f *frameBuffer = new Vector3f[options->height * options->width];
		float scale = tan(options->fov * 0.5 * PI / 180.0);
		Vector3f origin(0, 0, 0);
		int count = 0;
		for (int j = 0; j < options->height; j++)
		{
			for (int i = 0; i < options->width; i++)
			{
				float x = (2 * ((i + 0.5) / (float)options->width) - 1) * options->aspectRatio * scale;
				float y = (1 - 2 * ((j + 0.5) / (float)options->height)) * scale;
				Vector3f dir(x, y, -1);
				dir = dir.normalize();
				// std::cout << "( " << dir.x << " , " << dir.y << " )\n";
				MAX_DEPTH = options->maxDepth;
				Vector3f result = trace(origin, dir, 0);
				frameBuffer[count++] = result;
			}
		}
		ofstream ofs("finalImage.ppm", ios::out);
		ofs << "P6\n"
			<< options->width << " " << options->height << "\n255\n";
		for (uint32_t i = 0; i < options->height * options->width; ++i)
		{
			char r = (char)(255 * clamp(0, 1, frameBuffer[i].x));
			char g = (char)(255 * clamp(0, 1, frameBuffer[i].y));
			char b = (char)(255 * clamp(0, 1, frameBuffer[i].z));
			ofs << r << g << b;
		}

		ofs.close();

		delete[] frameBuffer;
	}

	void addObjectToScene(Renderable *object) { sceneObjects.push_back(object); }

	void addLightToScene(Light *light) { lights.push_back(light); }
};