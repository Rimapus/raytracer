/*
** EPITECH PROJECT, 2026
** Point3D.cpp
** File description:
** Main file for the Point3D
*/

#include "Point3D.hpp"

namespace Math {

/**
 * @brief Translates this point by a vector.
 *
 * @param vector Translation vector.
 *
 * @return A new translated point.
 */
Point3D Point3D::operator+(const Vector3D &vector) const
{
    return Point3D(this->_x + vector.getX(),
                   this->_y + vector.getY(),
                   this->_z + vector.getZ());
}

/**
 * @brief Translates this point in place by a vector.
 *
 * @param vector Translation vector.
 *
 * @return Reference to this point after translation.
 */
Point3D &Point3D::operator+=(const Vector3D &vector)
{
    this->_x += vector.getX();
    this->_y += vector.getY();
    this->_z += vector.getZ();
    return *this;
}

}
