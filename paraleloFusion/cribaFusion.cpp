#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

// Función para imprimir los números primos
void imprimirPrimos(const std::vector<bool>& esPrimo) {
    std::cout << "Números primos encontrados: ";
    for (size_t i = 2; i < esPrimo.size(); ++i) {
        if (esPrimo[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

void cribaDeEratostenesParalela(unsigned long long n, std::vector<bool>& esPrimo) {
    // Crear un vector booleano para números hasta n
    esPrimo.assign(n + 1, true);

    // Eliminar el 0 y el 1, que no son primos
    esPrimo[0] = esPrimo[1] = false;

    unsigned long long raiz = static_cast<unsigned long long>(std::sqrt(n));

    // Criba inicial: marcar múltiplos de primos hasta √n
    #pragma omp parallel
    {
        #pragma omp for schedule(dynamic)
        for (unsigned long long p = 2; p <= raiz; ++p) {
            if (esPrimo[p]) {
                for (unsigned long long i = p * p; i <= n; i += p) {
                    esPrimo[i] = false;
                }
            }
        }

        // Dividir en bloques y procesar de forma paralela
        #pragma omp for schedule(dynamic)
        for (unsigned long long bloqueInicio = raiz + 1; bloqueInicio <= n; bloqueInicio += raiz) {
            unsigned long long bloqueFin = std::min(bloqueInicio + raiz - 1, n);
            for (unsigned long long p = 2; p <= raiz; ++p) {
                if (esPrimo[p]) {
                    unsigned long long primerMultiplo = std::max(p * p, (bloqueInicio + p - 1) / p * p);
                    for (unsigned long long i = primerMultiplo; i <= bloqueFin; i += p) {
                        esPrimo[i] = false;
                    }
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <n> <num_hilos>" << std::endl;
        return 1;
    }

    unsigned long long n = std::stoull(argv[1]);
    int numHilos = std::stoi(argv[2]);

    if (n < 2) {
        std::cerr << "El valor de n debe ser mayor o igual a 2." << std::endl;
        return 1;
    }

    if (numHilos < 1) {
        std::cerr << "El número de hilos debe ser mayor o igual a 1." << std::endl;
        return 1;
    }

    // Configurar el número de hilos
    omp_set_num_threads(numHilos);

    // Medir el tiempo de ejecución usando omp_get_wtime
    double inicio = omp_get_wtime();
    std::vector<bool> esPrimo;
    cribaDeEratostenesParalela(n, esPrimo);
    double fin = omp_get_wtime();

    std::cout << "Tiempo de ejecución: " << (fin - inicio) << " segundos" << std::endl;

    // Imprimir los números primos
    //imprimirPrimos(esPrimo);

    return 0;
}