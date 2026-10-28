/*
** EPITECH PROJECT, 2026
** Pyramid.cpp
** File description:
** Main file for the Pyramid
*/

#include "Pyramid.hpp"

namespace RayTracer {

Math::Vector3D Pyramid::pointToVector(const Math::Point3D &point)
{
    return Math::Vector3D(point.getX(), point.getY(), point.getZ());
}

Math::Vector3D Pyramid::vectorBetween(const Math::Point3D &from, const Math::Point3D &to)
{
    return Math::Vector3D(to.getX() - from.getX(),
                          to.getY() - from.getY(),
                          to.getZ() - from.getZ());
}

Math::Vector3D Pyramid::cross(const Math::Vector3D &left, const Math::Vector3D &right)
{
    return Math::Vector3D(
        left.getY() * right.getZ() - left.getZ() * right.getY(),
        left.getZ() * right.getX() - left.getX() * right.getZ(),
        left.getX() * right.getY() - left.getY() * right.getX());
}

Math::Point3D Pyramid::rotatePointAround(const Math::Point3D &point, const Math::Point3D &center,
                                         const Math::Vector3D &rotation)
{
    const Math::Vector3D local(point.getX() - center.getX(),
                               point.getY() - center.getY(),
                               point.getZ() - center.getZ());
    const Math::Vector3D rotated = Math::applyEulerXYZRotation(local, rotation);

    return Math::Point3D(center.getX() + rotated.getX(),
                         center.getY() + rotated.getY(),
                         center.getZ() + rotated.getZ());
}

const std::array<Pyramid::Face, 6> Pyramid::_faces = {
    {
     {0, 4, 1},
     {1, 4, 2},
     {2, 4, 3},
     {3, 4, 0},
     {0, 1, 2},
     {0, 2, 3},
     }
};

Pyramid::Pyramid(const Math::Point3D &baseCenter, double size, double height)
{
    const double halfSize = size / 2.0;

    this->_vertices = {
        {
         Math::Point3D(baseCenter.getX() - halfSize, baseCenter.getY(), baseCenter.getZ() - halfSize),
         Math::Point3D(baseCenter.getX() + halfSize, baseCenter.getY(), baseCenter.getZ() - halfSize),
         Math::Point3D(baseCenter.getX() + halfSize, baseCenter.getY(), baseCenter.getZ() + halfSize),
         Math::Point3D(baseCenter.getX() - halfSize, baseCenter.getY(), baseCenter.getZ() + halfSize),
         Math::Point3D(baseCenter.getX(), baseCenter.getY() + height, baseCenter.getZ()),
         }
    };
}

std::optional<double> Pyramid::hits(const Ray &ray) const
{
    std::optional<double> closestHit = std::nullopt;

    for (const Face &face : Pyramid::_faces) {
        const std::optional<double> distance = this->hitFace(ray, face);

        if (distance && (!closestHit || *distance < *closestHit)) {
            closestHit = distance;
        }
    }
    return closestHit;
}

Math::Vector3D Pyramid::getNormalAt(const Math::Point3D &point) const
{
    for (const Face &face : Pyramid::_faces) {
        if (this->isPointOnFace(point, face)) {
            return this->getFaceNormal(face);
        }
    }
    return this->getFaceNormal(Pyramid::_faces[0]);
}

void Pyramid::translate(const Math::Vector3D &offset)
{
    for (Math::Point3D &vertex : this->_vertices) {
        vertex += offset;
    }
}

void Pyramid::rotate(const Math::Vector3D &rotation)
{
    const Math::Point3D center = this->getCenter();

    for (Math::Point3D &vertex : this->_vertices) {
        vertex = Pyramid::rotatePointAround(vertex, center, rotation);
    }
}

std::optional<double> Pyramid::hitFace(const Ray &ray, const Face &face) const
{
    const double epsilon = 1e-8;
    const Math::Point3D &first = this->_vertices[face._first];
    const Math::Vector3D edge1 = Pyramid::vectorBetween(first, this->_vertices[face._second]);
    const Math::Vector3D edge2 = Pyramid::vectorBetween(first, this->_vertices[face._third]);
    const Math::Vector3D rayDirection = ray.getDirection();
    const Math::Vector3D rayOrigin = Pyramid::pointToVector(ray.getOrigin());
    const Math::Vector3D h = Pyramid::cross(rayDirection, edge2);
    const double determinant = edge1.dot(h);

    if (std::abs(determinant) < epsilon) {
        return std::nullopt;
    }

    const double inverseDeterminant = 1.0 / determinant;
    const Math::Vector3D s = rayOrigin - Pyramid::pointToVector(first);
    const double u = inverseDeterminant * s.dot(h);

    if (u < 0.0 || u > 1.0) {
        return std::nullopt;
    }

    const Math::Vector3D q = Pyramid::cross(s, edge1);
    const double v = inverseDeterminant * rayDirection.dot(q);

    if (v < 0.0 || u + v > 1.0) {
        return std::nullopt;
    }

    const double t = inverseDeterminant * edge2.dot(q);
    return (t >= 0.0) ? std::optional<double>(t) : std::nullopt;
}

Math::Vector3D Pyramid::getFaceNormal(const Face &face) const
{
    const Math::Point3D &first = this->_vertices[face._first];
    const Math::Vector3D edge1 = Pyramid::vectorBetween(first, this->_vertices[face._second]);
    const Math::Vector3D edge2 = Pyramid::vectorBetween(first, this->_vertices[face._third]);

    return Pyramid::cross(edge1, edge2).normalized();
}

bool Pyramid::isPointOnFace(const Math::Point3D &point, const Face &face) const
{
    const Math::Point3D &first = this->_vertices[face._first];
    const Math::Vector3D edge1 = Pyramid::vectorBetween(first, this->_vertices[face._second]);
    const Math::Vector3D edge2 = Pyramid::vectorBetween(first, this->_vertices[face._third]);
    const Math::Vector3D toPoint = Pyramid::vectorBetween(first, point);
    const Math::Vector3D normal = this->getFaceNormal(face);
    const double planeDistance = std::abs(toPoint.dot(normal));

    if (planeDistance > 1e-4) {
        return false;
    }

    const double dot00 = edge2.dot(edge2);
    const double dot01 = edge2.dot(edge1);
    const double dot02 = edge2.dot(toPoint);
    const double dot11 = edge1.dot(edge1);
    const double dot12 = edge1.dot(toPoint);
    const double denominator = dot00 * dot11 - dot01 * dot01;

    if (std::abs(denominator) < 1e-12) {
        return false;
    }

    const double invDenominator = 1.0 / denominator;
    const double u = (dot11 * dot02 - dot01 * dot12) * invDenominator;
    const double v = (dot00 * dot12 - dot01 * dot02) * invDenominator;

    return u >= -1e-4 && v >= -1e-4 && u + v <= 1.0001;
}

Math::Point3D Pyramid::getCenter(void) const
{
    Math::Vector3D sum(0.0, 0.0, 0.0);

    for (const Math::Point3D &vertex : this->_vertices) {
        sum += Pyramid::pointToVector(vertex);
    }
    sum /= static_cast<double>(this->_vertices.size());
    return Math::Point3D(sum.getX(), sum.getY(), sum.getZ());
}

}
