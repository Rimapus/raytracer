/*
** EPITECH PROJECT, 2026
** Transform.cpp
** File description:
** Transform helper implementations
*/

#include "Transform.hpp"

namespace Math {

double degreesToRadians(double value)
{
    return value * std::numbers::pi_v<double> / 180.0;
}

Vector3D rotateAroundX(const Vector3D &vector, double angleRadians)
{
    const double cosine = std::cos(angleRadians);
    const double sine = std::sin(angleRadians);

    return Vector3D(
        vector.getX(),
        vector.getY() * cosine - vector.getZ() * sine,
        vector.getY() * sine + vector.getZ() * cosine);
}

Vector3D rotateAroundY(const Vector3D &vector, double angleRadians)
{
    const double cosine = std::cos(angleRadians);
    const double sine = std::sin(angleRadians);

    return Vector3D(
        vector.getX() * cosine + vector.getZ() * sine,
        vector.getY(),
        -vector.getX() * sine + vector.getZ() * cosine);
}

Vector3D rotateAroundZ(const Vector3D &vector, double angleRadians)
{
    const double cosine = std::cos(angleRadians);
    const double sine = std::sin(angleRadians);

    return Vector3D(
        vector.getX() * cosine - vector.getY() * sine,
        vector.getX() * sine + vector.getY() * cosine,
        vector.getZ());
}

Vector3D applyEulerXYZRotation(const Vector3D &vector, const Vector3D &rotationDegrees)
{
    Vector3D result = rotateAroundX(vector, degreesToRadians(rotationDegrees.getX()));
    result = rotateAroundY(result, degreesToRadians(rotationDegrees.getY()));
    return rotateAroundZ(result, degreesToRadians(rotationDegrees.getZ()));
}

Vector3D applyInverseEulerXYZRotation(const Vector3D &vector, const Vector3D &rotationDegrees)
{
    Vector3D result = rotateAroundZ(vector, degreesToRadians(-rotationDegrees.getZ()));
    result = rotateAroundY(result, degreesToRadians(-rotationDegrees.getY()));
    return rotateAroundX(result, degreesToRadians(-rotationDegrees.getX()));
}

Vector3D toLocalVector(const Point3D &point, const Point3D &center, const Vector3D &rotationDegrees)
{
    const Vector3D centered(point.getX() - center.getX(),
                            point.getY() - center.getY(),
                            point.getZ() - center.getZ());
    return applyInverseEulerXYZRotation(centered, rotationDegrees);
}

}
