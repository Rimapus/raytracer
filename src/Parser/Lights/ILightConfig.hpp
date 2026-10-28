/*
** EPITECH PROJECT, 2026
** ILightConfig.hpp
** File description:
** Header file for the ILightConfig
*/

#pragma once

namespace RayTracer {

/**
 * @brief Supported light configuration types.
 */
enum class LightType {
    POINT,
    DIRECTIONAL,
};

class ILightConfig
{
public:
    /**
     * @brief Destroys the light configuration interface.
     */
    virtual ~ILightConfig(void) = default;

    /**
     * @brief Gets the light configuration type.
     *
     * @return Light configuration type.
     */
    virtual LightType getType(void) const = 0;
};

}
