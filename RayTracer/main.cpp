#include "Light.cpp"
#include "Raytracer.cpp"
#include "RenderOptions.cpp"
#include "Sphere.cpp"
#include "iostream"

using namespace std;

int main()
{
	RayTracer tracer;
	tracer.addLightToScene(new Light(Vector3f(10, 10, 10), Vector3f(0, 20, -20)));
		//tracer.addLightToScene(new Light(Vector3f(10, 10, 10), Vector3f(-11, 5, -20)));
	Material mat(Vector3f(1, 0.1f, 0.1f), 0.3, 0.8, 0.2, 25);
	Material reflectiveMat(Vector3f(0.5f, 0.5f, 0.5f), 0.4, 0.3, 0.7, 25);
	reflectiveMat.type = REFLECTION;
	mat.type = DIFFUSE_AND_GLOSSY;
	tracer.addObjectToScene(new Sphere(Vector3f(0, -5, -20), 2, mat));
	tracer.addObjectToScene(new Sphere(Vector3f(0, -11000, -2000), 10000, mat));
	tracer.addObjectToScene(new Sphere(Vector3f(5, -5, -20), 2, mat));
	RenderOptions options;
	options.height = 480;
	options.width = 640;
	options.fov = 50;
	options.maxDepth = 5;
	options.aspectRatio = options.width / (float)options.height;
	tracer.render(&options);
	return 0;
}