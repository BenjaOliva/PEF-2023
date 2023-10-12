#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <functional>

//Probando el git

int windowWidth = 1024;
int windowHeight = 720;

double customCos(double x)
{
    constexpr int terms = 100000;
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
    const int n = 100000;
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

std::vector<double> generateXValues(double start, double end, double step)
{
    std::vector<double> xValues;
    for (double x = start; x <= end; x += step)
    {
        xValues.push_back(x);
    }
    return xValues;
}

void drawFunction(const std::vector<double> &xValues, const std::vector<double> &yValues, float r, float g, float b)
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

void drawBoundedFunction(const std::function<double(double)> &func, double startX, double endX, float r, float g, float b)
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
        glVertex2f(x, y);
    }
    glEnd();
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Error al inicializar GLFW" << std::endl;
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "Gráfica de Funciones", NULL, NULL);
    if (!window)
    {
        std::cerr << "Error al crear la ventana GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    int numberOfLines = 10; // Set the number of replicated lines
    double step = 0.005;    // Adjust the step size for closer lines

    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);

        // Generate x values with a smaller step
        std::vector<double> xValues = generateXValues(-10.0, 10.0, step);

        // TODO: Se puede encapsular esta medición de tiempo en una función
        // que reciba la función a la que se le va a medir el tiempo
        // como parámetro?. De paso sacar el for a una función para poder perfilar.
        auto start = std::chrono::high_resolution_clock::now();
        // Calculate and draw the cosine functions at different Y positions
        for (int i = 0; i < numberOfLines; ++i)
        {
            std::vector<double> yCosValues;

            double yOffset = 1.8 - i * 0.4; // Adjust the yOffset for closer lines

            for (double x : xValues)
            {
                yCosValues.push_back(customCos(x) + yOffset);
            }

            // Draw the cosine function
            drawFunction(xValues, yCosValues, static_cast<float>(i) / numberOfLines, 0.0, 1.0 - static_cast<float>(i) / numberOfLines);
        }

        // Dibuja una función acotada, por ejemplo, el seno entre -2π y 2π
        drawBoundedFunction(customSen, -2 * 3.14, 2 * 3.14, 1.0, 0.0, 0.0);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        std::cout << "\nTiempo para graficar " << numberOfLines << " funciones: " << duration.count() << " milisegundos\n";

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
