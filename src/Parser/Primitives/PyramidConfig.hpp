/*
** EPITECH PROJECT, 2026
** PyramidConfig.hpp
** File description:
** Header file for the PyramidConfig
*/

#pragma once

#include "APrimitiveConfig.hpp"
#include "Math/Vector3D.hpp"
#include "Utils/Color.hpp"

namespace RayTracer {

class PyramidConfig : public APrimitiveConfig
{
public:
    /**
     * @brief Constructs a pyramid primitive configuration.
     *
     * @param position Pyramid base center.
     * @param size Pyramid square base side length.
     * @param height Pyramid height.
     * @param color Pyramid color.
     */
    PyramidConfig(Math::Vector3D position, double size, double height, Color color)
        : _position(position), _size(size), _height(height), _color(color) {}

    /**
     * @brief Destroys the pyramid configuration.
     */
    ~PyramidConfig(void) override = default;

    /**
     * @brief Gets the primitive type.
     *
     * @return `PrimitiveType::PYRAMID`.
     */
    PrimitiveType getType(void) const override
    {
        return PrimitiveType::PYRAMID;
    };

public:
    /**
     * @brief Gets pyramid base center.
     *
     * @return Pyramid base center.
     */
    Math::Vector3D getPosition(void) const
    {
        return this->_position;
    }

    /**
     * @brief Gets pyramid square base size.
     *
     * @return Base side length.
     */
    double getSize(void) const
    {
        return this->_size;
    }

    /**
     * @brief Gets pyramid height.
     *
     * @return Pyramid height.
     */
    double getHeight(void) const
    {
        return this->_height;
    }

    /**
     * @brief Gets pyramid color.
     *
     * @return Pyramid color.
     */
    Color getColor(void) const
    {
        return this->_color;
    }

private:
    /**
     * @brief Pyramid base center.
     */
    Math::Vector3D _position;

    /**
     * @brief Square base side length.
     */
    double _size;

    /**
     * @brief Pyramid height.
     */
    double _height;

    /**
     * @brief Pyramid color.
     */
    Color _color;
};

}
