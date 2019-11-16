#include "Raytracer.hpp"
#include "RenderOptions.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "iostream"

using namespace std;

int main()
{
	RenderOptions options;
	options.height = 500;
	options.width = 889;
	options.fov = 50;
	options.maxDepth = 50;
	options.aspectRatio = (float)options.width / (float)options.height;
	Scene *scene = new Scene(options);
	scene->camera.setPositionAndRotation(Vector3f(0, 0.5f, 0), Vector3f(0, 0, -1));
	scene->add(new Sphere(Vector3f(0, -0.2, -10), 1, new Lambertian(Vector3f(0.2, 0.2, 0.2))));
	scene->add(new Sphere(Vector3f(2, -0.2, -10), 1, new Metal(Vector3f(0.7, 0.7, 0.7), 0.6f)));
	scene->add(new Sphere(Vector3f(-2, -0.2, -10), -1, new Dielectric(1.3f)));
	scene->add(new Sphere(Vector3f(0, -999, -80), 1000, new Lambertian(Vector3f(0.2, 0.2, 0.2))));
	RayTracer tracer;
	tracer.setScene(scene);
	tracer.render(&options);
	return 0;
}