/*
** EPITECH PROJECT, 2026
** PointLightConfig.hpp
** File description:
** Header file for the PointLightConfig
*/

#pragma once

#include "ILightConfig.hpp"
#include "Math/Vector3D.hpp"
#include "Utils/Color.hpp"

namespace RayTracer {

class PointLightConfig : public ILightConfig
{
public:
    /**
     * @brief Constructs a point light configuration.
     *
     * @param position Point light position.
     * @param color Point light color.
     */
    PointLightConfig(Math::Vector3D position, Color color = Color(255, 255, 255))
        : _position(position), _color(color) {}

    /**
     * @brief Destroys the point light configuration.
     */
    ~PointLightConfig(void) override = default;

    /**
     * @brief Gets the light type.
     *
     * @return `LightType::POINT`.
     */
    LightType getType(void) const override
    {
        return LightType::POINT;
    };

public:
    /**
     * @brief Gets the point light position.
     *
     * @return Point light position.
     */
    Math::Vector3D getPosition(void) const
    {
        return this->_position;
    }

    /**
     * @brief Gets the point light color.
     *
     * @return Point light color.
     */
    Color getColor(void) const
    {
        return this->_color;
    }

private:
    /**
     * @brief Point light position.
     */
    Math::Vector3D _position;

    /**
     * @brief Point light color.
     */
    Color _color;
};

}
