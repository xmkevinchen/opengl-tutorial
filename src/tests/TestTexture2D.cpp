#include "TestTexture2D.h"
#include "Renderer.h"
#include "VertexArray.h"

#include "VertexBufferLayout.h"
#include "Texture.h"

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace test
{
    TestTexture2D::TestTexture2D()
        : m_TranslationA(glm::vec3(200, 200, 0)),
          m_TranslationB(glm::vec3(400, 200, 0)),
          m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
          m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
    {
        float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f, // 0
            50.0f, -50.0f, 1.0f, 0.0f,  // 1
            50.0f, 50.0f, 1.0f, 1.0f,   // 2
            -50.0f, 50.0f, 0.0f, 1.0f,  // 3
        };

        unsigned int indices[] = {
            0, 1, 2, // 0
            2, 3, 0, // 1
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VAO = std::make_unique<VertexArray>();
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);
        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        m_VAO->addBuffer(*m_VertexBuffer, layout);

        m_Texture = std::make_unique<Texture>("res/textures/opengl.png");
        m_Texture->bind();

        m_Shader = std::make_unique<Shader>("res/shaders/texture-basic.shader");
        m_Shader->bind();
        m_Shader->setUniform1i("u_Texture", 0);
    }

    TestTexture2D::~TestTexture2D()
    {
    }

    void TestTexture2D::onUpdate(float deltaTime)
    {
    }

    void TestTexture2D::onRender()
    {
        GLCall(glClearColor(0.0, 0.0, 0.0, 1.0));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        Renderer renderer;

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;

            m_Shader->bind();
            m_Shader->setUniformMat4f("u_MVP", mvp);
            renderer.draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;

            m_Shader->bind();
            m_Shader->setUniformMat4f("u_MVP", mvp);
            renderer.draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
    }

    void TestTexture2D::onImGuiRender()
    {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960);
        ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960);
    }
}
