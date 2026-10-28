/*
** EPITECH PROJECT, 2026
** PrimitiveFactory.cpp
** File description:
** Factory helper for runtime primitive creation
*/

#include "PrimitiveFactory.hpp"

namespace RayTracer {

/**
 * @brief Applies optional transformation values to a primitive.
 * @param primitive Primitive instance to update.
 * @param config Parsed primitive configuration.
 */
void PrimitiveFactory::applyTransformations(IPrimitive &primitive, const APrimitiveConfig &config)
{
    if (const auto translation = config.getTranslation()) {
        primitive.translate(translation.value());
    }
    if (const auto rotation = config.getRotation()) {
        primitive.rotate(rotation.value());
    }
}

/**
 * @brief Creates a runtime primitive instance from a parsed primitive configuration.
 * @param config The parsed primitive configuration.
 * @param index The index of the primitive.
 * @return A struct containing a unique pointer to the created primitive instance and its color.
 */
PrimitiveBuildResult PrimitiveFactory::create(const APrimitiveConfig &config, std::size_t index)
{
    switch (config.getType()) {
    case PrimitiveType::SPHERE: {
        const auto &sphere = dynamic_cast<const SphereConfig &>(config);
        const Math::Vector3D pos = sphere.getPosition();
        std::cout << "  [Sphere #" << index << "] "
                  << "center=(" << pos.getX() << ", "
                  << pos.getY() << ", "
                  << pos.getZ() << ") radius=" << sphere.getRadius() << std::endl;
        std::unique_ptr<Sphere> primitive = std::make_unique<Sphere>(
            Math::Point3D(pos.getX(), pos.getY(), pos.getZ()),
            sphere.getRadius());
        applyTransformations(*primitive, config);
        return {std::move(primitive), sphere.getColor(), config.getSpecular()};
    }
    case PrimitiveType::CYLINDER: {
        const auto &cylinder = dynamic_cast<const CylinderConfig &>(config);
        const Math::Vector3D pos = cylinder.getPosition();
        std::cout << "  [Cylinder #" << index << "] "
                  << "center=(" << pos.getX() << ", "
                  << pos.getY() << ", "
                  << pos.getZ() << ") radius=" << cylinder.getRadius()
                  << " height=" << cylinder.getHeight()
                  << " limited=" << (cylinder.isLimited() ? "true" : "false") << std::endl;
        std::unique_ptr<Cylinder> primitive = std::make_unique<Cylinder>(
            Math::Point3D(pos.getX(), pos.getY(), pos.getZ()),
            cylinder.getRadius(),
            cylinder.getHeight(),
            cylinder.isLimited());
        applyTransformations(*primitive, config);
        return {std::move(primitive), cylinder.getColor(), config.getSpecular()};
    }
    case PrimitiveType::CONE: {
        const auto &cone = dynamic_cast<const ConeConfig &>(config);
        const Math::Vector3D pos = cone.getPosition();
        std::cout << "  [Cone #" << index << "] "
                  << "center=(" << pos.getX() << ", "
                  << pos.getY() << ", "
                  << pos.getZ() << ") radius=" << cone.getRadius()
                  << " height=" << cone.getHeight()
                  << " limited=" << (cone.isLimited() ? "true" : "false") << std::endl;
        std::unique_ptr<Cone> primitive = std::make_unique<Cone>(
            Math::Point3D(pos.getX(), pos.getY(), pos.getZ()),
            cone.getRadius(),
            cone.getHeight(),
            cone.isLimited());
        applyTransformations(*primitive, config);
        return {std::move(primitive), cone.getColor(), config.getSpecular()};
    }
    case PrimitiveType::TORUS: {
        const auto &torus = dynamic_cast<const TorusConfig &>(config);
        const Math::Vector3D pos = torus.getPosition();
        std::cout << "  [Torus #" << index << "] "
                  << "center=(" << pos.getX() << ", "
                  << pos.getY() << ", "
                  << pos.getZ() << ") majorRadius=" << torus.getMajorRadius()
                  << " minorRadius=" << torus.getMinorRadius() << std::endl;
        std::unique_ptr<Torus> primitive = std::make_unique<Torus>(
            Math::Point3D(pos.getX(), pos.getY(), pos.getZ()),
            torus.getMajorRadius(),
            torus.getMinorRadius());
        applyTransformations(*primitive, config);
        return {std::move(primitive), torus.getColor(), config.getSpecular()};
    }
    case PrimitiveType::PYRAMID: {
        const auto &pyramid = dynamic_cast<const PyramidConfig &>(config);
        const Math::Vector3D pos = pyramid.getPosition();
        std::cout << "  [Pyramid #" << index << "] "
                  << "baseCenter=(" << pos.getX() << ", "
                  << pos.getY() << ", "
                  << pos.getZ() << ") size=" << pyramid.getSize()
                  << " height=" << pyramid.getHeight() << std::endl;
        std::unique_ptr<Pyramid> primitive = std::make_unique<Pyramid>(
            Math::Point3D(pos.getX(), pos.getY(), pos.getZ()),
            pyramid.getSize(),
            pyramid.getHeight());
        applyTransformations(*primitive, config);
        return {std::move(primitive), pyramid.getColor(), config.getSpecular()};
    }
    case PrimitiveType::TANGLECUBE: {
        const auto &tanglecube = dynamic_cast<const TanglecubeConfig &>(config);
        const Math::Vector3D pos = tanglecube.getPosition();
        std::cout << "  [Tanglecube #" << index << "] "
                  << "center=(" << pos.getX() << ", "
                  << pos.getY() << ", "
                  << pos.getZ() << ") scale=" << tanglecube.getScale() << std::endl;
        std::unique_ptr<Tanglecube> primitive = std::make_unique<Tanglecube>(
            Math::Point3D(pos.getX(), pos.getY(), pos.getZ()),
            tanglecube.getScale());
        applyTransformations(*primitive, config);
        return {std::move(primitive), tanglecube.getColor(), config.getSpecular()};
    }
    case PrimitiveType::PLANE: {
        const auto &plane = dynamic_cast<const PlaneConfig &>(config);
        std::cout << "  [Plane #" << index << "] position="
                  << plane.getPosition() << std::endl;
        std::unique_ptr<Plane> primitive = std::make_unique<Plane>(plane.getPosition(), plane.getAxis());
        applyTransformations(*primitive, config);
        return {std::move(primitive), plane.getColor(), config.getSpecular()};
    }
    }

    throw std::runtime_error("Unsupported primitive type");
}

}
