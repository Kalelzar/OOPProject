#ifndef OOPPROJECT_COMMANDLIST_HPP
#define OOPPROJECT_COMMANDLIST_HPP

#include "ScannerContext.hpp"
#include "../collection/HashMap.hpp"
#include "Token.hpp"
#include "../SimpleString.hpp"

namespace Hotel {
    class CommandList {
    private:
        HashMap<TokenType, ScannerContext> commandMap;
        HashMap<SimpleString, TokenType> nameToToken;
        HashMap<SimpleString, SimpleString> nameToDescr;

        static CommandList globalCommandList;

        void copy(CommandList const &other) {
            nameToToken = other.nameToToken;
            commandMap = other.commandMap;
            nameToDescr = other.nameToDescr;
        }

    public:

        static CommandList getCommandList() {
            return globalCommandList;
        }

        static void setCommandList(CommandList const& cl){
            globalCommandList = cl;
        }

        CommandList() {
            nameToToken = {};
            commandMap = {};
            nameToDescr = {};
        }

        CommandList(CommandList const &other) {
            if (&other != this) {
                copy(other);
            }
        }

        CommandList &operator=(CommandList const &other) {
            if (&other != this) {
                copy(other);
            }
            return *this;
        }

        void registerCommand(SimpleString name, TokenType tokenType, ScannerContext ctx,
            SimpleString descr) {
            commandMap.put(tokenType, ctx);
            nameToToken.put(name, tokenType);
            nameToDescr.put(name, descr);
        }

        void printCommands() {
            std::cout << "Commands!" << std::endl;
            nameToToken.keys()->foreach([](SimpleString str) {
                std::cout << "K: " << str << std::endl;
            });
        };

        void printCommandsWithDescription(){
            std::cout<<"Simple Command-line interface for Hotel Management"<<std::endl;
            unique_ptr<ArrayList<SimpleString>> keys = nameToDescr.keys();
            unique_ptr<ArrayList<SimpleString>> values = nameToDescr.values();
            for(int i = 0; i < keys->length(); i++){
                std::cout<<keys->get(i)<<" "<<values->get(i)<<std::endl;
            }
        }

        bool isCommand(TokenType tokenType) {
            return commandMap.contains(tokenType);
        }

        bool isCommand(SimpleString name) {
            return nameToToken.contains(name);
        }

        unique_ptr<Nullable<ScannerContext>> contextFor(TokenType tokenType) {
            return commandMap.get(tokenType);
        }

        unique_ptr<Nullable<TokenType>> tokenFor(SimpleString name) {
            return nameToToken.get(name);
        }
    };
}

#endif //OOPPROJECT_COMMANDLIST_HPP
