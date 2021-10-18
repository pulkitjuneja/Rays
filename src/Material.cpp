#include "Material.hpp"

Vector3f Material::randomInUnitSphere()
{
    Vector3f unit;
    do
    {
        unit = Vector3f(drand48(), drand48(), drand48()) * 2 - Vector3f(1, 1, 1);
    } while (unit.lengthSquared() >= 1.0f);
    return unit;
}

Vector3f Material::reflect(const Vector3f &v, const Vector3f &normal)
{
    return v - normal * 2 * normal.dot(v);
}

// -------------------------------------------------------------------------------------------------------

bool Lambertian::scatter(const Ray &inputRay, HitData &rec, Vector3f &attenuation, Ray &outputRay)
{
    Vector3f target = rec.hitPoint + rec.normal + randomInUnitSphere();
    Vector3f direction = (target - rec.hitPoint).normalize();
    outputRay = Ray(rec.hitPoint, direction);
    attenuation = albedo;
    return true;
}

// -------------------------------------------------------------------------------------------------------

bool Metal::scatter(const Ray &inputRay, HitData &rec, Vector3f &attenuation, Ray &outputRay)
{
    Vector3f reflected = reflect(inputRay.direction, rec.normal) + randomInUnitSphere() * fuzz;
    outputRay = Ray(rec.hitPoint, reflected.normalize());
    attenuation = albedo;
    return (outputRay.direction.dot(rec.normal) > 0);
}

// -------------------------------------------------------------------------------------------------------

bool Dielectric::refract(const Vector3f &direction, const Vector3f &normal, const float niOverNt, Vector3f refracted)
{

    float dot = direction.dot(normal);
    float discriminant = 1 - ((niOverNt * niOverNt) * (1 - dot * dot));
    if (discriminant > 0)
    {
        refracted = ((direction - normal * dot) * niOverNt) - (normal * sqrt(discriminant));
        refracted = refracted.normalize();
        return true;
    }
    else
    {
        return false;
    }
}

float Dielectric::schlick(float cosine, float refractiveIndex)
{
    float r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool Dielectric::scatter(const Ray &inputRay, HitData &rec, Vector3f &attenuation, Ray &outputRay)
{
    Vector3f outwardNormal;
    float insideOrOutside = inputRay.direction.dot(rec.normal);
    Vector3f refractedDirection(0, 0, 0);
    attenuation = Vector3f(1.0, 1.0, 1.0f);
    Vector3f reflectedDirection = reflect(inputRay.direction, rec.normal);
    float cosine, reflectionProb;
    float niOverNt;
    if (insideOrOutside > 0) // if > 0 means ray is inside of the sphere
    {
        outwardNormal = -rec.normal;
        niOverNt = refractiveIndex;
        float length = sqrt(inputRay.direction.lengthSquared());
        cosine = inputRay.direction.dot(rec.normal);
        cosine = sqrt(1 - refractiveIndex * refractiveIndex * (1 - cosine * cosine));
    }
    else
    {
        outwardNormal = rec.normal;
        niOverNt = 1.0f / refractiveIndex;
        float length = sqrt(inputRay.direction.lengthSquared());
        cosine = -(inputRay.direction.dot(rec.normal));
    }

    if (refract(inputRay.direction, outwardNormal, niOverNt, refractedDirection))
    {
        reflectionProb = schlick(cosine, refractiveIndex);
    }
    else
    {
        reflectionProb = 1.0f;
    }

    if (drand48() < reflectionProb)
    {
        outputRay = Ray(rec.hitPoint, refractedDirection);
    }
    else
    {
        outputRay = Ray(rec.hitPoint, reflectedDirection);
    }
    return true;
}
