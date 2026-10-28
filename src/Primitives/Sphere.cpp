/*
** EPITECH PROJECT, 2026
** Sphere.cpp
** File description:
** Main file for the Sphere
*/

#include "Sphere.hpp"

namespace RayTracer {

/**
 * @brief Checks whether a ray intersects this sphere.
 *
 * @param ray Ray to test.
 *
 * @return True if the ray intersects this sphere, false otherwise.
 */
std::optional<double> Sphere::hits(const Ray &ray) const
{
    const Math::Vector3D rayDirection = ray.getDirection();
    const Math::Point3D rayOrigin = ray.getOrigin();
    const Math::Vector3D centerToOrigin(rayOrigin.getX() - this->_center.getX(),
                                        rayOrigin.getY() - this->_center.getY(),
                                        rayOrigin.getZ() - this->_center.getZ());

    const double a = rayDirection.dot(rayDirection);
    const double halfB = rayDirection.dot(centerToOrigin);
    const double c = centerToOrigin.dot(centerToOrigin) - this->_radius * this->_radius;
    const double discriminant = halfB * halfB - a * c;

    if (discriminant < 0.0 || std::abs(a) < 1e-12) {
        return std::nullopt;
    }

    const double sqrtD = std::sqrt(discriminant);
    const double invA = 1.0 / a;
    const double t1 = (-halfB - sqrtD) * invA;
    const double t2 = (-halfB + sqrtD) * invA;

    if (t1 >= 0.0 && t2 >= 0.0) {
        return std::min(t1, t2);
    }
    if (t1 >= 0.0) {
        return std::optional<double>(t1);
    }
    if (t2 >= 0.0) {
        return std::optional<double>(t2);
    }
    return std::nullopt;
}

/**
 * @brief Computes the surface normal at a point on the sphere.
 *
 * @param point Point on the sphere surface.
 *
 * @return Unit-length normal vector.
 */
Math::Vector3D Sphere::getNormalAt(const Math::Point3D &point) const
{
    const Math::Vector3D normal(point.getX() - this->_center.getX(),
                                point.getY() - this->_center.getY(),
                                point.getZ() - this->_center.getZ());

    return normal.normalized();
}

/**
 * @brief Translates this sphere by the given offsets.
 *
 * @param offset Translation offset.
 */
void Sphere::translate(const Math::Vector3D &offset)
{
    this->_center += offset;
}

/**
 * @brief Rotates this sphere.
 *
 * @param rotation Rotation vector.
 */
void Sphere::rotate(const Math::Vector3D &)
{
}

}
