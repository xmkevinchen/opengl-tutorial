#include <GL/glew.h> // Need to before glfw3.h
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // Setting window properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    int width = 960;
    int height = 540;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "OpenGL Application", NULL, NULL);
    if (!window)
    {
        GLCall(glfwTerminate());
        return -1;
    }

    /* Make the window's context current */
    GLCall(glfwMakeContextCurrent(window));

    GLCall(glfwSwapInterval(1));

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cerr << "ERROR: could not initial glew" << std::endl;
        return -1;
    }

    float positions[] = {
        100.0f,  100.0f, 0.0f, 0.0f, // 0
        200.0f,  100.0f, 1.0f, 0.0f, // 1
        200.0f,  200.0f, 1.0f, 1.0f, // 2
        100.0f,  200.0f, 0.0f, 1.0f, // 3
    };

    unsigned int indices[] = {
        0, 1, 2, // 0
        2, 3, 0, // 1
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, 0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

    glm::mat4 mvp = proj * view * model;

    // Shader shader("res/shaders/basic-uniform.shader");
    Shader shader("res/shaders/texture-basic.shader");
    shader.bind();
    shader.setUniformMat4f("u_MVP", mvp);

    Texture texture("res/textures/opengl.png");
    texture.bind();
    shader.setUniform1i("u_Texture", 0);

    Renderer renderer;

    // float red = 0.0f;
    // float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.clear();
        // shader.setUniform4f("u_Color", red, 0.3f, 0.8f, 1.0f);

        renderer.draw(va, ib, shader);

        // red += increment;
        // if (red > 1.0f)
        // {
        //     increment = -0.05;
        // }
        // else if (red < 0.0f)
        // {
        //     increment = 0.05;
        // }

        /* Swap front and back buffers */
        GLCall(glfwSwapBuffers(window));

        /* Poll for and process events */
        GLCall(glfwPollEvents());
    }

    glfwTerminate();
    return 0;
}
