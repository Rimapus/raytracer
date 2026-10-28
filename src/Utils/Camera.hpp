/*
** EPITECH PROJECT, 2026
** Camera.hpp
** File description:
** Header file for the Camera
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Ray.hpp"
#include "Rectangle3D.hpp"
#include <cmath>

namespace RayTracer {

class Camera
{
public:
    /**
     * @brief Constructs a camera configured for a given image size and vertical field of view.
     *
     * @param imageWidth Output image width in pixels.
     * @param imageHeight Output image height in pixels.
     * @param verticalFovDegrees Vertical field of view in degrees.
     */
    Camera(int imageWidth = 1, int imageHeight = 1, double verticalFovDegrees = 90.0);

    /**
     * @brief Copy-constructs a camera.
     *
     * @param other Camera to copy.
     */
    Camera(const Camera &other) = default;

    /**
     * @brief Assigns camera state from another camera.
     *
     * @param other Camera to copy.
     *
     * @return Reference to this camera.
     */
    Camera &operator=(const Camera &other) = default;

    /**
     * @brief Destroys the camera.
     */
    ~Camera(void) = default;

public:
    /**
     * @brief Gets the camera origin.
     *
     * @return Camera origin point.
     */
    Math::Point3D getOrigin(void) const
    {
        return this->_origin;
    }

    /**
     * @brief Gets the camera screen rectangle.
     *
     * @return Screen rectangle in 3D space.
     */
    RayTracer::Rectangle3D getScreen(void) const
    {
        return this->_screen;
    }

    /**
     * @brief Sets the camera origin.
     *
     * @param origin New camera origin.
     */
    void setOrigin(const Math::Point3D &origin)
    {
        const Math::Vector3D delta(
            origin.getX() - this->_origin.getX(),
            origin.getY() - this->_origin.getY(),
            origin.getZ() - this->_origin.getZ());

        this->_origin = origin;
        this->_screen.setOrigin(this->_screen.getOrigin() + delta);
    }

    /**
     * @brief Sets the camera screen rectangle.
     *
     * @param screen New screen rectangle.
     */
    void setScreen(const RayTracer::Rectangle3D &screen)
    {
        this->_screen = screen;
    }

public:
    /**
     * @brief Builds a ray passing through normalized screen coordinates.
     *
     * @param u Horizontal normalized coordinate.
     * @param v Vertical normalized coordinate.
     *
     * @return Generated ray from camera origin to screen position.
     */
    RayTracer::Ray ray(double u, double v) const;

private:
    /**
     * @brief Returns the focal length used by the camera model.
     *
     * @return Camera focal length.
     */
    static double focalLength(void);

    /**
     * @brief Computes a safe aspect ratio and guards against invalid dimensions.
     *
     * @param image_width Image width in pixels.
     * @param image_height Image height in pixels.
     *
     * @return Aspect ratio value.
     */
    static double safeAspectRatio(int image_width, int image_height);

    /**
     * @brief Clamps the vertical FOV to a valid angular range.
     *
     * @param vertical_fov_degrees Input vertical field of view in degrees.
     *
     * @return Clamped vertical field of view in degrees.
     */
    static double clampedVerticalFovDegrees(double vertical_fov_degrees);

    /**
     * @brief Computes viewport height from vertical field of view.
     *
     * @param vertical_fov_degrees Vertical field of view in degrees.
     *
     * @return Viewport height.
     */
    static double viewportHeight(double vertical_fov_degrees);

    /**
     * @brief Computes viewport width from image dimensions and field of view.
     *
     * @param image_width Image width in pixels.
     * @param image_height Image height in pixels.
     * @param vertical_fov_degrees Vertical field of view in degrees.
     *
     * @return Viewport width.
     */
    static double viewportWidth(int image_width, int image_height, double vertical_fov_degrees);

private:
    /**
     * @brief Camera origin in world space.
     */
    Math::Point3D _origin;

    /**
     * @brief Camera projection screen rectangle.
     */
    RayTracer::Rectangle3D _screen;
};

}
