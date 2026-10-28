/*
** EPITECH PROJECT, 2026
** Torus.cpp
** File description:
** Main file for the Torus
*/

#include "Torus.hpp"

namespace RayTracer {

/**
 * @brief Evaluates the implicit torus equation at a given point.
 *
 * @param p Point in the torus local space.
 * @param R Major radius.
 * @param r Minor radius.
 *
 * @return Implicit function value.
 */
static double torusImplicit(double x, double y, double z, double R, double r)
{
    const double sumSq = x * x + y * y + z * z;
    return (sumSq + R * R - r * r) * (sumSq + R * R - r * r) - 4.0 * R * R * (x * x + z * z);
}

/**
 * @brief Checks whether a ray intersects the torus and returns the
 * distance to the intersection point.
 *
 * @param ray Ray to test.
 *
 * @return Distance to the hit point (t >= 0). Returns std::nullopt when there
 * is no intersection.
 */
std::optional<double> Torus::hits(const Ray &ray) const
{
    const Math::Vector3D rayDirection = Math::applyInverseEulerXYZRotation(ray.getDirection(), this->_rotation);
    const Math::Vector3D rayOrigin = Math::toLocalVector(ray.getOrigin(), this->_center, this->_rotation);

    const double R = this->_majorRadius;
    const double r = this->_minorRadius;

    const double ox = rayOrigin.getX();
    const double oy = rayOrigin.getY();
    const double oz = rayOrigin.getZ();
    const double dx = rayDirection.getX();
    const double dy = rayDirection.getY();
    const double dz = rayDirection.getZ();

    const double boundRadius = R + r;
    const double sphereA = dx * dx + dy * dy + dz * dz;
    const double sphereB = 2.0 * (ox * dx + oy * dy + oz * dz);
    const double sphereC = ox * ox + oy * oy + oz * oz - boundRadius * boundRadius;
    const double sphereDiscriminant = sphereB * sphereB - 4.0 * sphereA * sphereC;

    if (sphereDiscriminant < 0.0) {
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
    const double sampleStep = interval / 256.0 > 0.01 ? interval / 256.0 : 0.01;

    double prevF = torusImplicit(ox + dx * t, oy + dy * t, oz + dz * t, R, r);
    if (std::abs(prevF) < 1e-6) {
        return t;
    }

    while (t < maxT) {
        const double nextT = t + sampleStep;
        const double clampedNextT = nextT < maxT ? nextT : maxT;
        const double nextF = torusImplicit(ox + dx * clampedNextT,
                                           oy + dy * clampedNextT,
                                           oz + dz * clampedNextT,
                                           R,
                                           r);

        if (prevF == 0.0 || prevF * nextF <= 0.0) {
            double low = t;
            double high = clampedNextT;
            double lowF = prevF;
            double mid = low;
            for (int iter = 0; iter < 32; ++iter) {
                mid = 0.5 * (low + high);
                const double fm = torusImplicit(ox + dx * mid,
                                                oy + dy * mid,
                                                oz + dz * mid,
                                                R,
                                                r);
                if (std::abs(fm) < 1e-6) {
                    break;
                }
                if (lowF * fm <= 0.0) {
                    high = mid;
                } else {
                    low = mid;
                    lowF = fm;
                }
            }
            if (mid >= 0.0) {
                return mid;
            }
        }

        t = clampedNextT;
        prevF = nextF;
    }

    return std::nullopt;
}

/**
 * @brief Computes the surface normal at a point on the torus.
 *
 * @param point Point on the torus surface.
 *
 * @return Unit-length normal vector.
 */
Math::Vector3D Torus::getNormalAt(const Math::Point3D &point) const
{
    const Math::Vector3D localPoint = Math::toLocalVector(point, this->_center, this->_rotation);
    const double x = localPoint.getX();
    const double y = localPoint.getY();
    const double z = localPoint.getZ();
    const double R = this->_majorRadius;
    const double r = this->_minorRadius;

    const double sumSq = x * x + y * y + z * z;
    const double radialTerm = sumSq + R * R - r * r;
    const double sideFactor = 4.0 * (sumSq - R * R - r * r);
    const double gx = sideFactor * x;
    const double gy = 4.0 * radialTerm * y;
    const double gz = sideFactor * z;

    return Math::applyEulerXYZRotation(Math::Vector3D(gx, gy, gz).normalized(), this->_rotation);
}

/**
 * @brief Translate the torus.
 *
 * @param offset Translation offset.
 */
void Torus::translate(const Math::Vector3D &offset)
{
    this->_center += offset;
}

/**
 * @brief Rotate the torus.
 *
 * @param rotation Rotation vector.
 */
void Torus::rotate(const Math::Vector3D &rotation)
{
    this->_rotation += rotation;
}

}
