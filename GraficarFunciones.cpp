#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <functional>

using namespace std;

int windowWidth = 1024;
int windowHeight = 720;

double customCos(double x)
{
    constexpr int terms = 10000;
    double result = 1.0;
    double term = 1.0;

    for (int n = 1; n < terms; n++)
    {
        term *= (-x * x) / ((2 * n) * (2 * n - 1));
        result += term;
    }

    return result;
}

double customSen(double x)
{
    const int n = 10000;
    double seno = 0.0;
    double term = x;
    int sign = 1;

    for (int i = 1; i <= n; i += 2)
    {
        seno += sign * term;
        sign *= -1;
        term *= (x * x) / ((i + 1) * (i + 2));
    }

    return seno;
}

vector<double> generateXValues(double start, double end, double step)
{
    vector<double> xValues;
    for (double x = start; x <= end; x += step)
    {
        xValues.push_back(x);
    }
    return xValues;
}

void drawFunction(const vector<double> &xValues, const vector<double> &yValues, float r, float g, float b)
{
    glLoadIdentity();
    glOrtho(-10, 10, -2, 2, -1, 1);

    glColor3f(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2f(-10.0, 0.0);
    glVertex2f(10.0, 0.0);
    glVertex2f(0.0, -2.0);
    glVertex2f(0.0, 2.0);
    glEnd();

    glColor3f(r, g, b);
    glBegin(GL_LINE_STRIP);

    for (size_t i = 0; i < xValues.size(); ++i)
    {
        glVertex2f(xValues[i], yValues[i]);
    }
    glEnd();
}

void iterateAndDraw(int numberOfLines, const std::vector<double>& xValues) {
    for (int i = 0; i < numberOfLines; ++i) {
        std::vector<double> yCosValues;
        double yOffset = 1.8 - i * 0.4;
        for (double x : xValues) {
            yCosValues.push_back(customCos(x) + yOffset);
        }
        drawFunction(xValues, yCosValues, static_cast<float>(i) / numberOfLines, 0.0, 1.0 - static_cast<float>(i) / numberOfLines);
    }
}

void measure(void (*func)(int, const std::vector<double>&), int numberOfLines, const std::vector<double>& xValues) {
    auto start = std::chrono::high_resolution_clock::now();
    
    func(numberOfLines, xValues);
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "\nTiempo para graficar " << numberOfLines << " funciones: " << duration.count() << " milisegundos\n";
    
}

void drawBoundedFunction(const std::function<double(double)> &func, double startX, double endX, float r, float g, float b, double verticalOffset)
{
    glLoadIdentity();
    glOrtho(-10, 10, -2, 2, -1, 1);

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

int main() {

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
    double step = 0.005;    

    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);

        vector<double> xValues = generateXValues(-10.0, 10.0, step);
        
        auto start = chrono::high_resolution_clock::now();

        // TODO: Se puede encapsular esta medición de tiempo en una función
        // que reciba la función a la que se le va a medir el tiempo
        // como parámetro?. De paso sacar el for a una función para poder perfilar.

         // Call the measure function with iterateAndDraw as a parameter
        measure(iterateAndDraw, numberOfLines, xValues);

        
        
        auto start = std::chrono::high_resolution_clock::now();
        // Calculate and draw the cosine functions at different Y positions
        for (int i = 0; i < numberOfLines; ++i)
        {
            vector<double> yCosValues;

            double yOffset = 1.8 - i * 0.4; // Adjust the yOffset for closer lines
            double verticalOffSet = (i % 2 == 0) ? -(i / 2) * 0.5 : ((i + 1) / 2) * 0.5;

            float r = static_cast<float>(i % 3);
            float g = static_cast<float>((i + 1) % 3);
            float b = static_cast<float>((i + 2) % 3);


            drawBoundedFunction(customSen, -5, 5, r, g, b, verticalOffSet);

            for (double x : xValues)
            {
                yCosValues.push_back(customCos(x) + yOffset);
            }

            // Draw the cosine function
            drawFunction(xValues, yCosValues, static_cast<float>(i) / numberOfLines, 0.0, 1.0 - static_cast<float>(i) / numberOfLines);
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duration = end - start;

        cout << "\nTiempo para graficar " << numberOfLines << " funciones: " << duration.count() << " milisegundos\n";

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
