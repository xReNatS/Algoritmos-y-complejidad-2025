//El codigo presente se elaboro con ayuda de IA
#include "sequence_difference.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

// Calcula tabla de LCS
vector<vector<int>> calcular_tabla_lcs(const string &s, const string &t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            dp[i][j] = (s[i - 1] == t[j - 1]) ? (dp[i - 1][j - 1] + 1) : max(dp[i - 1][j], dp[i][j - 1]);
    return dp;
}

// Reconstruye posiciones de LCS
vector<pair<int, int>> reconstruir_lcs(const vector<vector<int>> &dp, const string &s, const string &t) {
    int i = s.size(), j = t.size();
    vector<pair<int, int>> posiciones;
    while (i > 0 && j > 0) {
        if (s[i - 1] == t[j - 1]) {
            posiciones.emplace_back(i - 1, j - 1);
            --i; --j;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }
    reverse(posiciones.begin(), posiciones.end());
    return posiciones;
}

// Función principal exportada
vector<pair<string, string>> resolver_diferencias_dp(const string& secuencia_s, const string& secuencia_t) {
    auto dp = calcular_tabla_lcs(secuencia_s, secuencia_t);
    auto posiciones = reconstruir_lcs(dp, secuencia_s, secuencia_t);

    vector<pair<string, string>> pares_diferencias;
    int previo_s = -1, previo_t = -1;
    for (const auto& p : posiciones) {
        int i = p.first, j = p.second;
        string diff_s = secuencia_s.substr(previo_s + 1, i - previo_s - 1);
        string diff_t = secuencia_t.substr(previo_t + 1, j - previo_t - 1);
        if (!diff_s.empty() || !diff_t.empty())
            pares_diferencias.emplace_back(diff_s, diff_t);
        previo_s = i;
        previo_t = j;
    }

    string cola_s = secuencia_s.substr(previo_s + 1);
    string cola_t = secuencia_t.substr(previo_t + 1);
    if (!cola_s.empty() || !cola_t.empty())
        pares_diferencias.emplace_back(cola_s, cola_t);

    return pares_diferencias;
}


// MAIN para pruebas por stdin
/* int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    cout << k << "\n";
    while (k--) {
        int n, m;
        string secuencia_s, secuencia_t;
        cin >> n;
        getline(cin, secuencia_s);
        if (secuencia_s.empty()) getline(cin, secuencia_s);
        else secuencia_s = secuencia_s.substr(1);
        cin >> m;
        getline(cin, secuencia_t);
        if (secuencia_t.empty()) getline(cin, secuencia_t);
        else secuencia_t = secuencia_t.substr(1);

        auto pares = resolver_diferencias_dp(secuencia_s, secuencia_t);

        cout << pares.size() << "\n";
        for (const auto& par : pares) {
            if (!par.first.empty() && !par.second.empty())
                cout << par.first << " " << par.second << "\n";
            else if (!par.first.empty())
                cout << par.first << "\n";
            else
                cout << par.second << "\n";
        }
    }
    return 0;
} */
