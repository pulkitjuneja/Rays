#pragma once 

#include "Raytracer.cpp"
#include "Light.cpp"
#include "Sphere.cpp"
#include "iostream"
#include "RenderOptions.cpp"

using namespace std;

void main() {
	RayTracer tracer;
	tracer.addLightToScene(new Light(Vector3f(1, 10, 1), Vector3f(-20, 10, 10)));
	Material mat(Vector3f(0.8f,0.6f,0.5f),0.3,0.3,0.7,25);
	mat.type = DIFFUSE_AND_GLOSSY;
	tracer.addObjectToScene(new Sphere(Vector3f(-1, 0, -22), 2,mat));
	tracer.addObjectToScene(new Sphere(Vector3f(-1, 5, -22), 2, mat));
	RenderOptions options;
	options.height = 480;
	options.width = 640;
	options.fov = 30;
	options.aspectRatio = options.width / (float)options.height;
	tracer.render(&options);
}