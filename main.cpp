#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Define los valores máximos y mínimos para el juego
const int MAX = std::numeric_limits<int>::max();
const int MIN = std::numeric_limits<int>::min();

// Función que imprime los palitos actuales en el juego
void imprimirPalitos(std::vector<std::string> palitos){
    for(int i = 0; i < palitos.size(); i++) {
        std::cout << palitos[i] << " ";
    }
    std::cout << std::endl;
}

// Función que remueve los palitos del juego
std::vector<std::string> removerPalitos(std::vector<std::string> palitos, int numPalitos){
    for(int i = 0; i < numPalitos; i++){
        palitos.pop_back();
    }
    return palitos;
}

// Algoritmo minimax para decidir el mejor movimiento
int minimax(std::vector<std::string> estado, int profundidad, bool esJugadorMax) {
    // Caso base: si solo queda un palito, gana el jugador que no está jugando
    if (estado.size() == 1) {
        if (esJugadorMax) {
            return MIN;
        } else {
            return MAX;
        }
    }

    // Caso base: si se alcanza la profundidad máxima, se devuelve 0
    if (profundidad == 0) {
        return 0;
    }

    // Si es el turno del jugador Max, busca el valor máximo
    if (esJugadorMax) {
        int mejorValor = MIN;
        for (int i = 1; i <= 3; i++) {
            if (estado.size() >= i) {
                std::vector<std::string> nuevoEstado = removerPalitos(estado, i);
                int valor = minimax(nuevoEstado, profundidad - 1, false);
                mejorValor = std::max(mejorValor, valor);
            }
        }
        return mejorValor;
    } else {
        // Si es el turno del jugador Min, busca el valor mínimo
        int mejorValor = MAX;
        for (int i = 1; i <= 3; i++) {
            if (estado.size() >= i) {
                std::vector<std::string> nuevoEstado = removerPalitos(estado, i);
                int valor = minimax(nuevoEstado, profundidad - 1, true);
                mejorValor = std::min(mejorValor, valor);
            }
        }
        return mejorValor;
    }
}

// Función que controla los movimientos de la IA
std::vector<std::string> movimientoIA(std::vector<std::string> palitos){
    std::srand(std::time(nullptr));
    int mejorValor = MIN;
    int mejorMovimiento = 1;
    for (int i = 1; i <= 3; i++) {
        if (palitos.size() >= i) {
            std::vector<std::string> nuevoEstado = removerPalitos(palitos, i);
            int valor = minimax(nuevoEstado, 5, false);
            if (valor > mejorValor) {
                mejorValor = valor;
                mejorMovimiento = i;
            }
        }
    }
    std::cout << "La IA elige " << mejorMovimiento << " palitos." << std::endl;
    return removerPalitos(palitos, mejorMovimiento);
}

int main() {
    // Inicializa el vector de palitos
    std::vector<std::string> palitos;
    int cantidadPalitosInicial;

    std::cout << "Introduce la cantidad inicial de palitos a jugar: " << std::endl;
    std::cin >> cantidadPalitosInicial;

    for(int i = 0; i < cantidadPalitosInicial; i++){
        palitos.push_back(" | ");
    }

    imprimirPalitos(palitos);
    int numPalitos = 0;

    do{
        std::cout << "Turno del jugador: " << std::endl;
        std::cin >> numPalitos;
        // Asegurarse de que el jugador elige entre 1 y 3 palitos
        if(numPalitos != 1 && numPalitos != 2 && numPalitos != 3){
            do{
                std::cout << "Solo puedes elegir entre 1 y 3 palitos para quitar: " << std::endl;
                std::cin >> numPalitos;
            }while(numPalitos != 1 && numPalitos != 2 && numPalitos != 3);
        }
        std::cout << numPalitos << std::endl;
        palitos = removerPalitos(palitos, numPalitos);
        // Si solo queda un palito, el jugador gana
        if(palitos.size() == 1) {
            std::cout << "GANADOR: JUGADOR " << std::endl;
            return 0;
        }
        imprimirPalitos(palitos);
        std::cout << "Turno de la IA: " << std::endl;
        palitos = movimientoIA(palitos);
        imprimirPalitos(palitos);
        // Si solo queda un palito, la IA gana
        if(palitos.size() == 1) {
            std::cout << "GANADOR: IA " << std::endl;
            return 0;
        }
    }while(!palitos.empty());

    return 0;
}
