/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IPrimitives.hpp
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Utils/Ray.hpp"
#include <optional>

namespace RayTracer {

class IPrimitive
{
public:
    virtual ~IPrimitive() = default;

    /**
     * @brief Checks whether a ray intersects the object and returns
     * the distance along the ray to the hit point.
     *
     * @param ray Ray to test.
     *
     * @return Distance to the hit point (t >= 0). Returns std::nullopt when
     * there is no intersection.
     */
    virtual std::optional<double> hits(const Ray &ray) const = 0;

    /**
     * @brief Computes the surface normal at a given point.
     *
     * @param point Point on the primitive surface.
     *
     * @return Unit-length surface normal.
     */
    virtual Math::Vector3D getNormalAt(const Math::Point3D &point) const = 0;

    /**
     * @brief Translate the object.
     *
     * @param offset Translation offset.
     */
    virtual void translate(const Math::Vector3D &offset) = 0;

    /**
     * @brief Rotate the object.
     *
     * @param rotation Rotation vector.
     */
    virtual void rotate(const Math::Vector3D &rotation) = 0;
};

}
