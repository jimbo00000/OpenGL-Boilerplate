// glfw3_boilerplate.cpp

#ifdef _WIN32
#  define WINDOWS_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#endif
#include <stdio.h>

#include <algorithm>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

GLFWwindow* g_pWindow = NULL;
int g_red = 0;
float g_green = .5f;

static void error_callback(int error, const char* description)
{
    (void)error;
    fprintf(stderr, "Error: %s\n", description);
}

///@return 0 for success, non-zero otherwise
int initGL(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    return 0;
}

void display()
{
    glClearColor((float)g_red, (float)g_green, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void resize(GLFWwindow* window, int w, int h)
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    printf("resize: %d %d   %d %d\n", w,h, width, height);
}

void mouseWheel(GLFWwindow* window, double x, double y)
{
    (void)window;
    (void)x;
    g_green += .1f* (float)y;
    g_green = std::max(0.f, g_green);
    g_green = std::min(1.f, g_green);
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    (void)window;
    (void)scancode;
    (void)action;
    (void)mods;

    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        exit(0);
        break;

    default:
        g_red = 1 - g_red;
        break;
    }
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

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        return -1;

    if (initGL(argc, argv) != 0)
        return 0;

    g_pWindow = glfwCreateWindow(600, 600, "GL Boilerplate", 0, 0);
    glfwMakeContextCurrent(g_pWindow);
    glfwSwapInterval(0);

    glfwSetKeyCallback(g_pWindow, keyboard);
    glfwSetScrollCallback(g_pWindow, mouseWheel);
    glfwSetWindowSizeCallback(g_pWindow, resize);

    while (glfwWindowShouldClose(g_pWindow) == 0)
    {
        display();
        glfwPollEvents();
        glfwSwapBuffers(g_pWindow);
    }

    glfwTerminate();
    return 0;
}
