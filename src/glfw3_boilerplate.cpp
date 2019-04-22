// glfw3_boilerplate.cpp

#ifdef _WIN32
#  define WINDOWS_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#endif
#include <stdio.h>

#include <GLFW/glfw3.h>

GLFWwindow* g_pWindow = NULL;

///@return 0 for success, non-zero otherwise
int initGL(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    return 0;
}

void display()
{
    glClearColor(0, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main(int argc, char *argv[])
{
    {
        printf("Compiled against GLFW %i.%i.%i\n",
            GLFW_VERSION_MAJOR,
            GLFW_VERSION_MINOR,
            GLFW_VERSION_REVISION);
        int major, minor, revision;
        glfwGetVersion(&major, &minor, &revision);
        printf("Running against GLFW %i.%i.%i\n", major, minor, revision);
        printf("%s\n", glfwGetVersionString());
    }

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
