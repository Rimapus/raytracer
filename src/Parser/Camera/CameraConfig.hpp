/*
** EPITECH PROJECT, 2026
** CameraConfig.hpp
** File description:
** Header file for the CameraConfig
*/

#pragma once

#include "Math/Vector3D.hpp"

namespace RayTracer {

class CameraConfig
{
public:
    /**
     * @brief Constructs a default camera configuration.
     */
    CameraConfig(void) = default;

    /**
     * @brief Constructs a camera configuration.
     *
     * @param width Render width in pixels.
     * @param height Render height in pixels.
     * @param position Camera position in world space.
     * @param rotation Camera rotation in degrees.
     * @param fieldOfView Vertical field of view in degrees.
     */
    CameraConfig(double width, double height, Math::Vector3D position, Math::Vector3D rotation, double fieldOfView)
        : _width(width), _height(height), _position(position), _rotation(rotation), _fieldOfView(fieldOfView) {}

    /**
     * @brief Destroys the camera configuration.
     */
    ~CameraConfig(void) = default;

public:
    /**
     * @brief Gets camera image width.
     *
     * @return Camera image width.
     */
    double getWidth(void) const
    {
        return this->_width;
    }

    /**
     * @brief Gets camera image height.
     *
     * @return Camera image height.
     */
    double getHeight(void) const
    {
        return this->_height;
    }

    /**
     * @brief Gets camera position.
     *
     * @return Camera position vector.
     */
    Math::Vector3D getPosition(void) const
    {
        return this->_position;
    }

    /**
     * @brief Gets camera rotation.
     *
     * @return Camera rotation vector.
     */
    Math::Vector3D getRotation(void) const
    {
        return this->_rotation;
    }

    /**
     * @brief Gets camera field of view.
     *
     * @return Camera field of view.
     */
    double getFieldOfView(void) const
    {
        return this->_fieldOfView;
    }

private:
    /**
     * @brief Camera image width.
     */
    double _width;

    /**
     * @brief Camera image height.
     */
    double _height;

    /**
     * @brief Camera position in world space.
     */
    Math::Vector3D _position;

    /**
     * @brief Camera rotation in degrees.
     */
    Math::Vector3D _rotation;

    /**
     * @brief Camera field of view.
     */
    double _fieldOfView;
};

}
