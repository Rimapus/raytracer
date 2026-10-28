/*
** EPITECH PROJECT, 2026
** Transform.hpp
** File description:
** Common transform helpers for 3D vectors/points
*/

#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <cmath>
#include <numbers>

namespace Math {

/**
 * @brief Converts an angle in degrees to radians.
 *
 * @param value Angle in degrees.
 *
 * @return Angle in radians.
 */
double degreesToRadians(double value);

/**
 * @brief Rotates a vector around the X axis.
 *
 * @param vector Input vector.
 * @param angleRadians Rotation angle in radians.
 *
 * @return Rotated vector.
 */
Vector3D rotateAroundX(const Vector3D &vector, double angleRadians);

/**
 * @brief Rotates a vector around the Y axis.
 *
 * @param vector Input vector.
 * @param angleRadians Rotation angle in radians.
 *
 * @return Rotated vector.
 */
Vector3D rotateAroundY(const Vector3D &vector, double angleRadians);

/**
 * @brief Rotates a vector around the Z axis.
 *
 * @param vector Input vector.
 * @param angleRadians Rotation angle in radians.
 *
 * @return Rotated vector.
 */
Vector3D rotateAroundZ(const Vector3D &vector, double angleRadians);

/**
 * @brief Applies Euler rotation in X->Y->Z order.
 *
 * @param vector Input vector.
 * @param rotationDegrees Rotation angles in degrees.
 *
 * @return Rotated vector.
 */
Vector3D applyEulerXYZRotation(const Vector3D &vector, const Vector3D &rotationDegrees);

/**
 * @brief Applies inverse Euler rotation in reverse order.
 *
 * @param vector Input vector.
 * @param rotationDegrees Rotation angles in degrees.
 *
 * @return Rotated vector in inverse transform space.
 */
Vector3D applyInverseEulerXYZRotation(const Vector3D &vector, const Vector3D &rotationDegrees);

/**
 * @brief Converts a world-space point to local vector space.
 *
 * @param point World-space point.
 * @param center Local origin center in world-space.
 * @param rotationDegrees Local rotation in degrees.
 *
 * @return Point represented as a rotated local vector.
 */
Vector3D toLocalVector(const Point3D &point, const Point3D &center, const Vector3D &rotationDegrees);

}
