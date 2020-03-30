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


void Hotel::RoomStateEvent::setNote(const char *note) {
    freeNote();
    this->note = new char[strlen(note) + 1];
    noteFreed = false;
    strcpy(this->note, note);
}

Hotel::RoomStateEvent::RoomStateEvent(){
    init(RoomState::UNKNOWN, {}, {}, {}, "");
}


Hotel::RoomStateEvent &Hotel::RoomStateEvent::operator=(const Hotel::RoomStateEvent &other) {
    if (&other != this)
        copy(other);
    return *this;
}

Hotel::RoomStateEvent::RoomStateEvent(const Hotel::RoomStateEvent &other) {
    if (&other != this)
        copy(other);
}

void Hotel::RoomStateEvent::copy(const Hotel::RoomStateEvent &other) {
    freeNote();
    noteFreed = false;
    init(other.state, other.room, other.from, other.to, other.getNote());
}

void Hotel::RoomStateEvent::init(RoomState const& _state,
          Room const& _room,
          Date const& _from,
          Date const& _to,
          const char* _note){
    state = _state;
    room = _room;
    from = _from;
    to = _to;
    note = new char[strlen(_note) + 1];
    noteFreed = false;
    strcpy(note, _note);
}

Hotel::RoomStateEvent::RoomStateEvent(RoomState const& _state,
                                      Room const& _room,
                                      Date const& _from,
                                      Date const& _to){
    init(_state, _room, _from, _to, "");
}

Hotel::RoomStateEvent::RoomStateEvent(RoomState const& _state,
                                      Room const& _room,
                                      Date const& _from,
                                      Date const& _to,
                                      const char* _note){
    init(_state, _room, _from, _to, _note);
}
