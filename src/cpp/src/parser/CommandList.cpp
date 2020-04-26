#include "CommandList.hpp"

Hotel::CommandList Hotel::CommandList::globalCommandList{};

void Hotel::CommandList::copy(CommandList const &other) {
    nameToToken = other.nameToToken;
    commandMap = other.commandMap;
    nameToDescr = other.nameToDescr;
}

Hotel::CommandList::CommandList() {
    nameToToken = {};
    commandMap = {};
    nameToDescr = {};
}

Hotel::CommandList::CommandList(CommandList const &other){
    if (&other != this) {
        copy(other);
    }
}

Hotel::CommandList &Hotel::CommandList::operator=(Hotel::CommandList const &other){
    if (&other != this) {
        copy(other);
    }
    return *this;
}

void Hotel::CommandList::registerCommand(SimpleString name, TokenType tokenType,
                                         ScannerContext ctx,
                                         SimpleString descr) {
    commandMap.put(tokenType, ctx);
    nameToToken.put(name, tokenType);
    nameToDescr.put(name, descr);
}

void Hotel::CommandList::printCommandsWithDescription(){
    std::cout<<"Simple Command-line interface for Hotel Management"<<std::endl;
    unique_ptr<ArrayList<SimpleString>> keys = nameToDescr.keys();
    unique_ptr<ArrayList<SimpleString>> values = nameToDescr.values();
    for(int i = 0; i < keys->length(); i++){
        std::cout<<keys->get(i)<<" "<<values->get(i)<<std::endl;
    }
}

bool Hotel::CommandList::isCommand(TokenType tokenType){
    return commandMap.contains(tokenType);
}

bool Hotel::CommandList::isCommand(SimpleString name){
    return nameToToken.contains(name);
}

unique_ptr<Nullable<ScannerContext>> Hotel::CommandList::contextFor(TokenType tokenType){
    return commandMap.get(tokenType);
}

unique_ptr<Nullable<TokenType>> Hotel::CommandList::tokenFor(SimpleString name) {
    return nameToToken.get(name);
}
