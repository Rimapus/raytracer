/*
** EPITECH PROJECT, 2026
** Cone.cpp
** File description:
** Main file for the Cone
*/

#include "Cone.hpp"

namespace RayTracer {

std::optional<double> Cone::hits(const Ray &ray) const
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

    const double k = this->_radius / this->_height;
    const double kk = k * k;
    const double heightOffset = maxY - rayOrigin.getY();

    const double a = dirX * dirX + dirZ * dirZ - kk * dirY * dirY;
    if (std::abs(a) >= 1e-12) {
        const double halfB = originX * dirX + originZ * dirZ + kk * heightOffset * dirY;
        const double c = originX * originX + originZ * originZ - kk * heightOffset * heightOffset;
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

                const double hitY = rayOrigin.getY() + dirY * t;
                if (hitY > maxY) {
                    return;
                }
                if (this->_limited && hitY < minY) {
                    return;
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
        const double baseT = (minY - rayOrigin.getY()) / dirY;
        const double baseX = originX + dirX * baseT;
        const double baseZ = originZ + dirZ * baseT;
        if (baseT >= 0.0 && baseX * baseX + baseZ * baseZ <= this->_radius * this->_radius) {
            if (!closestHit || baseT < *closestHit) {
                closestHit = baseT;
            }
        }
    }

    return closestHit;
}

Math::Vector3D Cone::getNormalAt(const Math::Point3D &point) const
{
    const double halfHeight = this->_height / 2.0;
    const Math::Vector3D localPoint = Math::toLocalVector(point, this->_center, this->_rotation);
    const double minY = -halfHeight;
    const double maxY = halfHeight;

    if (this->_limited && std::abs(localPoint.getY() - minY) < 1e-6) {
        return Math::applyEulerXYZRotation(Math::Vector3D(0.0, -1.0, 0.0), this->_rotation);
    }

    const double k = this->_radius / this->_height;
    const double gx = 2.0 * localPoint.getX();
    const double gy = 2.0 * k * k * (maxY - localPoint.getY());
    const double gz = 2.0 * localPoint.getZ();

    return Math::applyEulerXYZRotation(Math::Vector3D(gx, gy, gz).normalized(), this->_rotation);
}

void Cone::translate(const Math::Vector3D &offset)
{
    this->_center += offset;
}

void Cone::rotate(const Math::Vector3D &rotation)
{
    this->_rotation += rotation;
}

}
