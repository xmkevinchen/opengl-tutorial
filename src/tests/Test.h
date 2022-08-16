#pragma once
#include <string>
#include <functional>
#include <vector>
#include <iostream>

namespace test
{
    class Test
    {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void onUpdate(float deltaTime) {}
        virtual void onRender() {}
        virtual void onImGuiRender() {}
    };

    struct MenuItem
    {
        std::string label;
        std::function<Test *()> initializer;
    };

    class Menu : public Test
    {
    public:
        Menu(Test *&currentTest);

        void onImGuiRender() override;

        template <typename T>
        void registerTest(const std::string &name)
        {
            MenuItem test = {
                name,
                []()
                { return new T(); },
            };

            std::cout << "Register test: " << name << std::endl;

            m_Tests.push_back(test);
        }

    private:
        std::vector<MenuItem> m_Tests;
        Test *&m_CurrentTest;
    };
}
