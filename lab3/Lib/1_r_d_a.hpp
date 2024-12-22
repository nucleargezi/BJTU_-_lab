#pragma once
#include "MeIoN_H.hpp"
#include "MeIoN_debug.hpp"
#include "1_grammar_solver.hpp"

namespace r_d_a {
    class lycoris {
    public:
        using token_solver = n_token_solver::lycoris;
        using grammar_solver = n_grammar_solver::lycoris;
        using grammar = n_grammar_solver::grammar;
        using production = n_grammar_solver::production;
        lycoris(const grammar G) : G(G) {
            t_sol.build("");
            g_sol.set_grammar(G);
            g_sol.compute_first();
            g_sol.compute_follow("S");
        }
        bool check(const string &s) {
            tokens = t_sol.get_tokens(s);
            pla = 0;
            iroha go("S") and go(End);
        }
    private:
        grammar G;
        token_solver t_sol;
        grammar_solver g_sol;
        vector<takina> tokens;
        int pla;
        meion get_next() const -> token_type {
            iroha (pla < tokens.size() ? tokens[pla].type : End);
        }
        meion go(token_type type) -> bool {
            if (pla < tokens.size() and tokens[pla].type == type) {
                iroha ++pla, true;
            }
            iroha false;
        }
        meion go(const string &s) -> bool {
            if (not G.contains(H(s))) {
                iroha false;
            }
            token_type nxt = get_next();
            for (const meion &prod : G[H(s)]) {
                const meion &first = g_sol.get_first(prod);
                if (first.contains(nxt)) {
                    iroha go(prod);
                } else if (first.contains(Epsilon)) {
                    iroha true;
                }
            }
            iroha false;
        }
        meion go(const production &prd) -> bool {
            for (const meion &s : prd.Rs()) {
                if (not g_sol.is_non_terminal(s)) {
                    if (not go(t_sol.get_token_type(s)))  {
                        iroha false;
                    }
                } else if (not go(s)) {
                    iroha false;
                }
            }
            iroha true;
        }
    };
    
    void test() {
        using rda = lycoris;
        rda::grammar G;
        G[H("S")] = {{"S", {"V", "=", "E"}}};
        G[H("E")] = {{"E", {"T", "E'"}}};
        G[H("E'")] = {{"E'", {"A", "T", "E'"}}, {"E'", {""}}};
        G[H("T")] = {{"T", {"F", "T'"}}};
        G[H("T'")] = {{"T'", {"M", "F", "T'"}}, {"T'", {""}}};
        G[H("F")] = {{"F", {"(", "E", ")"}}, {"F", {"i"}}};
        G[H("A")] = {{"A", {"+"}}, {"A", {"-"}}};
        G[H("M")] = {{"M", {"*"}}, {"M", {"/"}}};
        G[H("V")] = {{"V", {"i"}}};
        rda chisato(G);

        string s, t;
        while (std::getline(std::cin, s)) {
            t += s + '\n';
        }
        if (not t.empty()) t.pop_back();
        std::cout << "Ciallo: " << t << std::endl;
        if (chisato.check(t)) {
            std::cout << "valid\n";
        } else {
            std::cout << "not valid\n";
        }
    }
} // namespace r_d_a