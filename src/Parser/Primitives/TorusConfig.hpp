/*
** EPITECH PROJECT, 2026
** TorusConfig.hpp
** File description:
** Header file for the TorusConfig
*/

#pragma once

#include "APrimitiveConfig.hpp"
#include "Math/Vector3D.hpp"
#include "Utils/Color.hpp"

namespace RayTracer {

class TorusConfig : public APrimitiveConfig
{
public:
    /**
     * @brief Constructs a torus primitive configuration.
     *
     * @param position Torus center position.
     * @param majorRadius Major radius (distance to tube center).
     * @param minorRadius Minor radius (tube radius).
     * @param color Torus color.
     */
    TorusConfig(Math::Vector3D position, double majorRadius, double minorRadius, Color color)
        : _position(position), _majorRadius(majorRadius), _minorRadius(minorRadius), _color(color) {}

    /**
     * @brief Destroys the torus configuration.
     */
    ~TorusConfig(void) override = default;

    /**
     * @brief Gets the primitive type.
     *
     * @return `PrimitiveType::TORUS`.
     */
    PrimitiveType getType(void) const override
    {
        return PrimitiveType::TORUS;
    };

public:
    /**
     * @brief Gets torus position.
     *
     * @return Torus position.
     */
    Math::Vector3D getPosition(void) const
    {
        return this->_position;
    }

    /**
     * @brief Gets torus major radius.
     *
     * @return Torus major radius.
     */
    double getMajorRadius(void) const
    {
        return this->_majorRadius;
    }

    /**
     * @brief Gets torus minor radius.
     *
     * @return Torus minor radius.
     */
    double getMinorRadius(void) const
    {
        return this->_minorRadius;
    }

    /**
     * @brief Gets torus color.
     *
     * @return Torus color.
     */
    Color getColor(void) const
    {
        return this->_color;
    }

private:
    /**
     * @brief Torus position.
     */
    Math::Vector3D _position;

    /**
     * @brief Torus major radius.
     */
    double _majorRadius;

    /**
     * @brief Torus minor radius.
     */
    double _minorRadius;

    /**
     * @brief Torus color.
     */
    Color _color;
};

}
