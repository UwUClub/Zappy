/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** App
*/

#include "App.hpp"
#include <vulkan/vulkan.h>

namespace Zappy::GUI {
    App::App() : _window(nullptr)
    {
        if (glfwInit() == 0) {
            throw std::runtime_error("Failed to initialize GLFW");
        }
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        _window = glfwCreateWindow(WIDTH, HEIGHT, "Zappy", nullptr, nullptr);
    }

    App::~App()
    {
        glfwDestroyWindow(_window);

        glfwTerminate();
    }

    void App::createInstance()
    {
        VkApplicationInfo appInfo;
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Zappy";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Zappy";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_2;
    }

    void App::run()
    {
        while (glfwWindowShouldClose(_window) == 0) {
            glfwPollEvents();
        }
    }
} // namespace Zappy::GUI
