/*
** EPITECH PROJECT, 2026
** ConeConfig.hpp
** File description:
** Header file for the ConeConfig
*/

#pragma once

#include "APrimitiveConfig.hpp"
#include "Math/Vector3D.hpp"
#include "Utils/Color.hpp"

namespace RayTracer {

class ConeConfig : public APrimitiveConfig
{
public:
    /**
     * @brief Constructs a cone primitive configuration.
     *
     * @param position Cone center position.
     * @param radius Cone base radius.
     * @param height Cone height.
     * @param limited Whether the cone is limited.
     * @param color Cone color.
     */
    ConeConfig(Math::Vector3D position, double radius, double height, bool limited, Color color)
        : _position(position), _radius(radius), _height(height), _limited(limited), _color(color) {}

    /**
     * @brief Destroys the cone configuration.
     */
    ~ConeConfig(void) override = default;

    /**
     * @brief Gets the primitive type.
     *
     * @return `PrimitiveType::CONE`.
     */
    PrimitiveType getType(void) const override
    {
        return PrimitiveType::CONE;
    };

public:
    /**
     * @brief Gets cone position.
     *
     * @return Cone position.
     */
    Math::Vector3D getPosition(void) const
    {
        return this->_position;
    }

    /**
     * @brief Gets cone base radius.
     *
     * @return Cone base radius.
     */
    double getRadius(void) const
    {
        return this->_radius;
    }

    /**
     * @brief Gets cone height.
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

    /**
     * @brief Gets cone color.
     *
     * @return Cone color.
     */
    Color getColor(void) const
    {
        return this->_color;
    }

private:
    /**
     * @brief Cone position.
     */
    Math::Vector3D _position;

    /**
     * @brief Cone base radius.
     */
    double _radius;

    /**
     * @brief Cone height.
     */
    double _height;

    /**
     * @brief Whether the cone is limited.
     */
    bool _limited;

    /**
     * @brief Cone color.
     */
    Color _color;
};

}
