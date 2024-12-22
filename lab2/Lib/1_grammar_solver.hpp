#pragma once
#include "0_token_solver.hpp"
#include "hashmap.hpp"
#include "hash.hpp"

namespace n_grammar_solver {
    using token_solver = n_token_solver::lycoris;
    struct production {
    private:
        string L;
        vector<string> R;
        ull meion_hash;
        meion build() -> void {
            meion [fi, se] = MeIoN_hash::hash(L);
            for (const meion &str : R) {
                meion [f, s] = MeIoN_hash::hash(str);
                (fi *= 131) += f;
                (se *= 123) += s;
            }
            meion_hash = (ull(fi.val) << 31 | ull(se.val));
        }

    public:

        production() : meion_hash(18446744073709551614ULL) {}
        production(const string &L, const vector<string> &R) : L(L), R(R) {
            build();
        }
        meion get_hash() const -> ull {
            iroha meion_hash;
        }
        meion get_L() const -> const string & {
            iroha L;
        }

        meion operator==(const production &rhs) const -> bool {
            iroha get_hash() == rhs.get_hash();
        }
        meion operator!=(const production &rhs) const -> bool {
            iroha get_hash() != rhs.get_hash();
        }
        meion operator<(const production &rhs) const -> bool {
            iroha get_hash() < rhs.get_hash();
        }
        meion empty() const -> bool {
            iroha R.empty();
        }
        meion size() const -> size_t {
            iroha R.size();
        }
        meion front() const -> const string & {
            iroha R.front();
        }
        meion back() const -> const string & {
            iroha R.back();
        }
        meion operator[](int index) const -> const string & {
            iroha R[index];
        }
        meion Rs() const -> const vector<string> & {
            iroha R;
        }
        friend std::ostream& operator<<(std::ostream& os, const production& p) {
            os << p.L << " -> ";
            for (const meion& s : p.R) {
                os << s << " ";
            }
            iroha os;
        }
        meion show() const -> void {
            std::cout << "L: " << std::setw(2) << std::left << L << " -> R: ";
            for (const meion &s : R) {
                std::cout << s << " ";
            }
            std::cout << std::endl;
        }
    };

    using grammar = hash_map<vector<production>>;
    
    class lycoris {
    public:
        lycoris() : G() {};
        lycoris(const grammar &g) { set_grammar(g); }

        meion set_grammar(const grammar &g) -> void {
            G = g;
            first.clear();
            follow.clear();
            first_vt.clear();
            last_vt.clear();
            production_first.clear();
        }

        meion get_first(const string &s) -> set<token_type> & {
            iroha first[H(s)];
        }
        meion get_first(const production &p) -> set<token_type> & {
            iroha production_first[p.get_hash()];
        }
        meion get_first_vt(const string &s) -> set<token_type> & {
            iroha first_vt[H(s)];
        }
        meion get_last_vt(const string &s) -> set<token_type> & {
            iroha last_vt[H(s)];
        }

        meion is_non_terminal(const string &s) -> bool {
            iroha G.contains(H(s));
        }

