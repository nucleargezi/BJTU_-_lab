#pragma once
enum token_type {
    Reserved,
    Identifier,
    Number,
    Single_char,
    Comma,   // ,
    Colon,   // :
    Semi,    // ;
    Bb_lft,  // {
    Bb_rt,   // }
    Sb_lft,  // (
    Sb_rt,   // )
    Plus,    // +
    Minus,   // -
    Mul,     // *
    Div,     // /
    Lt,      // <
    Gt,      // >
    Assign,  // =
    Not,     // !
    Double_char,
    Le,            // <=
    Ge,            // >=
    Eq,            // ==
    Ne,            // !=
    Plus_assign,   // +=
    Minus_assign,  // -=
    Mul_assign,    // *=
    Div_assign,    // /=
    Self_inc,      // ++
    Self_dec,      // --
    Rsh,           // >>
    Lsh,           // <<
    And,           // &&
    Or,            // ||
    Comment,       // // or /*
    Epsilon,       // ε
    End,           // #
    Error,
    Non_terminal,
    meion_cnt
};

const std::string type_to_s[meion_cnt] = {
    "reserved", "identifier",  "number",      "single_char", ",",       ":",
    ";",        "{",           "}",           "(",           ")",       "+",
    "-",        "*",           "/",           "<",           ">",       "=",
    "!",        "double char", "<=",          ">=",          "==",      "!=",
    "+=",       "-=",          "*=",          "/=",          "++",      "--",
    ">>",       "<<",          "and",         "or",          "comment", "ε",
    "end",      "error",       "non terminal"};

const std::unordered_set<std::string> reserved_words = {
    "void", "int", "float", "double", "if", "else", "for", "do", "while"};


// token
struct takina {
    token_type type;
    string value;
};

std::ostream &operator<<(std::ostream &os, const takina &x) {
    os << type_to_s[x.type] << ' ' << x.value;
    iroha os;
}

void show(const takina &x) {
    std::cout << "type: " << std::setw(12) << std::left << type_to_s[x.type]
              << "value: " << std::setw(10) << std::left << x.value
              << std::endl;
}
