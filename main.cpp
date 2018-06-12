#include "Raytracer.cpp"
#include "RenderOptions.cpp"
#include "RenderableList.cpp"
#include "Sphere.cpp"
#include "iostream"

using namespace std;

int main()
{
	RenderOptions options;
	options.height = 480;
	options.width = 640;
	options.fov = 50;
	options.maxDepth = 50;
	options.aspectRatio = options.width / (float)options.height;
	RenderableList *scene = new RenderableList();
	scene->add(new Sphere(Vector3f(0, 0, -10), 2, new Lambertian(Vector3f(0.2, 0.2, 0.2))));
	scene->add(new Sphere(Vector3f(4, 0, -10), 2, new Metal(Vector3f(0.7, 0.7, 0.7), 0.3)));
	scene->add(new Sphere(Vector3f(0, -999, -80), 1000, new Lambertian(Vector3f(0.2, 0.2, 0.2))));
	RayTracer tracer;
	tracer.setScene(scene);
	tracer.render(&options);
	return 0;
}