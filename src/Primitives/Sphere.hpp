/*
** EPITECH PROJECT, 2026
** Sphere.hpp
** File description:
** Header file for the Sphere
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Primitives/IPrimitives.hpp"
#include "Utils/Ray.hpp"
#include <algorithm>
#include <cmath>
#include <optional>

namespace RayTracer {

class Sphere : public IPrimitive
{
public:
    /**
     * @brief Constructs a sphere from center and radius.
     *
     * @param center Sphere center.
     * @param radius Sphere radius.
     */
    Sphere(const Math::Point3D &center, double radius)
        : _center(center), _radius(radius) {}

    /**
     * @brief Destroys the sphere.
     */
    ~Sphere(void) override = default;

public:
    /**
     * @brief Gets the sphere center.
     *
     * @return Sphere center.
     */
    Math::Point3D getCenter(void) const
    {
        return this->_center;
    }

    /**
     * @brief Gets the sphere radius.
     *
     * @return Sphere radius.
     */
    double getRadius(void) const
    {
        return this->_radius;
    }

    /**
     * @brief Sets the sphere center.
     *
     * @param value New sphere center.
     */
    void setCenter(const Math::Point3D &value)
    {
        this->_center = value;
    }

    /**
     * @brief Sets the sphere radius.
     *
     * @param value New sphere radius.
     */
    void setDirection(double value)
    {
        this->_radius = value;
    }

public:
    /**
     * @brief Checks whether a ray intersects the sphere and returns the
     * distance to the intersection point.
     *
     * @param ray Ray to test.
     *
     * @return Distance to the hit point (t >= 0). Returns std::nullopt when there
     * is no intersection.
     */
    std::optional<double> hits(const Ray &ray) const override;

    /**
     * @brief Computes the surface normal at a point on the sphere.
     *
     * @param point Point on the sphere surface.
     *
     * @return Unit-length normal vector.
     */
    Math::Vector3D getNormalAt(const Math::Point3D &point) const override;

    /**
     * @brief Translate the sphere.
     *
     * @param offset Translation offset.
     */
    void translate(const Math::Vector3D &offset) override;

    /**
     * @brief Rotate the sphere.
     *
     * @param rotation Rotation vector.
     */
    void rotate(const Math::Vector3D &rotation) override;

private:
    /**
     * @brief Center point of the sphere.
     */
    Math::Point3D _center;

    /**
     * @brief Radius of the sphere.
     */
    double _radius;
};

}
