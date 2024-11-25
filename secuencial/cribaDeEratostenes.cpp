#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

void cribaDeEratostenes(unsigned long long n) {
    // Crear un vector booleano para números hasta n
    std::vector<bool> esPrimo(n + 1, true);

    // Eliminar el 0 y el 1, que no son primos
    esPrimo[0] = esPrimo[1] = false;

    // Algoritmo de la criba de Eratóstenes
    for (unsigned long long p = 2; p * p <= n; ++p) {
        if (esPrimo[p]) {
            // Marcar los múltiplos de p como no primos
            for (unsigned long long i = p * p; i <= n; i += p) {
                esPrimo[i] = false;
            }
        }
    }

    // Imprimir todos los números primos menores o iguales a n
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

    auto inicio = std::chrono::high_resolution_clock::now();
    cribaDeEratostenes(n);
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;

    std::cout << "Tiempo de ejecución: " << duracion.count() << " segundos" << std::endl;

    return 0;
}