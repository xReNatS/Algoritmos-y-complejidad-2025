// sequence_difference.hpp
#ifndef SEQUENCE_DIFFERENCE_HPP
#define SEQUENCE_DIFFERENCE_HPP

#include <string>
#include <vector>
#include <utility>

// Función principal del algoritmo de fuerza bruta.
// Recibe dos secuencias y devuelve un vector de pares con las diferencias mínimas.
std::vector<std::pair<std::string, std::string>>
resolver_diferencias(const std::string& secuencia_s, const std::string& secuencia_t);

#endif // SEQUENCE_DIFFERENCE_HPP
