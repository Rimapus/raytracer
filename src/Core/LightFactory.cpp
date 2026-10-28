/*
** EPITECH PROJECT, 2026
** LightFactory.cpp
** File description:
** Factory helper for runtime light creation
*/

#include "LightFactory.hpp"

namespace RayTracer {

/**
 * @brief Creates a runtime light instance from a parsed light configuration.
 * @param config The parsed light configuration.
 * @param index The index of the light.
 * @return A unique pointer to the created light instance.
 */
std::unique_ptr<ILight> LightFactory::create(const ILightConfig &config, std::size_t index)
{
    switch (config.getType()) {
    case LightType::POINT: {
        const auto &pointLight = dynamic_cast<const PointLightConfig &>(config);
        const Math::Vector3D position = pointLight.getPosition();
        const Color color = pointLight.getColor();
        std::cout << "  [Point Light #" << index << "] "
                  << "position=(" << position.getX() << ", "
                  << position.getY() << ", "
                  << position.getZ() << ") "
                  << "color=(" << static_cast<int>(color.getRed()) << ", "
                  << static_cast<int>(color.getGreen()) << ", "
                  << static_cast<int>(color.getBlue()) << ")" << std::endl;
        return std::make_unique<PointLight>(
            Math::Point3D(position.getX(), position.getY(), position.getZ()),
            5000.0,
            color);
    }
    case LightType::DIRECTIONAL: {
        const auto &dirLight = dynamic_cast<const DirectionalLightConfig &>(config);
        const Math::Vector3D directionDegrees = dirLight.getDirection();
        const Math::Vector3D baseDown(0.0, -1.0, 0.0);
        const Math::Vector3D direction = Math::applyEulerXYZRotation(baseDown, directionDegrees);
        const Color color = dirLight.getColor();
        std::cout << "  [Directional Light #" << index << "] "
                  << "rotation=(" << directionDegrees.getX() << ", "
                  << directionDegrees.getY() << ", "
                  << directionDegrees.getZ() << ") deg -> dir=("
                  << direction.getX() << ", "
                  << direction.getY() << ", "
                  << direction.getZ() << ") "
                  << "color=(" << static_cast<int>(color.getRed()) << ", "
                  << static_cast<int>(color.getGreen()) << ", "
                  << static_cast<int>(color.getBlue()) << ")" << std::endl;
        return std::make_unique<DirectionalLight>(direction, 1.0, color);
    }
    }

    throw std::runtime_error("Unsupported light type");
}

}