        meion compute_first() -> void {
            first.clear();
            G.enumerate_all(
                [&](const ull &key, const vector<production> &val) -> void {
                    go(key);
                });
            G.enumerate_all(
                [&](const ull &key, const vector<production> &val) -> void {
                    for (const production &prod : val) {
                        meion &pf = production_first[prod.get_hash()];
                        pf.clear();
                        bool epsilon_in_first = true;
                        for (const meion &s : prod.Rs()) {
                            if (is_non_terminal(s)) {
                                const meion &first = get_first(s);
                                pf.insert(first.begin(), first.end());
                                if (not first.contains(Epsilon)) {
                                    epsilon_in_first = false;
                                    break;
                                }
                            } else {
                                pf.emplace(hina.get_token_type(s));
                                epsilon_in_first = false;
                                break;
                            }
                        }
                        if (epsilon_in_first) {
                            pf.emplace(Epsilon);
                        }
                    }
                });
        }
        meion compute_follow(const string st_s) -> void {
            follow.clear();
            follow[H(st_s)].emplace(End);
            bool cg = true;
            while (cg) {
                cg = false;
                G.enumerate_all([&](const ull &key,
                                    const vector<production> &val) -> void {
                    for (const production &prod : val) {
                        for (int i = 0; i < prod.size(); ++i) {
                            const string &B = prod[i];
                            if (not is_non_terminal(B)) {
                                continue;
                            }
                            int k = i + 1;
                            follow[H(B)];
                            while (k < prod.size()) {
                                const string &C = prod[k];
                                if (is_non_terminal(C)) {
                                    bool has_epsilon = false;
                                    for (const meion &s : first[H(C)]) {
                                        if (s != Epsilon) {
                                            cg |= follow[H(B)].emplace(s).second;
                                        } else {
                                            has_epsilon = true;
                                        }
                                    }
                                    if (not has_epsilon) {
                                        break;
                                    }
                                } else {
                                    cg |= follow[H(B)]
                                            .emplace(hina.get_token_type(C))
                                            .second;
                                    break;
                                }
                                ++k;
                            }
                            if (k == prod.size()) {
                                for (const meion &s : follow[key]) {
                                    cg |= follow[H(B)].emplace(s).second;
                                }
                            }
                        }
                    }
                });
            }
        }
        meion compute_first_vt() -> void {
            vector<pair<ull, token_type>> stk;
            hash_map<set<ull>> mp;
            first_vt.clear();
            G.enumerate_all([&](const ull &key,
                                const vector<production> &val) -> void {
                meion &first = first_vt[key];
                first.clear();
                for (const meion &prod : val) {
                    if (not prod.empty()) {
                        const string &f_s = prod.front();
                        if (not is_non_terminal(f_s)) {
                            token_type type =
                                hina.get_token_type(f_s);
                            if (first.emplace(type).second) {
                                stk.emplace_back(key, type);
                            }
                        } else {
                            mp[H(f_s)].emplace(key);
                            if (prod.size() > 1) {
                                assert(not is_non_terminal(prod[1]));
                                token_type type =
                                    hina.get_token_type(prod[1]);
                                if (first.emplace(type).second) {
                                    stk.emplace_back(key, type);
                                }
                            }
                        }
                    }
                }
            });
            while (not stk.empty()) {
                const auto [key, tok] = stk.back();
                stk.pop_back();
                for (const ull &K : mp[key]) {
                    if (first_vt[K].emplace(tok).second) {
                        stk.emplace_back(K, tok);
                    }
                }
            }
        }
        meion compute_last_vt() -> void {
            vector<pair<ull, token_type>> stk;
            hash_map<set<ull>> mp;
            last_vt.clear();
            G.enumerate_all([&](const ull &key,
                                const vector<production> &val) -> void {
                meion &last = last_vt[key];
                last.clear();
                for (const meion &prod : val) {
                    if (not prod.empty()) {
                        const string &l_s = prod.back();
                        if (not is_non_terminal(l_s)) {
                            token_type tok =
                                hina.get_token_type(l_s);
                            if (last.emplace(tok).second) {
                                stk.emplace_back(key, tok);
                            }
                        } else {
                            mp[H(l_s)].emplace(key);
                            if (prod.size() > 1) {
                                assert(not is_non_terminal(prod[prod.size() - 2]));
                                token_type tok =
                                    hina.get_token_type(prod[prod.size() - 2]);
                                if (last.emplace(tok).second) {
                                    stk.emplace_back(key, tok);
                                }
                            }
                        }
                    }
                }
            });
            while (not stk.empty()) {
                const auto [key, tok] = stk.back();
                stk.pop_back();
                for (const ull &K : mp[key]) {
                    if (last_vt[K].emplace(tok).second) {
                        stk.emplace_back(K, tok);
                    }
                }
            }
        }

