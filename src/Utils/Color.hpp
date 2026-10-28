/*
** EPITECH PROJECT, 2026
** Color.hpp
** File description:
** Header file for the Color
*/

#pragma once

#include <algorithm>
#include <cstdint>

namespace RayTracer {

class Color
{
public:
    /**
     * @brief Constructs a default color.
     */
    Color(void) = default;

    /**
     * @brief Constructs a color from RGB channels.
     *
     * @param red Red channel value.
     * @param green Green channel value.
     * @param blue Blue channel value.
     */
    Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
        : _red(red), _green(green), _blue(blue) {}

    /**
     * @brief Destroys the color.
     */
    ~Color(void) = default;

    /**
     * @brief Gets the red channel.
     *
     * @return Red channel value.
     */
    std::uint8_t getRed(void) const
    {
        return this->_red;
    }

    /**
     * @brief Gets the green channel.
     *
     * @return Green channel value.
     */
    std::uint8_t getGreen(void) const
    {
        return this->_green;
    }

    /**
     * @brief Gets the blue channel.
     *
     * @return Blue channel value.
     */
    std::uint8_t getBlue(void) const
    {
        return this->_blue;
    }

    /**
     * @brief Sets the red channel.
     *
     * @param value New red channel value.
     */
    void setRed(std::uint8_t value)
    {
        this->_red = value;
    }

    /**
     * @brief Sets the green channel.
     *
     * @param value New green channel value.
     */
    void setGreen(std::uint8_t value)
    {
        this->_green = value;
    }

    /**
     * @brief Sets the blue channel.
     *
     * @param value New blue channel value.
     */
    void setBlue(std::uint8_t value)
    {
        this->_blue = value;
    }

public:
    /**
     * @brief Multiplies all channels by a scalar.
     *
     * @param value Scalar multiplier.
     *
     * @return Scaled color.
     */
    Color operator*(double value) const
    {
        const double r = static_cast<double>(this->_red) * value;
        const double g = static_cast<double>(this->_green) * value;
        const double b = static_cast<double>(this->_blue) * value;

        return Color(
            static_cast<std::uint8_t>(std::clamp(r, 0.0, 255.0)),
            static_cast<std::uint8_t>(std::clamp(g, 0.0, 255.0)),
            static_cast<std::uint8_t>(std::clamp(b, 0.0, 255.0)));
    }

    /**
     * @brief Multiplies channels component-wise, normalized to [0, 1].
     *
     * @param other Color to modulate by (treated as [0, 255] gain per channel).
     *
     * @return Modulated color.
     */
    Color operator*(const Color &other) const
    {
        const double r = static_cast<double>(this->_red) * (static_cast<double>(other._red) / 255.0);
        const double g = static_cast<double>(this->_green) * (static_cast<double>(other._green) / 255.0);
        const double b = static_cast<double>(this->_blue) * (static_cast<double>(other._blue) / 255.0);

        return Color(
            static_cast<std::uint8_t>(std::clamp(r, 0.0, 255.0)),
            static_cast<std::uint8_t>(std::clamp(g, 0.0, 255.0)),
            static_cast<std::uint8_t>(std::clamp(b, 0.0, 255.0)));
    }

    /**
     * @brief Adds another color component-wise.
     *
     * @param other Color to add.
     *
     * @return Sum color.
     */
    Color operator+(const Color &other) const
    {
        const int r = static_cast<int>(this->_red) + static_cast<int>(other._red);
        const int g = static_cast<int>(this->_green) + static_cast<int>(other._green);
        const int b = static_cast<int>(this->_blue) + static_cast<int>(other._blue);

        return Color(
            static_cast<std::uint8_t>(std::clamp(r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(b, 0, 255)));
    }

private:
    /**
     * @brief Red channel value.
     */
    std::uint8_t _red;

    /**
     * @brief Green channel value.
     */
    std::uint8_t _green;

    /**
     * @brief Blue channel value.
     */
    std::uint8_t _blue;
};

}
