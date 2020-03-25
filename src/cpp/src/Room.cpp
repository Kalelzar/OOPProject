//
// Created by Kalelzar on 25/03/2020.
//

#include <cstring>
#include "Room.hpp"

Hotel::Room::Room(int id) {
    init(id);
}

void Hotel::Room::setNote(const char *note) {
    freeNote();
    this->note = new char[strlen(note) + 1];
    noteFreed = false;
    strcpy(this->note, note);
}

void Hotel::Room::setState(Hotel::RoomState state, Hotel::Date from, Hotel::Date to) {
    this->state = state;
    stateFrom = from;
    stateTo = to;
}

Hotel::Room::Room() {
    init(0);
}

void Hotel::Room::init(int id) {
    this->id = id;
    state = RoomState::FREE;
    stateFrom = Date::today();
    stateTo = Date::today();
    note = new char[1];
    note[0] = '\0';
    noteFreed = false;
}

Hotel::Room &Hotel::Room::operator=(const Hotel::Room &other) {
    if (&other != this)
        copy(other);
    return *this;
}

Hotel::Room::Room(const Hotel::Room &other) {
    if (&other != this){}
        copy(other);
}

void Hotel::Room::copy(const Hotel::Room &other) {
    id = other.getID();
    state = other.getState();
    stateFrom = other.getStateFrom();
    stateTo = other.getStateTo();
    freeNote();
    note = new char[strlen(other.getNote()) + 1];
    strcpy(note, other.note);
    noteFreed = false;
}
