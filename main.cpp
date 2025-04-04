
/*
* Fernando Rocha Martínez A00836634
*
* Instrucciones:
* Utilizando la técnica de programación de "algoritmos avaros" y "programación dinámica",
* escribe en equipos de máximo dos personas, en C++ un programa que resuelve el problema del cambio de monedas.
*
* El programa recibe un número entero N, seguido de N valores enteros (uno en cada línea)
* que representan las diferentes denominaciones disponibles de las monedas.
* Seguido de esto, el programa recibe dos números enteros: P y Q,
* (uno en cada línea) por la entrada estándar,
* que representan P: el precio de un producto dado y Q: es el billete o moneda con el que se paga dicho producto.
*
* La salida del programa es una lista de N valores correspondientes
* al número de monedas de cada denominación, de mayor a menor, una en cada línea,
* que se tienen que dar para dar el cambio por el producto pagado,
* primero utilizando programación dinámica y luego utilizando un algoritmo avaro.
*
* Complejidad computacional:
* - El algoritmo de programación dinámica tiene una complejidad de O(N * cambio), donde:
*   - N es la cantidad de denominaciones de monedas.
*   - cambio es la cantidad a devolver.
* - El algoritmo avaro tiene una complejidad de O(N), ya que recorre las denominaciones una sola vez.
*
* Correr con:
* g++ -std=c++17 -o main main.cpp
* ./main
*
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * @brief Calcula el cambio óptimo utilizando programación dinámica.
 * @param denominaciones Lista de denominaciones de monedas.
 * @param cambio Monto de cambio a devolver.
 */
void cambio_dinamico(const vector<int>& denominaciones, int cambio) {
    int n = denominaciones.size();
    vector<int> dp(cambio + 1, INT_MAX);
    vector<int> seleccion(cambio + 1, -1);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = denominaciones[i]; j <= cambio; j++) {
            if (dp[j - denominaciones[i]] != INT_MAX && dp[j - denominaciones[i]] + 1 < dp[j]) {
                dp[j] = dp[j - denominaciones[i]] + 1;
                seleccion[j] = i;
            }
        }
    }

    vector<int> resultado(n, 0);
    if (dp[cambio] == INT_MAX) {
        for (int i = 0; i < n; i++) {
            cout << "0" << endl;
        }
        return;
    }

    int tempCambio = cambio;
    while (tempCambio > 0) {
        int index = seleccion[tempCambio];
        if (index == -1)
            break;
        resultado[index]++;
        tempCambio -= denominaciones[index];
    }

    for (int i = 0; i < n; i++) {
        cout << resultado[i] << endl;
    }
}

/**
 * @brief Calcula el cambio utilizando un algoritmo avaro.
 * @param denominaciones Lista de denominaciones de monedas.
 * @param cambio Monto de cambio a devolver.
 */
void cambio_avaro(const vector<int>& denominaciones, int cambio) {
    int n = denominaciones.size();
    vector<int> resultado(n, 0);

    for (int i = 0; i < n; i++) {
        resultado[i] = cambio / denominaciones[i];
        cambio %= denominaciones[i];
    }

    for (int i = 0; i < n; i++) {
        cout << resultado[i] << endl;
    }
}

int main() {
    int N;
    cin >> N;

    vector<int> denominaciones(N);
    for (int i = 0; i < N; i++) {
        cin >> denominaciones[i];
    }

    // Ordenar en orden descendente para el algoritmo avaro
    sort(denominaciones.rbegin(), denominaciones.rend());

    int P, Q;
    cin >> P >> Q;

    if (Q < P) {
        cout << "Falta dinero para pagar ese producto" << endl;
    } else if (Q == P) {
        cout << "No hay cambio por dar" << endl;
    } else {
        int cambio = Q - P;

        // Cambio con programación dinámica
        cambio_dinamico(denominaciones, cambio);
        // Cambio con algoritmo avaro
        cambio_avaro(denominaciones, cambio);
    }

    return 0;
}
