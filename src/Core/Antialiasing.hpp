/*
** EPITECH PROJECT, 2026
** Antialiasing.hpp
** File description:
** Header file for the Antialiasing
*/

#pragma once

#include "Parser/Antialiasing/AntialiasingConfig.hpp"
#include "Utils/Color.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <vector>

#define AA_ADAPTIVE_THRESHOLD 35.0

namespace RayTracer {

class Antialiasing
{
public:
    /**
     * @brief Constructs an antialiasing helper.
     */
    Antialiasing(void) = default;

    /**
     * @brief Constructs an antialiasing helper with explicit settings.
     *
     * @param enabled Whether antialiasing is active.
     * @param lowSampleCount Low-pass total sample count.
     * @param highSampleCount High-detail total sample count.
     */
    Antialiasing(bool enabled, int lowSampleCount, int highSampleCount)
        : _enabled(enabled), _lowSampleCount(lowSampleCount), _highSampleCount(highSampleCount) {}

    /**
     * @brief Destroys the antialiasing helper.
     */
    ~Antialiasing(void) = default;

public:
    /**
     * @brief Samples a pixel adaptively.
     *
     * @param sampler Sub-pixel sampler.
     *
     * @return Antialiased color.
     */
    Color sampleAdaptive(const std::function<Color(double, double)> &sampler) const;

private:
    /**
     * @brief Floating-point color accumulator used to avoid early channel clamping.
     */
    struct ColorAccumulator
    {
        double _red = 0.0;
        double _green = 0.0;
        double _blue = 0.0;
    };

    /**
     * @brief Samples a pixel with a regular square grid.
     *
     * @param sampler Sub-pixel sampler.
     * @param sampleCount Number of samples per axis.
     *
     * @return Averaged color.
     */
    Color sampleGrid(const std::function<Color(double, double)> &sampler, int sampleCount) const;

    /**
     * @brief Adds a color to an accumulator.
     *
     * @param accumulator Accumulator to update.
     * @param color Color to add.
     */
    static void addColor(ColorAccumulator &accumulator, const Color &color);

    /**
     * @brief Converts an accumulator to a color average.
     *
     * @param accumulator Accumulated color channels.
     * @param sampleCount Number of accumulated samples.
     *
     * @return Averaged color.
     */
    static Color accumulatorToColor(const ColorAccumulator &accumulator, double sampleCount);

    /**
     * @brief Computes RGB Euclidean distance between two colors.
     *
     * @param left First color.
     * @param right Second color.
     *
     * @return Color distance.
     */
    static double colorDistance(const Color &left, const Color &right);

    /**
     * @brief Computes the maximum pairwise color distance in a color array.
     *
     * @param colors Color samples.
     * @param count Number of samples.
     *
     * @return Maximum pairwise distance.
     */
    static double maxColorDistance(const Color *colors, std::size_t count);

    /**
     * @brief Computes one deterministic sub-pixel offset.
     *
     * @param sampleIndex Sample index.
     * @param sampleCount Total sample count.
     * @param offsetX Output horizontal offset.
     * @param offsetY Output vertical offset.
     */
    static void computeSampleOffset(int sampleIndex, int sampleCount, double &offsetX, double &offsetY);

    /**
     * @brief Clamps a sample offset to the pixel.
     *
     * @param value Offset value.
     *
     * @return Clamped offset.
     */
    static double clampOffset(double value);

    /**
     * @brief Samples a regular grid with exactly sampleCount entries.
     *
     * @param sampler Sub-pixel sampler.
     * @param sampleCount Total sample count.
     *
     * @return Averaged color.
     */
    Color sampleRegularGrid(const std::function<Color(double, double)> &sampler, int sampleCount) const;

private:
    /**
     * @brief Whether antialiasing is active.
     */
    bool _enabled = true;

    /**
     * @brief Total low-pass sample count.
     */
    int _lowSampleCount = AA_DEFAULT_LOW_SAMPLE_COUNT;

    /**
     * @brief Total high-detail sample count.
     */
    int _highSampleCount = AA_DEFAULT_HIGH_SAMPLE_COUNT;
};

}
