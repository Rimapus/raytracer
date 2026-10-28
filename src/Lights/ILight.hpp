/*
** EPITECH PROJECT, 2026
** ILight.hpp
** File description:
** Header file for the ILight interface
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Utils/Color.hpp"

namespace RayTracer {

class ILight
{
public:
    /**
     * @brief Destroys the light.
     */
    virtual ~ILight(void) = default;

    /**
     * @brief Gets the light color.
     *
     * @return Light color.
     */
    virtual Color getColor(void) const = 0;

    /**
     * @brief Gets the unit direction from a point toward the light.
     *
     * @param point Surface point being shaded.
     *
     * @return Unit-length direction vector.
     */
    virtual Math::Vector3D directionFrom(const Math::Point3D &point) const = 0;

    /**
     * @brief Gets the light intensity at a point.
     *
     * @param point Surface point being shaded.
     *
     * @return Intensity multiplier.
     */
    virtual double getIntensityAt(const Math::Point3D &point) const = 0;

    /**
     * @brief Distance from a point to the light (infinity for directional).
     *
     * @param point Surface point.
     *
     * @return Distance to the light.
     */
    virtual double distanceTo(const Math::Point3D &point) const = 0;
};

}
