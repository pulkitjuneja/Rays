#include "Light.cpp"
#include "Raytracer.cpp"
#include "RenderOptions.cpp"
#include "Sphere.cpp"
#include "iostream"

using namespace std;

int main()
{
	RayTracer tracer;
	tracer.addLightToScene(new Light(Vector3f(10, 10, 10), Vector3f(-300, 10, 10)));
	Material mat(Vector3f(1, 0.1f, 0.1f), 0.3, 0.3, 0.7, 25);
	Material reflectiveMat(Vector3f(0.5f, 0.5f, 0.5f), 0.4, 0.3, 0.7, 25);
	reflectiveMat.type = REFLECTION;
	mat.type = DIFFUSE_AND_GLOSSY;
	tracer.addObjectToScene(new Sphere(Vector3f(-1, 0, -58), 2, reflectiveMat));
	tracer.addObjectToScene(new Sphere(Vector3f(0, -500, -300), 500, mat));
	tracer.addObjectToScene(new Sphere(Vector3f(-5, 5, -18), 2, mat));
	RenderOptions options;
	options.height = 480;
	options.width = 640;
	options.fov = 50;
	options.maxDepth = 5;
	options.aspectRatio = options.width / (float)options.height;
	tracer.render(&options);
	return 0;
}