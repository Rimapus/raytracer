/*
** EPITECH PROJECT, 2026
** Vector3D.hpp
** File description:
** Header file for the Vector3D
*/

#pragma once

#include <cmath>

namespace Math {

class Vector3D
{
public:
    /**
     * @brief Constructs a zero vector.
     */
    Vector3D(void) = default;

    /**
     * @brief Constructs a vector from explicit components.
     *
     * @param x X component.
     * @param y Y component.
     * @param z Z component.
     */
    Vector3D(double x, double y, double z)
        : _x(x), _y(y), _z(z) {}

    /**
     * @brief Destroys the vector.
     */
    ~Vector3D(void) = default;

public:
    /**
     * @brief Gets the X component.
     *
     * @return X component.
     */
    double getX(void) const
    {
        return this->_x;
    }

    /**
     * @brief Gets the Y component.
     *
     * @return Y component.
     */
    double getY(void) const
    {
        return this->_y;
    }

    /**
     * @brief Gets the Z component.
     *
     * @return Z component.
     */
    double getZ(void) const
    {
        return this->_z;
    }

    /**
     * @brief Sets the X component.
     *
     * @param value New X component.
     */
    void setX(double value)
    {
        this->_x = value;
    }

    /**
     * @brief Sets the Y component.
     *
     * @param value New Y component.
     */
    void setY(double value)
    {
        this->_y = value;
    }

    /**
     * @brief Sets the Z component.
     *
     * @param value New Z component.
     */
    void setZ(double value)
    {
        this->_z = value;
    }

public:
    /**
     * @brief Computes the Euclidean length of the vector.
     *
     * @return Vector length.
     */
    double length(void) const;

    /**
     * @brief Computes the dot product with another vector.
     *
     * @param other Other vector.
     *
     * @return Dot product value.
     */
    double dot(const Vector3D &other) const;

    /**
     * @brief Returns a unit-length copy of this vector.
     *
     * @return Normalized vector.
     */
    Vector3D normalized(void) const;

public:
    /**
     * @brief Adds another vector component-wise.
     *
     * @param other Vector to add.
     *
     * @return Sum vector.
     */
    Vector3D operator+(const Vector3D &other) const;

    /**
     * @brief Adds another vector in place component-wise.
     *
     * @param other Vector to add.
     *
     * @return Reference to this vector.
     */
    Vector3D &operator+=(const Vector3D &other);

    /**
     * @brief Subtracts another vector component-wise.
     *
     * @param other Vector to subtract.
     *
     * @return Difference vector.
     */
    Vector3D operator-(const Vector3D &other) const;

    /**
     * @brief Subtracts another vector in place component-wise.
     *
     * @param other Vector to subtract.
     *
     * @return Reference to this vector.
     */
    Vector3D &operator-=(const Vector3D &other);

    /**
     * @brief Multiplies by another vector component-wise.
     *
     * @param other Vector to multiply with.
     *
     * @return Product vector.
     */
    Vector3D operator*(const Vector3D &other) const;

    /**
     * @brief Multiplies by another vector in place component-wise.
     *
     * @param other Vector to multiply with.
     *
     * @return Reference to this vector.
     */
    Vector3D &operator*=(const Vector3D &other);

    /**
     * @brief Divides by another vector component-wise.
     *
     * @param other Vector divisor.
     *
     * @return Quotient vector.
     */
    Vector3D operator/(const Vector3D &other) const;

    /**
     * @brief Divides by another vector in place component-wise.
     *
     * @param other Vector divisor.
     *
     * @return Reference to this vector.
     */
    Vector3D &operator/=(const Vector3D &other);

    /**
     * @brief Multiplies all components by a scalar.
     *
     * @param value Scalar multiplier.
     *
     * @return Scaled vector.
     */
    Vector3D operator*(double value) const;

    /**
     * @brief Multiplies all components by a scalar in place.
     *
     * @param value Scalar multiplier.
     *
     * @return Reference to this vector.
     */
    Vector3D &operator*=(double value);

    /**
     * @brief Divides all components by a scalar.
     *
     * @param value Scalar divisor.
     *
     * @return Scaled vector.
     */
    Vector3D operator/(double value) const;

    /**
     * @brief Divides all components by a scalar in place.
     *
     * @param value Scalar divisor.
     *
     * @return Reference to this vector.
     */
    Vector3D &operator/=(double value);

private:
    /**
     * @brief X component.
     */
    double _x = 0.0;

    /**
     * @brief Y component.
     */
    double _y = 0.0;

    /**
     * @brief Z component.
     */
    double _z = 0.0;
};

}
