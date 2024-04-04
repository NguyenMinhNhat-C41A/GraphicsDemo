#pragma once
#include <iostream>
#include <map>
#include <string>
#include <GLFW/glfw3.h>

class GLFWKeyMap
{
public:
    static int getKey(int p_iIndex)
    {

        int value = 0;
        try
        {
            value = GLFWKeyMap::GLFW_KEYMAP.at(p_iIndex);
        }
        catch (const std::out_of_range &e)
        {
            // Handle the case where the key is not found
            // std::cout << "GLFWKEYMAP - KEY_NOT_FOUND: " << p_iIndex << std::endl;
            value = -1;
        }
        return value;
    }

private:
    static const std::map<int, int> GLFW_KEYMAP;
};
