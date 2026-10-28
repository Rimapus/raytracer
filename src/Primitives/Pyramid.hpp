/*
** EPITECH PROJECT, 2026
** Pyramid.hpp
** File description:
** Header file for the Pyramid
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Math/Transform.hpp"
#include "Math/Vector3D.hpp"
#include "Primitives/IPrimitives.hpp"
#include "Utils/Ray.hpp"
#include <array>
#include <cmath>
#include <optional>

namespace RayTracer {

class Pyramid : public IPrimitive
{
public:
    /**
     * @brief Constructs a square-base pyramid from a base center, size and height.
     *
     * @param baseCenter Center of the square base.
     * @param size Square base side length.
     * @param height Pyramid height.
     */
    Pyramid(const Math::Point3D &baseCenter, double size, double height);

    /**
     * @brief Destroys the pyramid.
     */
    ~Pyramid(void) override = default;

public:
    /**
     * @brief Checks whether a ray intersects the pyramid and returns the
     * distance to the intersection point.
     *
     * @param ray Ray to test.
     *
     * @return Distance to the hit point (t >= 0). Returns std::nullopt when there
     * is no intersection.
     */
    std::optional<double> hits(const Ray &ray) const override;

    /**
     * @brief Computes the surface normal at a point on the pyramid.
     *
     * @param point Point on the pyramid surface.
     *
     * @return Unit-length normal vector.
     */
    Math::Vector3D getNormalAt(const Math::Point3D &point) const override;

    /**
     * @brief Translate the pyramid.
     *
     * @param offset Translation offset.
     */
    void translate(const Math::Vector3D &offset) override;

    /**
     * @brief Rotate the pyramid around its center.
     *
     * @param rotation Rotation vector.
     */
    void rotate(const Math::Vector3D &rotation) override;

private:
    /**
     * @brief One triangular pyramid face.
     */
    struct Face
    {
        std::size_t _first;
        std::size_t _second;
        std::size_t _third;
    };

    /**
     * @brief Checks whether a ray intersects one triangular face.
     *
     * @param face Face indices.
     *
     * @return Face hit distance.
     */
    std::optional<double> hitFace(const Ray &ray, const Face &face) const;

    /**
     * @brief Computes the normal of one triangular face.
     *
     * @param face Face indices.
     *
     * @return Face normal.
     */
    Math::Vector3D getFaceNormal(const Face &face) const;

    /**
     * @brief Checks whether a point is on a face.
     *
     * @param point Surface point.
     * @param face Face indices.
     *
     * @return True when the point belongs to the face.
     */
    bool isPointOnFace(const Math::Point3D &point, const Face &face) const;

    /**
     * @brief Computes the pyramid rotation center.
     *
     * @return Rotation center.
     */
    Math::Point3D getCenter(void) const;

private:
    /**
     * @brief Converts a point to a vector with the same coordinates.
     *
     * @param point Point to convert.
     *
     * @return Converted vector.
     */
    static Math::Vector3D pointToVector(const Math::Point3D &point);

    /**
     * @brief Computes the vector between two points.
     *
     * @param from Start point.
     * @param to End point.
     *
     * @return Vector from start to end.
     */
    static Math::Vector3D vectorBetween(const Math::Point3D &from, const Math::Point3D &to);

    /**
     * @brief Computes the cross product between two vectors.
     *
     * @param left Left vector.
     * @param right Right vector.
     *
     * @return Cross product.
     */
    static Math::Vector3D cross(const Math::Vector3D &left, const Math::Vector3D &right);

    /**
     * @brief Rotates a point around a center.
     *
     * @param point Point to rotate.
     * @param center Rotation center.
     * @param rotation Rotation vector.
     *
     * @return Rotated point.
     */
    static Math::Point3D rotatePointAround(const Math::Point3D &point, const Math::Point3D &center,
                                           const Math::Vector3D &rotation);

private:
    /**
     * @brief Pyramid vertices. First four are base corners, last is apex.
     */
    std::array<Math::Point3D, 5> _vertices;

    /**
     * @brief Triangular faces. The square base is split into two triangles.
     */
    static const std::array<Face, 6> _faces;
};

}
