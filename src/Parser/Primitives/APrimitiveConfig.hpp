/*
** EPITECH PROJECT, 2026
** APrimitiveConfig.hpp
** File description:
** Header file for the APrimitiveConfig
*/

#pragma once

#include "IPrimitiveConfig.hpp"
#include "Math/Vector3D.hpp"
#include <optional>

namespace RayTracer {

class APrimitiveConfig : public IPrimitiveConfig
{
public:
    /**
     * @brief Constructs a default primitive configuration.
     */
    APrimitiveConfig(void) = default;

    /**
     * @brief Destroys the primitive configuration base.
     */
    ~APrimitiveConfig(void) override = default;

public:
    /**
     * @brief Sets optional translation for the primitive.
     *
     * @param value Translation vector.
     */
    void setTranslation(Math::Vector3D value)
    {
        this->_translation = value;
    }

    /**
     * @brief Gets optional translation for the primitive.
     *
     * @return Optional translation vector.
     */
    std::optional<Math::Vector3D> getTranslation(void) const
    {
        return this->_translation;
    }

    /**
     * @brief Sets optional rotation for the primitive.
     *
     * @param value Rotation vector.
     */
    void setRotation(Math::Vector3D value)
    {
        this->_rotation = value;
    }

    /**
     * @brief Gets optional rotation for the primitive.
     *
     * @return Optional rotation vector.
     */
    std::optional<Math::Vector3D> getRotation(void) const
    {
        return this->_rotation;
    }

    /**
     * @brief Sets specular factor in [0, 1].
     */
    void setSpecular(double value)
    {
        this->_specular = value;
    }

    /**
     * @brief Gets specular factor.
     */
    double getSpecular(void) const
    {
        return this->_specular;
    }

protected:
    /**
     * @brief Optional primitive translation.
     */
    std::optional<Math::Vector3D> _translation = std::nullopt;

    /**
     * @brief Optional primitive rotation.
     */
    std::optional<Math::Vector3D> _rotation = std::nullopt;

    /**
     * @brief Specular factor in [0, 1]. 0 = diffuse only, 1 = full mirror.
     */
    double _specular = 0.0;
};

}
