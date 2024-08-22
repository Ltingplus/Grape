#pragma once

#include "glm/glm.hpp"

struct Sphere
{
    glm::vec3 Position{0.0f};
    float Radius = 0.5f;

    glm::vec3 Albedo{ 1.0f };
};

struct Scene
{
    std::vector<Sphere> Spheres;
    glm::vec3 LightDir{-1,-1,-1};
};