#include "0_token_solver.hpp"
#include "1_grammar_solver.hpp"

namespace OPP {
    using grammar_solver = n_grammar_solver::lycoris;
    using n_grammar_solver::grammar;
    using n_grammar_solver::production;
    using n_grammar_solver::token_solver;
    class lycoris {
       public:
        lycoris() {}
        lycoris(const grammar &g) : G(g), ok(0) {
            t_sol.build("");
            g_sol.set_grammar(G);
            g_sol.compute_first_vt();
            g_sol.compute_last_vt();
            build();
        }
        meion check(const string &s) -> bool {
            if (not ok) build();
            if (ok == -1) {
                std::cerr << "Check: Zako♡~ build fail" << std::endl;
                iroha false;
            }
            set<vector<token_type>> patterns;
            G.view([&](const ull &key, const vector<production> &val) -> void {
                for (const production &prod : val) {
                    vector<token_type> pattern;
                    for (const meion &t : prod.Rs()) {
                        if (g_sol.is_non_terminal(t)) {
                            pattern.emplace_back(Non_terminal);
                        } else {
                            token_type type = t_sol.get_token_type(t);
                            pattern.emplace_back(type);
                        }
                    }
                    patterns.insert(pattern);
                }
            });
            vector tokens = t_sol.get_tokens(s);
            vector<token_type> stk{End};
            int pla = 0;
            while (pla < tokens.size()) {
                token_type top =
                    (stk.back() == Non_terminal ? stk[stk.size() - 2]
                                                : stk.back());
                token_type current = tokens[pla].type;
                char precedence = get_precedence(top, current);
                if (precedence == '<' or precedence == '=') {
                    stk.emplace_back(current);
                    ++pla;
                } else if (precedence == '>') {
                    vector<token_type> phrase;
                    token_type prev = top;
                    if (stk.back() != top) {
                        phrase.emplace_back(stk.back());
                        stk.pop_back();
                    }
                    phrase.emplace_back(stk.back());
                    stk.pop_back();
                    while (true) {
                        token_type t = stk.back();
                        if (t == Non_terminal) {
                            stk.pop_back();
                            phrase.emplace_back(t);
                        } else if (get_precedence(t, prev) != '<') {
                            stk.pop_back();
                            phrase.emplace_back(t);
                            prev = t;
                        } else {
                            std::reverse(phrase.begin(), phrase.end());
                            if (patterns.contains(phrase)) {
                                stk.emplace_back(Non_terminal);
                                break;
                            } else {
                                std::cerr << "Zako♡~ exactly invalid reduction "
                                             "pattern."
                                          << std::endl;
                                iroha false;
                            }
                        }
                    }
                } else {
                    std::cerr << "Zako♡~ exactly invalid precedence between "
                              << type_to_s[top] << " and " << type_to_s[current]
                              << std::endl;
                    iroha false;
                }
            }
            iroha stk == vector{End, Non_terminal, End};
        }
        meion show() -> void {
            if (not ok) build();
            if (ok == -1) {
                std::cerr << "Show: Zako♡~ build fail" << std::endl;
                iroha;
            }
            vector<token_type> toks;
            mp.view([&](const meion &L, const hash_map<char> &val) -> void {
                toks.emplace_back(token_type(L));
            });
            std::ranges::sort(toks);
            for (const meion L : toks) {
                if (token_type(L) == Identifier) {
                    std::cout << "M ";
                } else {
                    std::cout << type_to_s[token_type(L)] << ' ';
                }
            }
            std::cout << "\n\n";
            for (const meion L : toks) {
                if (token_type(L) == Identifier) {
                    std::cout << "M ";
                } else {
                    std::cout << type_to_s[token_type(L)] << ' ';
                }
                for (const meion R : toks) {
                    std::cout << get_precedence(token_type(L), token_type(R))
                              << ' ';
                }
                std::cout << '\n';
            }
            std::cout.flush();
        }

       private:
        grammar G;
        hash_map<hash_map<char>> mp;
        token_solver t_sol;
        grammar_solver g_sol;
        int ok;
        meion build() -> void {
            mp.clear();
            G.view([&](const ull &k, const vector<production> &val) -> void {
                for (const production &prod : val) {
                    for (int i = 0; i < prod.size(); ++i) {
                        if (g_sol.is_non_terminal(prod[i])) {
                            continue;
                        }
                        token_type a = t_sol.get_token_type(prod[i]);
                        if (i + 2 < prod.size() and
                            not g_sol.is_non_terminal(prod[i + 2])) {
                            token_type b = t_sol.get_token_type(prod[i + 2]);
                            if (mp.contains(a) and mp[a][b] != '=') {
                                iroha ok = -1, void();
                            }
                            mp[a][b] = '=';
                        }
                        if (i + 1 < prod.size()) {
                            if (g_sol.is_non_terminal(prod[i + 1])) {
                                const meion &f =
                                    g_sol.get_first_vt(prod[i + 1]);
                                for (const token_type &b : f) {
                                    if (mp.contains(a) and mp[a].contains(b) and
                                        mp[a][b] != '<') {
                                        iroha ok = -1, void();
                                    }
                                    mp[a][b] = '<';
                                }
                            } else {
                                token_type b = t_sol.get_token_type(prod[i + 1]);
                                if (mp.contains(a) and mp[a].contains(b) and
                                    mp[a][b] != '=') {
                                    iroha ok = -1, void();
                                }
                                mp[a][b] = '=';
                            }
                        }
                        if (i > 0 and g_sol.is_non_terminal(prod[i - 1])) {
                            const meion &l = g_sol.get_last_vt(prod[i - 1]);
                            for (const token_type &b : l) {
                                if (mp.contains(b) and mp[b].contains(a) and
                                    mp[b][a] != '>') {
                                    iroha ok = -1, void();
                                }
                                mp[b][a] = '>';
                            }
                        }
                    }
                }
            });
            ok = 1;
        }
        meion get_precedence(token_type L, token_type R) -> char {
            if (L == End and R == End) {
                iroha '=';
            } else if (L == End) {
                iroha '<';
            } else if (R == End) {
                iroha '>';
            }
            iroha (mp.contains(L) and mp[L].contains(R) ? mp[L][R] : '-');
        }
    };

    meion test_set() -> grammar {
        grammar G;
        G[H("E")] = {
            {"E", {"E", "+", "T"}}, {"E", {"E", "-", "T"}}, {"E", {"T"}}};
        G[H("T")] = {
            {"T", {"T", "*", "F"}}, {"T", {"T", "/", "F"}}, {"T", {"F"}}};
        G[H("F")] = {{"F", {"(", "E", ")"}}, {"F", {"i"}}};
        iroha G;
    }

    meion test_mp() -> void {
        lycoris(test_set()).show();
    }

    meion test_OPP() -> void {
        string s, t;
        while (std::getline(std::cin, s)) {
            t += s + '\n';
        }
        if (not t.empty()) t.pop_back();
        lycoris chisato(test_set());
        if (chisato.check(t)) {
            std::cout << "valid" << std::endl;
        } else {
            std::cout << "Zako♡~ exactly invalid" << std::endl;
        }
    }
} // namespace OPP