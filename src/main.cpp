/*
** EPITECH PROJECT, 2026
** main.cpp
** File description:
** Main file for the RayTracer
*/

#include "Core/Core.hpp"
#include "Parser/Parser.hpp"
#include <iostream>

static int
printUsage(int returnValue = 0)
{
    std::cout << "Usage: ./raytracer <SCENE_FILE>\n"
              << "\tSCENE_FILE: scene configuration\n";
    return returnValue;
}

/**
 * @brief Main entry point for the raytracer project.
 *
 * @return Return value of the program.
 */
int main(int ac, char **av)
{
    if (ac != 2) {
        return printUsage(ERROR);
    }
    if (std::string(av[1]) == "--help") {
        return printUsage(SUCCESS);
    }

    try {
        RayTracer::Parser parser(av[1]);
        RayTracer::Parser::Config config = parser.parse();

        RayTracer::Core core;
        if (core.initialize(config) != 0) {
            std::cerr << "Failed to initialize core" << std::endl;
            return 84;
        }
        if (core.render() != 0) {
            std::cerr << "Failed to render scene" << std::endl;
            return 84;
        }
        if (core.saveImage("output.ppm") != 0) {
            std::cerr << "Failed to save image" << std::endl;
            return 84;
        }

        std::cout << "Raytracing completed successfully!" << std::endl;
    } catch (const std::exception &error) {
        std::cerr << error.what() << std::endl;
        return 84;
    }

    return SUCCESS;
}
