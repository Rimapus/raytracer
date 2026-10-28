/*
** EPITECH PROJECT, 2026
** Core.hpp
** File description:
** Header file for the RayTracing Core - Main orchestrator
*/

#pragma once

#include "Antialiasing.hpp"
#include "Core/Image.hpp"
#include "Display.hpp"
#include "LightFactory.hpp"
#include "Lights/DirectionalLight.hpp"
#include "Lights/ILight.hpp"
#include "Lights/PointLight.hpp"
#include "Math/Transform.hpp"
#include "Parser/Parser.hpp"
#include "PrimitiveFactory.hpp"
#include "Primitives/Cone.hpp"
#include "Primitives/Cylinder.hpp"
#include "Primitives/Plane.hpp"
#include "Primitives/Pyramid.hpp"
#include "Primitives/Sphere.hpp"
#include "Primitives/Tanglecube.hpp"
#include "Primitives/Torus.hpp"
#include "Utils/Camera.hpp"
#include "Utils/Color.hpp"
#include <algorithm>
#include <atomic>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#define ERROR 84
#define SUCCESS 0

namespace RayTracer {

/**
 * @brief Core orchestrator for the raytracing engine.
 *
 * The Core class is the central manager that:
 * - Initializes the scene from parser configuration
 * - Manages camera and rendering
 * - Coordinates all components
 */
class Core
{
public:
    /**
     * @brief Constructs a Core instance.
     */
    Core(void)
        : _camera(nullptr), _initialized(false) {}

    /**
     * @brief Destroys the Core.
     */
    ~Core(void) = default;

public:
    /**
     * @brief Initializes the core with parsed scene configuration.
     *
     * @param config Parser configuration containing camera,
     * primitives, and lights.
     * @return 0 on success, 84 on error.
     */
    int initialize(const Parser::Config &config);

    /**
     * @brief Renders the scene.
     *
     * @return 0 on success, 84 on error.
     */
    int render(void);

    /**
     * @brief Saves the rendered image to file.
     *
     * @param filename Output filename (e.g., "output.ppm").
     * @return 0 on success, 84 on error.
     */
    int saveImage(const std::string &filename);

private:
    /**
     * @brief Initializes the camera from configuration.
     *
     * @param config Camera configuration.
     * @return 0 on success, 84 on error.
     */
    int initializeCamera(const std::unique_ptr<CameraConfig> &config);

    /**
     * @brief Initializes primitives from configuration.
     *
     * @param configs Primitive configurations.
     * @return 0 on success, 84 on error.
     */
    int initializePrimitives(const std::vector<std::unique_ptr<APrimitiveConfig>> &configs);

    /**
     * @brief Applies optional primitive transformations from parsed configuration.
     *
     * @param primitive Primitive instance to update.
     * @param config Primitive configuration containing optional transform data.
     */
    static void applyPrimitiveTransformations(IPrimitive &primitive, const APrimitiveConfig &config);

    /**
     * @brief Initializes lights from configuration.
     *
     * @param configs Light configurations.
     * @return 0 on success, 84 on error.
     */
    int initializeLights(const std::vector<std::unique_ptr<ILightConfig>> &configs);

    /**
     * @brief Computes the shaded color at a hit point.
     *
     * @param baseColor Color of the hit primitive.
     * @param hitPoint Hit point in world space.
     * @param normal Surface normal at the hit point.
     * @param viewDir Direction from hit point toward the camera.
     * @param specular Specular factor in [0, 1].
     *
     * @return Shaded pixel color.
     */
    Color shade(const Color &baseColor, const Math::Point3D &hitPoint, const Math::Vector3D &normal, const Math::Vector3D &viewDir, double specular) const;

    /**
     * @brief Traces one ray through the scene.
     *
     * @param ray Ray to trace.
     * @param depth Current recursion depth.
     *
     * @return Shaded ray color.
     */
    Color traceRay(const Ray &ray, int depth = 0) const;

    /**
     * @brief Samples one sub-pixel location.
     *
     * @param x Pixel X coordinate.
     * @param y Pixel Y coordinate.
     * @param offsetX Horizontal offset inside the pixel, in [0, 1].
     * @param offsetY Vertical offset inside the pixel, in [0, 1].
     *
     * @return Sample color.
     */
    Color samplePixel(int x, int y, double offsetX, double offsetY) const;

    /**
     * @brief Renders a range of rows for the image buffer.
     *
     * @param startY Start row (inclusive).
     * @param endY End row (exclusive).
     * @param rowsDone Counter for completed rows.
     * @param rowReady Flags for completed rows.
     */
    void renderStripe(int startY, int endY, std::atomic<int> &rowsDone, std::vector<std::atomic<bool>> &rowReady);

private:
    /**
     * @brief Camera instance for the scene.
     * Initialized during core initialization.
     */
    std::unique_ptr<Camera> _camera;

    /**
     * @brief Flag indicating if the core is initialized.
     */
    bool _initialized;

    /**
     * @brief List of primitives in the scene.
     * Populated during initialization.
     */
    std::vector<std::unique_ptr<IPrimitive>> _primitives;

    /**
     * @brief Corresponding color for each primitive.
     */
    std::vector<Color> _primitiveColors;

    /**
     * @brief Specular factor for each primitive.
     */
    std::vector<double> _primitiveSpeculars;

    /**
     * @brief List of lights in the scene.
     * Populated during initialization.
     */
    std::vector<std::unique_ptr<ILight>> _lights;

    /**
     * @brief Ambient light multiplier.
     */
    double _ambient = 0.0;

    /**
     * @brief Diffuse light multiplier.
     */
    double _diffuse = 1.0;

    /**
     * @brief Image buffer for the rendered scene.
     * Populated during rendering.
     */
    std::unique_ptr<Image> _image;

    /**
     * @brief Antialiasing helper.
     */
    std::unique_ptr<Antialiasing> _antialiasing;
};

}
