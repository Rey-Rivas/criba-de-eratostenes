#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

// Función para imprimir números primos
void imprimirPrimos(const std::vector<bool>& esPrimo) {
    std::cout << "Números primos: ";
    for (unsigned long long p = 2; p < esPrimo.size(); ++p) {
        if (esPrimo[p]) {
            std::cout << p << " ";
        }
    }
    std::cout << std::endl;
}

void cribaDeEratostenesParalela(unsigned long long n, std::vector<bool>& esPrimo) {
    // Crear un vector booleano para números hasta n
    esPrimo.assign(n + 1, true);

    // Eliminar el 0 y el 1, que no son primos
    esPrimo[0] = esPrimo[1] = false;

    // Evitar desbordamiento en la condición del bucle
    unsigned long long raizN = static_cast<unsigned long long>(std::sqrt(n));

    // Algoritmo de la criba de Eratóstenes con OpenMP
    #pragma omp parallel for schedule(dynamic)
    for (unsigned long long p = 2; p <= raizN; ++p) {
        if (esPrimo[p]) {
            for (unsigned long long i = p * p; i <= n; i += p) {
                esPrimo[i] = false;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <n> <número_de_hilos>" << std::endl;
        return 1;
    }

    unsigned long long n = std::stoull(argv[1]);
    int numHilos = std::stoi(argv[2]);

    if (n < 2) {
        std::cerr << "El valor de n debe ser mayor o igual a 2." << std::endl;
        return 1;
    }

    if (numHilos <= 0) {
        std::cerr << "El número de hilos debe ser mayor a 0." << std::endl;
        return 1;
    }

    // Configurar el número de hilos en OpenMP
    omp_set_num_threads(numHilos);

    // Vector para almacenar la información de números primos
    std::vector<bool> esPrimo;

    // Medir tiempo usando OpenMP
    double inicio = omp_get_wtime();
    cribaDeEratostenesParalela(n, esPrimo);
    double fin = omp_get_wtime();

    // Imprimir los números primos
    //imprimirPrimos(esPrimo);

    std::cout << "Tiempo de ejecución: " << (fin - inicio) << " segundos" << std::endl;

    return 0;
}