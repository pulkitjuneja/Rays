
#include "Raytracer.hpp"
#include "RenderOptions.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "iostream"

using namespace std;

float randomFloat()
{
	return (float)drand48();
}

void generateRandomScene(Scene *scene)
{
	const int range = 7;
	// Dielectric dielectricMaterial(1.5f);
	scene->add(new Sphere(Vector3f(0.0f, -1000.0f, 0.0f), 1000, new Lambertian(Vector3f(0.5f, 0.5f, 0.5f))));

	for (int a = -range; a < range; ++a)
	{
		for (int b = -range; b < range; ++b)
		{
			float chooseMaterial = randomFloat();
			Vector3f center(a + 1.5f * randomFloat(), 0.2f, b + 1.5f * randomFloat());
			if ((center - Vector3f(4.0f, 0.2f, 0.0f)).lengthSquared() > 1.0f)
			{
				if (chooseMaterial < 0.5f)
				{
					scene->add(new Sphere(center, 0.2f, new Lambertian(Vector3f(randomFloat() * randomFloat(), randomFloat() * randomFloat(), randomFloat() * randomFloat()))));
				}
				else if (chooseMaterial < 0.95f)
				{
					scene->add(new Sphere(center, 0.2f, new Metal(Vector3f(0.5f * (1 + randomFloat()), 0.5f * (1 + randomFloat()), 0.5f * (1 + randomFloat())), 0.5f * randomFloat())));
				}
				else
				{
					scene->add(new Sphere(center, 0.2f, new Dielectric(randomFloat())));
				}
			}
			cout << "inner iteration over \n";
		}
		cout << "outer iteration over \n";
	}
	cout << "Loop over \n";
	// scene->add(new Sphere(Vector3f(-3.9f, 1.0f, 0), 1.0f, new Lambertian(Vector3f(0.4f, 0.9f, 0.1f))));
	// scene->add(new Sphere(Vector3f(0, 1, 0), 1.0f, new Metal(Vector3f(0.7f, 0.6f, 0.5f), 0.001f)));
	// scene->add(new Sphere(Vector3f(3.9f, 1, 0), 1.0f, &dielectricMaterial));
}

int main()
{
	RenderOptions options;
	options.height = 500;
	options.width = 889;
	options.fov = 90;
	options.maxDepth = 50;
	options.aspectRatio = (float)options.width / (float)options.height;
	Scene *scene = new Scene(options);
	scene->camera.setPositionAndRotation(Vector3f(0, 0.3f, 0.0f), Vector3f(0, 0, -1));
	generateRandomScene(scene);
	RayTracer tracer;
	tracer.setScene(scene);
	cout << "scene gen over \n";
	tracer.render(&options);
	return 0;
}