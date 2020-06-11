//
// Created by Kalelzar on 25/03/2020.
//
#include "Room.hpp"

namespace Hotel {
Room::Room(int _id, int _beds) {
  id = _id;
  beds = _beds;
  checkedIn = false;
}

Room::Room() {
  id = -1;
  beds = 0;
  checkedIn = false;
}
} // namespace Hotel
