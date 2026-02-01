#include <iostream>
#include <omp.h>

#define N 1000
#define CHUNK 150
#define MOSTRAR 20

void imprimeArreglo(const float *d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";

    float a[N], b[N], c[N];
    int i;

    // Inicialización
    for (i = 0; i < N; i++)
    {
        a[i] = i * 10.0f;
        b[i] = (i + 3) * 3.7f;
    }

    int pedazos = CHUNK;

    // Suma en paralelo
    #pragma omp parallel for shared(a, b, c, pedazos) private(i) schedule(static, pedazos)
    for (i = 0; i < N; i++)
    {
        c[i] = a[i] + b[i];

        // Verificación de OpenMP (sin saturar salida)
        if (i % 100 == 0)
        {
            #pragma omp critical
            std::cout << "Hilo " << omp_get_thread_num()
                      << " ejecutando i = " << i << std::endl;
        }
    }

    std::cout << "\nImprimiendo los primeros " << MOSTRAR << " valores del arreglo a:\n";
    imprimeArreglo(a);

    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo b:\n";
    imprimeArreglo(b);

    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo c:\n";
    imprimeArreglo(c);

    return 0;
}

void imprimeArreglo(const float *d)
{
    for (int x = 0; x < MOSTRAR; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}
