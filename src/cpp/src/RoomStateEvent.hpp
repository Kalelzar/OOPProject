//
// Created by Kalelzar on 30/03/2020.
//

#ifndef OOPPROJECT_ROOMSTATEEVENT_HPP
#define OOPPROJECT_ROOMSTATEEVENT_HPP

#include "Date.hpp"
#include "Room.hpp"

namespace Hotel {

/**
 * Describes the state a room is in.
 * A room is either free, taken or unavailable.
 * Only a free room can be checked-into.
 * Only a taken room can be checked-out of.
 * Only a free room may be marked unavailable.
 * If state is unknown then something went horribly wrong.
 */
enum class RoomState { FREE, TAKEN, WAS_TAKEN, UNAVAILABLE, UNKNOWN = -1 };

class RoomStateEvent {
private:
  char *note{};

  /**
   * Frees the memory associated with the note
   */
  void freeNote() { delete[] note; }

  /**
   * Safely copies a different room state event to this one
   * @param other the room state event to copy
   */
  void copy(RoomStateEvent const &other);

  /// Initialize the event
  void init(RoomState const &_state, Room const &_room, Date const &_from,
            Date const &_to, const char *_note, int _extra);

public:
  RoomState state;
  Room room;
  Date from;
  Date to;
  int extra;

  RoomStateEvent();

  RoomStateEvent(RoomState const &_state, Room const &_room, Date const &_from,
                 Date const &_to);

  RoomStateEvent(RoomState const &_state, Room const &_room, Date const &_from,
                 Date const &_to, const char *_note, int extra);

  RoomStateEvent(RoomStateEvent const &other);

  RoomStateEvent &operator=(RoomStateEvent const &other);

  ~RoomStateEvent() { freeNote(); }

  /**
   * Set the note attached to this room state event
   * @param note the note
   */
  void setNote(const char *note);

  /**
   * The note attached to this room state event
   * @return the note
   */
  char *getNote() const { return note; }

  bool operator==(RoomStateEvent const &other) const;

  bool operator!=(RoomStateEvent const &other) const;

  bool operator>(RoomStateEvent const &other) const;

  bool operator>=(RoomStateEvent const &other) const;

  bool operator<(RoomStateEvent const &other) const;

  bool operator<=(RoomStateEvent const &other) const;

  friend std::ostream &operator<<(std::ostream &out,
                                  RoomStateEvent const &rse) {
    switch (rse.state) {
    case RoomState::FREE:
      out << "free ";
      break;
    case RoomState::TAKEN:
    case RoomState::WAS_TAKEN:
      out << "checkin ";
      break;
    case RoomState::UNAVAILABLE:
      out << "unavailable ";
      break;
    case RoomState::UNKNOWN:
      out << "unknown ";
      break;
    }

    out << rse.room.id << " " << rse.from << " " << rse.to << " \""
        << rse.getNote() << "\"";

    if (rse.extra != -1) {
      out << " " << rse.extra;
    }

    out << std::endl;
    if (rse.state == RoomState::WAS_TAKEN) {
      out << "checkout " << rse.room.id << std::endl;
    }
    return out;
  }
};

} // namespace Hotel

#endif // OOPPROJECT_ROOMSTATEEVENT_HPP
