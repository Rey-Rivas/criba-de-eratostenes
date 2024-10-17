#include <iostream>
#include <vector>
#include <cstdlib>  // Para usar atoi()
#include <chrono>   // Para medir el tiempo

void cribaDeEratostenes(int n) {
    // Crear un vector booleano de tamaño n+1, inicializado en true
    std::vector<bool> esPrimo(n + 1, true);

    // Eliminar el 0 y el 1, que no son primos
    esPrimo[0] = esPrimo[1] = false;

    // Algoritmo de la criba de Eratóstenes
    for (int p = 2; p * p <= n; ++p) {
        if (esPrimo[p]) {
            // Marcar los múltiplos de p como no primos
            for (int i = p * p; i <= n; i += p) {
                esPrimo[i] = false;
            }
        }
    }

    // Imprimir todos los números primos menores o iguales a n
    std::cout << "Números primos menores o iguales a " << n << ": ";
    for (int p = 2; p <= n; ++p) {
        if (esPrimo[p]) {
            std::cout << p << " ";
        }
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    // Comprobar si se ha pasado un argumento
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <n>" << std::endl;
        return 1;
    }

    // Convertir el argumento de cadena a entero
    int n = std::atoi(argv[1]);

    if (n < 2) {
        std::cerr << "El valor de n debe ser mayor o igual a 2." << std::endl;
        return 1;
    }

    // Iniciar la medición de tiempo
    auto inicio = std::chrono::high_resolution_clock::now();

    // Ejecutar la criba de Eratóstenes
    cribaDeEratostenes(n);

    // Terminar la medición de tiempo
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;

    // Imprimir el tiempo que tomó en segundos
    std::cout << "Tiempo de ejecución: " << duracion.count() << " segundos" << std::endl;

    return 0;
}
