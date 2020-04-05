#ifndef OOPPROJECT_TOKEN_HPP
#define OOPPROJECT_TOKEN_HPP

#include<cstring>
#include<iostream>

enum class TokenType {
    TOKEN_ADD, TOKEN_REMOVE,

    TOKEN_OPEN, TOKEN_CLOSE, TOKEN_SAVE, TOKEN_SAVE_AS,
    TOKEN_HELP, TOKEN_EXIT,

    TOKEN_CHECKIN, TOKEN_CHECKOUT, TOKEN_REPORT, TOKEN_FIND,
    TOKEN_FIND_F, TOKEN_UNAVAILABLE, TOKEN_AVAILABILITY,

    TOKEN_STRING, TOKEN_NUMBER, TOKEN_DATE,
    TOKEN_NUMERIC_RANGE,

    TOKEN_ERROR, TOKEN_EOF
};

struct Token {
private:
    void create(TokenType _t, const char *_lexeme, int length, int _line) {
        t = _t;
        line = _line;
        lexeme = new char[length + 1];
        strncpy(lexeme, _lexeme, length);
        lexeme[length] = '\0';
    }

    void copy(Token const &other) {
        create(other.t, other.lexeme, strlen(other.lexeme), other.line);
    }

public:
    TokenType t;
    char *lexeme;
    int line;

    Token(TokenType _t, const char *_lexeme, int length, int _line) {
        create(_t, _lexeme, length, _line);
    }

    ~Token() {
        delete[] lexeme;
    }

    Token() {
        create(TokenType::TOKEN_EOF, "", 0, 0);
    }

    Token(const Token &other) {
        if (this != &other)
            copy(other);
    }

    Token &operator=(Token const &other) {
        if (this != &other) {
            delete[] lexeme;
            copy(other);
        }
        return *this;
    }

    bool operator==(Token const &other) const {
        return t == other.t &&
               line == other.line && strcmp(lexeme, other.lexeme) == 0;
    }

    friend std::ostream &operator<<(std::ostream &out, Token const &token) {

        switch(token.t){

            case TokenType::TOKEN_ADD:
                out<<"(ADD)";
                break;
            case TokenType::TOKEN_REMOVE:
                out<<"(REMOVE)";
                break;
            case TokenType::TOKEN_OPEN:
                out<<"(OPEN)";
                break;
            case TokenType::TOKEN_CLOSE:
                out<<"(CLOSE)";
                break;
            case TokenType::TOKEN_SAVE:
                out<<"(SAVE)";
                break;
            case TokenType::TOKEN_SAVE_AS:
                out<<"(SAVE AS)";
                break;
            case TokenType::TOKEN_HELP:
                out<<"(HELP)";
                break;
            case TokenType::TOKEN_EXIT:
                out<<"(EXIT)";
                break;
            case TokenType::TOKEN_CHECKIN:
                out<<"(CHECK IN)";
                break;
            case TokenType::TOKEN_CHECKOUT:
                out<<"(CHECK OUT)";
                break;
            case TokenType::TOKEN_REPORT:
                out<<"(REPORT)";
                break;
            case TokenType::TOKEN_FIND:
                out<<"(FIND)";
                break;
            case TokenType::TOKEN_FIND_F:
                out<<"(FIND!)";
                break;
            case TokenType::TOKEN_UNAVAILABLE:
                out<<"(UNAVAILABLE)";
                break;
            case TokenType::TOKEN_STRING:
                out<<"(STRING)";
                break;
            case TokenType::TOKEN_NUMBER:
                out<<"(NUMBER)";
                break;
            case TokenType::TOKEN_DATE:
                out<<"(DATE)";
                break;
            case TokenType::TOKEN_NUMERIC_RANGE:
                out<<"(NUMERIC RANGE)";
                break;
            case TokenType::TOKEN_ERROR:
                out<<"(ERROR)";
                break;
            case TokenType::TOKEN_EOF:
                out<<"(EOF)";
                break;
        }

        out << token.line << ": " << token.lexeme;
        return out;
    }
};

#endif //OOPPROJECT_TOKEN_HPP
