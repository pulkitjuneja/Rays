#pragma once

#include "Vector3.cpp"
#include "global.h"
#include "RenderOptions.cpp"
#include "Material.cpp"
#include "RenderableList.cpp"

#define PI 3.14159265

using namespace std;

class RayTracer
{
protected:
	int MAX_DEPTH;
	RenderableList *scene;
	// vector<Renderable *> sceneObjects;
	Vector3f trace(Ray &ray, int depth)
	{
		if (depth >= MAX_DEPTH)
		{
			return Vector3f(0, 0, 0);
		}
		HitRecord rec;
		if (scene->intersects(ray, rec))
		{
			rec.calculateProperties(ray);
			Ray scattered;
			Vector3f attenuation;
			rec.material->scatter(ray, rec, attenuation, scattered);
			return trace(scattered, depth + 1) * attenuation;
		}
		else
		{
			// float t = 0.5f * (ray.direction.y + 1);
			// return Vector3f(1.0f, 1.0f, 1.0f) * (1 - t) + Vector3f(0.5f, 0.7f, 1.0f) * t;
			return Vector3f(0.5, 0.7, 1.0);
		}
	}

	template <typename T>
	T clamp(const T &value, const T &low, const T &high)
	{
		return value < low ? low : (value > high ? high : value);
	}

public:
	void render(RenderOptions *options)
	{
		MAX_DEPTH = options->maxDepth;
		int ns = 50;
		Vector3f *frameBuffer = new Vector3f[options->height * options->width];
		float scale = tan(options->fov * 0.5 * PI / 180.0);
		Vector3f origin(0, 0, 0);
		int count = 0;
		for (int j = 0; j < options->height; j++)
		{
			for (int i = 0; i < options->width; i++)
			{
				Vector3f color(0, 0, 0);
				for (int s = 0; s < ns; s++)
				{
					float x = (2 * ((i + 0.5) / (float)options->width) - 1) * options->aspectRatio * scale;
					float y = (1 - 2 * ((j + 0.5) / (float)options->height)) * scale;
					Vector3f dir(x, y, -1);
					dir = dir.normalize();
					Ray ray(origin, dir);
					color = color + trace(ray, 0);
				}
				color = color / ns;
				color = Vector3f(sqrt(color.x), sqrt(color.y), sqrt(color.z));
				frameBuffer[count++] = color;
			}
		}
		writeToImgae(frameBuffer, options);
	}

	void setScene(RenderableList *scene)
	{
		this->scene = scene;
	}

	void writeToImgae(Vector3f *frameBuffer, RenderOptions *options)
	{
		ofstream ofs("finalImage.ppm", ios::out);
		ofs << "P6\n"
				<< options->width << " " << options->height << "\n255\n";
		for (uint32_t i = 0; i < options->height * options->width; ++i)
		{
			char r = (char)(255 * clamp(frameBuffer[i].x, 0.0f, 1.0f));
			char g = (char)(255 * clamp(frameBuffer[i].y, 0.0f, 1.0f));
			char b = (char)(255 * clamp(frameBuffer[i].z, 0.0f, 1.0f));
			ofs << r << g << b;
		}
		ofs.close();
		delete[] frameBuffer;
	}

	// void addObjectToScene(Renderable *object) { sceneObjects.push_back(object); }
};