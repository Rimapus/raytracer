/*
** EPITECH PROJECT, 2026
** SphereConfig.hpp
** File description:
** Header file for the SphereConfig
*/

#pragma once

#include "APrimitiveConfig.hpp"
#include "Math/Vector3D.hpp"
#include "Utils/Color.hpp"

namespace RayTracer {

class SphereConfig : public APrimitiveConfig
{
public:
    /**
     * @brief Constructs a sphere primitive configuration.
     *
     * @param position Sphere center position.
     * @param radius Sphere radius.
     * @param color Sphere color.
     */
    SphereConfig(Math::Vector3D position, double radius, Color color)
        : _position(position), _radius(radius), _color(color) {}

    /**
     * @brief Destroys the sphere configuration.
     */
    ~SphereConfig(void) override = default;

    /**
     * @brief Gets the primitive type.
     *
     * @return `PrimitiveType::SPHERE`.
     */
    PrimitiveType getType(void) const override
    {
        return PrimitiveType::SPHERE;
    };

public:
    /**
     * @brief Gets sphere position.
     *
     * @return Sphere position.
     */
    Math::Vector3D getPosition(void) const
    {
        return this->_position;
    }

    /**
     * @brief Gets sphere radius.
     *
     * @return Sphere radius.
     */
    double getRadius(void) const
    {
        return this->_radius;
    }

    /**
     * @brief Gets sphere color.
     *
     * @return Sphere color.
     */
    Color getColor(void) const
    {
        return this->_color;
    }

private:
    /**
     * @brief Sphere position.
     */
    Math::Vector3D _position;

    /**
     * @brief Sphere radius.
     */
    double _radius;

    /**
     * @brief Sphere color.
     */
    Color _color;
};

}
