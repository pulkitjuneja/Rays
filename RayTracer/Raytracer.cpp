#pragma once 

#include "global.h"
#include <vector>
#include "Vector3.cpp"
#include "Light.cpp"
#include "renderable.cpp"
#include <algorithm>


using namespace std;

class RayTracer {
protected:
	const int MAX_DEPTH = 5;
	vector<Renderable*> sceneObjects;
	vector<Light*> lights;
public:
	Vector3f trace(Vector3f &rayOrigin, Vector3f &raydirection, int depth) {
		Renderable* hitObject = NULL;
		Vector3f hitColor = Vector3f(0, 0, 0);
		float tnear = INT_MAX;
		if (checkRayCollision(rayOrigin, raydirection, hitObject, tnear)) {
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
				for (vector<Light*>::iterator lt = lights.begin; lt != lights.end(); lt++) {
					Vector3f lightDir = ((*lt)->position - phit).normalize();
					float distanceToLight = ((*lt)->position - phit).lengthSquared();
					float LdotN = std::max(0.0f, lightDir.dot(nhit));
					Renderable * shadowHitObject = NULL;
					float tnearShadow = INT_MAX;
					bool isInShadow = checkRayCollision(shadowPointOrig, lightDir, shadowHitObject, tnearShadow) && (tnearShadow*tnearShadow < distanceToLight);
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


	bool checkRayCollision(Vector3f &origin, Vector3f &dir, Renderable *hitObject, float &tnear) {
		for (vector<Renderable*>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
			float distance;
			if ((*it)->intersects(origin, dir, distance)) {
				if (distance < tnear) {
					tnear = distance;
					hitObject = *it;
					return true;
				}
			}
		}
		return false;
	}

	void addObjectToScene(Renderable *object) {
		sceneObjects.push_back(object);
	}

	void addLightToScene(Light * light) {
		lights.push_back(light);
	}

};