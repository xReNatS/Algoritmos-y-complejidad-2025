#ifndef SEQUENCE_DIFFERENCE_DP_HPP
#define SEQUENCE_DIFFERENCE_DP_HPP

#include <string>
#include <vector>
#include <utility>

// Prototipo de función principal para obtener las diferencias entre dos secuencias
std::vector<std::pair<std::string, std::string>>
resolver_diferencias_dp(const std::string& secuencia_s, const std::string& secuencia_t);

#endif // SEQUENCE_DIFFERENCE_DP_HPP