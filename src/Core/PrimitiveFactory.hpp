/*
** EPITECH PROJECT, 2026
** PrimitiveFactory.hpp
** File description:
** Factory helper for runtime primitive creation
*/

#pragma once

#include "Parser/Primitives/APrimitiveConfig.hpp"
#include "Parser/Primitives/ConeConfig.hpp"
#include "Parser/Primitives/CylinderConfig.hpp"
#include "Parser/Primitives/PlaneConfig.hpp"
#include "Parser/Primitives/PyramidConfig.hpp"
#include "Parser/Primitives/SphereConfig.hpp"
#include "Parser/Primitives/TanglecubeConfig.hpp"
#include "Parser/Primitives/TorusConfig.hpp"
#include "Primitives/Cone.hpp"
#include "Primitives/Cylinder.hpp"
#include "Primitives/IPrimitives.hpp"
#include "Primitives/Plane.hpp"
#include "Primitives/Pyramid.hpp"
#include "Primitives/Sphere.hpp"
#include "Primitives/Tanglecube.hpp"
#include "Primitives/Torus.hpp"
#include "Utils/Color.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>

namespace RayTracer {

/**
 * @brief Factory pattern used to convert parsed primitive configs into runtime primitives.
 */
struct PrimitiveBuildResult
{
    std::unique_ptr<IPrimitive> _primitive;
    Color _color;
    double _specular = 0.0;
};

class PrimitiveFactory
{
public:
    /**
     * @brief Creates a runtime primitive instance from a parsed primitive configuration.
     * @param config The parsed primitive configuration.
     * @param index The index of the primitive.
     * @return A struct containing a unique pointer to the created primitive instance and its color.
     */
    static PrimitiveBuildResult create(const APrimitiveConfig &config, std::size_t index);

private:
    static void applyTransformations(IPrimitive &primitive, const APrimitiveConfig &config);
};

}
