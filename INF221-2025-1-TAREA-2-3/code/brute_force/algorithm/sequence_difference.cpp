#include "sequence_difference.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

string substr_seguro(const string &s, int start, int endExclusive) {
    int sz = s.size();
    if (start < 0) start = 0;
    if (endExclusive < start) endExclusive = start;
    if (start > sz) start = sz;
    if (endExclusive > sz) endExclusive = sz;
    return s.substr(start, endExclusive - start);
}

bool esSubsecuencia(const string &sub, const string &t, vector<int> &pos_t) {
    pos_t.clear();
    int idx = 0;
    for (char c : sub) {
        bool encontrado = false;
        while (idx < (int)t.size()) {
            if (t[idx] == c) {
                pos_t.push_back(idx);
                encontrado = true;
                idx++;
                break;
            }
            idx++;
        }
        if (!encontrado) return false;
    }
    return true;
}

vector<pair<string, string>> resolver_diferencias(const string& sec_s, const string& sec_t) {
    int n = sec_s.size();
    int m = sec_t.size();
    string lcs;
    vector<int> mejor_pos_t;
    int total = 1 << n;
    for (int mask = 0; mask < total; ++mask) {
        string sub;
        sub.reserve(n);
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i)) sub.push_back(sec_s[i]);
        if ((int)sub.size() <= (int)lcs.size()) continue;
        vector<int> pos_t;
        if (esSubsecuencia(sub, sec_t, pos_t)) {
            lcs = sub;
            mejor_pos_t = pos_t;
        }
    }

    vector<int> pos_s;
    int idx_s = 0;
    for (char c : lcs) {
        for (int j = idx_s; j < n; ++j) {
            if (sec_s[j] == c) {
                pos_s.push_back(j);
                idx_s = j + 1;
                break;
            }
        }
    }

    vector<pair<string, string>> pares;
    int prev_s = -1, prev_t = -1;
    for (size_t i = 0; i < lcs.size(); ++i) {
        int ps = pos_s[i];
        int pt = mejor_pos_t[i];
        string diff_s = substr_seguro(sec_s, prev_s + 1, ps);
        string diff_t = substr_seguro(sec_t, prev_t + 1, pt);
        if (!diff_s.empty() || !diff_t.empty())
            pares.emplace_back(diff_s, diff_t);
        prev_s = ps;
        prev_t = pt;
    }
    string cola_s = substr_seguro(sec_s, prev_s + 1, sec_s.size());
    string cola_t = substr_seguro(sec_t, prev_t + 1, sec_t.size());
    if (!cola_s.empty() || !cola_t.empty())
        pares.emplace_back(cola_s, cola_t);

    return pares;
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

        auto pares = resolver_diferencias(secuencia_s, secuencia_t);

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
