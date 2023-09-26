#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>

// Función que dibuja la gráfica de una función con un color dado
void drawFunction(float (*func)(float), float r, float g, float b) {

    glLoadIdentity();
    glOrtho(-10, 10, -2, 2, -1, 1);

    // Dibuja los ejes X e Y
    glColor3f(255, 255, 255);  // Color blanco para los ejes
    glBegin(GL_LINES);
    glVertex2f(-10.0, 0.0);
    glVertex2f(10.0, 0.0);
    glVertex2f(0.0, -4.0);
    glVertex2f(0.0, 4.0);
    glEnd();

    glColor3f(r, g, b);
    glBegin(GL_LINE_STRIP);
    for (float x = -10.0; x <= 10.0; x += 0.05) {
        float y = func(x);
        glVertex2f(x, y);
    }
    glEnd();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Gráfica de Funciones", NULL, NULL);
    if (!window) {
        std::cerr << "Error al crear la ventana GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glOrtho(-10, 10, -2, 2, -1, 1);

        // Dibuja las funciones con diferentes colores
        drawFunction([](float x) { return std::sin(x); }, 1.0, 0.0, 0.0);
        drawFunction([](float x) { return std::sin(-x); }, 1.0, 0.0, 0.0); 
        drawFunction([](float x) { return std::cos(x); }, 0.0, 1.0, 0.0); 
        drawFunction([](float x) { return std::cos(x*3); }, 0.0, 1.0, 0.0); 
        drawFunction([](float x) { return x * x; }, 0.0, 0.0, 1.0);
        drawFunction([](float x) { return std::tan(x); }, 1.0, 1.0, 0.0); 
        drawFunction([](float x) { return std::exp(x); }, 1.0, 0.0, 1.0);  
        drawFunction([](float x) { return std::log(x + 1); }, 0.0, 1.0, 1.0); 
        drawFunction([](float x) { return std::sqrt(x); }, 0.5, 0.5, 0.5);  
        drawFunction([](float x) { return std::abs(std::sin(x)); }, 0.0, 1.0, 0.5);  
        drawFunction([](float x) { return std::ceil(x); }, 0.5, 0.0, 0.5); 
        drawFunction([](float x) { return std::floor(x); }, 1.0, 0.5, 0.0);  
        drawFunction([](float x) { return std::exp(-x); }, 0.8, 0.2, 0.8);  
        drawFunction([](float x) { return std::log(x + 1); }, 0.2, 0.7, 0.4);  
        drawFunction([](float x) { return std::tanh(x); }, 0.4, 0.8, 0.2); 
        drawFunction([](float x) { return std::abs(x); }, 0.7, 0.4, 0.1);
        drawFunction([](float x) { return std::sinh(x); }, 0.5, 0.2, 0.7);  
        drawFunction([](float x) { return std::cosh(x); }, 0.2, 0.6, 0.8);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}