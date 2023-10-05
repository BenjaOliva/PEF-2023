
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

Compile the project (in my case I'm using WSL)
* Choose the compile optimizarion level that you prefer (-O1, -O0, etc)

```bash
  g++ -O1 -o GraficarFunciones GraficarFunciones.cpp $(pkg-config --cflags --libs glfw3 
glew)
```

🌟Run the project

```bash
  ./GraficarFunciones
```