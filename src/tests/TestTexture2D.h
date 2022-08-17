#pragma once

#include "Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include <memory>
#include <glm/glm.hpp>

namespace test
{

    class TestTexture2D : public Test
    {
    private:
        glm::vec3 m_TranslationA, m_TranslationB;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;

        glm::mat4 m_Proj, m_View;

    public:
        TestTexture2D();
        ~TestTexture2D();

        void onUpdate(float deltaTime) override;
        void onRender() override;
        void onImGuiRender() override;
    };
}
