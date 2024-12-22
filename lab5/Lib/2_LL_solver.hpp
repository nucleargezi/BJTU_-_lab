#pragma once
#include "1_grammar_solver.hpp"

namespace LL {
    using grammar_solver = n_grammar_solver::lycoris;
    using n_grammar_solver::grammar;
    using n_grammar_solver::production;
    using n_grammar_solver::token_solver;
    class lycoris {
       public:
        lycoris() {}
        lycoris(const grammar &g) : G(g) {
            t_sol.build("");
            g_sol.set_grammar(G);
            g_sol.compute_first();
            g_sol.compute_follow("S");
            build();
        }
        meion check(const string &s) -> bool {
            vector tokens = t_sol.get_tokens(s);
            vector<string> stk{"S"};
            int pla = 0;
            while (not stk.empty()) {
                string t = stk.back();
                meion token = tokens[pla];
                if (g_sol.is_non_terminal(t)) {
                    if (st[H(t)].contains(token.type)) {
                        stk.pop_back();
                        const production &prod = st[H(t)][token.type];
                        for (const meion &x : std::views::reverse(prod.Rs())) {
                            if (not x.empty()) {
                                stk.emplace_back(x);
                            }
                        }
                    } else {
                        iroha std::cerr << "Honto ni yowai'♡~ unexpected token "
                                        << token.value << std::endl,
                            false;
                    }
                } else if (t_sol.get_token_type(t) == token.type) {
                    stk.pop_back();
                    ++pla;
                } else {
                    iroha std::cerr << "Zako♡~ token match failed"
                                    << std::endl,
                        false;
                }
            }
            assert(tokens.back().type == End);
            iroha pla + 1 == tokens.size();
        }
        meion show_st() -> void {
            std::cout << "ST table" << '\n';
            vector<string> out;
            st.view(
                [&](const ull &key, const hash_map<production> &val) -> void {
                    out.emplace_back();
                    meion &s = out.back();
                    s += HINA[key] + " : {\n";
                    vector<string> pv;
                    val.view([&](const meion &k, const production &v) -> void {
                        pv.emplace_back();
                        pv.back() += "  " + type_to_s[k] + " -> ";
                        for (const meion &x : v.Rs()) {
                            pv.back() += x + " ";
                        }
                        pv.back() += "\n";
                    });
                    std::ranges::sort(pv);
                    for (const string &x : pv) {
                        s += x;
                    }
                    s += "}\n";
                });
            std::ranges::sort(out);
            for (const string &s : out) {
                std::cout << s;
            }
            std::cout.flush();
        }
       private:
        grammar G;
        hash_map<hash_map<production>> st;
        token_solver t_sol;
        grammar_solver g_sol;
        meion build() -> void {
            G.enumerate_all([&](const ull &key, const vector<production> &val) -> void {
                for (const production &prod : val) {
                    meion f = g_sol.get_first(prod);
                    for (const meion &tok : f) {
                        if (tok != Epsilon) {
                            st[key][tok] = prod;
                        }
                    }
                    if (f.contains(Epsilon)) {
                        const meion &follow = g_sol.get_follow(key);
                        for (const meion &tok : follow) {
                            st[key][tok] = prod;
                        }
                    }
                }

            });
        }
    };

    meion test_set() -> grammar {
        grammar G;
        G[H("S")] = {{"S", {"V", "=", "E"}}};
        G[H("E")] = {{"E", {"T", "E'"}}};
        G[H("E'")] = {{"E'", {"A", "T", "E'"}}, {"E'", {""}}};
        G[H("T")] = {{"T", {"F", "T'"}}};
        G[H("T'")] = {{"T'", {"M", "F", "T'"}}, {"T'", {""}}};
        G[H("F")] = {{"F", {"(", "E", ")"}}, {"F", {"i"}}};
        G[H("A")] = {{"A", {"+"}}, {"A", {"-"}}};
        G[H("M")] = {{"M", {"*"}}, {"M", {"/"}}};
        G[H("V")] = {{"V", {"i"}}};
        return G;
    }

    meion test_st() -> void {
        lycoris chisato(test_set());
        chisato.show_st();
    }

    meion test_rda() -> void {
        lycoris chisato(test_set());
        string s, t;
        while (std::getline(std::cin, s)) {
            t += s + '\n';
        }
        if (not t.empty()) t.pop_back();
        std::cout << "Ciallo: " << t << std::endl;
        
        if (chisato.check(t)) {
            std::cout << "valid" << std::endl;
        } else {
            std::cout << "Zako♡~ exactly invalid" << std::endl;
        }
    }
} // namespace LL