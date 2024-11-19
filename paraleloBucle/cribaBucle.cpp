#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

void cribaDeEratostenes(unsigned long long n) {
    // Crear un vector booleano para números hasta n
    std::vector<bool> esPrimo(n + 1, true);

    // Eliminar el 0 y el 1, que no son primos
    esPrimo[0] = esPrimo[1] = false;

    // Algoritmo de la criba de Eratóstenes con paralelización
    unsigned long long limite = std::sqrt(n);

    for (unsigned long long p = 2; p <= limite; ++p) {
        if (esPrimo[p]) {
            // Paralelizar el marcado de múltiplos de p
            #pragma omp parallel for schedule(dynamic)
            for (unsigned long long i = p * p; i <= n; i += p) {
                esPrimo[i] = false;
            }
        }
    }

    // Imprimir todos los números primos menores o iguales a n (comentado para evitar ralentizaciones)
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

    double inicio = omp_get_wtime(); // Inicio del cronómetro
    cribaDeEratostenes(n);
    double fin = omp_get_wtime();   // Fin del cronómetro

    std::cout << "Tiempo de ejecución: " << (fin - inicio) << " segundos" << std::endl;

    return 0;
}
