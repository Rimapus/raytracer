/*
** EPITECH PROJECT, 2026
** SceneConfigBuilder.hpp
** File description:
** Builder helper for parser scene configuration
*/

#pragma once

#include "Parser/Parser.hpp"
#include <utility>

namespace RayTracer {

/**
 * @brief Builder pattern used to assemble the parsed scene configuration step by step.
 */
class SceneConfigBuilder
{
public:
    void setCamera(std::unique_ptr<CameraConfig> camera)
    {
        this->_config._cameraConfig = std::move(camera);
    }

    void addPrimitive(std::unique_ptr<APrimitiveConfig> primitive)
    {
        this->_config._primitivesConfig.push_back(std::move(primitive));
    }

    void addLight(std::unique_ptr<ILightConfig> light)
    {
        this->_config._lightsConfig.push_back(std::move(light));
    }

    void setAmbient(double ambient)
    {
        this->_config._ambient = ambient;
    }

    void setDiffuse(double diffuse)
    {
        this->_config._diffuse = diffuse;
    }

    void setAntialiasing(std::unique_ptr<AntialiasingConfig> antialiasingConfig)
    {
        this->_config._antialiasingConfig = std::move(antialiasingConfig);
    }

    Parser::Config build(void) &&
    {
        return std::move(this->_config);
    }

private:
    Parser::Config _config;
};

}
