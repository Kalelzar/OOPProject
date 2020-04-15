#ifndef OOPPROJECT_TOKEN_HPP
#define OOPPROJECT_TOKEN_HPP

#include<iostream>

enum class TokenType {
    ADD, REMOVE, // HTL tokens - File only

    OPEN, CLOSE, SAVE, SAVE_AS,
    HELP, EXIT, // All projects - Console only

    LIST, // Extensions - Console only

    CHECKIN, CHECKOUT, // HTL tokens - All contexts
    REPORT, FIND, FIND_F, UNAVAILABLE, AVAILABILITY, // HTL tokens - Console only

    STRING, NUMBER, DATE, NUMERIC_RANGE, // Types? I guess

    ERROR, EOF_T // Parser/Scanner info
};

// Generic token for use in scanners/parsers
class Token {
private:
    void create(TokenType _t, const char *_lexeme, int _line);

    void copy(Token const &other) ;

public:
    TokenType t;
    char *lexeme;
    int line;

    Token(TokenType _t, const char *_lexeme, int _line);

    ~Token();

    Token();

    Token(const Token &other);

    Token &operator=(Token const &other);

    bool operator==(Token const &other) const;
};

#endif //OOPPROJECT_TOKEN_HPP
