/*
** EPITECH PROJECT, 2026
** LightFactory.hpp
** File description:
** Factory helper for runtime light creation
*/

#pragma once

#include "Lights/DirectionalLight.hpp"
#include "Lights/PointLight.hpp"
#include "Math/Transform.hpp"
#include "Parser/Lights/DirectionalLightConfig.hpp"
#include "Parser/Lights/ILightConfig.hpp"
#include "Parser/Lights/PointLightConfig.hpp"
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

namespace RayTracer {

/**
 * @brief Factory pattern used to convert parsed light configs into runtime lights.
 */
class LightFactory
{
public:
    /**
     * @brief Creates a runtime light instance from a parsed light configuration.
     */
    static std::unique_ptr<ILight> create(const ILightConfig &config, std::size_t index);
};

}
