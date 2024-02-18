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

### Analisis de Optimizaciones por compilador

Utilizamos Compiler explorer para ver la diferencia de codigo generado por distintos niveles de optimizacion sobre el codigo de `FuncionesMath.cpp`. Dandonos estos resultados:

En `-O0`:

```asm
cosMath(double):
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        movsd   QWORD PTR [rbp-8], xmm0
        mov     rax, QWORD PTR [rbp-8]
        movq    xmm0, rax
        call    cos
        movq    rax, xmm0
        movq    xmm0, rax
        leave
        ret
senMath(double):
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        movsd   QWORD PTR [rbp-8], xmm0
        mov     rax, QWORD PTR [rbp-8]
        movq    xmm0, rax
        call    sin
        movq    rax, xmm0
        movq    xmm0, rax
        leave
        ret
customCos(double):
        push    rbp
        mov     rbp, rsp
        movsd   QWORD PTR [rbp-40], xmm0
        mov     DWORD PTR [rbp-24], 1000
        movsd   xmm0, QWORD PTR .LC0[rip]
        movsd   QWORD PTR [rbp-8], xmm0
        movsd   xmm0, QWORD PTR .LC0[rip]
        movsd   QWORD PTR [rbp-16], xmm0
        mov     DWORD PTR [rbp-20], 1
        jmp     .L6
.L7:
        movsd   xmm0, QWORD PTR [rbp-40]
        movq    xmm1, QWORD PTR .LC1[rip]
        xorpd   xmm0, xmm1
        mulsd   xmm0, QWORD PTR [rbp-40]
        mov     eax, DWORD PTR [rbp-20]
        add     eax, eax
        sub     eax, 1
        imul    eax, DWORD PTR [rbp-20]
        add     eax, eax
        pxor    xmm1, xmm1
        cvtsi2sd        xmm1, eax
        divsd   xmm0, xmm1
        movsd   xmm1, QWORD PTR [rbp-16]
        mulsd   xmm0, xmm1
        movsd   QWORD PTR [rbp-16], xmm0
        movsd   xmm0, QWORD PTR [rbp-8]
        addsd   xmm0, QWORD PTR [rbp-16]
        movsd   QWORD PTR [rbp-8], xmm0
        add     DWORD PTR [rbp-20], 1
.L6:
        cmp     DWORD PTR [rbp-20], 999
        jle     .L7
        movsd   xmm0, QWORD PTR [rbp-8]
        movq    rax, xmm0
        movq    xmm0, rax
        pop     rbp
        ret
customSen(double):
        push    rbp
        mov     rbp, rsp
        movsd   QWORD PTR [rbp-40], xmm0
        mov     DWORD PTR [rbp-28], 1000
        pxor    xmm0, xmm0
        movsd   QWORD PTR [rbp-8], xmm0
        movsd   xmm0, QWORD PTR [rbp-40]
        movsd   QWORD PTR [rbp-16], xmm0
        mov     DWORD PTR [rbp-20], 1
        mov     DWORD PTR [rbp-24], 1
        jmp     .L10
.L11:
        pxor    xmm0, xmm0
        cvtsi2sd        xmm0, DWORD PTR [rbp-20]
        mulsd   xmm0, QWORD PTR [rbp-16]
        movsd   xmm1, QWORD PTR [rbp-8]
        addsd   xmm0, xmm1
        movsd   QWORD PTR [rbp-8], xmm0
        neg     DWORD PTR [rbp-20]
        movsd   xmm0, QWORD PTR [rbp-40]
        mulsd   xmm0, xmm0
        mov     eax, DWORD PTR [rbp-24]
        lea     edx, [rax+1]
        mov     eax, DWORD PTR [rbp-24]
        add     eax, 2
        imul    eax, edx
        pxor    xmm1, xmm1
        cvtsi2sd        xmm1, eax
        divsd   xmm0, xmm1
        movsd   xmm1, QWORD PTR [rbp-16]
        mulsd   xmm0, xmm1
        movsd   QWORD PTR [rbp-16], xmm0
        add     DWORD PTR [rbp-24], 2
.L10:
        cmp     DWORD PTR [rbp-24], 1000
        jle     .L11
        movsd   xmm0, QWORD PTR [rbp-8]
        movq    rax, xmm0
        movq    xmm0, rax
        pop     rbp
        ret
.LC0:
        .long   0
        .long   1072693248
.LC1:
        .long   0
        .long   -2147483648
        .long   0
        .long   0
```

- Conclusion de `-O0`: Vemos que el compilador no ha optimizado las funciones `customCos` y `customSen` generando un codigo de 113 lineas.

En `-O1`:

