//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_HTLINTERPRETER_HPP
#define OOPPROJECT_HTLINTERPRETER_HPP

#include "Token.hpp"
#include "../HotelState.hpp"
#include "../ReachedEndOfStreamException.hpp"
#include "../WrongTokenTypeException.hpp"
#include "CommandList.hpp"

#include <iostream>
#include <cstring>
#include <cstdlib>

namespace Hotel {

    class HTLInterpreter {
    private:
        shared_ptr<ArrayList<Token>> tokens;
        unsigned index = 0;

        bool isAtEnd() const {
            return index >= tokens->length();
        }

        Token next(){
            if(isAtEnd()) throw ReachedEndOfStreamException{};
            else {
                index++;
                return tokens->get(index-1);
            }
        }

        Token peek() const {
            if(isAtEnd()) throw ReachedEndOfStreamException{};
            else {
                return tokens->get(index);
            }
        }

        void error(int line, const char* msg) const {
            char sline[32];
            sprintf(sline, "%d", line);
            char nmsg[6 + strlen(sline)+ 3 + strlen(msg) + 1];
            strcpy(nmsg, "Line: ");
            strcpy(nmsg+6, sline);
            strcpy(nmsg+6+strlen(sline), " - ");
            strcpy(nmsg+6+strlen(sline)+3, msg);
            //std::cerr<<nmsg<<std::endl;
            throw WrongTokenTypeException(msg);
        }

        Token consume(TokenType type, const char* msg){
            if(!matches(type)){
                error(peek().line, msg);
            }else{
                return next();
            }
        }

        bool matches(TokenType type) const {
            return peek().t == type;
        }

        Token prev() const {
            return tokens->get(index-1);
        }


        void add(HotelState &state){
            if(matches(TokenType::NUMBER)){

                Token roomid = next();

                Token beds = consume(TokenType::NUMBER,
                                     "add <room> <beds> : <beds> should be a number");

                Room r {atoi(roomid.lexeme), atoi(beds.lexeme)};
                state.add(r);

            }else if(matches(TokenType::NUMERIC_RANGE)){
                error(peek().line, "Not implemented!");
            }else{
                error(peek().line, "add <room> <beds> : <room> should be a number or a numeric range");
            }
        }

        void remove(HotelState &state){
            if(matches(TokenType::NUMBER)){

                Token roomid = next();

                Room r {atoi(roomid.lexeme), 0};
                state.remove(r);

            }else if(matches(TokenType::NUMERIC_RANGE)){
                error(peek().line, "Not implemented!");
            }else{
                error(peek().line, "remove <room> : <room> should be a number or a numeric range");
            }
        }

        void checkout(HotelState &state){
            Token roomid = consume(TokenType::NUMBER,
                                   "checkout <room>: <room> should be a number or a numeric range");
            state.checkout(atoi(roomid.lexeme));
        }

        void checkin(HotelState &state){
            if(matches(TokenType::NUMBER)){

                Token roomid = next();

                Token from = consume(TokenType::DATE,
                  "checkin <room> <from> <to> <note> : <from> should be date.");

                Token to = consume(TokenType::DATE,
                    "checkin <room> <from> <to> <note> : <to> should be date.");

                Token note = consume(TokenType::STRING,
                  "checkin <room> <from> <to> <note> : <note> should be string.");

                state.checkin(atoi(roomid.lexeme), Date(from.lexeme), Date(to.lexeme),
                              note.lexeme);

            }else if(matches(TokenType::NUMERIC_RANGE)){
                error(peek().line, "Not implemented!");
            }else{
                error(peek().line, "checkin <room> <from> <to> <note> : <room> should be a number or a numeric range");
            }
        }

        void unavailable(HotelState &state){
            if(matches(TokenType::NUMBER)){

                Token roomid = next();

                Token from = consume(TokenType::DATE,
                                     "unavailable <room> <from> <to> <note> : <from> should be date.");

                Token to = consume(TokenType::DATE,
                                   "unavailable <room> <from> <to> <note> : <to> should be date.");

                Token note = consume(TokenType::STRING,
                                     "unavailable <room> <from> <to> <note> : <note> should be string.");

                state.unavailable(atoi(roomid.lexeme), Date(from.lexeme), Date(to.lexeme),
                              note.lexeme);

            }else if(matches(TokenType::NUMERIC_RANGE)){
                error(peek().line, "Not implemented!");
            }else{
                error(peek().line, "unavailable <room> <from> <to> <note> : <room> should be a number or a numeric range");
            }
        }

        void report(HotelState &state){
            Token from = consume(TokenType::DATE,
                                 "report <from> <to> : <from> should be a date");

            Token to = consume(TokenType::DATE,
                                 "report <from> <to> : <to> should be a date");

            state.report(Date(from.lexeme), Date(to.lexeme));
        }

