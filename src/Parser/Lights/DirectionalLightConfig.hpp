/*
** EPITECH PROJECT, 2026
** DirectionalLightConfig.hpp
** File description:
** Header file for the DirectionalLightConfig
*/

#pragma once

#include "ILightConfig.hpp"
#include "Math/Vector3D.hpp"
#include "Utils/Color.hpp"

namespace RayTracer {

class DirectionalLightConfig : public ILightConfig
{
public:
    /**
     * @brief Constructs a directional light configuration.
     *
     * @param direction Directional light orientation.
     * @param color Directional light color.
     */
    DirectionalLightConfig(Math::Vector3D direction, Color color = Color(255, 255, 255))
        : _direction(direction), _color(color) {}

    /**
     * @brief Destroys the directional light configuration.
     */
    ~DirectionalLightConfig(void) override = default;

    /**
     * @brief Gets the light type.
     *
     * @return `LightType::DIRECTIONAL`.
     */
    LightType getType(void) const override
    {
        return LightType::DIRECTIONAL;
    };

public:
    /**
     * @brief Gets the directional light direction.
     *
     * @return Directional light direction.
     */
    Math::Vector3D getDirection(void) const
    {
        return this->_direction;
    }

    /**
     * @brief Gets the directional light color.
     *
     * @return Directional light color.
     */
    Color getColor(void) const
    {
        return this->_color;
    }

private:
    /**
     * @brief Directional light orientation.
     */
    Math::Vector3D _direction;

    /**
     * @brief Directional light color.
     */
    Color _color;
};

}
