#include "Mesh.h"

Mesh::~Mesh()
{
    if (shader != nullptr)
    {
        delete shader;
        shader = nullptr;
    }
}

void Mesh::Create(Shader* _shader, glm::vec4 color)
{
    shader = _shader;
    vertexData = {
        -2.0f, -2.0f, 0.0f,
        2.0f, -2.0f, 0.0f,
        0.0f, 2.0f, 0.0f
    };
    colorData = color;
    indexData = { 0, 1, 2 };
}

void Mesh::Render(glm::mat4 _wvp, std::string name)
{
    _wvp *= world;

    shader->LoadDataToBuffer(vertexData, colorData, indexData);
    shader->Draw(&_wvp[0][0], indexData.size());
}

void Mesh::RotateWorld(float _angle, glm::vec3 axis)
{
    world = glm::rotate(world, _angle, axis);
}

void Mesh::TranslateWorld(glm::vec3 _offset)
{
    world = glm::translate(world, _offset);
}