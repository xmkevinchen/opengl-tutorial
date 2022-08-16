#include "Test.h"
#include <imgui/imgui.h>

namespace test
{
    Menu::Menu(Test *&currentTest) : m_CurrentTest(currentTest) {}

    void Menu::onImGuiRender()
    {
        for (auto &test : m_Tests) {
            if (ImGui::Button(test.label.c_str()))
                m_CurrentTest = test.initializer();
        }
    }
}
