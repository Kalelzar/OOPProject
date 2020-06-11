#include "HTLPrettyPrinter.hpp"

namespace Hotel {
void HTLPrettyPrinter::printRooms(const std::unique_ptr<ArrayList<Room>> &rooms,
                                  std::ostream *to) {
  if (rooms->length() == 0)
    return;
  std::unique_ptr<ArrayList<Room>> sorted =
      rooms->sort([](Room r1, Room r2) { return r1.id < r2.id; });
  int ind = 0;
  int startid = sorted->get(0).id;
  int cbeds = sorted->get(0).beds;
  int curid = startid;
  do {
    int nid = sorted->get(ind).id;
    int beds = sorted->get(ind).beds;

    ind++;
    if (abs(curid - nid) <= 1 && beds == cbeds) {

      curid = nid;
    } else {

      if (startid == curid) {
        *to << "add " << curid << " " << cbeds << std::endl;
      } else {
        *to << "add " << startid << "-" << curid << " " << cbeds << std::endl;
      }
      cbeds = beds;
      startid = nid;
      curid = nid;
    }
    if (ind >= sorted->length()) {

      if (startid == curid) {
        *to << "add " << curid << " " << cbeds << std::endl;
      } else {
        *to << "add " << startid << "-" << curid << " " << cbeds << std::endl;
      }
    }
  } while (ind < sorted->length());
}

void HTLPrettyPrinter::printState(
    const std::unique_ptr<ArrayList<std::shared_ptr<RoomStateEvent>>> &rooms,
    std::ostream *to) {
  if (rooms->length() == 0)
    return;
  std::unique_ptr<ArrayList<std::shared_ptr<RoomStateEvent>>> sorted =
      rooms->sort([](std::shared_ptr<RoomStateEvent> const &r1,
                     std::shared_ptr<RoomStateEvent> const &r2) {
        return r1->to < r2->from;
      });
  sorted->foreach ([to](std::shared_ptr<RoomStateEvent> const &rse) mutable {
    *to << *rse;
  });
}
} // namespace Hotel
