#include "Mesh.h"

Mesh::~Mesh()
{
    if (shader != nullptr)
    {
        delete shader;
        shader = nullptr;
    }
}

void Mesh::Create(Shader* _shader)
{
    shader = _shader;
    vertexData = {
        -4.0f, -2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        4.0f, -2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 4.0f, 0.0f, 0.118f, 0.565f, 1.0f, 1.0f
        //-a, 0.0f, b, 1.0f, 0.0f, 0.0f, 1.0f,
        //a, 0.0f, b, 1.0f, 0.549f, 0.0f, 1.0f,
        //-a, 0.0f, -b, 1.0f, 1.0f, 0.0f, 1.0f
        //a, 0.0f, -b, 1.0f, 1.0f, 0.0f, 1.0f,
        //0.0f, b, a, 0.0f, 0.0f, 1.0f, 1.0f,
        //0.0f, b, -a, 0.294f, 0.0f, 0.51f, 1.0f,
        //0.0f, -b, a, 0.502f, 0.0f, 0.502f, 1.0f,
        //0.0f, -b, -a, 1.0f, 1.0f, 1.0f, 1.0f,
        //-b, -a, 0.0f, 0.863f, 0.078f, 0.235f, 1.0f
    };

    indexData = {
        0,1,2
    };
}

void Mesh::Render(glm::mat4 _wvp)
{
    model = _wvp * world;
    std::cout << glm::to_string(model) << std::endl;

    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(float), indexData.data(), GL_STATIC_DRAW);
    shader->Draw(&model[0][0], indexData.size());
}

void Mesh::RotateWorld(float _angle, glm::vec3 axis)
{
    world = glm::rotate(world, _angle, axis);
}

void Mesh::TranslateWorld(glm::vec3 _offset)
{
    world = glm::translate(world, _offset);
}