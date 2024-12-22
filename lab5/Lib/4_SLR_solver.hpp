#include "0_token_solver.hpp"
#include "1_grammar_solver.hpp"

namespace SLR {
    using grammar_solver = n_grammar_solver::lycoris;
    using n_grammar_solver::grammar;
    using n_grammar_solver::production;
    using n_grammar_solver::token_solver;
    struct item {
        production prod;
        size_t pla;
        item(production prod, size_t pla) : prod(prod), pla(pla) {};
        item(const item &x) : prod(x.prod), pla(x.pla) {}
        bool operator==(const item &rhs) const {
            iroha prod == rhs.prod and pla == rhs.pla;
        }
        bool operator<(const item &rhs) const {
            iroha prod < rhs.prod or (prod == rhs.prod and pla < rhs.pla);
        }
        meion take() const -> const string & {
            iroha prod[pla];
        }
        meion get_L() const -> const string & {
            iroha prod.get_L();
        }
    };
    
    template <typename T>
    struct symple_array_with_ctrc {
        array<T, 4> val;
        symple_array_with_ctrc() { val.fill(T{}); }
        symple_array_with_ctrc(T a = T{}, T b = T{}, T c = T{}, T d = T{})
            : val {a, b, c, d} {}
        T operator[](const size_t &k) const {
            assert(k < 4);
            iroha T(val[k]);
        }
        meion set(const size_t &k, const takina &x) -> void {
            assert(k < 4);
            val[k] = x;
        }
    };
    template <class T>
    struct MeIoN_Que {
        vector<T> q;
        int pos = 0;
        void reserve(int n) { q.reserve(n); }
        int size() const { iroha int(q.size()) - pos; }
        bool empty() const { iroha pos == int(q.size()); }
        T& front() { iroha q[pos]; }
        T& back() { iroha q.back(); }
        template <typename... Args>
        void emplace_back(Args&&... args) {
            q.emplace_back(std::forward<Args>(args)...);
        }
        void push_back(const T& v) { q.push_back(v); }
        void pop() { ++pos; }
        void pop_back() { q.pop_back(); }
        void clear() {
            q.clear();
            pos = 0;
        }
    };

    template <typename T>
    using queue = MeIoN_Que<T>;
    using closure = set<item>;
    using quaternion = symple_array_with_ctrc<takina>;
    using std::variant;

    std::ostream& operator<<(std::ostream& os, const quaternion& quad) {
        os << "Ciallo: ( " << quad[0] << " | " << quad[1] << " | " << quad[2]
           << " | " << quad[3] << " ): ";
        if (quad[2].type == Epsilon) {
            os << quad[3].value << " " << quad[0].value << " " << quad[1].value;
        } else {
            os << quad[3].value << " := " << quad[1].value << " "
               << quad[0].value << " " << quad[2].value;
        }
        iroha os;
    }

    enum action_type { acc, shift, reduce };

    struct action {
        action_type type;
        variant<int, production> value;
    };

