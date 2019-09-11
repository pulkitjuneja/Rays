#pragma once
#include "Raytracer.hpp"

using namespace std;

Vector3f RayTracer::trace(Ray &ray, int depth)
{
    if (depth >= MAX_DEPTH)
    {
        return Vector3f(0, 0, 0);
    }
    HitData rec;
    if (scene->intersects(ray, rec))
    {
        rec.calculateProperties(ray);
        Ray scattered;
        Vector3f attenuation;
        if (rec.material->scatter(ray, rec, attenuation, scattered))
        {
            return trace(scattered, depth + 1) * attenuation;
        }
        else
        {
            return Vector3f(0.0f, 0.0f, 0.0f);
        }
    }
    else
    {
        // float t = 0.5f * (ray.direction.y + 1);
        // return Vector3f(1.0f, 1.0f, 1.0f) * (1 - t) + Vector3f(0.5f, 0.7f, 1.0f) * t;
        return Vector3f(0.5, 0.7, 1.0);
    }
}

void RayTracer::render(RenderOptions *options)
{
    MAX_DEPTH = options->maxDepth;
    int ns = 50;
    Vector3f *frameBuffer = new Vector3f[options->height * options->width];
    int count = 0;
    for (int j = options->height - 1; j >= 0; j--)
    {
        for (int i = 0; i < options->width; i++)
        {
            Vector3f color(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                float x = float(i + drand48()) / float(options->width);
                float y = float(j + drand48()) / float(options->height);
                Ray ray = scene->camera.getCameraRay(x, y);
                // Vector3f dir(x, y, -1);
                // dir = dir.normalize();
                // Ray ray(origin, dir);
                color = color + trace(ray, 0);
            }
            color = color / ns;
            color = Vector3f(sqrt(color.x), sqrt(color.y), sqrt(color.z));
            frameBuffer[count++] = color;
        }
    }
    writeToImgae(frameBuffer, options);
}

void RayTracer::setScene(Scene *scene)
{
    this->scene = scene;
}

void RayTracer::writeToImgae(Vector3f *frameBuffer, RenderOptions *options)
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