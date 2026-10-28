/*
** EPITECH PROJECT, 2026
** Plane.cpp
** File description:
** Main file for the Plane
*/

#include "Plane.hpp"

namespace RayTracer {

/**
 * @brief Checks whether a ray intersects this plane.
 *
 * @param ray Ray to test.
 *
 * @return True if the ray intersects this plane, false otherwise.
 */
std::optional<double> Plane::hits(const Ray &ray) const
{
    const Math::Vector3D rayDirection = ray.getDirection();
    const Math::Point3D rayOrigin = ray.getOrigin();
    double originCoord = 0.0;
    double dirCoord = 0.0;

    switch (this->_axis) {
    case PlaneConfig::PlaneAxis::X:
        originCoord = rayOrigin.getX();
        dirCoord = rayDirection.getX();
        break;
    case PlaneConfig::PlaneAxis::Y:
        originCoord = rayOrigin.getY();
        dirCoord = rayDirection.getY();
        break;
    case PlaneConfig::PlaneAxis::Z:
        originCoord = rayOrigin.getZ();
        dirCoord = rayDirection.getZ();
        break;
    }
    if (std::abs(dirCoord) < 1e-6) {
        return std::nullopt;
    }

    const double t = (static_cast<double>(this->_position) - originCoord) / dirCoord;
    return (t >= 0.0) ? std::optional<double>(t) : std::nullopt;
}

/**
 * @brief Computes the surface normal at a point on the plane.
 *
 * @param point Point on the plane surface.
 *
 * @return Unit-length normal vector.
 */
Math::Vector3D Plane::getNormalAt(const Math::Point3D &) const
{
    switch (this->_axis) {
    case PlaneConfig::PlaneAxis::X:
        return Math::Vector3D(-1.0, 0.0, 0.0);
    case PlaneConfig::PlaneAxis::Y:
        return Math::Vector3D(0.0, 1.0, 0.0);
    case PlaneConfig::PlaneAxis::Z:
        return Math::Vector3D(0.0, 0.0, -1.0);
    }
    return Math::Vector3D(0.0, 0.0, -1.0);
}

/**
 * @brief Translates this plane by the given offsets.
 *
 * @param offset Translation offset.
 */
void Plane::translate(const Math::Vector3D &offset)
{
    switch (this->_axis) {
    case PlaneConfig::PlaneAxis::X:
        this->_position += static_cast<int>(std::lround(offset.getX()));
        break;
    case PlaneConfig::PlaneAxis::Y:
        this->_position += static_cast<int>(std::lround(offset.getY()));
        break;
    case PlaneConfig::PlaneAxis::Z:
        this->_position += static_cast<int>(std::lround(offset.getZ()));
        break;
    }
}

/**
 * @brief Rotates this plane.
 *
 * @param rotation Rotation vector.
 */
void Plane::rotate(const Math::Vector3D &)
{
}

}
