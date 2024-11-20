#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

// Función que ejecuta la criba de Eratóstenes
void cribaDeEratostenes(unsigned long long n, std::vector<bool>& esPrimo) {
    esPrimo.assign(n + 1, true);

    // Eliminar el 0 y el 1, que no son primos
    esPrimo[0] = esPrimo[1] = false;

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
}

// Función para imprimir números primos
void imprimirPrimos(const std::vector<bool>& esPrimo) {
    std::cout << "Números primos: ";
    for (size_t p = 2; p < esPrimo.size(); ++p) {
        if (esPrimo[p]) {
            std::cout << p << " ";
        }
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <n> <num_hilos>" << std::endl;
        return 1;
    }

    unsigned long long n;
    int numHilos;

    try {
        n = std::stoull(argv[1]);
        numHilos = std::stoi(argv[2]);
    } catch (const std::exception& e) {
        std::cerr << "Error: los argumentos deben ser un número entero válido." << std::endl;
        return 1;
    }

    if (n < 2) {
        std::cerr << "El valor de n debe ser mayor o igual a 2." << std::endl;
        return 1;
    }

    if (numHilos < 1) {
        std::cerr << "El número de hilos debe ser mayor o igual a 1." << std::endl;
        return 1;
    }

    // Configurar el número de hilos en OpenMP
    omp_set_num_threads(numHilos);

    std::vector<bool> esPrimo;

    double inicio = omp_get_wtime(); // Inicio del cronómetro
    cribaDeEratostenes(n, esPrimo);
    double fin = omp_get_wtime();   // Fin del cronómetro

    //imprimirPrimos(esPrimo);

    std::cout << "Tiempo de ejecución: " << (fin - inicio) << " segundos" << std::endl;

    return 0;
}