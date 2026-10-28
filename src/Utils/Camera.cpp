/*
** EPITECH PROJECT, 2026
** Camera.cpp
** File description:
** Main file for the Camera
*/

#include "Camera.hpp"
#include "Utils/Rectangle3D.hpp"

namespace RayTracer {
/**
 * @brief Constructs a camera and computes its screen rectangle from image settings.
 *
 * @param imageWidth Output image width in pixels.
 * @param imageHeight Output image height in pixels.
 * @param verticalFovDegrees Vertical field of view in degrees.
 */
Camera::Camera(int imageWidth, int imageHeight, double verticalFovDegrees)
    : _origin(0.0, 0.0, 0.0)
{
    const double height = this->viewportHeight(verticalFovDegrees);
    const double width = this->viewportWidth(imageWidth, imageHeight, verticalFovDegrees);

    this->_screen = Rectangle3D(
        Math::Point3D(-width / 2.0, -height / 2.0, this->focalLength()),
        Math::Vector3D(width, 0.0, 0.0),
        Math::Vector3D(0.0, height, 0.0));
}

/**
 * @brief Builds a ray through the camera screen at normalized coordinates.
 *
 * @param u Horizontal normalized coordinate.
 * @param v Vertical normalized coordinate.
 *
 * @return Ray originating from the camera toward the selected screen point.
 */
RayTracer::Ray Camera::ray(double u, double v) const
{
    Math::Point3D pixel = this->_screen.pointAt(u, v);

    return RayTracer::Ray(
        this->_origin,
        Math::Vector3D(
            pixel.getX() - this->_origin.getX(),
            pixel.getY() - this->_origin.getY(),
            pixel.getZ() - this->_origin.getZ()));
}

/**
 * @brief Returns the fixed focal length used by this camera model.
 *
 * @return Focal length value.
 */
double Camera::focalLength(void)
{
    return 1.0;
}

/**
 * @brief Computes a valid aspect ratio from image dimensions.
 *
 * @param imageWidth Image width in pixels.
 * @param imageHeight Image height in pixels.
 *
 * @return Aspect ratio, or 1.0 when dimensions are invalid.
 */
double Camera::safeAspectRatio(int imageWidth, int imageHeight)
{
    if (imageWidth <= 0 || imageHeight <= 0) {
        return 1.0;
    }
    return static_cast<double>(imageWidth) / static_cast<double>(imageHeight);
}

/**
 * @brief Clamps a vertical FOV to a valid range.
 *
 * @param verticalFovDegrees Input vertical field of view in degrees.
 *
 * @return Clamped vertical field of view.
 */
double Camera::clampedVerticalFovDegrees(double verticalFovDegrees)
{
    if (verticalFovDegrees < 1.0) {
        return 1.0;
    }
    if (verticalFovDegrees > 179.0) {
        return 179.0;
    }
    return verticalFovDegrees;
}

/**
 * @brief Computes viewport height from vertical field of view.
 *
 * @param verticalFovDegrees Vertical field of view in degrees.
 *
 * @return Viewport height.
 */
double Camera::viewportHeight(double verticalFovDegrees)
{
    const double theta = clampedVerticalFovDegrees(verticalFovDegrees) * std::acos(-1.0) / 180.0;
    return 2.0 * std::tan(theta / 2.0) * focalLength();
}

/**
 * @brief Computes viewport width from dimensions and vertical FOV.
 *
 * @param imageWidth Image width in pixels.
 * @param imageHeight Image height in pixels.
 * @param verticalFovDegrees Vertical field of view in degrees.
 *
 * @return Viewport width.
 */
double Camera::viewportWidth(int imageWidth, int imageHeight, double verticalFovDegrees)
{
    return viewportHeight(verticalFovDegrees) * safeAspectRatio(imageWidth, imageHeight);
}

}
