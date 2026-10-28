/*
** EPITECH PROJECT, 2026
** CylinderConfig.hpp
** File description:
** Header file for the CylinderConfig
*/

#pragma once

#include "APrimitiveConfig.hpp"
#include "Math/Vector3D.hpp"
#include "Utils/Color.hpp"

namespace RayTracer {

class CylinderConfig : public APrimitiveConfig
{
public:
    /**
     * @brief Constructs a cylinder primitive configuration.
     *
     * @param position Cylinder center position.
     * @param radius Cylinder radius.
     * @param height Cylinder height.
     * @param limited Whether the cylinder is limited.
     * @param color Cylinder color.
     */
    CylinderConfig(Math::Vector3D position, double radius, double height, bool limited, Color color)
        : _position(position), _radius(radius), _height(height), _limited(limited), _color(color) {}

    /**
     * @brief Destroys the cylinder configuration.
     */
    ~CylinderConfig(void) override = default;

    /**
     * @brief Gets the primitive type.
     *
     * @return `PrimitiveType::CYLINDER`.
     */
    PrimitiveType getType(void) const override
    {
        return PrimitiveType::CYLINDER;
    };

public:
    /**
     * @brief Gets cylinder position.
     *
     * @return Cylinder position.
     */
    Math::Vector3D getPosition(void) const
    {
        return this->_position;
    }

    /**
     * @brief Gets cylinder radius.
     *
     * @return Cylinder radius.
     */
    double getRadius(void) const
    {
        return this->_radius;
    }

    /**
     * @brief Gets cylinder height.
     *
     * @return Cylinder height.
     */
    double getHeight(void) const
    {
        return this->_height;
    }

    /**
     * @brief Gets whether the cylinder is limited.
     *
     * @return True if the cylinder is limited.
     */
    bool isLimited(void) const
    {
        return this->_limited;
    }

    /**
     * @brief Gets cylinder color.
     *
     * @return Cylinder color.
     */
    Color getColor(void) const
    {
        return this->_color;
    }

private:
    /**
     * @brief Cylinder position.
     */
    Math::Vector3D _position;

    /**
     * @brief Cylinder radius.
     */
    double _radius;

    /**
     * @brief Cylinder height.
     */
    double _height;

    /**
     * @brief Whether the cylinder is limited.
     */
    bool _limited;

    /**
     * @brief Cylinder color.
     */
    Color _color;
};

}
