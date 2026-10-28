/*
** EPITECH PROJECT, 2026
** Cylinder.cpp
** File description:
** Main file for the Cylinder
*/

#include "Cylinder.hpp"

namespace RayTracer {

/**
 * @brief Checks whether a ray intersects this cylinder.
 *
 * @param ray Ray to test.
 *
 * @return True if the ray intersects this cylinder, false otherwise.
 */
std::optional<double> Cylinder::hits(const Ray &ray) const
{
    const Math::Vector3D rayDirection = Math::applyInverseEulerXYZRotation(ray.getDirection(), this->_rotation);
    const Math::Vector3D rayOrigin = Math::toLocalVector(ray.getOrigin(), this->_center, this->_rotation);
    const double halfHeight = this->_height / 2.0;
    const double minY = -halfHeight;
    const double maxY = halfHeight;
    const double originX = rayOrigin.getX();
    const double originZ = rayOrigin.getZ();
    const double dirX = rayDirection.getX();
    const double dirY = rayDirection.getY();
    const double dirZ = rayDirection.getZ();
    std::optional<double> closestHit = std::nullopt;
    const double radiusSquared = this->_radius * this->_radius;

    const double a = dirX * dirX + dirZ * dirZ;
    if (std::abs(a) >= 1e-12) {
        const double halfB = originX * dirX + originZ * dirZ;
        const double c = originX * originX + originZ * originZ - radiusSquared;
        const double discriminant = halfB * halfB - a * c;

        if (discriminant >= 0.0) {
            const double sqrtD = std::sqrt(discriminant);
            const double invA = 1.0 / a;
            const double t1 = (-halfB - sqrtD) * invA;
            const double t2 = (-halfB + sqrtD) * invA;

            auto considerHit = [&](double t) {
                if (t < 0.0) {
                    return;
                }

                if (this->_limited) {
                    const double hitY = rayOrigin.getY() + dirY * t;
                    if (hitY < minY || hitY > maxY) {
                        return;
                    }
                }

                if (!closestHit || t < *closestHit) {
                    closestHit = t;
                }
            };

            considerHit(t1);
            considerHit(t2);
        }
    }

    if (this->_limited && std::abs(dirY) >= 1e-12) {
        const double bottomT = (minY - rayOrigin.getY()) / dirY;
        const double bottomX = originX + dirX * bottomT;
        const double bottomZ = originZ + dirZ * bottomT;
        if (bottomT >= 0.0 && bottomX * bottomX + bottomZ * bottomZ <= radiusSquared) {
            if (!closestHit || bottomT < *closestHit) {
                closestHit = bottomT;
            }
        }

        const double topT = (maxY - rayOrigin.getY()) / dirY;
        const double topX = originX + dirX * topT;
        const double topZ = originZ + dirZ * topT;
        if (topT >= 0.0 && topX * topX + topZ * topZ <= radiusSquared) {
            if (!closestHit || topT < *closestHit) {
                closestHit = topT;
            }
        }
    }

    return closestHit;
}

/**
 * @brief Computes the surface normal at a point on the cylinder.
 *
 * @param point Point on the cylinder surface.
 *
 * @return Unit-length normal vector.
 */
Math::Vector3D Cylinder::getNormalAt(const Math::Point3D &point) const
{
    const double halfHeight = this->_height / 2.0;
    const Math::Vector3D localPoint = Math::toLocalVector(point, this->_center, this->_rotation);
    const double minY = -halfHeight;
    const double maxY = halfHeight;

    if (this->_limited) {
        if (std::abs(localPoint.getY() - maxY) < 1e-6) {
            return Math::applyEulerXYZRotation(Math::Vector3D(0.0, 1.0, 0.0), this->_rotation);
        }
        if (std::abs(localPoint.getY() - minY) < 1e-6) {
            return Math::applyEulerXYZRotation(Math::Vector3D(0.0, -1.0, 0.0), this->_rotation);
        }
    }

    return Math::applyEulerXYZRotation(Math::Vector3D(localPoint.getX(), 0.0, localPoint.getZ()), this->_rotation).normalized();
}

/**
 * @brief Translates this cylinder by the given offsets.
 *
 * @param offset Translation offset.
 */
void Cylinder::translate(const Math::Vector3D &offset)
{
    this->_center += offset;
}

/**
 * @brief Rotates this cylinder.
 *
 * @param rotation Rotation vector.
 */
void Cylinder::rotate(const Math::Vector3D &rotation)
{
    this->_rotation += rotation;
}

}
