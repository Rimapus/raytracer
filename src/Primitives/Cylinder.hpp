/*
** EPITECH PROJECT, 2026
** Cylinder.hpp
** File description:
** Header file for the Cylinder
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

class Cylinder : public IPrimitive
{
public:
    /**
     * @brief Constructs a cylinder from center, radius and height.
     *
     * @param center Cylinder center.
     * @param radius Cylinder radius.
     * @param height Cylinder height.
     * @param limited Whether the cylinder is limited.
     */
    Cylinder(const Math::Point3D &center, double radius, double height, bool limited)
        : _center(center), _radius(radius), _height(height), _limited(limited) {}

    /**
     * @brief Destroys the cylinder.
     */
    ~Cylinder(void) override = default;

public:
    /**
     * @brief Gets the cylinder center.
     *
     * @return Cylinder center.
     */
    Math::Point3D getCenter(void) const
    {
        return this->_center;
    }

    /**
     * @brief Gets the cylinder radius.
     *
     * @return Cylinder radius.
     */
    double getRadius(void) const
    {
        return this->_radius;
    }

    /**
     * @brief Gets the cylinder height.
     *
     * @return Cylinder height.
     */
    double getHeight(void) const
    {
        return this->_height;
    }

    /**
     * @brief Gets whether the cylinder is limited.
     *
     * @return True if the cylinder is limited.
     */
    bool isLimited(void) const
    {
        return this->_limited;
    }

public:
    /**
     * @brief Checks whether a ray intersects the cylinder and returns the
     * distance to the intersection point.
     *
     * @param ray Ray to test.
     *
     * @return Distance to the hit point (t >= 0). Returns std::nullopt when there
     * is no intersection.
     */
    std::optional<double> hits(const Ray &ray) const override;

    /**
     * @brief Computes the surface normal at a point on the cylinder.
     *
     * @param point Point on the cylinder surface.
     *
     * @return Unit-length normal vector.
     */
    Math::Vector3D getNormalAt(const Math::Point3D &point) const override;

    /**
     * @brief Translate the cylinder.
     *
     * @param offset Translation offset.
     */
    void translate(const Math::Vector3D &offset) override;

    /**
     * @brief Rotate the cylinder.
     *
     * @param rotation Rotation vector.
     */
    void rotate(const Math::Vector3D &rotation) override;

private:
    /**
     * @brief Center point of the cylinder.
     */
    Math::Point3D _center;

    /**
     * @brief Radius of the cylinder.
     */
    double _radius;

    /**
     * @brief Height of the cylinder.
     */
    double _height;

    /**
     * @brief Whether the cylinder is limited.
     */
    bool _limited;

    /**
     * @brief Rotation applied to the cylinder.
     */
    Math::Vector3D _rotation = Math::Vector3D(0.0, 0.0, 0.0);
};

}
