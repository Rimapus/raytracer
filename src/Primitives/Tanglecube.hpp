/*
** EPITECH PROJECT, 2026
** Tanglecube.hpp
** File description:
** Header file for the Tanglecube
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Math/Transform.hpp"
#include "Math/Vector3D.hpp"
#include "Primitives/IPrimitives.hpp"
#include "Utils/Ray.hpp"
#include <cmath>
#include <optional>

namespace RayTracer {

class Tanglecube : public IPrimitive
{
public:
    /**
     * @brief Constructs a tanglecube from center and scale.
     *
     * @param center Tanglecube center.
     * @param scale Tanglecube scale.
     */
    Tanglecube(const Math::Point3D &center, double scale)
        : _center(center), _scale(scale) {}

    /**
     * @brief Destroys the tanglecube.
     */
    ~Tanglecube(void) override = default;

public:
    /**
     * @brief Checks whether a ray intersects the tanglecube and returns the
     * distance to the intersection point.
     *
     * @param ray Ray to test.
     *
     * @return Distance to the hit point (t >= 0). Returns std::nullopt when there
     * is no intersection.
     */
    std::optional<double> hits(const Ray &ray) const override;

    /**
     * @brief Computes the surface normal at a point on the tanglecube.
     *
     * @param point Point on the tanglecube surface.
     *
     * @return Unit-length normal vector.
     */
    Math::Vector3D getNormalAt(const Math::Point3D &point) const override;

    /**
     * @brief Translate the tanglecube.
     *
     * @param offset Translation offset.
     */
    void translate(const Math::Vector3D &offset) override;

    /**
     * @brief Rotate the tanglecube.
     *
     * @param rotation Rotation vector.
     */
    void rotate(const Math::Vector3D &rotation) override;

private:
    /**
     * @brief Computes the canonical tanglecube implicit surface value.
     *
     * @param x Local x coordinate.
     * @param y Local y coordinate.
     * @param z Local z coordinate.
     *
     * @return Implicit surface value.
     */
    static double tanglecubeImplicit(double x, double y, double z);

private:
    /**
     * @brief Center point of the tanglecube.
     */
    Math::Point3D _center;

    /**
     * @brief Scale applied to the canonical tanglecube.
     */
    double _scale;

    /**
     * @brief Rotation applied to the tanglecube.
     */
    Math::Vector3D _rotation = Math::Vector3D(0.0, 0.0, 0.0);
};

}
