/*
** EPITECH PROJECT, 2026
** Antialiasing.cpp
** File description:
** Antialiasing implementation
*/

#include "Antialiasing.hpp"

namespace RayTracer {

/**
 * @brief Adds a color to an accumulator.
 *
 * @param accumulator Accumulator to update.
 * @param color Color to add.
 */
void Antialiasing::addColor(ColorAccumulator &accumulator, const Color &color)
{
    accumulator._red += static_cast<double>(color.getRed());
    accumulator._green += static_cast<double>(color.getGreen());
    accumulator._blue += static_cast<double>(color.getBlue());
}

/**
 * @brief Converts an accumulator to a color average.
 *
 * @param accumulator Accumulated color channels.
 * @param sampleCount Number of accumulated samples.
 *
 * @return Averaged color.
 */
Color Antialiasing::accumulatorToColor(const ColorAccumulator &accumulator, double sampleCount)
{
    return Color(
        static_cast<std::uint8_t>(std::clamp(accumulator._red / sampleCount, 0.0, 255.0)),
        static_cast<std::uint8_t>(std::clamp(accumulator._green / sampleCount, 0.0, 255.0)),
        static_cast<std::uint8_t>(std::clamp(accumulator._blue / sampleCount, 0.0, 255.0)));
}

/**
 * @brief Computes RGB Euclidean distance between two colors.
 *
 * @param left First color.
 * @param right Second color.
 *
 * @return Color distance.
 */
double Antialiasing::colorDistance(const Color &left, const Color &right)
{
    const double red = static_cast<double>(left.getRed()) - static_cast<double>(right.getRed());
    const double green = static_cast<double>(left.getGreen()) - static_cast<double>(right.getGreen());
    const double blue = static_cast<double>(left.getBlue()) - static_cast<double>(right.getBlue());

    return std::sqrt(red * red + green * green + blue * blue);
}

/**
 * @brief Computes the maximum pairwise color distance in a color array.
 *
 * @param colors Color samples.
 * @param count Number of samples.
 *
 * @return Maximum pairwise distance.
 */
double Antialiasing::maxColorDistance(const Color *colors, std::size_t count)
{
    double maxDistance = 0.0;

    for (std::size_t i = 0; i < count; ++i) {
        for (std::size_t j = i + 1; j < count; ++j) {
            maxDistance = std::max(maxDistance, Antialiasing::colorDistance(colors[i], colors[j]));
        }
    }
    return maxDistance;
}

/**
 * @brief Clamps a sample offset to the pixel.
 *
 * @param value Offset value.
 *
 * @return Clamped offset.
 */
double Antialiasing::clampOffset(double value)
{
    return std::clamp(value, 0.0, 1.0);
}

/**
 * @brief Computes one deterministic sub-pixel offset.
 *
 * @param sampleIndex Sample index.
 * @param sampleCount Total sample count.
 * @param offsetX Output horizontal offset.
 * @param offsetY Output vertical offset.
 */
void Antialiasing::computeSampleOffset(int sampleIndex, int sampleCount, double &offsetX, double &offsetY)
{
    const double goldenAngle = 2.399963229728653;
    const double radius = std::sqrt((static_cast<double>(sampleIndex) + 0.5) / static_cast<double>(sampleCount)) * 0.5;
    const double angle = static_cast<double>(sampleIndex) * goldenAngle;

    offsetX = Antialiasing::clampOffset(0.5 + std::cos(angle) * radius);
    offsetY = Antialiasing::clampOffset(0.5 + std::sin(angle) * radius);
}

/**
 * @brief Samples a pixel with a regular square grid.
 *
 * @param sampler Sub-pixel sampler.
 * @param sampleCount Number of samples per axis.
 *
 * @return Averaged color.
 */
Color Antialiasing::sampleGrid(const std::function<Color(double, double)> &sampler, int sampleCount) const
{
    return this->sampleRegularGrid(sampler, sampleCount);
}

/**
 * @brief Samples a regular grid with exactly sampleCount entries.
 *
 * @param sampler Sub-pixel sampler.
 * @param sampleCount Total sample count.
 *
 * @return Averaged color.
 */
Color Antialiasing::sampleRegularGrid(const std::function<Color(double, double)> &sampler, int sampleCount) const
{
    ColorAccumulator accumulator;

    for (int sampleIndex = 0; sampleIndex < sampleCount; ++sampleIndex) {
        double offsetX = 0.5;
        double offsetY = 0.5;

        Antialiasing::computeSampleOffset(sampleIndex, sampleCount, offsetX, offsetY);
        Antialiasing::addColor(accumulator, sampler(offsetX, offsetY));
    }
    return Antialiasing::accumulatorToColor(accumulator, static_cast<double>(sampleCount));
}

/**
 * @brief Samples a pixel adaptively based on low-pass color contrast.
 *
 * @param sampler Sub-pixel sampler.
 *
 * @return Antialiased color.
 */
Color Antialiasing::sampleAdaptive(const std::function<Color(double, double)> &sampler) const
{
    if (!this->_enabled) {
        return sampler(0.5, 0.5);
    }

    std::vector<Color> lowSamples;

    lowSamples.reserve(static_cast<std::size_t>(this->_lowSampleCount));
    for (int sampleIndex = 0; sampleIndex < this->_lowSampleCount; ++sampleIndex) {
        double offsetX = 0.5;
        double offsetY = 0.5;

        Antialiasing::computeSampleOffset(sampleIndex, this->_lowSampleCount, offsetX, offsetY);
        lowSamples.push_back(sampler(offsetX, offsetY));
    }

    if (Antialiasing::maxColorDistance(lowSamples.data(), lowSamples.size()) > AA_ADAPTIVE_THRESHOLD) {
        return this->sampleGrid(sampler, this->_highSampleCount);
    }

    ColorAccumulator accumulator;
    for (const Color &color : lowSamples) {
        Antialiasing::addColor(accumulator, color);
    }
    return Antialiasing::accumulatorToColor(accumulator, static_cast<double>(lowSamples.size()));
}

}
