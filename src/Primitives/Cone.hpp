/*
** EPITECH PROJECT, 2026
** Cone.hpp
** File description:
** Header file for the Cone
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

class Cone : public IPrimitive
{
public:
    /**
     * @brief Constructs a cone from center, base radius and height.
     *
     * @param center Cone center.
     * @param radius Cone base radius.
     * @param height Cone height.
     * @param limited Whether the cone is limited.
     */
    Cone(const Math::Point3D &center, double radius, double height, bool limited)
        : _center(center), _radius(radius), _height(height), _limited(limited) {}

    /**
     * @brief Destroys the cone.
     */
    ~Cone(void) override = default;

public:
    /**
     * @brief Gets the cone center.
     *
     * @return Cone center.
     */
    Math::Point3D getCenter(void) const
    {
        return this->_center;
    }

    /**
     * @brief Gets the cone base radius.
     *
     * @return Cone base radius.
     */
    double getRadius(void) const
    {
        return this->_radius;
    }

    /**
     * @brief Gets the cone height.
     *
     * @return Cone height.
     */
    double getHeight(void) const
    {
        return this->_height;
    }

    /**
     * @brief Gets whether the cone is limited.
     *
     * @return True if the cone is limited.
     */
    bool isLimited(void) const
    {
        return this->_limited;
    }

public:
    /**
     * @brief Checks whether a ray intersects the cone and returns the
     * distance to the intersection point.
     *
     * @param ray Ray to test.
     *
     * @return Distance to the hit point (t >= 0). Returns std::nullopt when there
     * is no intersection.
     */
    std::optional<double> hits(const Ray &ray) const override;

    /**
     * @brief Computes the surface normal at a point on the cone.
     *
     * @param point Point on the cone surface.
     *
     * @return Unit-length normal vector.
     */
    Math::Vector3D getNormalAt(const Math::Point3D &point) const override;

    /**
     * @brief Translate the cone.
     *
     * @param offset Translation offset.
     */
    void translate(const Math::Vector3D &offset) override;

    /**
     * @brief Rotate the cone.
     *
     * @param rotation Rotation vector.
     */
    void rotate(const Math::Vector3D &rotation) override;

private:
    /**
     * @brief Center point of the cone.
     */
    Math::Point3D _center;

    /**
     * @brief Base radius of the cone.
     */
    double _radius;

    /**
     * @brief Height of the cone.
     */
    double _height;

    /**
     * @brief Whether the cone is limited.
     */
    bool _limited;

    /**
     * @brief Rotation applied to the cone.
     */
    Math::Vector3D _rotation = Math::Vector3D(0.0, 0.0, 0.0);
};

}
