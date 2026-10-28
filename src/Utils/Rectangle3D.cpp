/*
** EPITECH PROJECT, 2026
** Rectangle3D.cpp
** File description:
** Main file for the Rectangle3D
*/

#include "Rectangle3D.hpp"

namespace RayTracer {

/**
 * @brief Computes a point on this rectangle from normalized coordinates.
 *
 * @param u Horizontal normalized coordinate.
 * @param v Vertical normalized coordinate.
 *
 * @return Point located on the rectangle plane.
 */
Math::Point3D Rectangle3D::pointAt(double u, double v) const
{
    return Math::Point3D(
        this->_origin.getX() + u * this->_bottomSide.getX() + v * this->_leftSide.getX(),
        this->_origin.getY() + u * this->_bottomSide.getY() + v * this->_leftSide.getY(),
        this->_origin.getZ() + u * this->_bottomSide.getZ() + v * this->_leftSide.getZ());
}

}
