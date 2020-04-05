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
        std::istream* input;
        int line = 1;
    public:
        CommandScanner(ScannerContext sc, std::istream* input, CommandList const& cl){
            this->sc = sc;
            this->input = input;
            this->cl = cl;
            this->cl.printCommands();
        }

        unique_ptr<ArrayList<Token>> scan(){
            unique_ptr<ArrayList<Token>> list = make_unique<ArrayList<Token>>();
            while(!input->eof()){
                char sline[513];
                input->getline(sline, 512);
                if(input->eof()) break;
                list->appendAll(*scanLine(sline));
                line++;
            }
            list->append(Token{TokenType::TOKEN_EOF, "", 0, line});
            return list;
        }

        unique_ptr<ArrayList<Token>> scanNext(){
            unique_ptr<ArrayList<Token>> list = make_unique<ArrayList<Token>>();
            char sline[513];
            input->getline(sline, 512);
            if(input->eof()){
                list->append(Token{TokenType::TOKEN_EOF, "EOF", 3, line});
                return list;
            }
            list->appendAll(*scanLine(sline));
            line++;
            list->append(Token{TokenType::TOKEN_EOF, "EOF", 3, line});
            return list;
        }

        unique_ptr<ArrayList<Token>> scanLine(const char* line){
            unique_ptr<ArrayList<Token>> list = make_unique<ArrayList<Token>>();
            int linelen = strlen(line);

            int index = 0;
            while(index < linelen){
                if(line[index] == '"'){

                    index++;
                    int start = index;
                    while(line[index] != '"'){

                        index++;
                        if(index >= linelen){

                            const char errorMsg[] = "Unterminated string.";
                            list->append({TokenType::TOKEN_ERROR,
                                         errorMsg, (int) strlen(errorMsg), this->line });
                            return list;
                        }
                    }

                    if(index+1 != linelen && line[index+1] != ' '){
                        const char errorMsg[] = "Expected whitespace or EOL after string.";
                        list->append({TokenType::TOKEN_ERROR,
                                      errorMsg, (int) strlen(errorMsg), this->line });
                        return list;
                    }

                    char lexeme[index-start];
                    strncpy(lexeme, line+start, index-start);
                    lexeme[index-start] = '\0';
                    list->append({TokenType::TOKEN_STRING, lexeme, (int) strlen(lexeme), this->line});
                    index++;
                }else if(isdigit(line[index]) || (line[index] == '-' && index+1 < linelen && isdigit(line[index+1]))){


                    int start = index;
                    index++;
                    TokenType tt = TokenType::TOKEN_NUMBER;
                    while(isdigit(line[index])){

                        index++;
                        if(line[index] == '-'  && tt==TokenType::TOKEN_NUMBER){

                            tt = TokenType::TOKEN_NUMERIC_RANGE;
                            index++;
                        }else if(line[index] == '-'  && tt==TokenType::TOKEN_NUMERIC_RANGE){
                            tt = TokenType::TOKEN_DATE;
                            index++;
                        }else if(line[index] == '-'){
                            const char errorMsg[] = "Malformed numeric range.";
                            list->append({TokenType::TOKEN_ERROR,
                                          errorMsg, (int) strlen(errorMsg), this->line });
                            return list;
                        }
                    }


                    if(line[index-1] == '-' || (index != linelen && line[index] != ' ')){
                        const char errorMsg[] = "Malformed number or numeric range.";
                        list->append({TokenType::TOKEN_ERROR,
                                      errorMsg, (int) strlen(errorMsg), this->line });
                        return list;
                    }
                    char lexeme[index-start];
                    strncpy(lexeme, line+start, index-start);
                    lexeme[index-start] = '\0';
                    list->append({tt, lexeme, (int) strlen(lexeme), this->line});
                    index++;
                }else if(line[index] == ' '){
                    index++;
                }else if(isalpha(line[index])){
                    int start = index;
                    index++;
                    while(isalnum(line[index]) || line[index]=='!'){
                        index++;
                    }

                    if(index != linelen && line[index] != ' '){
                        const char errorMsg[] = "Expected whitespace or EOL after identifier.";
                        list->append({TokenType::TOKEN_ERROR,
                                      errorMsg, (int) strlen(errorMsg), this->line });
                        return list;
                    }

                    char lexeme[index-start];
                    strncpy(lexeme, line+start, index-start);
                    lexeme[index-start] = '\0';
                    unique_ptr<Nullable<TokenType>> tt = cl.tokenFor(lexeme);
                    if(tt->isDefined()){
                        list->append({tt->get(), lexeme, (int) strlen(lexeme), this->line});
                    }else{
                        const char errorMsg[] = "Unrecognized identifier.";
                        list->append({TokenType::TOKEN_ERROR,
                                      errorMsg, (int) strlen(errorMsg), this->line });
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
