#ifndef OOPPROJECT_HTLPRETTYPRINTER_HPP
#define OOPPROJECT_HTLPRETTYPRINTER_HPP

#include "../Room.hpp"
#include "../RoomStateEvent.hpp"
#include "../collection/ArrayList.hpp"

namespace Hotel {
class HTLPrettyPrinter {

private:
public:
  static void printRooms(std::unique_ptr<ArrayList<Room>> const &rooms,
                         std::ostream *to);

  static void printState(
      std::unique_ptr<ArrayList<std::shared_ptr<RoomStateEvent>>> const &rooms,
      std::ostream *to);
};
} // namespace Hotel
#endif // OOPPROJECT_HTLPRETTYPRINTER_HPP
