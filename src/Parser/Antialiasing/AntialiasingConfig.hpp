/*
** EPITECH PROJECT, 2026
** AntialiasingConfig.hpp
** File description:
** Header file for the AntialiasingConfig
*/

#pragma once

#define AA_DEFAULT_LOW_SAMPLE_COUNT 2
#define AA_DEFAULT_HIGH_SAMPLE_COUNT 4

namespace RayTracer {

class AntialiasingConfig
{
public:
    /**
     * @brief Constructs a default antialiasing configuration.
     */
    AntialiasingConfig(void) = default;

    /**
     * @brief Constructs an antialiasing configuration.
     *
     * @param enabled Whether antialiasing is active.
     * @param lowSampleCount Low-pass total sample count.
     * @param highSampleCount High-detail total sample count.
     */
    AntialiasingConfig(bool enabled, int lowSampleCount, int highSampleCount)
        : _enabled(enabled), _lowSampleCount(lowSampleCount), _highSampleCount(highSampleCount) {}

    /**
     * @brief Destroys the antialiasing configuration.
     */
    ~AntialiasingConfig(void) = default;

public:
    /**
     * @brief Gets whether antialiasing is active.
     *
     * @return True when antialiasing is active.
     */
    bool isEnabled(void) const
    {
        return this->_enabled;
    }

    /**
     * @brief Gets the low-pass sample count.
     *
     * @return Low-pass sample count.
     */
    int getLowSampleCount(void) const
    {
        return this->_lowSampleCount;
    }

    /**
     * @brief Gets the high-detail sample count.
     *
     * @return High-detail sample count.
     */
    int getHighSampleCount(void) const
    {
        return this->_highSampleCount;
    }

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
