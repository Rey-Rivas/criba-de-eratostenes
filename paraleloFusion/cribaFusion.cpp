#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

void cribaDeEratostenesParalela(unsigned long long n) {
    // Crear un vector booleano para números hasta n
    std::vector<bool> esPrimo(n + 1, true);

    // Eliminar el 0 y el 1, que no son primos
    esPrimo[0] = esPrimo[1] = false;

    unsigned long long raiz = static_cast<unsigned long long>(std::sqrt(n));

    // Criba inicial: marcar múltiplos de primos hasta √n
    #pragma omp parallel
    {
        // Compartir el cálculo de los primos base hasta √n
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

    // Opcional: imprimir los números primos
    /*
    std::cout << "Números primos menores o iguales a " << n << ": ";
    for (unsigned long long p = 2; p <= n; ++p) {
        if (esPrimo[p]) {
            std::cout << p << " ";
        }
    }
    std::cout << std::endl;
    */
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

    // Medir el tiempo de ejecución usando omp_get_wtime
    double inicio = omp_get_wtime();
    cribaDeEratostenesParalela(n);
    double fin = omp_get_wtime();

    std::cout << "Tiempo de ejecución: " << (fin - inicio) << " segundos" << std::endl;

    return 0;
}
