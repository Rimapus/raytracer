/*
** EPITECH PROJECT, 2026
** Parser.cpp
** File description:
** Main file for the Parser
*/

#include "Parser.hpp"
#include "SceneConfigBuilder.hpp"
#include <algorithm>
#include <cstdint>

namespace RayTracer {

/**
 * @brief Parsers used for each primitive section key.
 */
const std::unordered_map<std::string, std::function<std::unique_ptr<APrimitiveConfig>(const libconfig::Setting &)>> Parser::_primitiveParsers = {
    {"spheres",     Parser::parseSphere    },
    {"planes",      Parser::parsePlane     },
    {"cylinders",   Parser::parseCylinder  },
    {"cones",       Parser::parseCone      },
    {"toruses",     Parser::parseTorus     },
    {"pyramids",    Parser::parsePyramid   },
    {"tanglecubes", Parser::parseTanglecube},
};

/**
 * @brief Parsers used for each light section key.
 */
const std::unordered_map<std::string, std::function<std::unique_ptr<ILightConfig>(const libconfig::Setting &)>> Parser::_lightParsers = {
    {"point",       Parser::parsePointLight      },
    {"directional", Parser::parseDirectionalLight},
};

/**
 * @brief Constructs a parser for a configuration file.
 *
 * @param filePath Path to the configuration file.
 */
Parser::Parser(std::string filePath)
    : _filePath(filePath)
{
    try {
        this->_config.readFile(filePath.c_str());

    } catch (const libconfig::FileIOException &) {
        throw std::runtime_error("Error while reading file '" + filePath + "'");
    } catch (const libconfig::ParseException &error) {
        throw std::runtime_error(std::string("Parse error at ") + error.getFile() + ":" + std::to_string(error.getLine()) + " = " + error.getError());
    }
};

/**
 * @brief Parses the full scene configuration.
 *
 * @return Parsed scene configuration.
 */
Parser::Config Parser::parse(void)
{
    SceneConfigBuilder builder;

    this->parseCamera(builder);
    this->parseAntialiasing(builder);
    this->parsePrimitives(builder);
    this->parseLights(builder);

    return std::move(builder).build();
}

/**
 * @brief Checks whether an antialiasing sample count is supported.
 *
 * @param value Sample count.
 *
 * @return True when the sample count is supported.
 */
bool Parser::isValidAntialiasingSampleCount(int value)
{
    return value == 2 || value == 4 || value == 8 || value == 16;
}

/**
 * @brief Validates antialiasing sample count pair.
 *
 * @param lowSampleCount Low-pass sample count.
 * @param highSampleCount High-detail sample count.
 */
void Parser::validateAntialiasingSamples(int lowSampleCount, int highSampleCount)
{
    if (!Parser::isValidAntialiasingSampleCount(lowSampleCount) ||
        !Parser::isValidAntialiasingSampleCount(highSampleCount)) {
        throw std::runtime_error("Antialiasing sample counts must be 2, 4, 8 or 16");
    }
    if (highSampleCount <= lowSampleCount) {
        throw std::runtime_error("Antialiasing high sample count must be greater than low sample count");
    }
}

/**
 * @brief Parses the camera section.
 */
void Parser::parseCamera(SceneConfigBuilder &builder)
{
    if (!this->_config.exists("camera")) {
        throw std::runtime_error("Setting 'camera' is not present in configuration file");
    }

    const libconfig::Setting &camera = this->_config.lookup("camera");
    int width, height, x, y, z, rotationX, rotationY, rotationZ;
    float fieldOfView;
    try {
        if (!camera["resolution"].lookupValue("width", width) ||
            !camera["resolution"].lookupValue("height", height) ||
            !camera["position"].lookupValue("x", x) ||
            !camera["position"].lookupValue("y", y) ||
            !camera["position"].lookupValue("z", z) ||
            !camera["rotation"].lookupValue("x", rotationX) ||
            !camera["rotation"].lookupValue("y", rotationY) ||
            !camera["rotation"].lookupValue("z", rotationZ) ||
            !camera.lookupValue("fieldOfView", fieldOfView)) {
            throw std::runtime_error("Could not parse camera settings");
        }
    } catch (const libconfig::SettingNotFoundException &error) {
        throw std::runtime_error(std::string("Could not parse camera settings at ") + error.getPath());
    }

    builder.setCamera(std::make_unique<CameraConfig>(
        width, height,
        Math::Vector3D(x, y, z),
        Math::Vector3D(rotationX, rotationY, rotationZ),
        fieldOfView));
}

/**
 * @brief Parses antialiasing settings.
 */
void Parser::parseAntialiasing(SceneConfigBuilder &builder)
{
    bool enabled = true;
    int lowSampleCount = AA_DEFAULT_LOW_SAMPLE_COUNT;
    int highSampleCount = AA_DEFAULT_HIGH_SAMPLE_COUNT;

    if (!this->_config.exists("antialiasing")) {
        builder.setAntialiasing(std::make_unique<AntialiasingConfig>());
        return;
    }

    const libconfig::Setting &antialiasing = this->_config.lookup("antialiasing");

    try {
        if (antialiasing.exists("enabled") &&
            !antialiasing.lookupValue("enabled", enabled)) {
            throw std::runtime_error("Could not parse antialiasing enabled setting");
        }
        if (antialiasing.exists("low") &&
            !antialiasing.lookupValue("low", lowSampleCount)) {
            throw std::runtime_error("Could not parse antialiasing low sample count");
        }
        if (antialiasing.exists("high") &&
            !antialiasing.lookupValue("high", highSampleCount)) {
            throw std::runtime_error("Could not parse antialiasing high sample count");
        }
    } catch (const libconfig::SettingNotFoundException &error) {
        throw std::runtime_error(std::string("Could not parse antialiasing settings at ") + error.getPath());
    }

    Parser::validateAntialiasingSamples(lowSampleCount, highSampleCount);
    builder.setAntialiasing(std::make_unique<AntialiasingConfig>(enabled, lowSampleCount, highSampleCount));
}

/**
 * @brief Parses all primitive sections.
 */
void Parser::parsePrimitives(SceneConfigBuilder &builder)
{
    if (!this->_config.exists("primitives")) {
        return;
    }

    const libconfig::Setting &primitives = this->_config.lookup("primitives");
    for (const auto &primitiveParser : this->_primitiveParsers) {
        if (!primitives.exists(primitiveParser.first.c_str())) {
            continue;
        }

        const libconfig::Setting &primitivesSetting = primitives[primitiveParser.first.c_str()];
        for (int i = 0; i < primitivesSetting.getLength(); i++) {
            const libconfig::Setting &primitiveSetting = primitivesSetting[i];

            builder.addPrimitive(primitiveParser.second(primitiveSetting));
        }
    }
}

/**
 * @brief Applies optional translation and rotation settings to a primitive.
 *
 * @param primitiveConfig Primitive configuration to update.
 * @param setting Primitive node containing transformation values.
 */
void Parser::applyPrimitiveTransformations(APrimitiveConfig &primitiveConfig, const libconfig::Setting &setting)
{
    if (setting.exists("translation")) {
        int translationX, translationY, translationZ;

        if (!setting["translation"].lookupValue("x", translationX) ||
            !setting["translation"].lookupValue("y", translationY) ||
            !setting["translation"].lookupValue("z", translationZ)) {
            throw std::runtime_error("Could not parse translation settings");
        }
        primitiveConfig.setTranslation(Math::Vector3D(translationX, translationY, translationZ));
    }

    if (setting.exists("rotation")) {
        int rotationX, rotationY, rotationZ;

        if (!setting["rotation"].lookupValue("x", rotationX) ||
            !setting["rotation"].lookupValue("y", rotationY) ||
            !setting["rotation"].lookupValue("z", rotationZ)) {
            throw std::runtime_error("Could not parse rotation settings");
        }
        primitiveConfig.setRotation(Math::Vector3D(rotationX, rotationY, rotationZ));
    }

    if (setting.exists("specular")) {
        double specular = 0.0;
        if (!setting.lookupValue("specular", specular)) {
            throw std::runtime_error("Could not parse specular setting");
        }
        if (specular < 0.0) {
            specular = 0.0;
        }
        if (specular > 1.0) {
            specular = 1.0;
        }
        primitiveConfig.setSpecular(specular);
    }
}

/**
 * @brief Parses one sphere primitive setting.
 *
 * @param setting Primitive setting node.
 *
 * @return Parsed sphere primitive configuration.
 */
std::unique_ptr<APrimitiveConfig> Parser::parseSphere(const libconfig::Setting &setting)
{
    int x, y, z, radius, red, green, blue;

    try {
        if (
            !setting.lookupValue("x", x) ||
            !setting.lookupValue("y", y) ||
            !setting.lookupValue("z", z) ||
            !setting.lookupValue("radius", radius) ||
            !setting["color"].lookupValue("r", red) ||
            !setting["color"].lookupValue("g", green) ||
            !setting["color"].lookupValue("b", blue)) {
            throw std::runtime_error("Could not parse sphere settings");
        }
    } catch (const libconfig::SettingNotFoundException &error) {
        throw std::runtime_error(std::string("Could not parse sphere settings at ") + error.getPath());
    }

    std::unique_ptr<SphereConfig> sphereConfig = std::make_unique<SphereConfig>(
        Math::Vector3D(x, y, z),
        radius,
        Color(red, green, blue));

    Parser::applyPrimitiveTransformations(*sphereConfig, setting);

    return sphereConfig;
}

/**
 * @brief Parses one cylinder primitive setting.
 *
 * @param setting Primitive setting node.
 *
 * @return Parsed cylinder primitive configuration.
 */
std::unique_ptr<APrimitiveConfig> Parser::parseCylinder(const libconfig::Setting &setting)
{
    int x, y, z, radius, height, red, green, blue;
    bool limited = true;

    try {
        if (
            !setting.lookupValue("x", x) ||
            !setting.lookupValue("y", y) ||
            !setting.lookupValue("z", z) ||
            !setting.lookupValue("radius", radius) ||
            !setting.lookupValue("height", height) ||
            !setting["color"].lookupValue("r", red) ||
            !setting["color"].lookupValue("g", green) ||
            !setting["color"].lookupValue("b", blue)) {
            throw std::runtime_error("Could not parse cylinder settings");
        }
        if (setting.exists("limited") && !setting.lookupValue("limited", limited)) {
            throw std::runtime_error("Could not parse cylinder limited flag");
        }
    } catch (const libconfig::SettingNotFoundException &error) {
        throw std::runtime_error(std::string("Could not parse cylinder settings at ") + error.getPath());
    }

    std::unique_ptr<CylinderConfig> cylinderConfig = std::make_unique<CylinderConfig>(
        Math::Vector3D(x, y, z),
        radius,
        height,
        limited,
        Color(red, green, blue));

    Parser::applyPrimitiveTransformations(*cylinderConfig, setting);

    return cylinderConfig;
}

/**
 * @brief Parses one cone primitive setting.
 *
 * @param setting Primitive setting node.
 *
 * @return Parsed cone primitive configuration.
 */
std::unique_ptr<APrimitiveConfig> Parser::parseCone(const libconfig::Setting &setting)
{
    int x, y, z, radius, height, red, green, blue;
    bool limited = true;

    try {
        if (
            !setting.lookupValue("x", x) ||
            !setting.lookupValue("y", y) ||
            !setting.lookupValue("z", z) ||
            !setting.lookupValue("radius", radius) ||
            !setting.lookupValue("height", height) ||
            !setting["color"].lookupValue("r", red) ||
            !setting["color"].lookupValue("g", green) ||
            !setting["color"].lookupValue("b", blue)) {
            throw std::runtime_error("Could not parse cone settings");
        }
        if (setting.exists("limited") && !setting.lookupValue("limited", limited)) {
            throw std::runtime_error("Could not parse cone limited flag");
        }
    } catch (const libconfig::SettingNotFoundException &error) {
        throw std::runtime_error(std::string("Could not parse cone settings at ") + error.getPath());
    }

    std::unique_ptr<ConeConfig> coneConfig = std::make_unique<ConeConfig>(
        Math::Vector3D(x, y, z),
        radius,
        height,
        limited,
        Color(red, green, blue));

    Parser::applyPrimitiveTransformations(*coneConfig, setting);

    return coneConfig;
}

/**
 * @brief Parses one torus primitive setting.
 *
 * @param setting Primitive setting node.
 *
 * @return Parsed torus primitive configuration.
 */
std::unique_ptr<APrimitiveConfig> Parser::parseTorus(const libconfig::Setting &setting)
{
    int x, y, z, majorRadius, minorRadius, red, green, blue;

    try {
        if (
            !setting.lookupValue("x", x) ||
            !setting.lookupValue("y", y) ||
            !setting.lookupValue("z", z) ||
            !setting.lookupValue("majorRadius", majorRadius) ||
            !setting.lookupValue("minorRadius", minorRadius) ||
            !setting["color"].lookupValue("r", red) ||
            !setting["color"].lookupValue("g", green) ||
            !setting["color"].lookupValue("b", blue)) {
            throw std::runtime_error("Could not parse torus settings");
        }
    } catch (const libconfig::SettingNotFoundException &error) {
        throw std::runtime_error(std::string("Could not parse torus settings at ") + error.getPath());
    }

    std::unique_ptr<TorusConfig> torusConfig = std::make_unique<TorusConfig>(
        Math::Vector3D(x, y, z),
        majorRadius,
        minorRadius,
        Color(red, green, blue));

    Parser::applyPrimitiveTransformations(*torusConfig, setting);

    return torusConfig;
}

/**
 * @brief Parses one plane primitive setting.
 *
 * @param setting Primitive setting node.
 *
 * @return Parsed plane primitive configuration.
 */
std::unique_ptr<APrimitiveConfig> Parser::parsePlane(const libconfig::Setting &setting)
{
    std::string axis;
    int position, red, green, blue;

    try {
        if (!setting.lookupValue("axis", axis) ||
            !setting.lookupValue("position", position) ||
            !setting["color"].lookupValue("r", red) ||
            !setting["color"].lookupValue("g", green) ||
            !setting["color"].lookupValue("b", blue)) {
            throw std::runtime_error("Could not parse plane settings");
        }
    } catch (const libconfig::SettingNotFoundException &error) {
        throw std::runtime_error(std::string("Could not parse plane settings at ") + error.getPath());
    }

    PlaneConfig::PlaneAxis resolvedAxis;
    if (axis == "X") {
        resolvedAxis = PlaneConfig::PlaneAxis::X;
    } else if (axis == "Y") {
        resolvedAxis = PlaneConfig::PlaneAxis::Y;
    } else if (axis == "Z") {
        resolvedAxis = PlaneConfig::PlaneAxis::Z;
    } else {
        throw std::runtime_error("Got wrong plane axis");
    }

    std::unique_ptr<PlaneConfig> planeConfig = std::make_unique<PlaneConfig>(
        resolvedAxis,
        position,
        Color(red, green, blue));

    Parser::applyPrimitiveTransformations(*planeConfig, setting);

    return planeConfig;
}

/**
 * @brief Parses one pyramid primitive setting.
 *
 * @param setting Primitive setting node.
 *
 * @return Parsed pyramid primitive configuration.
 */
std::unique_ptr<APrimitiveConfig> Parser::parsePyramid(const libconfig::Setting &setting)
{
    int x, y, z, size, height, red, green, blue;

    try {
        if (!setting.lookupValue("x", x) ||
            !setting.lookupValue("y", y) ||
            !setting.lookupValue("z", z) ||
            !setting.lookupValue("size", size) ||
            !setting.lookupValue("height", height) ||
            !setting["color"].lookupValue("r", red) ||
            !setting["color"].lookupValue("g", green) ||
            !setting["color"].lookupValue("b", blue)) {
            throw std::runtime_error("Could not parse pyramid settings");
        }
    } catch (const libconfig::SettingNotFoundException &error) {
        throw std::runtime_error(std::string("Could not parse pyramid settings at ") + error.getPath());
    }

    std::unique_ptr<PyramidConfig> pyramidConfig = std::make_unique<PyramidConfig>(
        Math::Vector3D(x, y, z),
        size,
        height,
        Color(red, green, blue));

    Parser::applyPrimitiveTransformations(*pyramidConfig, setting);

    return pyramidConfig;
}

/**
 * @brief Parses one tanglecube primitive setting.
 *
 * @param setting Primitive setting node.
 *
 * @return Parsed tanglecube primitive configuration.
 */
std::unique_ptr<APrimitiveConfig> Parser::parseTanglecube(const libconfig::Setting &setting)
{
    int x, y, z, scale, red, green, blue;

    try {
        if (!setting.lookupValue("x", x) ||
            !setting.lookupValue("y", y) ||
            !setting.lookupValue("z", z) ||
            !setting.lookupValue("scale", scale) ||
            !setting["color"].lookupValue("r", red) ||
            !setting["color"].lookupValue("g", green) ||
            !setting["color"].lookupValue("b", blue)) {
            throw std::runtime_error("Could not parse tanglecube settings");
        }
    } catch (const libconfig::SettingNotFoundException &error) {
        throw std::runtime_error(std::string("Could not parse tanglecube settings at ") + error.getPath());
    }

    std::unique_ptr<TanglecubeConfig> tanglecubeConfig = std::make_unique<TanglecubeConfig>(
        Math::Vector3D(x, y, z),
        scale,
        Color(red, green, blue));

    Parser::applyPrimitiveTransformations(*tanglecubeConfig, setting);

    return tanglecubeConfig;
}

/**
 * @brief Parses all light sections.
 */
void Parser::parseLights(SceneConfigBuilder &builder)
{
    if (!this->_config.exists("lights")) {
        return;
    }

    const libconfig::Setting &lights = this->_config.lookup("lights");
    double ambient = 0.0;
    double diffuse = 1.0;

    if (lights.exists("ambient") && lights.lookupValue("ambient", ambient)) {
        builder.setAmbient(ambient);
    }
    if (lights.exists("diffuse") && lights.lookupValue("diffuse", diffuse)) {
        builder.setDiffuse(diffuse);
    }
    for (const auto &lightParser : this->_lightParsers) {
        if (!lights.exists(lightParser.first.c_str())) {
            continue;
        }

        const libconfig::Setting &lightsSetting = lights[lightParser.first.c_str()];
        for (int i = 0; i < lightsSetting.getLength(); i++) {
            const libconfig::Setting &lightSetting = lightsSetting[i];

            builder.addLight(lightParser.second(lightSetting));
        }
    }
}

/**
 * @brief Parses one point light setting.
 *
 * @param setting Light setting node.
 *
 * @return Parsed point light configuration.
 */
std::unique_ptr<ILightConfig> Parser::parsePointLight(const libconfig::Setting &setting)
{
    int x, y, z;
    int red = 255, green = 255, blue = 255;

    try {
        if (
            !setting.lookupValue("x", x) ||
            !setting.lookupValue("y", y) ||
            !setting.lookupValue("z", z)) {
            throw std::runtime_error("Could not parse point light settings");
        }
        if (setting.exists("color")) {
            if (!setting["color"].lookupValue("r", red) ||
                !setting["color"].lookupValue("g", green) ||
                !setting["color"].lookupValue("b", blue)) {
                throw std::runtime_error("Could not parse point light color");
            }
        }
    } catch (const libconfig::SettingNotFoundException &error) {
        throw std::runtime_error(std::string("Could not parse point light settings at ") + error.getPath());
    }

    return std::make_unique<PointLightConfig>(
        Math::Vector3D(x, y, z),
        Color(static_cast<std::uint8_t>(std::clamp(red, 0, 255)),
              static_cast<std::uint8_t>(std::clamp(green, 0, 255)),
              static_cast<std::uint8_t>(std::clamp(blue, 0, 255))));
}

/**
 * @brief Parses one directional light setting.
 *
 * @param setting Light setting node.
 *
 * @return Parsed directional light configuration.
 */
std::unique_ptr<ILightConfig> Parser::parseDirectionalLight(const libconfig::Setting &setting)
{
    int directionX, directionY, directionZ;
    int red = 255, green = 255, blue = 255;

    try {
        if (
            !setting["direction"].lookupValue("x", directionX) ||
            !setting["direction"].lookupValue("y", directionY) ||
            !setting["direction"].lookupValue("z", directionZ)) {
            throw std::runtime_error("Could not parse directional light settings");
        }
        if (setting.exists("color")) {
            if (!setting["color"].lookupValue("r", red) ||
                !setting["color"].lookupValue("g", green) ||
                !setting["color"].lookupValue("b", blue)) {
                throw std::runtime_error("Could not parse directional light color");
            }
        }
    } catch (const libconfig::SettingNotFoundException &error) {
        throw std::runtime_error(std::string("Could not parse directional light settings at ") + error.getPath());
    }

    return std::make_unique<DirectionalLightConfig>(
        Math::Vector3D(directionX, directionY, directionZ),
        Color(static_cast<std::uint8_t>(std::clamp(red, 0, 255)),
              static_cast<std::uint8_t>(std::clamp(green, 0, 255)),
              static_cast<std::uint8_t>(std::clamp(blue, 0, 255))));
}

}
