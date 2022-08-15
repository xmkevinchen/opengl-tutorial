#include "Shader.h"
#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string &filepath)
    : m_RendererID(0), m_Filepath(filepath)
{
    auto source = parse(filepath);
    m_RendererID = create(source.vertex, source.fragment);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID))
}

void Shader::bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::setUniform1i(const std::string &name, int value)
{
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform1f(const std::string &name, float value)
{
    GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setUniform4f(
    const std::string &name,
    float v0, float v1, float v2, float v3)
{
    int location = getUniformLocation(name);
    if (location != -1)
    {
        GLCall(glUniform4f(location, v0, v1, v2, v3))
    }
}

void Shader::setUniformMat4f(const std::string &name, const glm::mat4 &matrix)
{
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::getUniformLocation(const std::string &name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    {
        return m_UniformLocationCache[name];
    }
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
    {
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
    }

    m_UniformLocationCache[name] = location;
    return location;
}

ShaderProgramSource Shader::parse(const std::string &filepath)
{
    std::ifstream stream(filepath);

    std::string line;
    std::stringstream ss[2];
    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
    };
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    stream.close();

    return {
        ss[0].str(),
        ss[1].str()};
}

unsigned int Shader::compile(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (GL_FALSE == result)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile "
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::create(const std::string &vertexShader,
                            const std::string &fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = compile(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compile(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}
