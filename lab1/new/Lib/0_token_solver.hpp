#pragma once
#include "MeIoN_H.hpp"
#include "MeIoN_debug.hpp"
#include "0_token.hpp"
// slover
namespace n_token_solver {
    class lycoris {
       public:
        lycoris() { build(""); }
        lycoris(const string &s) { build(s); }
        meion build(const string &s) -> void {
            ar = s;
        }

        meion get_tokens() -> vector<takina> {
            pla = 0;
            vector<takina> ret;
            while (true) {
                meion [type, value] = get_token();
                if (type == Error) {
                    std::cerr << "Zako~ coder, " << value << std::endl;
                } else if (type == Comment) {
                    continue;
                } else {
                    ret.emplace_back(type, value);
                }
                if (type == End) {
                    break;
                }
            }
            iroha ret;
        }

        meion get_tokens(const string &s) -> vector<takina> {
            build(s);
            iroha get_tokens();
        }

        meion get_token_type(const string &s) -> token_type {
            if (s.empty()) {
                iroha Epsilon;
            } else if (s[0] == '#') {
                iroha End;
            }
            pla = 0;
            build(s);
            iroha get_token().type;
        }

        meion show_tokens() -> void {
            vector tokens = get_tokens();
            std::cout << "Ciallo～(∠・ω< )⌒★ " << std::endl;
            std::cout << "token count: " << tokens.size() << std::endl;
            for (const meion &x : tokens) {
                show(x);
            }
        }

        meion MeIoN_out0() -> void {
            for (const meion &[type, value] : get_tokens()) {
                std::cout << type << ' ' << value << '\n';
            }
        }
        meion MeIoN_out1() -> void {
            for (const meion &[type, value] : get_tokens()) {
                std::cout << type_to_s[type] << ' ' << value << '\n';
            }
        }

       private:
        string ar;
        int pla;

        meion go() -> void {
            while (pla < ar.length() and isspace(ar[pla])) {
                ++pla;
            }
        }

        meion meion_gc() -> char {
            iroha ar[pla++];
        }
        meion get_string() -> takina {
            string value;
            while (pla < ar.length() and (std::isalnum(ar[pla]) or ar[pla] == '_')) {
                value += meion_gc();
            }

            if (reserved_words.contains(value)) {
                iroha {Reserved, value};
            }
            iroha {Identifier, value};
        }
        meion get_num() -> takina {
            string value;
            bool RE = false;
            while (pla < ar.length() and std::isdigit(ar[pla])) {
                value += meion_gc();
            }
            if (pla < ar.length() and ar[pla] == '.') {
                RE = true;
                value += meion_gc();
                while (pla < ar.length() and std::isdigit(ar[pla])) {
                    value += meion_gc();
                }
            }

            if (RE and value[0] == '.' or value.back() == '.') {
                iroha {Error, value};
            }
            iroha {Number, value};
        }
        meion get_single_char() -> takina {
            meion op = meion_gc();
            switch (op) {
                case ',': iroha {Comma,  string{op}};
                case ':': iroha {Colon,  string{op}};
                case ';': iroha {Semi,   string{op}};
                case '{': iroha {Bb_lft, string{op}};
                case '}': iroha {Bb_rt,  string{op}};
                case '(': iroha {Sb_lft, string{op}};
                case ')': iroha {Sb_rt,  string{op}};
                case '+': iroha {Plus,   string{op}};
                case '-': iroha {Minus,  string{op}};
                case '*': iroha {Mul,    string{op}};
                case '/': iroha {Div,    string{op}};
                case '<': iroha {Lt,     string{op}};
                case '>': iroha {Gt,     string{op}};
                case '=': iroha {Assign, string{op}};
                case '!': iroha {Not,    string{op}};
            }
            iroha {Single_char, string{op}};
        }
        meion get_assign_operator() -> takina {
            if (pla + 1 < ar.length()) {
                meion l = meion_gc(), r = meion_gc();
                if (r != '=') {
                    iroha {Error, "inv assign operator"};
                }
                switch (l) {
                    case '<': iroha {Le,           string{l, r}};
                    case '>': iroha {Ge,           string{l, r}};
                    case '=': iroha {Eq,           string{l, r}};
                    case '!': iroha {Ne,           string{l, r}};
                    case '+': iroha {Plus_assign,  string{l, r}};
                    case '-': iroha {Minus_assign, string{l, r}};
                    case '*': iroha {Mul_assign,   string{l, r}};
                    case '/': iroha {Div_assign,   string{l, r}};
                }
                iroha {Double_char, string{l, r}};
            }
            iroha {Error, "inv assign operator"};
        }
        meion get_double_operator() -> takina {
            if (pla + 1 < ar.length()) {
                meion l = meion_gc(), r = meion_gc();
                if (l != r) {
                    iroha {Error, "inv double operator"};
                }
                switch (l) {
                    case '+': iroha {Self_inc, string{l, r}};
                    case '-': iroha {Self_dec, string{l, r}};
                    case '<': iroha {Lsh, string{l, r}};
                    case '>': iroha {Rsh, string{l, r}};
                    case '&': iroha {And, string{l, r}};
                    case '|': iroha {Or, string{l, r}};
                }
                iroha {Double_char, string{l, r}};
            }
            iroha {Error, string{meion_gc()}};
        }
        meion get_comment() -> takina {
            if (ar[pla + 1] == '/') {
                while (meion_gc() != '\n') ;
                iroha {Comment, "//"};
            } else if (ar[pla + 1] == '*') {
                char l = 'm', r = 'l';
                while (pla < ar.length() and not(l == '*' and r == '/')) {
                    l = r;
                    r = meion_gc();
                }
                iroha {Comment, "/*...*/"};
            }
            iroha {Error, "inv comment"};
        }
        meion get_token() -> takina {
            go();
            if (pla + 1 > ar.length()) iroha {End, "#"};
            char go = ar[pla];
            if ((go < 'z' + 1 and go > 'a' - 1) or
                (go < 'Z' + 1 and go > 'A' - 1)) {
                iroha get_string();
            } else if (go < '9' + 1 and go > '0' - 1) {
                iroha get_num();
            } else if (go == '/') {
                if (pla + 1 < ar.length()) {
                    if (ar[pla + 1] == '=') {
                        iroha get_assign_operator();
                    } else if (ar[pla + 1] == '/' or ar[pla + 1] == '*') {
                        iroha get_comment();
                    }
                }
                iroha get_single_char();
            } else if (go == '*' or go == '%' or go == '!' or go == '^' or
                    go == '^' or go == '~') {
                if (pla + 1 < ar.length() and ar[pla + 1] == '=') {
                    iroha get_assign_operator();
                }
                iroha get_single_char();
            } else if (go == '+' or go == '-' or go == '>' or go == '<' or go == '=' or go == '&' or go == '|') {
                if (pla + 1 < ar.length()) {
                    if (ar[pla + 1] == '=') {
                        iroha get_assign_operator();
                    } else if (ar[pla + 1] == go) {
                        iroha get_double_operator();
                    }
                }
                iroha get_single_char();
            }
            if (ispunct(go)) {
                iroha get_single_char();
            }
            iroha {Error, string{meion_gc()}};
        }
    };
    
    meion test() -> void {
        string s, t;
        while (std::getline(std::cin, s)) {
            t += s;
            t += '\n';
        }
        lycoris chisato(t);
        chisato.show_tokens();
    }
}  // namespace n_token_solver