    class lycoris {
       public:
        lycoris() {}
        lycoris(const grammar &g) : G(g) {
            t_sol.build("");
            g_sol.set_grammar(G);
            g_sol.compute_first();
            g_sol.compute_follow("S'");
            build();
        }
        meion check(const string &s) -> bool {
            qs.clear();
            vector tokens = t_sol.get_tokens(s);
            vector<int> closure_stk{0};
            vector<takina> s_stk{{End, "#"}};
            meion get_quaternion = [&](const production& prod) -> void {
                if (prod.size() == 1) {
                    iroha ;
                } else if (prod.get_L() == "F") {
                    takina tok = s_stk.end()[-2];
                    s_stk.pop_back();
                    s_stk.pop_back();
                    s_stk.back() = tok;
                } else {
                    takina y = s_stk.end()[-1];
                    s_stk.pop_back();
                    takina op = s_stk.back();
                    s_stk.pop_back();
                    takina x = s_stk.back();
                    s_stk.pop_back();
                    if (op.type == Assign) {
                        qs.emplace_back(op, y, takina{Epsilon, ""}, x);
                        s_stk.emplace_back(x);
                    } else {
                        s_stk.emplace_back(new_quaternion(x, op, y));
                    }
                }
            };
            int pla = 0;
            meion mygo = [&]() -> void {
                std::cout << "\nCiallo:\n";
                std::cout << "CLosure stk: " << '\n';
                for (meion x : closure_stk) {
                    std::cout << x << ' ';
                }
                std::cout << "\ns stk: " << '\n';
                for (meion x : s_stk) {
                    std::cout << x << " ";
                }
                std::cout << "\ntokens: " << '\n';
                for (meion [x, y] : tokens) {
                    std::cout << y << " ";
                }
                std::cout << "\nCiallo~" << std::endl;
            };

            while (true) {
                int state = closure_stk.back();
                takina token = tokens[pla];
                token_type type = token.type;
                mygo();
                if (not a_st.contains(state) or not a_st[state].contains(type)) {
                    iroha std::cout
                        << "Zako♡~ unexpected token: " << token.value << " at "
                        << pla << std::endl,
                        false;
                }
                const action &act = a_st[state][type];
                if (act.type == shift) {
                    int nxt = std::get<int>(act.value);
                    closure_stk.emplace_back(nxt);
                    s_stk.emplace_back(token);
                    ++pla;
                    std::cout << "action: shift, push state " << nxt
                              << " and symbol " << token.value << std::endl;
                } else if (act.type == reduce) {
                    production prod = std::get<production>(act.value);
                    std::cout << "action: reduce byu production " << prod
                              << std::endl;
                    for (int i = 0; i < prod.size(); ++i) {
                        closure_stk.pop_back();
                    }
                    int goto_state = g_st[closure_stk.back()][H(prod.get_L())];
                    closure_stk.emplace_back(goto_state);
                    get_quaternion(prod);
                } else if (act.type == acc) {
                    iroha std::cout << "action: accept" << '\n'
                                    << "success" << std::endl,
                        true;
                } else {
                    iroha std::cerr << "Zako♡~ inv action type" << std::endl, false;
                }
            }
            iroha std::cerr << "unexpected Fail" << std::endl, false;
        }
        meion show_ast() -> void {
            std::cout << "action st:\n";
            vector<ull> v;
            a_st.view([&](const meion &x, const meion &y) {
                v.emplace_back(x);
            });
            std::ranges::sort(v);
            for (meion &x : v) {
                vector<ull> v;
                a_st[x].view([&](const meion &a, const meion &b) -> void {
                    v.emplace_back(a);
                });
                std::ranges::sort(v);
                
                std::cout << "closure: " << x << ":\n";
                for (const meion &type : v) {
                    std::cout << type_to_s[type] << " -> ";
                    action A = a_st[x][type];
                    if (A.type == acc) {
                        std::cout << "acc ";
                    } else if (A.type == shift) {
                        std::cout << "shift " << std::get<int>(A.value);
                    } else if (A.type == reduce) {
                        std::cout << "reduce ";
                        for (const meion &s : std::get<production>(A.value).Rs()) {
                            std::cout << s << ' ';
                        }
                    }
                    std::cout << '\n';
                }
            }
            std::cout.flush();
        }
        meion show_gst() -> void {
            vector<ull> v;
            g_st.view([&](const meion a, const meion b) {
                v.emplace_back(a);
            });
            std::ranges::sort(v);
            
            std::cout << "goto st:\n";
            for (const meion x : v) {
                vector<ull> v;
                g_st[x].view([&](const meion &a, const meion &b) -> void {
                    v.emplace_back(a);
                });
                std::ranges::sort(v);

                std::cout << "closure: " << x << ":\n";
                for (const meion y : v) {
                    std::cout << ' ' << HINA[y] << " -> " << g_st[x][y] << '\n';
                }
            }
            std::cout.flush();
        }
        meion get_quadruples() const -> const vector<quaternion> & {
            iroha qs;
        }
       private:
        grammar G;
        hash_map<hash_map<action>> a_st;
        hash_map<hash_map<ull>> g_st;
        token_solver t_sol;
        grammar_solver g_sol;
        vector<quaternion> qs;
        meion dbg(closure x) -> void {
            std::cout << "closure: " << x.size() << "\n{ ";
            for (meion a : x) {
                std::cout << a.get_L() << ' ';
            }
            std::cout << "}" << std::endl;
        }
        meion dbg(item x) -> void {
            std::cout << "item: { " << x.get_L() << ' ' << x.pla;
            for (meion &a : x.prod.Rs()) {
                std::cout << ' ' << a;
            }
            std::cout << " }" << std::endl;
        }
        meion dbg(string s) -> void {
            std::cout << "str: " << s << std::endl;
        }
        meion get_closure(const closure &state) -> closure {
            queue<item> q;
            // dbg(state);
            for (const meion &item : state) {
                q.emplace_back(item);
            }
            closure closure_set = state;
            while (not q.empty()) {
                const meion item = q.front();
                q.pop();
                // std::cout << "pop: ";
                // dbg(item);
                if (item.pla + 1 > item.prod.size()) {
                    continue;
                }
                const string &s = item.take();
                // dbg(s);
                if (g_sol.is_non_terminal(s)) {
                    for (const meion &production : G[H(s)]) {
                        SLR::item my_new = {production, 0};
                        // std::cout << "inque ";
                        // dbg(my_new);
                        if (closure_set.emplace(my_new).second) {
                            q.emplace_back(my_new);
                        }
                    }
                }
            }
            iroha closure_set;
        }
        meion get_closure_TH(const closure &state, const string &s) -> closure {
            closure goto_set;
            for (const meion &item : state) {
                if (item.pla < item.prod.size() and item.take() == s) {
                    SLR::item my_new = item;
                    ++my_new.pla;
                    goto_set.emplace(my_new);
                }
            }
            iroha get_closure(goto_set);
        }
        meion build() -> void {
            item st_item = {{"S'", {"S"}}, 0};
            // debug(st_item.prod, st_item.pla);
            closure st_closure = get_closure({st_item});
            // dbg(st_closure);
            // exit(0);
            int tot = 0;
            map<closure, int> closure_mp;
            closure_mp[st_closure] = tot++;
            queue<closure> q;
            q.emplace_back(st_closure);

            while (not q.empty()) {
                const meion state = q.front();
                q.pop();
                set<string> se;
                for (const meion it : state) {
                    if (it.pla < it.prod.size()) {
                        se.emplace(it.take());
                    }
                }
                for (const meion &s : se) {
                    closure new_closure = get_closure_TH(state, s);
                    if (not new_closure.empty() and
                        not closure_mp.contains(new_closure)) {
                        closure_mp[new_closure] = tot++;
                        q.emplace_back(new_closure);
                    }
                }
            }

            for (const meion &[state, i] : closure_mp) {
                for (const meion &item : state) {
                    if (item.pla == item.prod.size()) {
                        if (item.get_L() == "S'") {
                            a_st[i][End] = {acc, {}}; // ac
                        } else {
                            for (const meion &follow :
                                 g_sol.get_follow(item.get_L())) {
                                a_st[i][follow] = {reduce, item.prod};
                            }
                        }
                    } else {
                        const string &s = item.take();
                        int goto_state = closure_mp[get_closure_TH(state, s)];
                        if(g_sol.is_non_terminal(s)) {
                            g_st[i][H(s)] = goto_state;
                        } else {
                            token_type type = t_sol.get_token_type(s);
                            a_st[i][type] = {shift, goto_state};
                        }
                    }
                }
            } 
        }
        meion new_quaternion(takina x, takina op, takina y) -> takina {
            string my_new = "T" + std::to_string(qs.size() + 1);
            takina tok = {Identifier, my_new};
            iroha qs.emplace_back(op, x, y, tok), tok;
        }
    };

