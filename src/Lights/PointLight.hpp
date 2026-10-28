/*
** EPITECH PROJECT, 2026
** PointLight.hpp
** File description:
** Header file for the PointLight
*/

#pragma once

#include <cmath>

#include "Lights/ILight.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

namespace RayTracer {

class PointLight : public ILight
{
public:
    /**
     * @brief Constructs a point light.
     *
     * @param position Light position.
     * @param intensity Light intensity multiplier.
     */
    PointLight(const Math::Point3D &position, double intensity, const Color &color = Color(255, 255, 255))
        : _position(position), _intensity(intensity), _color(color) {}

    /**
     * @brief Destroys the point light.
     */
    ~PointLight(void) override = default;

public:
    /**
     * @brief Gets the unit direction from a point toward the light.
     *
     * @param point Surface point being shaded.
     *
     * @return Unit-length direction vector.
     */
    Math::Vector3D directionFrom(const Math::Point3D &point) const override
    {
        const Math::Vector3D toLight(this->_position.getX() - point.getX(), this->_position.getY() - point.getY(), this->_position.getZ() - point.getZ());

        return toLight.normalized();
    }

    /**
     * @brief Gets the light intensity at a point with inverse-square falloff.
     *
     * @param point Surface point being shaded.
     *
     * @return Attenuated intensity multiplier.
     */
    double getIntensityAt(const Math::Point3D &point) const override
    {
        const double dx = this->_position.getX() - point.getX();
        const double dy = this->_position.getY() - point.getY();
        const double dz = this->_position.getZ() - point.getZ();
        const double distSquared = dx * dx + dy * dy + dz * dz;

        if (distSquared < 1e-6) {
            return this->_intensity;
        }
        return this->_intensity / distSquared;
    }

    /**
     * @brief Distance from a point to the light.
     *
     * @param point Surface point.
     *
     * @return Distance to the light.
     */
    double distanceTo(const Math::Point3D &point) const override
    {
        const double dx = this->_position.getX() - point.getX();
        const double dy = this->_position.getY() - point.getY();
        const double dz = this->_position.getZ() - point.getZ();

        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

public:
    /**
     * @brief Gets the light position.
     *
     * @return Light position.
     */
    Math::Point3D getPosition(void) const
    {
        return this->_position;
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
     * @brief Light position.
     */
    Math::Point3D _position;

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