```asm
cosMath(double):
        sub     rsp, 8
        call    cos
        add     rsp, 8
        ret
senMath(double):
        sub     rsp, 8
        call    sin
        add     rsp, 8
        ret
customCos(double):
        movapd  xmm4, xmm0
        xorpd   xmm4, XMMWORD PTR .LC1[rip]
        mulsd   xmm4, xmm0
        mov     ecx, 1
        mov     eax, 1
        movsd   xmm1, QWORD PTR .LC0[rip]
        movapd  xmm0, xmm1
.L6:
        mov     edx, ecx
        imul    edx, eax
        add     edx, edx
        pxor    xmm3, xmm3
        cvtsi2sd        xmm3, edx
        movapd  xmm2, xmm4
        divsd   xmm2, xmm3
        mulsd   xmm1, xmm2
        addsd   xmm0, xmm1
        add     eax, 1
        add     ecx, 2
        cmp     eax, 1000
        jne     .L6
        ret
customSen(double):
        movapd  xmm4, xmm0
        mulsd   xmm4, xmm0
        mov     eax, 1
        mov     ecx, 1
        pxor    xmm2, xmm2
.L9:
        pxor    xmm1, xmm1
        cvtsi2sd        xmm1, ecx
        mulsd   xmm1, xmm0
        addsd   xmm2, xmm1
        neg     ecx
        lea     edx, [rax+1]
        add     eax, 2
        imul    edx, eax
        pxor    xmm3, xmm3
        cvtsi2sd        xmm3, edx
        movapd  xmm1, xmm4
        divsd   xmm1, xmm3
        mulsd   xmm0, xmm1
        cmp     eax, 1001
        jne     .L9
        movapd  xmm0, xmm2
        ret
.LC0:
        .long   0
        .long   1072693248
.LC1:
        .long   0
        .long   -2147483648
        .long   0
        .long   0
```

- Conclusion de `-O1`: Vemos que el compilador ha optimizado las funciones `customCos` y `customSen` reduciendo el codigo a 65 lineas.

En `-O2`:

```asm
cosMath(double):
        jmp     cos
senMath(double):
        jmp     sin
customCos(double):
        movapd  xmm4, xmm0
        mov     ecx, 1
        mov     eax, 1
        xorpd   xmm4, XMMWORD PTR .LC1[rip]
        mulsd   xmm4, xmm0
        movsd   xmm0, QWORD PTR .LC0[rip]
        movapd  xmm1, xmm0
.L5:
        mov     edx, ecx
        pxor    xmm3, xmm3
        movapd  xmm2, xmm4
        add     ecx, 2
        imul    edx, eax
        add     eax, 1
        add     edx, edx
        cvtsi2sd        xmm3, edx
        divsd   xmm2, xmm3
        mulsd   xmm0, xmm2
        addsd   xmm1, xmm0
        cmp     eax, 1000
        jne     .L5
        movapd  xmm0, xmm1
        ret
customSen(double):
        movapd  xmm4, xmm0
        mov     eax, 1
        mov     ecx, 1
        mulsd   xmm4, xmm0
        pxor    xmm2, xmm2
.L8:
        pxor    xmm1, xmm1
        lea     edx, [rax+1]
        pxor    xmm3, xmm3
        add     eax, 2
        cvtsi2sd        xmm1, ecx
        neg     ecx
        imul    edx, eax
        mulsd   xmm1, xmm0
        cvtsi2sd        xmm3, edx
        addsd   xmm2, xmm1
        movapd  xmm1, xmm4
        divsd   xmm1, xmm3
        mulsd   xmm0, xmm1
        cmp     eax, 1001
        jne     .L8
        movapd  xmm0, xmm2
        ret
.LC0:
        .long   0
        .long   1072693248
.LC1:
        .long   0
        .long   -2147483648
        .long   0
        .long   0
```

- Conclusion de `-O2`: Vemos que el compilador ha optimizado las funciones `customCos` y `customSen` reduciendo el codigo a 60 lineas.

En `-O3` ya no vemos diferencias con `-O2` por lo que no lo incluimos.

### Conclusiones finales

La diferencia principal entre las versiones generadas con diferentes niveles de optimización (O0 y O2) radica en la eficiencia y la estrategia de optimización utilizada. Aquí hay algunas diferencias clave:

Directivas de Salto:

- En la versión de O0, se usan las instrucciones call cos y call sin para llamar a las funciones de la biblioteca estándar cos y sin respectivamente.
  En la versión de O2, se utilizan instrucciones de salto (jmp cos y jmp sin) para saltar directamente a las implementaciones de las funciones cos y sin en la biblioteca estándar. Esto evita la sobrecarga de las llamadas de función.
  Optimización de Bucle:

- La versión de O0 utiliza un bucle explícito para calcular la aproximación de las funciones trigonométricas personalizadas (customCos y customSen). El bucle se ejecuta 999 veces en ambos casos.
  En la versión de O2, las funciones personalizadas se implementan con un enfoque diferente. Se utilizan técnicas de optimización para reducir la cantidad de cálculos repetidos y se logra el mismo resultado sin necesidad de un bucle explícito.
  Registro de Propósito General:

- En la versión de O0, se utilizan registros de propósito general como eax, edx, y ecx para algunas operaciones aritméticas y de control de bucle.
  En la versión de O2, el uso de registros de propósito general se minimiza, lo que puede mejorar el rendimiento al reducir el número de transferencias entre la memoria y los registros.
  Uso de Instrucciones SIMD:

- En la versión de O2, se utilizan instrucciones SIMD (Single Instruction, Multiple Data) como mulsd, addsd, y divsd para realizar cálculos en paralelo en datos de doble precisión, lo que puede mejorar significativamente el rendimiento en procesadores modernos que admiten estas instrucciones.

En resumen, la versión de O2 está más optimizada y utiliza técnicas avanzadas de optimización de compiladores para mejorar el rendimiento y la eficiencia del código generado en comparación con la versión de O0.
