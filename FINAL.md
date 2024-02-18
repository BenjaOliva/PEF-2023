# Optimizaciones y comparaciones

El proyecto cuenta con distintos niveles de optimización para poder comparar el rendimiento de cada uno de ellos. Para poder compilar el proyecto con distintos niveles de optimización, se debe cambiar el flag de optimización en el comando de compilación.

## Configuración de version anterior

- Cantidad de funciones a graficar: 20
- Cantidad de step: 0.5
- Cantidad de termino: 10.000

#### Tiempo promedio de dibujado: 415.8 ms

## Confuguación de versión optimizada - Final

- Cantidad de funciones a graficar: 20
- Cantidad de step: 0.15
- Cantidad de termino: 1000

#### Tiempo promedio de dibujado: 100 ms

## Comentarios finales

Como se puede observar, el tiempo de dibujado se redujo considerablemente. Esto se debe a que se redujo la cantidad de terminos a graficar y el step. Además, se optimizaron las funciones de dibujado y se eliminaron las funciones que no se utilizaban.

Tambien hemos probado reducir el valor de terminos a numeros mas bajos donde hemos obtenido tiempos mas rapidos comparado a las funciones de la libreria math.h pero como contraparte se pierde precision en los calculos.

