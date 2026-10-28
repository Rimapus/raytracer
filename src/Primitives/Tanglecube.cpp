/*
** EPITECH PROJECT, 2026
** Tanglecube.cpp
** File description:
** Main file for the Tanglecube
*/

#include "Tanglecube.hpp"

namespace RayTracer {

double Tanglecube::tanglecubeImplicit(double x, double y, double z)
{
    return x * x * x * x - 5.0 * x * x +
           y * y * y * y - 5.0 * y * y +
           z * z * z * z - 5.0 * z * z +
           11.8;
}

std::optional<double> Tanglecube::hits(const Ray &ray) const
{
    const Math::Vector3D rayDirection = Math::applyInverseEulerXYZRotation(ray.getDirection(), this->_rotation);
    const Math::Vector3D localOrigin = Math::toLocalVector(ray.getOrigin(), this->_center, this->_rotation) / this->_scale;
    const Math::Vector3D localDirection = rayDirection / this->_scale;
    const double ox = localOrigin.getX();
    const double oy = localOrigin.getY();
    const double oz = localOrigin.getZ();
    const double dx = localDirection.getX();
    const double dy = localDirection.getY();
    const double dz = localDirection.getZ();
    const double boundRadius = 3.6;
    const double sphereA = dx * dx + dy * dy + dz * dz;
    const double sphereB = 2.0 * (ox * dx + oy * dy + oz * dz);
    const double sphereC = ox * ox + oy * oy + oz * oz - boundRadius * boundRadius;
    const double sphereDiscriminant = sphereB * sphereB - 4.0 * sphereA * sphereC;

    if (sphereDiscriminant < 0.0 || std::abs(sphereA) < 1e-12) {
        return std::nullopt;
    }

    const double sphereSqrt = std::sqrt(sphereDiscriminant);
    double sphereT0 = (-sphereB - sphereSqrt) / (2.0 * sphereA);
    double sphereT1 = (-sphereB + sphereSqrt) / (2.0 * sphereA);
    if (sphereT0 > sphereT1) {
        const double tmp = sphereT0;
        sphereT0 = sphereT1;
        sphereT1 = tmp;
    }

    double t = sphereT0 > 0.0 ? sphereT0 : 0.0;
    const double maxT = sphereT1;
    if (t > maxT) {
        return std::nullopt;
    }

    const double interval = maxT - t;
    const double sampleStep = interval / 512.0 > 0.005 ? interval / 512.0 : 0.005;
    double prevF = Tanglecube::tanglecubeImplicit(ox + dx * t, oy + dy * t, oz + dz * t);

    if (std::abs(prevF) < 1e-6) {
        return t;
    }

    while (t < maxT) {
        const double nextT = t + sampleStep;
        const double clampedNextT = nextT < maxT ? nextT : maxT;
        const double nextF = Tanglecube::tanglecubeImplicit(ox + dx * clampedNextT,
                                                            oy + dy * clampedNextT,
                                                            oz + dz * clampedNextT);

        if (prevF == 0.0 || prevF * nextF <= 0.0) {
            double low = t;
            double high = clampedNextT;
            double lowF = prevF;
            double mid = low;

            for (int iter = 0; iter < 32; ++iter) {
                mid = 0.5 * (low + high);
                const double midF = Tanglecube::tanglecubeImplicit(ox + dx * mid,
                                                                   oy + dy * mid,
                                                                   oz + dz * mid);

                if (std::abs(midF) < 1e-6) {
                    break;
                }
                if (lowF * midF <= 0.0) {
                    high = mid;
                } else {
                    low = mid;
                    lowF = midF;
                }
            }
            return mid >= 0.0 ? std::optional<double>(mid) : std::nullopt;
        }

        t = clampedNextT;
        prevF = nextF;
    }
    return std::nullopt;
}

Math::Vector3D Tanglecube::getNormalAt(const Math::Point3D &point) const
{
    const Math::Vector3D localPoint = Math::toLocalVector(point, this->_center, this->_rotation) / this->_scale;
    const double x = localPoint.getX();
    const double y = localPoint.getY();
    const double z = localPoint.getZ();
    const Math::Vector3D localNormal(
        4.0 * x * x * x - 10.0 * x,
        4.0 * y * y * y - 10.0 * y,
        4.0 * z * z * z - 10.0 * z);

    return Math::applyEulerXYZRotation(localNormal.normalized(), this->_rotation);
}

void Tanglecube::translate(const Math::Vector3D &offset)
{
    this->_center += offset;
}

void Tanglecube::rotate(const Math::Vector3D &rotation)
{
    this->_rotation += rotation;
}

}
