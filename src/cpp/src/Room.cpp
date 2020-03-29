//
// Created by Kalelzar on 25/03/2020.
//

#include <cstring>
#include "Room.hpp"

bool Hotel::RoomStateEvent::operator==(RoomStateEvent const& other) const {
    return room == other.room
        && state == other.state
        && from == other.from
        && to == other.to;
}

bool Hotel::RoomStateEvent::operator!=(RoomStateEvent const& other) const {
    return !(*this == other);
}

bool Hotel::RoomStateEvent::operator>(RoomStateEvent const& other) const {
    return from > other.to;
}

bool Hotel::RoomStateEvent::operator<(RoomStateEvent const& other) const {
    return to < other.from;
}

bool Hotel::RoomStateEvent::operator>=(RoomStateEvent const& other) const {
    return from >= other.from;
}

bool Hotel::RoomStateEvent::operator<=(RoomStateEvent const& other) const {
    return to <= other.to;
}

Hotel::Room::Room(int _id, int _beds) {
    init(_id, _beds);
}

void Hotel::Room::setNote(const char *note) {
    freeNote();
    this->note = new char[strlen(note) + 1];
    noteFreed = false;
    strcpy(this->note, note);
}


Hotel::Room::Room() {
    init(0, 0);
}

void Hotel::Room::init(int _id, int _beds) {
    id = _id;
    beds = _beds;
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
    beds = other.getBeds();
    freeNote();
    note = new char[strlen(other.getNote()) + 1];
    strcpy(note, other.note);
    noteFreed = false;
}
