//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_HOTELSTATE_HPP
#define OOPPROJECT_HOTELSTATE_HPP

#include "DateRange.hpp"
#include "Date.hpp"
#include "Room.hpp"
#include "collection/HashMap.hpp"
#include "collection/RangeBinaryTree.hpp"
#include "RoomStateEvent.hpp"

namespace Hotel {
/// The core of the application.
/// Doubles as UI API
class HotelState {
private:
  HashMap<int, Room> rl{};
  RangeBinaryTree<DateRange, std::shared_ptr<RoomStateEvent>> tree{};
  char *filepath;
  bool modified;

  bool open = false;
  void copy(HotelState const &state);

    /**Set the state of a room.
     * @param state the state to set it to
     * @param roomid the id of the room whose state to change
     * @param from from which date the new state applies
     * @param to up to which date the new state applies
     * @param note a note to attach to the state
     * @param extra extra parameter needed by some states
     * @return a pointer to the generated {@link Hotel::RoomStateEvent State}
     */
  std::shared_ptr<Hotel::RoomStateEvent>
  setRoomState(RoomState state, int roomid, Hotel::Date from, Hotel::Date to,
               const char *note, int extra = -1);

    ///Return all RoomStateEvents that are active at the provided date.
  std::unique_ptr<ArrayList<std::shared_ptr<RoomStateEvent>>>
  roomEventsCovering(Date d) const;

    ///All rooms which are marked as free in the given time period
  std::unique_ptr<ArrayList<Room>> roomsAvailableFrom(Date from, Date to) const;

    ///Logic for the find function
  std::unique_ptr<Nullable<Hotel::Room>> findBackend(int beds, Date from,
                                                     Date to) const;

    ///Free used resources. Called on destruction
  void free();

public:
    ///Is a file open
  bool isOpen() const { return open; }

    ///Check if file is open and if it isn't print a message to stderr
  bool checkOpen() const {
    if (isOpen())
      return true;
    std::cerr << "You must open a file first!" << std::endl;
    return false;
  }

    ///Create a new state from a file.
  HotelState(const char *filepath);

    ///Generic state
  HotelState();

    ///Copy constructor
  HotelState(HotelState const &state);

    ///Assignment operator
  HotelState &operator=(HotelState const &other);


  ~HotelState();
    ///Reset internal state
  void clear();

    ///Set the path to the file this state is operating on.
  void setFile(const char *path);
    ///Return the path to the file.
  const char *getFile() const;

    ///Load info from file.
  void load();

    ///Close the file.
  void close();

    ///Save the file
  void save();

    ///Save to new file and set it as active file.
  void saveAs(const char *path);

    ///Add a new room
  void add(Room r);

    ///Remove a room
  void remove(Room r);

    ///Check into room
  void checkin(int roomid, Date start, Date end, const char *note, int people);

    ///Print all rooms that are free on the current date
  void available() const { available(Date::today()); }

    ///Print all room that are free on the given date
  void available(Date date) const;

    ///Check out of room
  void checkout(int roomid);

    ///Report room usage in the given time period.
  void report(Date from, Date to);

    ///Find a room with the specified amount of rooms available (or more) in the given time period.
  bool find(int beds, Date from, Date to) const;

  void findForce(int beds, Date from, Date to);

  void unavailable(int roomid, Date from, Date to, const char *note);

    };
}

#endif //OOPPROJECT_HOTELSTATE_HPP
