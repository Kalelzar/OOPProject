//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_COMMANDSCANNER_HPP
#define OOPPROJECT_COMMANDSCANNER_HPP

#include<iostream>
#include<cstring>
#include<cctype>
#include "../collection/ArrayList.hpp"
#include "ScannerContext.hpp"
#include "CommandList.hpp"
#include "Token.hpp"

namespace Hotel {


    class CommandScanner {
    private:
        ScannerContext sc;
        CommandList cl;
        std::istream *input;
        int line = 1;
    public:

        bool error = false;

        CommandScanner(ScannerContext sc, std::istream *input, CommandList const &cl) {
            this->sc = sc;
            this->input = input;
            this->cl = cl;
        }

        shared_ptr<ArrayList<Token>> scan() {
            error = false;
            shared_ptr<ArrayList<Token>> list = make_shared<ArrayList<Token>>();
            while (!input->eof()) {
                char sline[513];
                input->getline(sline, 512);
                if (input->eof()) break;
                list->appendAll(*scanLine(sline));
                line++;
            }
            list->append(Token{TokenType::TOKEN_EOF, "", 0, line});
            return list;
        }

        shared_ptr<ArrayList<Token>> scanNext() {
            error = false;
            shared_ptr<ArrayList<Token>> list = make_shared<ArrayList<Token>>();
            char sline[513];
            input->getline(sline, 512);
            if (input->eof()) {
                list->append(Token{TokenType::TOKEN_EOF, "", 0, line});
                return list;
            }
            list->appendAll(*scanLine(sline));
            line++;
            list->append(Token{TokenType::TOKEN_EOF, "", 0, line});
            return list;
        }

        shared_ptr<ArrayList<Token>> scanLine(const char *line) {
            shared_ptr<ArrayList<Token>> list = make_shared<ArrayList<Token>>();
            int linelen = strlen(line);

            int index = 0;
            while (index < linelen) {
                if (line[index] == '"') {

                    index++;
                    int start = index;
                    while (line[index] != '"') {

                        index++;
                        if (index >= linelen) {

                            const char errorMsg[] = "Unterminated string.";
                            list->append({TokenType::TOKEN_ERROR,
                                          errorMsg, (int) strlen(errorMsg), this->line});
                            error = true;
                            return list;
                        }
                    }

                    if (index + 1 != linelen && line[index + 1] != ' ') {
                        const char errorMsg[] = "Expected whitespace or EOL after string.";
                        list->append({TokenType::TOKEN_ERROR,
                                      errorMsg, (int) strlen(errorMsg), this->line});
                        error = true;
                        return list;
                    }

                    char lexeme[index - start];
                    strncpy(lexeme, line + start, index - start);
                    lexeme[index - start] = '\0';
                    list->append({TokenType::TOKEN_STRING, lexeme, (int) strlen(lexeme), this->line});
                    index++;
                } else if (isdigit(line[index]) ||
                           (line[index] == '-' && index + 1 < linelen && isdigit(line[index + 1]))) {

                    int start = index;
                    if(line[index] == '-') index++;
                    TokenType tt = TokenType::TOKEN_NUMBER;
                    while (isdigit(line[index])) {

                        index++;
                        if (line[index] == '-' && tt == TokenType::TOKEN_NUMBER) {

                            tt = TokenType::TOKEN_NUMERIC_RANGE;
                            index++;
                        } else if (line[index] == '-' && tt == TokenType::TOKEN_NUMERIC_RANGE) {
                            tt = TokenType::TOKEN_DATE;
                            index++;
                        } else if (line[index] == '-') {
                            const char errorMsg[] = "Malformed date.";
                            list->append({TokenType::TOKEN_ERROR,
                                          errorMsg, (int) strlen(errorMsg), this->line});
                            error = true;
                            return list;
                        }
                    }


                    if (line[index - 1] == '-' || (index != linelen && line[index] != ' ')) {
                        const char errorMsg[] = "Malformed number or numeric range.";
                        list->append({TokenType::TOKEN_ERROR,
                                      errorMsg, (int) strlen(errorMsg), this->line});
                        error = true;
                        return list;
                    }
                    char lexeme[index - start];
                    strncpy(lexeme, line + start, index - start);
                    lexeme[index - start] = '\0';
                    list->append({tt, lexeme, (int) strlen(lexeme), this->line});
                    index++;
                } else if (line[index] == ' ') {
                    index++;
                } else{
                    int start = index;
                    index++;
                    while (index < linelen && line[index] != ' ') {
                        index++;
                    }

                    if (index != linelen && line[index] != ' ') {
                        const char errorMsg[] = "Expected whitespace or EOL after identifier.";
                        list->append({TokenType::TOKEN_ERROR,
                                      errorMsg, (int) strlen(errorMsg), this->line});
                        error = true;
                        return list;
                    }

                    char lexeme[index - start];
                    strncpy(lexeme, line + start, index - start);
                    lexeme[index - start] = '\0';
                    shared_ptr<Nullable<TokenType>> tt = cl.tokenFor(lexeme);
                    if (tt->isDefined())
                    {
                        ScannerContext tctx = cl.contextFor(tt->get())
                            ->getOrElse(ScannerContext::UNDEFINED);
                        if(tctx == ScannerContext::ALL || tctx == sc || sc == ScannerContext::ALL){
                            list->append({tt->get(), lexeme, (int) strlen(lexeme), this->line});
                        }else{
                            const char errorMsg[] = "Command used in the wrong context.";
                            list->append({TokenType::TOKEN_ERROR,
                                          errorMsg, (int) strlen(errorMsg), this->line});
                            error = true;
                            return list;
                        }
                    } else {
                        list->append({TokenType::TOKEN_STRING,
                                      lexeme, (int) strlen(lexeme), this->line});
                        return list;
                    }
                    index++;
                }
            }

            return list;
        }
    };

}


#endif //OOPPROJECT_COMMANDSCANNER_HPP
