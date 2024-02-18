#define GL_SILENCE_DEPRECATION

#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <GLFW/glfw3.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <functional>
#include <cmath>
#include "../headers/FuncionesMath.h"

using namespace std;

int windowWidth = 1024;
int windowHeight = 720;

vector<double> generateXValues(double start, double end, double step) {
    vector<double> xValues;
    for (double x = start; x <= end; x += step)
    {
        xValues.push_back(x);
    }
    return xValues;
}

void drawMathFunction(const std::function<double(double)> &func, double startX, double endX, float r, float g, float b, double verticalOffset) {
    glLoadIdentity();
    glOrtho(startX, endX, -2, 2, -1, 1);

    glColor3f(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2f(-10.0, 0.0);
    glVertex2f(10.0, 0.0);
    glVertex2f(0.0, -2.0);
    glVertex2f(0.0, 2.0);
    glEnd();

    glColor3f(r, g, b);
    glBegin(GL_LINE_STRIP);

    for (double x = startX; x <= endX; x += 0.005)
    {
        double y = func(x);
        glVertex2f(x, y + verticalOffset * 0.2);
    }
    glEnd();
}

void iterateAndDrawMath(int numberOfLines, const std::vector<double>& xValues) {
    float r = 0, g = 0, b = 0;
    
    for (int i = 0; i < numberOfLines; ++i) {
        std::vector<double> yCosValues;
        double yOffset = 1.8 - i * 0.4;

        double verticalOffSet = (i % 2 == 0) ? -(i / 2) * 0.5 : ((i + 1) / 2) * 0.5;

        r = static_cast<float>(1);
        g = static_cast<float>(0);
        b = static_cast<float>(0);
        drawMathFunction(cosMath, -8, 8, r, g, b, verticalOffSet);

        r = static_cast<float>(0);
        g = static_cast<float>(1);
        b = static_cast<float>(0);
        drawMathFunction(senMath, -8, 8, r, g, b, verticalOffSet);
    }
}

void drawCustomFunction(const std::function<double(double)> &func, double startX, double endX, float r, float g, float b, double verticalOffset) {
    glLoadIdentity();
    glOrtho(startX, endX, -2, 2, -1, 1);

    glColor3f(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2f(-10.0, 0.0);
    glVertex2f(10.0, 0.0);
    glVertex2f(0.0, -2.0);
    glVertex2f(0.0, 2.0);
    glEnd();

    glColor3f(r, g, b);
    glBegin(GL_LINE_STRIP);

    for (double x = startX; x <= endX; x += 0.005)
    {
        double y = func(x);
        glVertex2f(x, y + verticalOffset * 0.2);
    }
    glEnd();
}


void iterateAndDrawCustom(int numberOfLines, const std::vector<double>& xValues) {
    float r = 0, g = 0, b = 0;
    
    for (int i = 0; i < numberOfLines; ++i) {
        std::vector<double> yCosValues;
        double yOffset = 1.8 - i * 0.4;

        double verticalOffSet = (i % 2 == 0) ? -(i / 2) * 0.5 : ((i + 1) / 2) * 0.5;

        r = static_cast<float>(1);
        g = static_cast<float>(0);
        b = static_cast<float>(0);
        drawCustomFunction(customCos, -8, 8, r, g, b, verticalOffSet);

        r = static_cast<float>(0);
        g = static_cast<float>(1);
        b = static_cast<float>(0);
        drawCustomFunction(customSen, -8, 8, r, g, b, verticalOffSet);
    }
}

void drawSquare(double centerX, double centerY, double size, float r, float g, float b) {
    
    glColor3f(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2f(-10.0, 0.0);
    glVertex2f(10.0, 0.0);
    glVertex2f(0.0, -2.0);
    glVertex2f(0.0, 2.0);
    glEnd();

    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    glVertex2f(centerX - size / 2, centerY - size / 2);
    glVertex2f(centerX + size / 2, centerY - size / 2);
    glVertex2f(centerX + size / 2, centerY + size / 2);
    glVertex2f(centerX - size / 2, centerY + size / 2);
    glEnd();
}

void iterateAndDrawSquares(int numberOfSquares, const std::vector<double>& xValues) {
    for (int i = 0; i < numberOfSquares; ++i) {
        double centerX = 0.0; 
        double centerY = 0.0;  
        double baseSize = 0.05; // tamanio del cuadrado base

        float r = static_cast<float>(i % 2); // Alterna entre rojo (0) y verde (1)
        float g = static_cast<float>((i + 1) % 2); // Alterna entre verde (0) y rojo (1)
        float b = 0.0f; // Sin azul

        double scaleFactor = i * 0.1; // Factor de escala para variar el tamaño de los cuadrados

        double size = baseSize + scaleFactor;

        drawSquare(centerX, centerY, size, r, g, b);
    }
}

void measure(void (*func)(int, const std::vector<double>&), int numberOfLines, const std::vector<double>& xValues) {
    auto start = std::chrono::high_resolution_clock::now();
    
    func(numberOfLines, xValues);
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "\nTiempo para graficar " << numberOfLines * 2 << " funciones: " << duration.count() << " milisegundos\n";
}

int graficarFunciones() {

    if (!glfwInit()) {
        cerr << "Error al inicializar GLFW" << endl;
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "Gráfica de Funciones", NULL, NULL);
    if (!window) {
        cerr << "Error al crear la ventana GLFW" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    int numberOfLines = 10;
    double step = 0.15;
    bool useCustomFunctions = true; // True funciones custom, false funciones math. //

    vector<double> xValues = generateXValues(-10.0, 10.0, step);

     while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        if (useCustomFunctions) {
            measure(iterateAndDrawCustom, numberOfLines, xValues);
        } else {
            measure(iterateAndDrawMath, numberOfLines, xValues);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    xValues.clear();
    xValues.shrink_to_fit();

    glfwTerminate();

    return 0;
}
