/*
** EPITECH PROJECT, 2026
** Torus.hpp
** File description:
** Header file for the Torus
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Math/Transform.hpp"
#include "Math/Vector3D.hpp"
#include "Primitives/IPrimitives.hpp"
#include "Utils/Ray.hpp"
#include <cmath>
#include <optional>

namespace RayTracer {

class Torus : public IPrimitive
{
public:
    /**
     * @brief Constructs a torus from center, major radius and minor radius.
     *
     * @param center Torus center.
     * @param majorRadius Major radius (distance from center to tube center).
     * @param minorRadius Minor radius (tube radius).
     */
    Torus(const Math::Point3D &center, double majorRadius, double minorRadius)
        : _center(center), _majorRadius(majorRadius), _minorRadius(minorRadius) {}

    /**
     * @brief Destroys the torus.
     */
    ~Torus(void) override = default;

public:
    /**
     * @brief Gets the torus center.
     *
     * @return Torus center.
     */
    Math::Point3D getCenter(void) const
    {
        return this->_center;
    }

    /**
     * @brief Gets the torus major radius.
     *
     * @return Torus major radius.
     */
    double getMajorRadius(void) const
    {
        return this->_majorRadius;
    }

    /**
     * @brief Gets the torus minor radius.
     *
     * @return Torus minor radius.
     */
    double getMinorRadius(void) const
    {
        return this->_minorRadius;
    }

public:
    /**
     * @brief Checks whether a ray intersects the torus and returns the
     * distance to the intersection point.
     *
     * @param ray Ray to test.
     *
     * @return Distance to the hit point (t >= 0). Returns std::nullopt when there
     * is no intersection.
     */
    std::optional<double> hits(const Ray &ray) const override;

    /**
     * @brief Computes the surface normal at a point on the torus.
     *
     * @param point Point on the torus surface.
     *
     * @return Unit-length normal vector.
     */
    Math::Vector3D getNormalAt(const Math::Point3D &point) const override;

    /**
     * @brief Translate the torus.
     *
     * @param offset Translation offset.
     */
    void translate(const Math::Vector3D &offset) override;

    /**
     * @brief Rotate the torus.
     *
     * @param rotation Rotation vector.
     */
    void rotate(const Math::Vector3D &rotation) override;

private:
    /**
     * @brief Center point of the torus.
     */
    Math::Point3D _center;

    /**
     * @brief Major radius of the torus.
     */
    double _majorRadius;

    /**
     * @brief Minor radius of the torus.
     */
    double _minorRadius;

    /**
     * @brief Rotation applied to the torus.
     */
    Math::Vector3D _rotation = Math::Vector3D(0.0, 0.0, 0.0);
};

}
