/*
** EPITECH PROJECT, 2026
** DirectionalLight.hpp
** File description:
** Header file for the DirectionalLight
*/

#pragma once

#include <limits>

#include "Lights/ILight.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

namespace RayTracer {

class DirectionalLight : public ILight
{
public:
    /**
     * @brief Constructs a directional light.
     *
     * @param direction Light propagation direction.
     * @param intensity Light intensity multiplier.
     */
    DirectionalLight(const Math::Vector3D &direction, double intensity, const Color &color = Color(255, 255, 255))
        : _direction(direction.normalized()), _intensity(intensity), _color(color) {}

    /**
     * @brief Destroys the directional light.
     */
    ~DirectionalLight(void) override = default;

public:
    /**
     * @brief Gets the unit direction from a point toward the light.
     *
     * @param point Surface point being shaded.
     *
     * @return Unit-length direction vector.
     */
    Math::Vector3D directionFrom(const Math::Point3D &) const override
    {
        return Math::Vector3D(-this->_direction.getX(), -this->_direction.getY(), -this->_direction.getZ());
    }

    /**
     * @brief Gets the light intensity at a point.
     *
     * @param point Surface point being shaded.
     *
     * @return Intensity multiplier.
     */
    double getIntensityAt(const Math::Point3D &) const override
    {
        return this->_intensity;
    }

    /**
     * @brief Distance to the light (infinite for directional).
     *
     * @return Infinity.
     */
    double distanceTo(const Math::Point3D &) const override
    {
        return std::numeric_limits<double>::infinity();
    }

public:
    /**
     * @brief Gets the light direction.
     *
     * @return Unit-length propagation direction.
     */
    Math::Vector3D getDirection(void) const
    {
        return this->_direction;
    }

    /**
     * @brief Gets the light color.
     *
     * @return Light color.
     */
    Color getColor(void) const override
    {
        return this->_color;
    }

private:
    /**
     * @brief Light propagation direction.
     */
    Math::Vector3D _direction;

    /**
     * @brief Light intensity multiplier.
     */
    double _intensity;

    /**
     * @brief Light color.
     */
    Color _color;
};

}
