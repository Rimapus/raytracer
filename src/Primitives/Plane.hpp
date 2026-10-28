/*
** EPITECH PROJECT, 2026
** Plane.hpp
** File description:
** Header file for the Plane
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Parser/Primitives/PlaneConfig.hpp"
#include "Primitives/IPrimitives.hpp"
#include "Utils/Ray.hpp"
#include <cmath>
#include <optional>

namespace RayTracer {

class Plane : public IPrimitive
{
public:
    /**
     * @brief Constructs a plane from a point and a normal axis.
     *
     * @param position Point on the plane.
     * @param axis Plane normal axis.
     */
    Plane(int position, PlaneConfig::PlaneAxis axis)
        : _position(position), _axis(axis) {}

    /**
     * @brief Destroys the plane.
     */
    ~Plane(void) override = default;

public:
    /**
     * @brief Gets the plane pos.
     *
     * @return Plane pos.
     */
    int getPosition(void) const
    {
        return this->_position;
    }

    /**
     * @brief Gets the plane axis.
     *
     * @return Plane axis.
     */
    PlaneConfig::PlaneAxis getAxis(void) const
    {
        return this->_axis;
    }

    /**
     * @brief Sets the plane pos.
     *
     * @param value New plane pos.
     */
    void setPosition(int value)
    {
        this->_position = value;
    }

    /**
     * @brief Sets the plane axis.
     *
     * @param value New plane axis.
     */
    void setAxis(PlaneConfig::PlaneAxis value)
    {
        this->_axis = value;
    }

public:
    /**
     * @brief Checks whether a ray intersects the plane and returns the
     * distance to the intersection point.
     *
     * @param ray Ray to test.
     *
     * @return Distance to the hit point (t >= 0). Returns std::nullopt when there
     * is no intersection.
     */
    std::optional<double> hits(const Ray &ray) const override;

    /**
     * @brief Computes the surface normal at a point on the plane.
     *
     * @param point Point on the plane surface.
     *
     * @return Unit-length normal vector.
     */
    Math::Vector3D getNormalAt(const Math::Point3D &point) const override;

    /**
     * @brief Translate the plane.
     *
     * @param offset Translation offset.
     */
    void translate(const Math::Vector3D &offset) override;

    /**
     * @brief Rotate the plane.
     *
     * @param rotation Rotation vector.
     */
    void rotate(const Math::Vector3D &rotation) override;

private:
    /**
     * @brief Position point of the plane.
     */
    int _position;

    /**
     * @brief Axis of the plane.
     */
    PlaneConfig::PlaneAxis _axis;
};

}
