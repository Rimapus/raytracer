/*
** EPITECH PROJECT, 2026
** Point3D.hpp
** File description:
** Header file for the Point3D
*/

#pragma once

#include "Vector3D.hpp"

namespace Math {

class Point3D
{
public:
    /**
     * @brief Constructs a point initialized at the origin.
     */
    Point3D(void) = default;

    /**
     * @brief Constructs a point from explicit coordinates.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     */
    Point3D(double x, double y, double z)
        : _x(x), _y(y), _z(z) {}

    /**
     * @brief Destroys the point.
     */
    ~Point3D(void) = default;

public:
    /**
     * @brief Gets the X coordinate.
     *
     * @return X coordinate.
     */
    double getX(void) const
    {
        return this->_x;
    }

    /**
     * @brief Gets the Y coordinate.
     *
     * @return Y coordinate.
     */
    double getY(void) const
    {
        return this->_y;
    }

    /**
     * @brief Gets the Z coordinate.
     *
     * @return Z coordinate.
     */
    double getZ(void) const
    {
        return this->_z;
    }

    /**
     * @brief Sets the X coordinate.
     *
     * @param value New X coordinate.
     */
    void setX(double value)
    {
        this->_x = value;
    }

    /**
     * @brief Sets the Y coordinate.
     *
     * @param value New Y coordinate.
     */
    void setY(double value)
    {
        this->_y = value;
    }

    /**
     * @brief Sets the Z coordinate.
     *
     * @param value New Z coordinate.
     */
    void setZ(double value)
    {
        this->_z = value;
    }

public:
    /**
     * @brief Translates the point by a vector and returns the resulting point.
     *
     * @param vector Translation vector.
     *
     * @return Translated point.
     */
    Point3D operator+(const Vector3D &vector) const;

    /**
     * @brief Translates the point in place by a vector.
     *
     * @param vector Translation vector.
     *
     * @return Reference to this point.
     */
    Point3D &operator+=(const Vector3D &vector);

private:
    /**
     * @brief X coordinate.
     */
    double _x = 0.0;

    /**
     * @brief Y coordinate.
     */
    double _y = 0.0;

    /**
     * @brief Z coordinate.
     */
    double _z = 0.0;
};

}
