/*
** EPITECH PROJECT, 2026
** Rectangle3D.hpp
** File description:
** Header file for the Rectangle3D
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include <cmath>

namespace RayTracer {

class Rectangle3D
{
public:
    /**
     * @brief Constructs a default rectangle.
     */
    Rectangle3D(void) = default;

    /**
     * @brief Constructs a rectangle with origin coordinates.
     *
     * @param x Origin X coordinate.
     * @param y Origin Y coordinate.
     * @param z Origin Z coordinate.
     */
    Rectangle3D(double x, double y, double z)
        : _origin(x, y, z) {}

    /**
     * @brief Constructs a rectangle from an origin and two side vectors.
     *
     * @param origin Rectangle origin.
     * @param bottom_side Bottom side direction and length.
     * @param left_side Left side direction and length.
     */
    Rectangle3D(const Math::Point3D &origin, const Math::Vector3D &bottom_side, const Math::Vector3D &left_side)
        : _origin(origin), _bottomSide(bottom_side), _leftSide(left_side) {}

    /**
     * @brief Destroys the rectangle.
     */
    ~Rectangle3D(void) = default;

public:
    /**
     * @brief Gets the rectangle origin.
     *
     * @return Rectangle origin point.
     */
    Math::Point3D getOrigin(void) const
    {
        return this->_origin;
    }

    /**
     * @brief Gets the bottom side vector.
     *
     * @return Bottom side vector.
     */
    Math::Vector3D getBottomSide(void) const
    {
        return this->_bottomSide;
    }

    /**
     * @brief Gets the left side vector.
     *
     * @return Left side vector.
     */
    Math::Vector3D getLeftSide(void) const
    {
        return this->_leftSide;
    }

    /**
     * @brief Sets the rectangle origin.
     *
     * @param value New origin point.
     */
    void setOrigin(const Math::Point3D &value)
    {
        this->_origin = value;
    }

    /**
     * @brief Sets the bottom side vector.
     *
     * @param value New bottom side vector.
     */
    void setBottomSide(const Math::Vector3D &value)
    {
        this->_bottomSide = value;
    }

    /**
     * @brief Sets the left side vector.
     *
     * @param value New left side vector.
     */
    void setLeftSide(const Math::Vector3D &value)
    {
        this->_leftSide = value;
    }

public:
    /**
     * @brief Computes a point on the rectangle from normalized coordinates.
     *
     * @param u Horizontal normalized coordinate along bottom side.
     * @param v Vertical normalized coordinate along left side.
     *
     * @return Point on the rectangle plane.
     */
    Math::Point3D pointAt(double u, double v) const;

private:
    /**
     * @brief Rectangle origin point.
     */
    Math::Point3D _origin;

    /**
     * @brief Bottom side vector.
     */
    Math::Vector3D _bottomSide;

    /**
     * @brief Left side vector.
     */
    Math::Vector3D _leftSide;
};

}
