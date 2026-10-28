/*
** EPITECH PROJECT, 2026
** Core.cpp
** File description:
** Core orchestrator implementation
*/

#include "Core.hpp"

namespace RayTracer {

/**
 * @brief Applies optional transformation values to a primitive.
 *
 * @param primitive Primitive instance to update.
 * @param config Parsed primitive configuration.
 */
void Core::applyPrimitiveTransformations(IPrimitive &primitive, const APrimitiveConfig &config)
{
    if (const auto translation = config.getTranslation()) {
        primitive.translate(translation.value());
    }
    if (const auto rotation = config.getRotation()) {
        primitive.rotate(rotation.value());
    }
}

/**
 * @brief Initializes the core from a parsed scene configuration.
 *
 * @param config Parsed scene configuration.
 *
 * @return 0 on success, 84 on error.
 */
int Core::initialize(const Parser::Config &config)
{
    if (this->_initialized) {
        std::cerr << "Core is already initialized" << std::endl;
        return ERROR;
    }
    if (this->initializeCamera(config._cameraConfig) != 0) {
        std::cerr << "Failed to initialize camera" << std::endl;
        return ERROR;
    }
    if (this->initializePrimitives(config._primitivesConfig) != 0) {
        std::cerr << "Failed to initialize primitives" << std::endl;
        return ERROR;
    }
    if (!config._antialiasingConfig) {
        std::cerr << "Antialiasing config is null" << std::endl;
        return ERROR;
    }
    this->_antialiasing = std::make_unique<Antialiasing>(
        config._antialiasingConfig->isEnabled(),
        config._antialiasingConfig->getLowSampleCount(),
        config._antialiasingConfig->getHighSampleCount());
    this->_ambient = config._ambient;
    this->_diffuse = config._diffuse;
    if (this->initializeLights(config._lightsConfig) != 0) {
        std::cerr << "Failed to initialize lights" << std::endl;
        return ERROR;
    }
    this->_initialized = true;
    return SUCCESS;
}

/**
 * @brief Initializes the camera and image buffer.
 *
 * @param config Parsed camera configuration.
 *
 * @return 0 on success, 84 on error.
 */
int Core::initializeCamera(const std::unique_ptr<CameraConfig> &config)
{
    if (!config) {
        std::cerr << "Camera config is null" << std::endl;
        return ERROR;
    }

    try {
        this->_camera = std::make_unique<Camera>(
            config->getWidth(),
            config->getHeight(),
            config->getFieldOfView());
        Math::Vector3D camPos = config->getPosition();
        this->_camera->setOrigin(Math::Point3D(camPos.getX(), camPos.getY(), camPos.getZ()));
        this->_image = std::make_unique<Image>(
            config->getWidth(),
            config->getHeight());

        std::cout << "[Core] Camera initialized: "
                  << config->getWidth() << "x" << config->getHeight()
                  << " FOV=" << config->getFieldOfView() << "°" << std::endl;
        return SUCCESS;
    } catch (const std::exception &e) {
        std::cerr << "Exception during camera initialization: " << e.what()
                  << std::endl;
        return ERROR;
    }
}

/**
 * @brief Initializes scene primitives from parsed primitive configurations.
 *
 * @param configs Parsed primitive configurations.
 *
 * @return 0 on success, 84 on error.
 */
int Core::initializePrimitives(const std::vector<std::unique_ptr<APrimitiveConfig>> &configs)
{
    std::cout << "[Core] Initializing " << configs.size()
              << " primitive(s)..." << std::endl;

    try {
        for (std::size_t i = 0; i < configs.size(); ++i) {
            const auto &primitive = configs[i];

            if (!primitive) {
                std::cerr << "  [Primitive #" << i << "] invalid config" << std::endl;
                return ERROR;
            }

            PrimitiveBuildResult primitiveResult = PrimitiveFactory::create(*primitive, i);
            this->_primitives.push_back(std::move(primitiveResult._primitive));
            this->_primitiveColors.push_back(primitiveResult._color);
            this->_primitiveSpeculars.push_back(primitiveResult._specular);
        }
        return SUCCESS;
    } catch (const std::exception &e) {
        std::cerr << "Exception during primitives initialization: "
                  << e.what() << std::endl;
        return ERROR;
    }
}

/**
 * @brief Initializes scene lights from parsed light configurations.
 *
 * @param configs Parsed light configurations.
 *
 * @return 0 on success, 84 on error.
 */
int Core::initializeLights(const std::vector<std::unique_ptr<ILightConfig>> &configs)
{
    std::cout << "[Core] Initializing " << configs.size()
              << " light(s)..." << std::endl;

    try {
        for (std::size_t i = 0; i < configs.size(); ++i) {
            const auto &light = configs[i];

            if (!light) {
                std::cerr << "  [Light #" << i << "] invalid config" << std::endl;
                return ERROR;
            }

            this->_lights.push_back(LightFactory::create(*light, i));
        }
        return SUCCESS;
    } catch (const std::exception &e) {
        std::cerr << "Exception during lights initialization: "
                  << e.what() << std::endl;
        return ERROR;
    }
}

/**
 * @brief Computes the shaded color at a hit point.
 *
 * @param baseColor     Color of the hit primitive
 * @param hitPoint      Hit point in world space
 * @param normal        Surface normal at the hit point
 *
 * @return Shaded pixel color.
 */
Color Core::shade(const Color &baseColor, const Math::Point3D &hitPoint, const Math::Vector3D &normal, const Math::Vector3D &viewDir, double specular) const
{
    Color result = baseColor * this->_ambient;
    const double shadowEpsilon = 1e-3;
    const double shininess = 32.0;

    for (const auto &light : this->_lights) {
        const Math::Vector3D toLight = light->directionFrom(hitPoint);
        const double cosTheta = std::max(0.0, normal.dot(toLight));

        if (cosTheta <= 0.0) {
            continue;
        }

        const Math::Point3D shadowOrigin(hitPoint.getX() + toLight.getX() * shadowEpsilon, hitPoint.getY() + toLight.getY() * shadowEpsilon, hitPoint.getZ() + toLight.getZ() * shadowEpsilon);
        const Ray shadowRay(shadowOrigin, toLight);
        const double lightDistance = light->distanceTo(hitPoint);
        bool occluded = false;

        for (const auto &primitive : this->_primitives) {
            const std::optional<double> distance = primitive->hits(shadowRay);
            if (distance.has_value() && *distance > shadowEpsilon && *distance < lightDistance) {
                occluded = true;
                break;
            }
        }
        if (occluded == true) {
            continue;
        }
        const double intensity = light->getIntensityAt(hitPoint);
        const double factor = this->_diffuse * cosTheta * intensity;
        const Color tinted = (baseColor * light->getColor()) * factor;
        result = result + tinted;

        if (specular > 0.0) {
            const Math::Vector3D reflectDir = (normal * (2.0 * cosTheta)) - toLight;
            const double specAngle = std::max(0.0, reflectDir.dot(viewDir));
            const double specFactor = std::pow(specAngle, shininess) * specular * intensity;
            result = result + (light->getColor() * specFactor);
        }
    }
    return result;
}

/**
 * @brief Traces a ray and shades the closest primitive intersection.
 *
 * @param ray Ray to trace.
 *
 * @return Shaded color, or black when the ray misses.
 */
Color Core::traceRay(const Ray &ray, int depth) const
{
    const int maxDepth = 4;
    double minDistance = std::numeric_limits<double>::max();
    int closestPrimitiveIndex = -1;
    const double rayEpsilon = 1e-6;

    for (std::size_t i = 0; i < this->_primitives.size(); ++i) {
        const std::optional<double> distance = this->_primitives[i]->hits(ray);
        if (distance && *distance >= rayEpsilon && *distance < minDistance) {
            minDistance = *distance;
            closestPrimitiveIndex = static_cast<int>(i);
        }
    }

    if (closestPrimitiveIndex < 0 || closestPrimitiveIndex >= static_cast<int>(this->_primitiveColors.size())) {
        return Color(0, 0, 0);
    }

    const Math::Vector3D rayDir = ray.getDirection();
    const Math::Point3D rayOrigin = ray.getOrigin();
    const Math::Point3D hitPoint(rayOrigin.getX() + rayDir.getX() * minDistance,
                                 rayOrigin.getY() + rayDir.getY() * minDistance,
                                 rayOrigin.getZ() + rayDir.getZ() * minDistance);
    const Math::Vector3D normal = this->_primitives[closestPrimitiveIndex]->getNormalAt(hitPoint);
    const double specular = this->_primitiveSpeculars[closestPrimitiveIndex];
    const Math::Vector3D viewDir = (rayDir * -1.0).normalized();

    Color local = this->shade(this->_primitiveColors[closestPrimitiveIndex], hitPoint, normal, viewDir, specular);

    if (specular <= 0.0 || depth >= maxDepth) {
        return local;
    }

    const double cosI = rayDir.dot(normal);
    const Math::Vector3D reflectDir = (rayDir - normal * (2.0 * cosI)).normalized();
    const Math::Point3D reflectOrigin(hitPoint.getX() + reflectDir.getX() * rayEpsilon,
                                      hitPoint.getY() + reflectDir.getY() * rayEpsilon,
                                      hitPoint.getZ() + reflectDir.getZ() * rayEpsilon);
    const Color reflected = this->traceRay(Ray(reflectOrigin, reflectDir), depth + 1);

    return (local * (1.0 - specular)) + (reflected * specular);
}

/**
 * @brief Samples one location inside a pixel.
 *
 * @param x Pixel X coordinate.
 * @param y Pixel Y coordinate.
 * @param offsetX Horizontal sub-pixel offset in [0, 1].
 * @param offsetY Vertical sub-pixel offset in [0, 1].
 *
 * @return Sampled color.
 */
Color Core::samplePixel(int x, int y, double offsetX, double offsetY) const
{
    const double u = (static_cast<double>(x) + offsetX) / static_cast<double>(this->_image->_width);
    const double v = 1.0 - (static_cast<double>(y) + offsetY) / static_cast<double>(this->_image->_height);

    return this->traceRay(this->_camera->ray(u, v));
}

/**
 * @brief Renders a range of rows for the image buffer.
 *
 * @param startY Start row (inclusive).
 * @param endY End row (exclusive).
 */
void Core::renderStripe(int startY, int endY, std::atomic<int> &rowsDone, std::vector<std::atomic<bool>> &rowReady)
{
    const int width = this->_image->_width;
    const int height = this->_image->_height;

    const int yBegin = std::max(0, startY);
    const int yEnd = std::min(endY, height);

    for (int y = yBegin; y < yEnd; ++y) {
        for (int x = 0; x < width; ++x) {
            this->_image->_pixels[y * width + x] = this->_antialiasing->sampleAdaptive(
                [this, x, y](double offsetX, double offsetY) {
                    return this->samplePixel(x, y, offsetX, offsetY);
                });
        }
        rowReady[static_cast<std::size_t>(y)].store(true, std::memory_order_release);
        rowsDone.fetch_add(1, std::memory_order_relaxed);
    }
}

/**
 * @brief Renders the scene into the image buffer.
 *
 * @return 0 on success, 84 on error.
 */
int Core::render(void)
{
    if (!this->_initialized) {
        std::cerr << "Core is not initialized. Call initialize() first."
                  << std::endl;
        return ERROR;
    }

    if (!this->_image) {
        std::cerr << "No image buffer available. Call initialize() first."
                  << std::endl;
        return ERROR;
    }

    unsigned int threadCount = std::thread::hardware_concurrency();
    if (threadCount == 0) {
        threadCount = 4;
    }
    if (static_cast<int>(threadCount) > this->_image->_height) {
        threadCount = static_cast<unsigned int>(this->_image->_height);
    }

    std::cout << "[Core] Starting render with " << threadCount << " threads." << std::endl;

    std::atomic<int> rowsDone(0);
    std::vector<std::atomic<bool>> rowReady(static_cast<std::size_t>(this->_image->_height));
    for (auto &flag : rowReady) {
        flag.store(false, std::memory_order_relaxed);
    }

    const int stripeSize = (this->_image->_height + static_cast<int>(threadCount) - 1) / static_cast<int>(threadCount);
    std::vector<std::thread> workers;
    workers.reserve(threadCount);

    for (unsigned int i = 0; i < threadCount; ++i) {
        const int startY = static_cast<int>(i) * stripeSize;
        const int endY = std::min(this->_image->_height, startY + stripeSize);
        if (startY >= endY) {
            break;
        }
        workers.emplace_back(&Core::renderStripe, this, startY, endY, std::ref(rowsDone), std::ref(rowReady));
    }

    const int width = this->_image->_width;
    const int height = this->_image->_height;
    Display display;
    const bool displayReady = display.initialize(width, height);
    if (!displayReady) {
        std::cerr << "Failed to create preview window" << std::endl;
    }

    const auto updateInterval = std::chrono::milliseconds(DISPLAY_UPDATE_INTERVAL_MS);
    auto lastUpdate = std::chrono::steady_clock::now();

    while (rowsDone.load(std::memory_order_relaxed) < height) {
        display.pumpEvents();
        const auto now = std::chrono::steady_clock::now();
        if (displayReady && display.isOpen() && now - lastUpdate >= updateInterval) {
            display.update(*this->_image, rowReady);
            lastUpdate = now;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_POLL_INTERVAL_MS));
    }
    if (displayReady && display.isOpen()) {
        display.finalize(*this->_image);
        display.waitUntilClosed();
    }
    for (auto &worker : workers) {
        worker.join();
    }

