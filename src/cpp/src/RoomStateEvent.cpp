//
// Created by Kalelzar on 30/03/2020.
//

#include "RoomStateEvent.hpp"

#include <cstring>

bool Hotel::RoomStateEvent::operator==(RoomStateEvent const &other) const {
  return room == other.room && state == other.state && from == other.from &&
         to == other.to;
}

bool Hotel::RoomStateEvent::operator!=(RoomStateEvent const &other) const {
  return !(*this == other);
}

bool Hotel::RoomStateEvent::operator>(RoomStateEvent const &other) const {
  return from > other.to;
}

bool Hotel::RoomStateEvent::operator<(RoomStateEvent const &other) const {
  return to < other.from;
}

bool Hotel::RoomStateEvent::operator>=(RoomStateEvent const &other) const {
  return from >= other.from;
}

bool Hotel::RoomStateEvent::operator<=(RoomStateEvent const &other) const {
  return to <= other.to;
}

void Hotel::RoomStateEvent::setNote(const char *note) {
  freeNote();
  this->note = new char[strlen(note) + 1];
  strcpy(this->note, note);
}

Hotel::RoomStateEvent::RoomStateEvent() {
  init(RoomState::UNKNOWN, {}, {}, {}, "", -1);
}

Hotel::RoomStateEvent &
Hotel::RoomStateEvent::operator=(const Hotel::RoomStateEvent &other) {
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
  init(other.state, other.room, other.from, other.to, other.getNote(),
       other.extra);
}

void Hotel::RoomStateEvent::init(RoomState const &_state, Room const &_room,
                                 Date const &_from, Date const &_to,
                                 const char *_note, int _extra) {
  state = _state;
  room = _room;
  from = _from;
  to = _to;
  extra = _extra;
  note = new char[strlen(_note) + 1];
  strcpy(note, _note);
}

Hotel::RoomStateEvent::RoomStateEvent(RoomState const &_state,
                                      Room const &_room, Date const &_from,
                                      Date const &_to) {
  init(_state, _room, _from, _to, "", -1);
}

Hotel::RoomStateEvent::RoomStateEvent(RoomState const &_state,
                                      Room const &_room, Date const &_from,
                                      Date const &_to, const char *_note,
                                      int extra) {
  init(_state, _room, _from, _to, _note, extra);
}
