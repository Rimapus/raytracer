/*
** EPITECH PROJECT, 2026
** TanglecubeConfig.hpp
** File description:
** Header file for the TanglecubeConfig
*/

#pragma once

#include "APrimitiveConfig.hpp"
#include "Math/Vector3D.hpp"
#include "Utils/Color.hpp"

namespace RayTracer {

class TanglecubeConfig : public APrimitiveConfig
{
public:
    /**
     * @brief Constructs a tanglecube primitive configuration.
     *
     * @param position Tanglecube center.
     * @param scale Tanglecube scale.
     * @param color Tanglecube color.
     */
    TanglecubeConfig(Math::Vector3D position, double scale, Color color)
        : _position(position), _scale(scale), _color(color) {}

    /**
     * @brief Destroys the tanglecube configuration.
     */
    ~TanglecubeConfig(void) override = default;

    /**
     * @brief Gets the primitive type.
     *
     * @return `PrimitiveType::TANGLECUBE`.
     */
    PrimitiveType getType(void) const override
    {
        return PrimitiveType::TANGLECUBE;
    };

public:
    /**
     * @brief Gets tanglecube center.
     *
     * @return Tanglecube center.
     */
    Math::Vector3D getPosition(void) const
    {
        return this->_position;
    }

    /**
     * @brief Gets tanglecube scale.
     *
     * @return Tanglecube scale.
     */
    double getScale(void) const
    {
        return this->_scale;
    }

    /**
     * @brief Gets tanglecube color.
     *
     * @return Tanglecube color.
     */
    Color getColor(void) const
    {
        return this->_color;
    }

private:
    /**
     * @brief Tanglecube center.
     */
    Math::Vector3D _position;

    /**
     * @brief Tanglecube scale.
     */
    double _scale;

    /**
     * @brief Tanglecube color.
     */
    Color _color;
};

}
