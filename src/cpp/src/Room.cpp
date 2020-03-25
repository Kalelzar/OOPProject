//
// Created by Kalelzar on 25/03/2020.
//

#include <cstring>
#include "Room.hpp"

Hotel::Room::Room(int id) {
    init(id);
}

void Hotel::Room::setNote(const char *note) {
    delete [] this->note;
    this->note = new char[strlen(note)+1];
    strcpy(this->note, note);
}

void Hotel::Room::setState(Hotel::RoomState state, Hotel::Date from, Hotel::Date to) {
    this->state=state;
    stateFrom = from;
    stateTo = to;
}

Hotel::Room::Room() {
    init(0);
}

void Hotel::Room::init(int id) {
    this->id = id;
    state=RoomState::FREE;
    stateFrom=Date::today();
    stateTo=Date::today();
    note=new char[1];
    strcpy(note, "");
}
