//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_ROOM_HPP
#define OOPPROJECT_ROOM_HPP

#include <memory>

namespace Hotel {
class RoomStateEvent; // Forward definition of RoomStateEvent
                      // Needed to resolve a circular dependency
/**
 * A room described by a number.
 * It also has a specific amount of beds.
 * And a state as well as a range for how long the state applies.
 * Free state can be indefinite unless there is a different state scheduled in
 * the future. States can also have a note attached to them.
 */
struct Room {
  int id{};
  int beds{};
  bool checkedIn{};
  std::shared_ptr<RoomStateEvent> rse;

  Room(int _id, int _beds);

  Room();

  /**
   * Checks if the provided room is the same as this one.
   * Rooms with the same number are treated as if they were the same
   * regardless of the rest of their state.
   * @param other the other room
   * @return is the other room the same as this one
   */
  bool operator==(Room const &other) const { return id == other.id; }

  bool operator!=(Room const &other) const { return !(*this == other); }
};

} // namespace Hotel
#endif // OOPPROJECT_ROOM_HPP
