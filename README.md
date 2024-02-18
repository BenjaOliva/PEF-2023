# Proyecto PEF - 2023

Este proyecto corresponde a la materia PEF dicatado en el segundo semestre de la carrera de Ingenieria en Informatica de la Universidad Blas Pascal en el año 2023.

## 🚀 Acerca del proyecto

Este repositorio contiene un proyecto escrito en C++ para graficar en un plano distintas lineas utilizando las funciones matematicas del sen y cos sin usar una libreria para poder calcular la performance para los distintos tipos de optimización.

## Instrucciones

Clone the project

```bash
  git clone https://github.com/BenjaOliva/PEF-2023.git
```

Go to the project directory

```bash
  cd PEF-2023
```

Run this command to install required libs

```bash
  sudo apt-get install libglfw3 libglfw3-dev libglew-dev mesa-common-dev
```

After the command, run this lines too

```bash
  pkg-config --libs glfw3
  pkg-config --libs glew
```

Compile the project

- Access the `src` folder

```bash
  cd src
```

- Compile the project using the following commands:

- Choose the compile optimizarion level that you prefer (-O1, -O0, etc)

For WSL:

```bash
  g++ -O1 -o Execute main.cpp GraficarFunciones.cpp FuncionesMath.cpp $(pkg-config --cflags --libs glfw3
glew)
```

For macOS:

```bash
  g++ -std=c++14 -o Execute main.cpp GraficarFunciones.cpp FuncionesMath.cpp -framework OpenGL -framework GLUT $(pkg-config --cflags --libs glfw3 glew)
```

For Linux:

```bash
g++ -o Execute main.cpp GraficarFunciones.cpp FuncionesMath.cpp -lGL -lGLEW -lglfw
```

Also for macOS you might have to add a .vscode folder with a c_cpp_properties.json, for example:

```json
{
  "configurations": [
    {
      "name": "Mac",
      "includePath": [
        "${workspaceFolder}/**",
        "/opt/homebrew/Cellar/glfw/3.3.8/include",
        "/opt/homebrew/Cellar/googletest/1.14.0/include"
      ],
      "defines": [],
      "macFrameworkPath": [
        "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks"
      ],
      "compilerPath": "/usr/bin/clang",
      "cStandard": "c17",
      "cppStandard": "c++17",
      "intelliSenseMode": "macos-clang-arm64"
    }
  ],
  "version": 4
}
```

🌟Run the project

```bash
  ./Execute
```

## Test the project

- Install the Google Test library

For MacOS:

```bash
  brew install googletest
```

For Linux:

```bash
  sudo apt-get install libgtest-dev
```

- From the root folder, run the following command:

```bash
  cd test
```

- Compile the test using the following commands:

For MacOS:

```bash
  g++ -std=c++14 -o tests tests.cpp ../src/FuncionesMath.cpp -I/opt/homebrew/Cellar/googletest/1.14.0/include -L/opt/homebrew/Cellar/googletest/1.14.0/lib -lgtest -lgtest_main -pthread
```

For Linux:

```bash
  g++ -o tests tests.cpp ../src/FuncionesMath.cpp -lgtest -lgtest_main -pthread
```

- 🚀 Run the test

```bash
  ./tests
```

- We run 14 tests and all of them passed! 🎉