#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

void cribaDeEratostenesParalela(unsigned long long n) {
    // Crear un vector booleano para números hasta n
    std::vector<bool> esPrimo(n + 1, true);

    // Eliminar el 0 y el 1, que no son primos
    esPrimo[0] = esPrimo[1] = false;

    // Algoritmo de la criba de Eratóstenes con OpenMP
    #pragma omp parallel for schedule(dynamic)
    for (unsigned long long p = 2; p * p <= n; ++p) {
        if (esPrimo[p]) {
            for (unsigned long long i = p * p; i <= n; i += p) {
                esPrimo[i] = false;
            }
        }
    }

    // Imprimir los números primos (si lo deseas, puedes descomentar esta parte)
    /*std::cout << "Números primos menores o iguales a " << n << ": ";
    for (unsigned long long p = 2; p <= n; ++p) {
        if (esPrimo[p]) {
            std::cout << p << " ";
        }
    }
    std::cout << std::endl;*/
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <n>" << std::endl;
        return 1;
    }

    unsigned long long n = std::stoull(argv[1]);

    if (n < 2) {
        std::cerr << "El valor de n debe ser mayor o igual a 2." << std::endl;
        return 1;
    }

    // Medir tiempo usando OpenMP
    double inicio = omp_get_wtime();
    cribaDeEratostenesParalela(n);
    double fin = omp_get_wtime();

    std::cout << "Tiempo de ejecución: " << (fin - inicio) << " segundos" << std::endl;

    return 0;
}
