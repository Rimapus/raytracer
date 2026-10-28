/*
** EPITECH PROJECT, 2026
** IPrimitiveConfig.hpp
** File description:
** Header file for the IPrimitiveConfig
*/

#pragma once

namespace RayTracer {

/**
 * @brief Supported primitive configuration types.
 */
enum class PrimitiveType {
    SPHERE,
    PLANE,
    CYLINDER,
    CONE,
    TORUS,
    PYRAMID,
    TANGLECUBE,
};

class IPrimitiveConfig
{
public:
    /**
     * @brief Destroys the primitive configuration interface.
     */
    virtual ~IPrimitiveConfig(void) = default;

    /**
     * @brief Gets the primitive configuration type.
     *
     * @return Primitive configuration type.
     */
    virtual PrimitiveType getType(void) const = 0;
};

}
