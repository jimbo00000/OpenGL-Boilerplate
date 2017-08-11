// glfw3_boilerplate.cpp

#ifdef _WIN32
#  define WINDOWS_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#endif

#include <GLFW/glfw3.h>

GLFWwindow* g_pWindow = nullptr;

///@return 0 for success, non-zero otherwise
int initGL(int argc, char** argv)
{
    return 0;
}

void display()
{
    glClearColor(0, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main(int argc, char *argv[])
{
    if (!glfwInit())
        return -1;

    if (initGL(argc, argv) != 0)
        return 0;

    g_pWindow = glfwCreateWindow(600, 600, "GL Boilerplate", 0, 0);
    glfwMakeContextCurrent(g_pWindow);
    glfwSwapInterval(0);

    while (glfwWindowShouldClose(g_pWindow) == false)
    {
        display();
        glfwPollEvents();
        glfwSwapBuffers(g_pWindow);
    }

    glfwTerminate();
    return 0;
}
