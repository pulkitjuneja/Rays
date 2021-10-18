#include "Camera.hpp"

Camera::Camera(float fov, float aspect)
{
    float theta = fov * M_PI / 180;
    float halfHeight = tan(theta / 2);
    float halfWidth = aspect * halfHeight;
    lowerLeftCorner = Vector3f(-halfWidth, -halfHeight, -1);
    width = Vector3f(2 * halfWidth, 0, 0);
    height = Vector3f(0, 2 * halfHeight, 0);
    origin = Vector3f(0, 0, 0);
}

Ray Camera::getCameraRay(float x, float y)
{
    Vector3f dir(lowerLeftCorner + width * x + height * y);
    dir = dir.normalize();
    return Ray(origin, dir);
}

void Camera::setPositionAndRotation(Vector3f worldPosition, Vector3f target)
{
    float halfHeight = float(height.y / 2);
    float halfWidth = float(width.x / 2);
    origin = worldPosition;
    Vector3f worldUp(0, 1, 0);
    Vector3f dir = (worldPosition - target).normalize();
    Vector3f right = worldUp.cross(dir).normalize();
    Vector3f up = dir.cross(right);
    lowerLeftCorner = origin - (right * halfWidth) - (up * halfHeight) - dir;
    width = right * (halfWidth * 2);
    height = up * (halfHeight * 2);
}
