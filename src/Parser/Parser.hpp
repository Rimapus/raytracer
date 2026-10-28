/*
** EPITECH PROJECT, 2026
** Parser.hpp
** File description:
** Header file for the Parser
*/

#pragma once

#include "Antialiasing/AntialiasingConfig.hpp"
#include "Camera/CameraConfig.hpp"
#include "Lights/DirectionalLightConfig.hpp"
#include "Lights/PointLightConfig.hpp"
#include "Math/Vector3D.hpp"
#include "Parser/Camera/CameraConfig.hpp"
#include "Parser/Lights/ILightConfig.hpp"
#include "Parser/Lights/PointLightConfig.hpp"
#include "Parser/Primitives/APrimitiveConfig.hpp"
#include "Parser/Primitives/ConeConfig.hpp"
#include "Parser/Primitives/CylinderConfig.hpp"
#include "Parser/Primitives/IPrimitiveConfig.hpp"
#include "Parser/Primitives/PlaneConfig.hpp"
#include "Parser/Primitives/PyramidConfig.hpp"
#include "Parser/Primitives/SphereConfig.hpp"
#include "Parser/Primitives/TanglecubeConfig.hpp"
#include "Parser/Primitives/TorusConfig.hpp"
#include "Primitives/PlaneConfig.hpp"
#include "Primitives/SphereConfig.hpp"
#include "Utils/Color.hpp"
#include <functional>
#include <iostream>
#include <libconfig.h++>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace RayTracer {

class SceneConfigBuilder;

class Parser
{
public:
    /**
     * @brief Parsed scene configuration.
     */
    struct Config
    {
        /**
         * @brief Parsed camera configuration.
         */
        std::unique_ptr<CameraConfig> _cameraConfig;

        /**
         * @brief Parsed primitive configurations.
         */
        std::vector<std::unique_ptr<APrimitiveConfig>> _primitivesConfig;

        /**
         * @brief Parsed light configurations.
         */
        std::vector<std::unique_ptr<ILightConfig>> _lightsConfig;

        /**
         * @brief Ambient light multiplier.
         */
        double _ambient = 0.0;

        /**
         * @brief Diffuse light multiplier.
         */
        double _diffuse = 1.0;

        /**
         * @brief Antialiasing settings.
         */
        std::unique_ptr<AntialiasingConfig> _antialiasingConfig;
    };

public:
    /**
     * @brief Constructs a parser for a scene file.
     *
     * @param filePath Path to the configuration file.
     */
    Parser(std::string filePath);

    /**
     * @brief Destroys the parser.
     */
    ~Parser(void) = default;

public:
    /**
     * @brief Parses the whole configuration file.
     *
     * @return Parsed scene configuration.
     */
    Config parse(void);

private:
    /**
     * @brief Parses camera settings.
     */
    void parseCamera(SceneConfigBuilder &builder);

    /**
     * @brief Parses antialiasing settings.
     */
    void parseAntialiasing(SceneConfigBuilder &builder);

    /**
     * @brief Checks whether an antialiasing sample count is supported.
     *
     * @param value Sample count.
     *
     * @return True when the sample count is supported.
     */
    static bool isValidAntialiasingSampleCount(int value);

    /**
     * @brief Validates antialiasing sample count pair.
     *
     * @param lowSampleCount Low-pass sample count.
     * @param highSampleCount High-detail sample count.
     */
    static void validateAntialiasingSamples(int lowSampleCount, int highSampleCount);

private:
    /**
     * @brief Parses primitive settings.
     */
    void parsePrimitives(SceneConfigBuilder &builder);

    /**
     * @brief Applies optional transformation settings to a primitive configuration.
     *
     * @param primitiveConfig Primitive configuration to update.
     * @param setting Primitive setting node containing transformation entries.
     */
    static void applyPrimitiveTransformations(APrimitiveConfig &primitiveConfig, const libconfig::Setting &setting);

    /**
     * @brief Parses one sphere primitive setting.
     *
     * @param setting Primitive setting node.
     *
     * @return Parsed sphere primitive configuration.
     */
    static std::unique_ptr<APrimitiveConfig> parseSphere(const libconfig::Setting &setting);

    /**
     * @brief Parses one cylinder primitive setting.
     *
     * @param setting Primitive setting node.
     *
     * @return Parsed cylinder primitive configuration.
     */
    static std::unique_ptr<APrimitiveConfig> parseCylinder(const libconfig::Setting &setting);

    /**
     * @brief Parses one cone primitive setting.
     *
     * @param setting Primitive setting node.
     *
     * @return Parsed cone primitive configuration.
     */
    static std::unique_ptr<APrimitiveConfig> parseCone(const libconfig::Setting &setting);

    /**
     * @brief Parses one plane primitive setting.
     *
     * @param setting Primitive setting node.
     *
     * @return Parsed plane primitive configuration.
     */
    static std::unique_ptr<APrimitiveConfig> parsePlane(const libconfig::Setting &setting);

    /**
     * @brief Parses one torus primitive setting.
     *
     * @param setting Primitive setting node.
     *
     * @return Parsed torus primitive configuration.
     */
    static std::unique_ptr<APrimitiveConfig> parseTorus(const libconfig::Setting &setting);

    /**
     * @brief Parses one pyramid primitive setting.
     *
     * @param setting Primitive setting node.
     *
     * @return Parsed pyramid primitive configuration.
     */
    static std::unique_ptr<APrimitiveConfig> parsePyramid(const libconfig::Setting &setting);

    /**
     * @brief Parses one tanglecube primitive setting.
     *
     * @param setting Primitive setting node.
     *
     * @return Parsed tanglecube primitive configuration.
     */
    static std::unique_ptr<APrimitiveConfig> parseTanglecube(const libconfig::Setting &setting);

private:
    /**
     * @brief Parses light settings.
     */
    void parseLights(SceneConfigBuilder &builder);

    /**
     * @brief Parses one point light setting.
     *
     * @param setting Light setting node.
     *
     * @return Parsed point light configuration.
     */
    static std::unique_ptr<ILightConfig> parsePointLight(const libconfig::Setting &setting);

    /**
     * @brief Parses one directional light setting.
     *
     * @param setting Light setting node.
     *
     * @return Parsed directional light configuration.
     */
    static std::unique_ptr<ILightConfig> parseDirectionalLight(const libconfig::Setting &setting);

private:
    /**
     * @brief Primitive parsers mapped by configuration key.
     */
    static const std::unordered_map<std::string, std::function<std::unique_ptr<APrimitiveConfig>(const libconfig::Setting &)>> _primitiveParsers;

    /**
     * @brief Light parsers mapped by configuration key.
     */
    static const std::unordered_map<std::string, std::function<std::unique_ptr<ILightConfig>(const libconfig::Setting &)>> _lightParsers;

private:
    /**
     * @brief Path to the configuration file.
     */
    std::string _filePath;

    /**
     * @brief Raw libconfig parser state.
     */
    libconfig::Config _config;
};

}
