/*
** EPITECH PROJECT, 2026
** Vector3D.cpp
** File description:
** Main file for the Vector3D
*/

#include "Vector3D.hpp"

namespace Math {

/**
 * @brief Computes the Euclidean length of this vector.
 *
 * @return Vector length.
 */
double Vector3D::length(void) const
{
    return std::sqrt((this->_x * this->_x) +
                     (this->_y * this->_y) +
                     (this->_z * this->_z));
}

/**
 * @brief Computes the dot product with another vector.
 *
 * @param other Other vector.
 *
 * @return Dot product value.
 */
double Vector3D::dot(const Vector3D &other) const
{
    return this->_x * other.getX() +
           this->_y * other.getY() +
           this->_z * other.getZ();
}

/**
 * @brief Returns a unit-length copy of this vector.
 *
 * @return Normalized vector.
 */
Vector3D Vector3D::normalized(void) const
{
    const double len = this->length();

    if (len < 1e-12) {
        return Vector3D(0.0, 0.0, 0.0);
    }
    return Vector3D(this->_x / len, this->_y / len, this->_z / len);
}

/**
 * @brief Adds another vector component-wise.
 *
 * @param other Vector to add.
 *
 * @return Sum vector.
 */
Vector3D Vector3D::operator+(const Vector3D &other) const
{
    return Vector3D(this->_x + other.getX(),
                    this->_y + other.getY(),
                    this->_z + other.getZ());
}

/**
 * @brief Adds another vector in place component-wise.
 *
 * @param other Vector to add.
 *
 * @return Reference to this vector.
 */
Vector3D &Vector3D::operator+=(const Vector3D &other)
{
    this->_x += other.getX();
    this->_y += other.getY();
    this->_z += other.getZ();
    return *this;
}

/**
 * @brief Subtracts another vector component-wise.
 *
 * @param other Vector to subtract.
 *
 * @return Difference vector.
 */
Vector3D Vector3D::operator-(const Vector3D &other) const
{
    return Vector3D(this->_x - other.getX(),
                    this->_y - other.getY(),
                    this->_z - other.getZ());
}

/**
 * @brief Subtracts another vector in place component-wise.
 *
 * @param other Vector to subtract.
 *
 * @return Reference to this vector.
 */
Vector3D &Vector3D::operator-=(const Vector3D &other)
{
    this->_x -= other.getX();
    this->_y -= other.getY();
    this->_z -= other.getZ();
    return *this;
}

/**
 * @brief Multiplies by another vector component-wise.
 *
 * @param other Vector to multiply with.
 *
 * @return Product vector.
 */
Vector3D Vector3D::operator*(const Vector3D &other) const
{
    return Vector3D(this->_x * other.getX(),
                    this->_y * other.getY(),
                    this->_z * other.getZ());
}

/**
 * @brief Multiplies by another vector in place component-wise.
 *
 * @param other Vector to multiply with.
 *
 * @return Reference to this vector.
 */
Vector3D &Vector3D::operator*=(const Vector3D &other)
{
    this->_x *= other.getX();
    this->_y *= other.getY();
    this->_z *= other.getZ();
    return *this;
}

/**
 * @brief Divides by another vector component-wise.
 *
 * @param other Vector divisor.
 *
 * @return Quotient vector.
 */
Vector3D Vector3D::operator/(const Vector3D &other) const
{
    return Vector3D(this->_x / other.getX(),
                    this->_y / other.getY(),
                    this->_z / other.getZ());
}

/**
 * @brief Divides by another vector in place component-wise.
 *
 * @param other Vector divisor.
 *
 * @return Reference to this vector.
 */
Vector3D &Vector3D::operator/=(const Vector3D &other)
{
    this->_x /= other.getX();
    this->_y /= other.getY();
    this->_z /= other.getZ();
    return *this;
}

/**
 * @brief Multiplies all components by a scalar.
 *
 * @param value Scalar multiplier.
 *
 * @return Scaled vector.
 */
Vector3D Vector3D::operator*(double value) const
{
    return Vector3D(this->_x * value,
                    this->_y * value,
                    this->_z * value);
}

/**
 * @brief Multiplies all components by a scalar in place.
 *
 * @param value Scalar multiplier.
 *
 * @return Reference to this vector.
 */
Vector3D &Vector3D::operator*=(double value)
{
    this->_x *= value;
    this->_y *= value;
    this->_z *= value;
    return *this;
}

/**
 * @brief Divides all components by a scalar.
 *
 * @param value Scalar divisor.
 *
 * @return Scaled vector.
 */
Vector3D Vector3D::operator/(double value) const
{
    return Vector3D(this->_x / value,
                    this->_y / value,
                    this->_z / value);
}

/**
 * @brief Divides all components by a scalar in place.
 *
 * @param value Scalar divisor.
 *
 * @return Reference to this vector.
 */
Vector3D &Vector3D::operator/=(double value)
{
    this->_x /= value;
    this->_y /= value;
    this->_z /= value;
    return *this;
}

}