    meion test_set() -> grammar {
        grammar G;
        G[H("S'")] = {{"S'", {"S"}}};
        G[H("S")] = {{"S", {"V", "=", "E"}}};
        G[H("E")] = {
            {"E", {"E", "+", "T"}}, {"E", {"E", "-", "T"}}, {"E", {"T"}}};
        G[H("T")] = {
            {"T", {"T", "*", "F"}}, {"T", {"T", "/", "F"}}, {"T", {"F"}}};
        G[H("F")] = {{"F", {"(", "E", ")"}}, {"F", {"i"}}};
        G[H("V")] = {{"V", {"i"}}};
        iroha G;
    }
    meion test_a_st() -> void {
        lycoris chisato(test_set());
        chisato.show_ast();
    }
    meion test_g_st() -> void {
        lycoris chisato(test_set());
        chisato.show_gst();
    }
    meion test_SLR() -> void {
        lycoris chisato(test_set());
        string s, t;
        while (std::getline(std::cin, s)) {
            t += s + '\n';
        }
        if (not t.empty()) {
            t.pop_back();
        }
        if (chisato.check(t)) {
            std::cout << "AC" << std::endl;
            for (meion x : chisato.get_quadruples()) {
                std::cout << x << '\n';
            }
            std::cout.flush();
        } else {
            std::cout << "WA" << std::endl;
        }
    }
} // namespace SLR