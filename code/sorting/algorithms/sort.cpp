#include <algorithm>
#include <vector>
#include "sort.hpp"

std::vector<int> sortArray(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());  // std::sort de la STL
    return arr;
}
