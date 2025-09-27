#include "Shader.h"

Shader:: ~Shader()
{
	if (programID != 0)
	{
		glDeleteProgram(programID);
	}

    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteBuffers(1, &indexBuffer);
}

void Shader::LoadAttributes()
{
	attrVertices = glGetAttribLocation(programID, "vertices");
    attrColors = glGetAttribLocation(programID, "colors");
    attrWVP = glGetUniformLocation(programID, "WVP");
}

void Shader::EvaluateShader(int _infoLength, GLuint _id)
{
	if (_infoLength > 0)
	{
		std::vector<char> errorMessage(_infoLength + 1);
		glGetShaderInfoLog(_id, _infoLength, NULL, &errorMessage[0]);
		M_ASSERT(NULL, ("%s\n", &errorMessage[0]));
	}
}

GLuint Shader::LoadShaderFile(const char* _filePath, GLenum _type)
{
    GLuint shaderID = glCreateShader(_type);

    std::string shaderCode;
    std::ifstream shaderStream(_filePath, std::ios::in);
    bool isOpen = shaderStream.is_open();
    M_ASSERT(shaderStream.is_open(), ("Impossible %s Read FAQ!\n", _filePath));
    std::string Line = "";
    while (getline(shaderStream, Line))
    {
        shaderCode += "\n" + Line;
    }
    shaderStream.close();

    char const* sourcePointer = shaderCode.c_str();
    glShaderSource(shaderID, 1, &sourcePointer, NULL);
    glCompileShader(shaderID);

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    EvaluateShader(infoLogLength, shaderID);

    glAttachShader(programID, shaderID);

    return shaderID;

}

void Shader::CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath)
{
    programID = glCreateProgram();

    GLuint vertexShaderID = LoadShaderFile(_vertexFilePath, GL_VERTEX_SHADER);
    GLuint fragmentShaderID = LoadShaderFile(_fragmentFilePath, GL_FRAGMENT_SHADER);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    EvaluateShader(infoLogLength, programID);

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &colorBuffer);
    glGenBuffers(1, &indexBuffer);
}

void Shader::LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath)
{
    CreateShaderProgram(_vertexFilePath, _fragmentFilePath);
    LoadAttributes();
}

void Shader::LoadDataToBuffer(std::vector<GLfloat> _vertexData, std::vector<GLfloat> _colorData, std::vector<GLubyte> _indexData)
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, _vertexData.size() * sizeof(float), _vertexData.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, _colorData.size() * sizeof(float), _colorData.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexData.size() * sizeof(float), _indexData.data(), GL_STATIC_DRAW);
}

void Shader::Draw(const GLfloat* _wvp, size_t size)
{
    glUseProgram(programID);
    glUniformMatrix4fv(attrWVP, 1, FALSE, _wvp);

    glEnableVertexAttribArray(attrVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(
        attrVertices,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(attrColors);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(
        attrColors,
        4,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_BYTE, (void*)0);
    glDisableVertexAttribArray(attrVertices);
    glDisableVertexAttribArray(attrColors);
}