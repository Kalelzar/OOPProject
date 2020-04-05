#ifndef OOPPROJECT_TOKEN_HPP
#define OOPPROJECT_TOKEN_HPP

#include<cstring>
#include<iostream>
enum class TokenType {
    TOKEN_ADD, TOKEN_REMOVE,

    TOKEN_OPEN, TOKEN_CLOSE, TOKEN_SAVE, TOKEN_SAVE_AS,
    TOKEN_HELP, TOKEN_EXIT,

    TOKEN_CHECKIN, TOKEN_CHECKOUT, TOKEN_REPORT, TOKEN_FIND,
    TOKEN_FIND_F, TOKEN_UNAVAILABLE,

    TOKEN_STRING, TOKEN_NUMBER, TOKEN_DATE,
    TOKEN_NUMERIC_RANGE, TOKEN_FILEPATH,

    TOKEN_ERROR, TOKEN_EOF
};

struct Token {
private:
    void create(TokenType _t, const char* _lexeme, int length, int _line){
        t = _t;
        line = _line;
        lexeme = new char[length+1];
        strncpy(lexeme, _lexeme, length);
        lexeme[length] = '\0';
    }
    void copy(Token const& other){
        create(other.t, other.lexeme, strlen(other.lexeme), other.line);
    }
public:
    TokenType t;
    char* lexeme;
    int line;

    Token(TokenType _t, const char* _lexeme, int length, int _line){
        create(_t, _lexeme, length, _line);
    }

    ~Token(){
        delete [] lexeme;
    }

    Token(){
        create(TokenType::TOKEN_EOF, "", 0, 0);
    }

    Token(const Token& other){
        if(this != &other)
            copy(other);
    }

    Token& operator=(Token const& other){
        if(this != &other){
            delete [] lexeme;
            copy(other);
        }
        return *this;
    }

    bool operator==(Token const& other) const {
        return t == other.t &&
            line == other.line && strcmp(lexeme, other.lexeme) == 0;
    }

    friend std::ostream& operator<<(std::ostream& out, Token const& token){
        //char l[token.length+1];
        //std::cout<<token.lexeme<<std::endl;
        //strncpy(l, token.lexeme, token.length);
        //l[token.length] = '\0';
        out<<token.line<<": "<<token.lexeme;
        return out;
    }
};

#endif //OOPPROJECT_TOKEN_HPP
