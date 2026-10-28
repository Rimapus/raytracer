/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** Image.hpp
*/

#pragma once
#include "Utils/Color.hpp"
#include <vector>

namespace RayTracer {

class Image
{
public:
    /**
     * @brief Constructs an image with given dimensions.
     *
     * @param width Image width in pixels.
     * @param height Image height in pixels.
     */
    Image(int width, int height)
        : _pixels(width * height), _width(width), _height(height) {}

    /**
     * @brief Destroys the image.
     */
    ~Image(void) = default;

    std::vector<Color> _pixels;
    int _width;
    int _height;
};

}
