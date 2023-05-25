/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** App
*/

#ifndef APP_HPP_
#define APP_HPP_
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace Zappy::GUI {
    const constexpr uint32_t WIDTH = 800;
    const constexpr uint32_t HEIGHT = 600;

    class App
    {
        public:
            App();
            ~App();

            App(const App &) = delete;
            App &operator=(const App &) = delete;
            App(App &&) = delete;
            App &operator=(App &&) = delete;

            void run();

        private:
            static void createInstance();
            GLFWwindow *_window;
    };
} // namespace Zappy::GUI
#endif /* !APP_HPP_ */
