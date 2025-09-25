#include "Mesh.h"

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);

    if (shader != nullptr)
    {
        delete shader;
        shader = nullptr;
    }
}

void Mesh::Create(Shader* _shader)
{
    shader = _shader;
    float a = 26.0f;
    float b = 42.0f;
    vertexData = {
        -a, 0.0f, b, 1.0f, 0.0f, 0.0f, 1.0f,
        a, 0.0f, b, 1.0f, 0.549f, 0.0f, 1.0f,
        -a, 0.0f, -b, 1.0f, 1.0f, 0.0f, 1.0f,
        a, 0.0f, -b, 1.0f, 1.0f, 0.0f, 1.0f,
        0.0f, b, a, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, b, -a, 0.294f, 0.0f, 0.51f, 1.0f,
        0.0f, -b, a, 0.502f, 0.0f, 0.502f, 1.0f,
        0.0f, -b, -a, 1.0f, 1.0f, 1.0f, 1.0f,
        b, a, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -b, a, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        b, -a, 0.0f, 0.118f, 0.565f, 1.0f, 1.0f,
        -b, -a, 0.0f, 0.863f, 0.078f, 0.235f, 1.0f
    };

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    indexData = {
        0,6,1,0,11,6,1,4,0,1,8,4,
        1,10,8,2,5,3,2,9,5,2,11,9,
        3,7,2,3,10,7,4,8,5,4,9,0,
        5,8,3,5,9,4,6,10,1,6,11,7,
        7,10,6,7,11,2,8,10,3,9,11,0
    };

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, indexData.size() * sizeof(float), indexData.data(), GL_STATIC_DRAW);

}

void Mesh::Render(glm::mat4 _wvp)
{
    glUseProgram(shader->GetProgramID());

    _wvp *= world;
    glUniformMatrix4fv(shader->GetAttrWVP(), 1, FALSE, &_wvp[0][0]);

    glEnableVertexAttribArray(shader -> GetAttrVertices());
    glVertexAttribPointer(
        shader->GetAttrVertices(),
        3,
        GL_FLOAT,
        GL_FALSE,
        7 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(shader -> GetAttrColors());
    glVertexAttribPointer(
        shader->GetAttrColors(),
        4,
        GL_FLOAT,
        GL_FALSE,
        7 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_BYTE, (void*)0);
    glDisableVertexAttribArray(shader->GetAttrVertices());
    glDisableVertexAttribArray(shader->GetAttrColors());
}

void Mesh::RotateWorld(float _angle, glm::vec3 axis)
{
    world = glm::rotate(world, _angle, axis);
}