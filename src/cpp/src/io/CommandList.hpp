#ifndef OOPPROJECT_COMMANDLIST_HPP
#define OOPPROJECT_COMMANDLIST_HPP
#include "ScannerContext.hpp"
#include "../collection/HashMap.hpp"
#include "Token.hpp"
#include "../SimpleString.hpp"
namespace Hotel {
    class CommandList {
    private:
        //HashMap<TokenType, ScannerContext> commandMap;
        HashMap<SimpleString, TokenType> nameToToken;

        void copy(CommandList const& other){
            nameToToken = other.nameToToken;
        }

    public:

        CommandList(){
            nameToToken = {};
        }

        CommandList(CommandList const& other){
            if(&other != this){
                copy(other);
            }
        }

        CommandList& operator=(CommandList const& other){
            if(&other != this){
                copy(other);
            }
            return *this;
        }

        void registerCommand(SimpleString name, TokenType tokenType, ScannerContext ctx){
            // commandMap.put(tokenType, ctx);
            nameToToken.put(name, tokenType);
        }

        void printCommands(){
            std::cout<<"Commands!"<<std::endl;
            nameToToken.keys()->foreach([](SimpleString str){
                                            std::cout<<"K: "<<str<<std::endl;
                                        });
        };

        bool isCommand(TokenType tokenType){
            return false; //commandMap.contains(tokenType);
        }

        bool isCommand(SimpleString name){
            return nameToToken.contains(name);
        }

        unique_ptr<Nullable<ScannerContext>> contextFor(TokenType tokenType){
            return make_unique<Null<ScannerContext>>();//commandMap.get(tokenType);
        }

        unique_ptr<Nullable<TokenType>> tokenFor(SimpleString name){
            return nameToToken.get(name);
        }
    };
}

#endif //OOPPROJECT_COMMANDLIST_HPP
