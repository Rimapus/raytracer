/*
** EPITECH PROJECT, 2026
** Ray.hpp
** File description:
** Header file for the Ray
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

namespace RayTracer {

class Ray
{
public:
    /**
     * @brief Constructs a default ray.
     */
    Ray(void) = default;

    /**
     * @brief Constructs a ray from origin and direction.
     *
     * @param origin Ray origin point.
     * @param direction Ray direction vector.
     */
    Ray(const Math::Point3D &origin, const Math::Vector3D &direction)
        : _origin(origin), _direction(direction) {}

    /**
     * @brief Destroys the ray.
     */
    ~Ray(void) = default;

    /**
     * @brief Gets the ray origin.
     *
     * @return Ray origin point.
     */
    Math::Point3D getOrigin(void) const
    {
        return this->_origin;
    }

    /**
     * @brief Gets the ray direction.
     *
     * @return Ray direction vector.
     */
    Math::Vector3D getDirection(void) const
    {
        return this->_direction;
    }

    /**
     * @brief Sets the ray origin.
     *
     * @param value New origin point.
     */
    void setOrigin(const Math::Point3D &value)
    {
        this->_origin = value;
    }

    /**
     * @brief Sets the ray direction.
     *
     * @param value New direction vector.
     */
    void setDirection(const Math::Vector3D &value)
    {
        this->_direction = value;
    }

private:
    /**
     * @brief Ray origin point.
     */
    Math::Point3D _origin;

    /**
     * @brief Ray direction vector.
     */
    Math::Vector3D _direction;
};

}
