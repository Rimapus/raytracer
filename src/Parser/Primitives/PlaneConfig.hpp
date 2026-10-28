/*
** EPITECH PROJECT, 2026
** PlaneConfig.hpp
** File description:
** Header file for the PlaneConfig
*/

#pragma once

#include "APrimitiveConfig.hpp"
#include "Utils/Color.hpp"

namespace RayTracer {

class PlaneConfig : public APrimitiveConfig
{
public:
    /**
     * @brief Supported plane axes.
     */
    enum class PlaneAxis {
        X,
        Y,
        Z,
    };

public:
    /**
     * @brief Constructs a plane primitive configuration.
     *
     * @param axis Plane axis.
     * @param position Plane position on selected axis.
     * @param color Plane color.
     */
    PlaneConfig(PlaneAxis axis, int position, Color color)
        : _axis(axis), _position(position), _color(color) {}

    /**
     * @brief Destroys the plane configuration.
     */
    ~PlaneConfig(void) override = default;

    /**
     * @brief Gets the primitive type.
     *
     * @return `PrimitiveType::PLANE`.
     */
    PrimitiveType getType(void) const override
    {
        return PrimitiveType::PLANE;
    };

public:
    /**
     * @brief Gets the plane axis.
     *
     * @return Plane axis.
     */
    PlaneAxis getAxis(void) const
    {
        return this->_axis;
    }

    /**
     * @brief Gets the plane position.
     *
     * @return Plane position on the selected axis.
     */
    int getPosition(void) const
    {
        return this->_position;
    }

    /**
     * @brief Gets the plane color.
     *
     * @return Plane color.
     */
    Color getColor(void) const
    {
        return this->_color;
    }

private:
    /**
     * @brief Plane axis.
     */
    PlaneAxis _axis;

    /**
     * @brief Plane position on selected axis.
     */
    int _position;

    /**
     * @brief Plane color.
     */
    Color _color;
};

}
