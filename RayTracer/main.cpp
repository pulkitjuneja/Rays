#pragma once 

#include "Raytracer.cpp"
#include "Light.cpp"
#include "Sphere.cpp"
#include "RenderOptions.cpp"

void main() {
	RayTracer tracer;
	tracer.addLightToScene(new Light(Vector3f(1, 1, 1), Vector3f(-20, 70, 20)));
	Material mat(Vector3f(0.8f,0.6f,0.5f),0.3,0.3,0.7,25);
	mat.type = DIFFUSE_AND_GLOSSY;
	tracer.addObjectToScene(new Sphere(Vector3f(-1, 0, -22), 2,mat));
	RenderOptions options;
	options.height = 480;
	options.width = 640;
	options.fov = 240;
	options.aspectRatio = options.width / (float)options.height;
	tracer.render(&options);
}	