    std::cout << "[Core] Render completed." << std::endl;
    return SUCCESS;
}

/**
 * @brief Saves the rendered image buffer to a file.
 *
 * @param filename Output image path.
 *
 * @return 0 on success, 84 on error.
 */
int Core::saveImage(const std::string &filename)
{
    if (!this->_initialized) {
        std::cerr << "Core is not initialized. Call initialize() first."
                  << std::endl;
        return ERROR;
    }

    if (!this->_image) {
        std::cerr << "No image to save. Call render() first." << std::endl;
        return ERROR;
    }

    std::cout << "[Core] Saving image to: " << filename << std::endl;

    try {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return ERROR;
        }

        file << "P3\n";
        file << this->_image->_width << " " << this->_image->_height << "\n";
        file << "255\n";

        for (int i = 0; i < this->_image->_width * this->_image->_height; ++i) {
            const Color &color = this->_image->_pixels[i];
            file << static_cast<int>(color.getRed()) << " "
                 << static_cast<int>(color.getGreen()) << " "
                 << static_cast<int>(color.getBlue()) << "\n";
        }

        file.close();
        std::cout << "[Core] Image saved successfully to: " << filename << std::endl;
        return SUCCESS;
    } catch (const std::exception &e) {
        std::cerr << "Exception while saving image: " << e.what() << std::endl;
        return ERROR;
    }
}

}