        void find(HotelState &state){
            Token beds = consume(TokenType::NUMBER,
                                 "find <beds> <from> <to> : <beds> should be a number");

            Token from = consume(TokenType::DATE,
                                 "find <beds> <from> <to> : <from> should be a date");

            Token to = consume(TokenType::DATE,
                               "find <beds> <from> <to> : <to> should be a date");

            state.find(atoi(beds.lexeme), Date(from.lexeme), Date(to.lexeme));
        }

        void find_f(HotelState &state){
            Token beds = consume(TokenType::NUMBER,
                                 "find! <beds> <from> <to> : <beds> should be a number");

            Token from = consume(TokenType::DATE,
                                 "find! <beds> <from> <to> : <from> should be a date");

            Token to = consume(TokenType::DATE,
                               "find! <beds> <from> <to> : <to> should be a date");

            state.findForce(atoi(beds.lexeme), Date(from.lexeme), Date(to.lexeme));
        }

        void available(HotelState &state){
            if(matches(TokenType::DATE)){
                Token date = next();
                state.available(Date(date.lexeme));
            }else{
                state.available();
            }
        }

        void save(HotelState &state){
            state.save();
        }

        void saveAs(HotelState &state){
            Token path = consume(TokenType::STRING, "saveas <path> : <path> should be string");
            state.saveAs(path.lexeme);
        }

        void open(HotelState &state){
            Token path = consume(TokenType::STRING, "open <path> : <path> should be string");
            state.setFile(path.lexeme);
            state.load();
        }

        void close(HotelState &state){
            state.close();
        }

    public:

        bool errorflag = false;

        HTLInterpreter(shared_ptr<ArrayList<Token>> _tokens){
            tokens = _tokens;
        }

        bool parse(HotelState &state){
            errorflag = false;
            while(!isAtEnd()){
                try{
                    switch(next().t){
                    case TokenType::ADD:
                        add(state);
                        break;
                    case TokenType::REMOVE:
                        remove(state);
                        break;
                    case TokenType::OPEN:
                        open(state);
                        break;
                    case TokenType::CLOSE:
                        close(state);
                        break;
                    case TokenType::SAVE:
                        save(state);
                        break;
                    case TokenType::SAVE_AS:
                        saveAs(state);
                        break;
                    case TokenType::HELP:
                        CommandList::getCommandList().printCommandsWithDescription ();
                        break;
                    case TokenType::EXIT:
                        return false;
                        break;
                    case TokenType::CHECKIN:
                        checkin(state);
                        break;
                    case TokenType::CHECKOUT:
                        checkout(state);
                        break;
                    case TokenType::REPORT:
                        report(state);
                        break;
                    case TokenType::FIND:
                        find(state);
                        break;
                    case TokenType::FIND_F:
                        find_f(state);
                        break;
                    case TokenType::UNAVAILABLE:
                        unavailable(state);
                        break;
                    case TokenType::STRING:
                        errorflag = true;
                        std::cerr<<"(Line "<<prev().line<<") "<<"Unexpected String -> " << prev().lexeme <<std::endl;
                        break;
                    case TokenType::NUMBER:
                        errorflag = true;
                        std::cerr<<"(Line "<<prev().line<<") "<<"Unexpected Number -> " << prev().lexeme <<std::endl;
                        break;
                    case TokenType::DATE:
                        errorflag = true;
                        std::cerr<<"(Line "<<prev().line<<") "<<"Unexpected Date -> " << prev().lexeme <<std::endl;
                        break;
                    case TokenType::NUMERIC_RANGE:
                        errorflag = true;
                        std::cerr<<"(Line "<<prev().line<<") "<<"Unexpected Numeric Range -> " << prev().lexeme <<std::endl;
                        break;
                    case TokenType::ERROR:
                        errorflag = true;
                        std::cerr<<"(Line "<<prev().line<<") "<<"Parsing error: " << prev().lexeme << std::endl;
                        break;
                    case TokenType::AVAILABILITY:
                        available(state);
                        break;
                    case TokenType::EOF_T:
                        return true;
                        break;
                    }
                }catch(NoValueException& e){
                    errorflag = true;
                    std::cerr<<e.what()<<std::endl;
                }catch(ReachedEndOfStreamException& e){
                    errorflag = true;
                    std::cerr<<e.what()<<std::endl;
                    return true;
                }catch(WrongTokenTypeException& e){
                    errorflag = true;
                    std::cerr<<e.what()<<std::endl;
                    while(peek().t == TokenType::STRING ||
                          peek().t == TokenType::NUMBER ||
                          peek().t == TokenType::DATE ||
                          peek().t == TokenType::NUMERIC_RANGE ||
                          peek().t == TokenType::ERROR){
                        Token n = next();
                        if(n.t == TokenType::ERROR){
                            std::cerr<<n.lexeme<<std::endl;
                        }
                    }
                }
            }
            return true;
        }

    };

}
#endif //OOPPROJECT_HTLINTERPRETER_HPP
