#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderProgramSource
{
    std::string vertex;
    std::string fragment;
};

class Shader
{
private:
    unsigned int m_RendererID;
    std::string m_Filepath;
    std::unordered_map<std::string, int> m_UniformLocationCache;

public:
    Shader(const std::string &filepath);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform1i(const std::string &name, int value);
    void setUniform1f(const std::string &name, float value);
    void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
    void setUniformMat4f(const std::string &name, const glm::mat4 &matrix);
private:
    int getUniformLocation(const std::string &name);
    unsigned int compile(unsigned int type,
                         const std::string &source);
    unsigned int create(const std::string &vertexShader,
                        const std::string &fragmentShader);
    ShaderProgramSource parse(const std::string &filepath);
};
