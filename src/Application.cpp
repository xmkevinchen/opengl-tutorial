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

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "TestClearColor.h"

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

    Renderer renderer;

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();

    test::Test *currentTest = nullptr;
    test::Menu *menu = new test::Menu(currentTest);
    currentTest = menu;

    menu->registerTest<test::TestClearColor>("Clear Color");

    test::TestClearColor test;

    while (!glfwWindowShouldClose(window))
    {
        GLCall(glClearColor(0.0, 0.0, 0.0, 1.0f));

        renderer.clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (currentTest)
        {
            currentTest->onUpdate(0.0f);
            currentTest->onRender();
            ImGui::Begin("Test");
            if (currentTest != menu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = menu;
            }
            currentTest->onImGuiRender();
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }

    delete currentTest;
    if (currentTest != menu)
    {
        delete menu;
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