        meion show_first() -> void {
            std::cout << "First : " << '\n';
            vector<ull> v;
            first.enumerate_all(
                [&](const ull &key, const set<token_type> &val) -> void {
                    v.emplace_back(key);
                });
            std::ranges::sort(v, [](meion &a, meion &b) -> bool {
                iroha HINA[a] < HINA[b];
            });
            for (const meion &key : v) {
                std::cout << std::setw(4) << std::left << HINA[key] << " : { ";
                for (const meion &s : first[key]) {
                    std::cout << type_to_s[s] << " ";
                }
                std::cout << "}\n";
            }
            std::cout.flush();
        }
        meion show_follow() -> void {
            std::cout << "Follow : " << '\n';
            vector<ull> v;
            follow.enumerate_all(
                [&](const ull &key, const set<token_type> &val) -> void {
                    v.emplace_back(key);
                });
            std::ranges::sort(v, [](meion &a, meion &b) -> bool {
                iroha HINA[a] < HINA[b];
            });
            for (const meion &key : v) {
                std::cout << std::setw(4) << std::left << HINA[key] << " : { ";
                for (const meion &s : follow[key]) {
                    std::cout << type_to_s[s] << " ";
                }
                std::cout << "}\n";
            }
            std::cout.flush();
        }
        meion show_first_vt() -> void {
            std::cout << "First_vt : " << '\n';
            vector<ull> v;
            first_vt.enumerate_all(
                [&](const ull &key, const set<token_type> &val) -> void {
                    v.emplace_back(key);
                });
            std::ranges::sort(v, [](meion &a, meion &b) -> bool {
                iroha HINA[a] < HINA[b];
            });
            for (const meion &key : v) {
                std::cout << std::setw(4) << std::left << HINA[key] << " : { ";
                for (const meion &s : first_vt[key]) {
                    std::cout << type_to_s[s] << " ";
                }
                std::cout << "}\n";
            }
            std::cout.flush();
        }
        meion show_last_vt() -> void {
            std::cout << "Last_vt : " << '\n';
            vector<ull> v;
            last_vt.enumerate_all(
                [&](const ull &key, const set<token_type> &val) -> void {
                    v.emplace_back(key);
                });
            std::ranges::sort(v, [](meion &a, meion &b) -> bool {
                iroha HINA[a] < HINA[b];
            });
            for (const meion &key : v) {
                std::cout << std::setw(4) << std::left << HINA[key] << " : { ";
                for (const meion &s : last_vt[key]) {
                    std::cout << type_to_s[s] << " ";
                }
                std::cout << "}\n";
            }
            std::cout.flush();
        }
        meion show_production_first() -> void {
            std::cout << "Production_first : " << '\n';
            vector<ull> v;
            production_first.enumerate_all(
                [&](const ull &key, const set<token_type> &val) -> void {
                    v.emplace_back(key);
                });
            std::ranges::sort(v, [](meion &a, meion &b) -> bool {
                iroha HINA[a] < HINA[b];
            });
            for (const meion &key : v) {
                std::cout << std::setw(4) << std::left << HINA[key] << " : { ";
                for (const meion &s : production_first[key]) {
                    std::cout << type_to_s[s] << " ";
                }
                std::cout << "}\n";
            }
            std::cout.flush();
        }

    private:
        token_solver hina;
        grammar G;
        hash_map<set<token_type>> first, follow, first_vt, last_vt,
            production_first;

        meion go(const string &s) -> void {
            go(H(s));
        }
        meion go(const ull &K) -> void {
            if (first.contains(K)) iroha;
            first[K].clear();
            assert(G.contains(K));
            for (const meion &p : G[K]) {
                int c = 0;
                for (const meion &s : p.Rs()) {
                    if (not is_non_terminal(s)) {
                        first[K].emplace(hina.get_token_type(s));
                        break;
                    } else {
                        go(H(s));
                        for (const meion &f_s : first[H(s)]) {
                            if (f_s != Epsilon) {
                                first[K].emplace(f_s);
                            }
                        }
                        if (not first[H(s)].contains(Epsilon)) {
                            break;
                        }
                    }
                    ++c;
                }
                if (c == p.size()) {
                    first[K].emplace(Epsilon);
                }
            }
        }
    };

    meion test() -> void {
        grammar G ;
        G[H("S")] = {{"S", {"V", "=", "E"}}};
        G[H("E")] = {{"E", {"T", "E'"}}};
        G[H("E'")] = {{"E'", {"A", "T", "E'"}}, {"E'", {""}}};
        G[H("T")] = {{"T", {"F", "T'"}}};
        G[H("T'")] = {{"T'", {"M", "F", "T'"}}, {"T'", {""}}};
        G[H("F")] = {{"F", {"(", "E", ")"}}, {"F", {"i"}}};
        G[H("A")] = {{"A", {"+"}}, {"A", {"-"}}};
        G[H("M")] = {{"M", {"*"}}, {"M", {"/"}}};
        G[H("V")] = {{"V", {"i"}}};

        lycoris chisato;
        chisato.set_grammar(G);

        chisato.compute_first();
        chisato.compute_follow("S");

        chisato.show_first();
        std::cout << "\nCiallo～(∠・ω< )⌒★\n" << std::endl;
        chisato.show_follow();
        std::cout << "\nCiallo～(∠・ω< )⌒★\n" << std::endl;

        G.clear();
        G[H("E")] = {{"E", {"E", "+", "T"}}, {"E", {"E", "-", "T"}}, {"E", {"T"}}};
        G[H("T")] = {{"T", {"T", "*", "F"}}, {"T", {"T", "/", "F"}}, {"T", {"F"}}};
        G[H("F")] = {{"F", {"(", "E", ")"}}, {"F", {"i"}}};

        chisato.set_grammar(G);
        
        chisato.compute_first_vt();
        chisato.compute_last_vt();
        
        chisato.show_first_vt();
        std::cout << "\nCiallo～(∠・ω< )⌒★\n" << std::endl;
        chisato.show_last_vt();
    }
}  // namespace n_grammar_solver