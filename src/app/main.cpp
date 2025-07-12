#include "config.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <map>

const int NUM_COLUMNS = 5;
const std::string FILENAME = "Tris.csv";

// Función para limpiar línea y extraer dígitos
std::vector<std::string> splitDigits(const std::string& line) {
    std::vector<std::string> tokens;
    std::istringstream ss(line);
    std::string tok;
    while (std::getline(ss, tok, ',')) {
        tok.erase(0, tok.find_first_not_of(" \t\r\n"));
        tok.erase(tok.find_last_not_of(" \t\r\n") + 1);
        if (tok.size() == 1 && std::isdigit(tok[0]))
            tokens.push_back(tok);
    }
    return tokens;
}

// Función para compactar una columna eliminando duplicados
std::vector<char> processColumn(const std::vector<std::string>& rawData) {
    std::vector<char> result;
    std::unordered_map<char, bool> seen;

    for (const auto& val : rawData) {
        char digit = val[0];
        if (!seen.count(digit)) {
            seen[digit] = true;
            result.push_back(digit);
        }
    }

    // Rellenar si hay menos de 10 valores
    while (result.size() < 10)
        result.push_back('?');

    return result;
}

int main() {
	std::cout << "tris-stalker v" << VERSION << '\n';
	std::cout << "------------------------------\n";

    std::ifstream file(FILENAME);
    if (!file.is_open()) {
        std::cerr << "Error: no se pudo abrir '" << FILENAME << "'\n";
        return 1;
    }

    std::string line;

    // Saltar encabezado
    if (!std::getline(file, line)) {
        std::cerr << "Archivo vacío.\n";
        return 1;
    }

    std::vector<std::vector<std::string>> rawData(NUM_COLUMNS);

    while (std::getline(file, line)) {
        auto tokens = splitDigits(line);
        if (tokens.size() != NUM_COLUMNS) continue;

        for (int col = 0; col < NUM_COLUMNS; ++col) {
            rawData[col].push_back(tokens[col]);
        }
    }

    // Procesar cada columna → obtener vector de chars únicos, en orden
    std::vector<std::vector<char>> matrix(NUM_COLUMNS);
    for (int col = 0; col < NUM_COLUMNS; ++col) {
        matrix[col] = processColumn(rawData[col]);
    }
	

    // Imprimir matriz procesada
    std::cout << "\n--- Matriz procesada (columnas con valores únicos) ---\n";
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < NUM_COLUMNS; ++col) {
            std::cout << matrix[col][row] << " ";
        }
        std::cout << '\n';
    }

    // Bucle interactivo
    std::string inputNumber;
    int n;

    while (true) {
        std::cout << "\nIngresa un número de al menos 5 dígitos (o 'q' para salir): ";
        std::cin >> inputNumber;

        if (inputNumber == "q" || inputNumber == "Q")
            break;

        if (inputNumber.length() < 5 || !std::all_of(inputNumber.begin(), inputNumber.end(), ::isdigit)) {
            std::cout << "Por favor ingresa un número válido de al menos 5 dígitos.\n";
            continue;
        }

        std::cout << "¿Cuántas combinaciones deseas obtener? ";
        std::cin >> n;

        if (n <= 0 || n > 100) {
            std::cout << "Por favor ingresa un valor entre 1 y 100.\n";
            continue;
        }

        std::vector<std::string> results;
        std::vector<int> indices(NUM_COLUMNS, 9); // empezamos desde abajo

        while ((int)results.size() < n) {
            std::map<char, int> availableDigits; // Conteo dinámico de uso

            // Inicializar conteo
            for (char c : inputNumber)
                availableDigits[c]++;

            std::string combo;
            bool found = true;

            for (int col = 0; col < NUM_COLUMNS; ++col) {
                bool match = false;
                for (int i = indices[col]; i >= 0; --i) {
                    char candidate = matrix[col][i];

                    if (availableDigits.count(candidate) && availableDigits[candidate] > 0) {
                        combo += candidate;
                        availableDigits[candidate]--;
                        indices[col] = i - 1;
                        match = true;
                        break;
                    }
                }
                if (!match) {
                    found = false;
                    // resetear índices para subir más arriba
                    for (int c = 0; c < NUM_COLUMNS; ++c)
                        indices[c]--;
                    break;
                }
            }

            if (found) {
                results.push_back(combo);
            } else {
                // Si ya no hay más opciones
                if (std::all_of(indices.begin(), indices.end(), [](int i){ return i < 0; }))
                    break;
            }
        }

        if (results.empty()) {
            std::cout << "No se encontraron combinaciones válidas.\n";
        } else {
            std::cout << "\n--- Combinaciones sugeridas ---\n";
            for (int i = 0; i < (int)results.size(); ++i) {
                std::cout << i+1 << ". " << results[i] << '\n';
            }
        }
    }

    std::cout << "¡Gracias por usar el programa!\n";
    return 0;
}
