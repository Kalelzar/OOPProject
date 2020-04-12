#ifndef OOPPROJECT_HTLPRETTYPRINTER_HPP
#define OOPPROJECT_HTLPRETTYPRINTER_HPP

#include "../collection/ArrayList.hpp"
#include "../Room.hpp"
#include "../RoomStateEvent.hpp"

namespace Hotel {
    class HTLPrettyPrinter {

    private:

    public:

        static void printRooms(unique_ptr<ArrayList<Room>> const& rooms, std::ostream* to){
            if(rooms->length()==0) return;
            unique_ptr<ArrayList<Room>> sorted = rooms
                ->sort([](Room r1, Room r2){return r1.id < r2.id;});
            int ind = 0;
            int startid = sorted->get(0).id;
            int cbeds  = sorted->get(0).beds;
            int curid = startid;
            do {
                int nid = sorted->get(ind).id;
                int beds = sorted->get(ind).beds;

                ind++;
                if(abs(curid-nid) <= 1 && beds == cbeds){

                    curid=nid;
                }else{

                    if(startid == curid) {
                        *to<<"add "<<curid<<" "<<cbeds<<std::endl;
                    }else{
                        *to<<"add "<<startid<<"-"<<curid<<" "<<cbeds<<std::endl;
                    }
                    cbeds = beds;
                    startid = nid;
                    curid = nid;
                }
                if(ind >= sorted->length()){

                    if(startid == curid) {
                        *to<<"add "<<curid<<" "<<cbeds<<std::endl;
                    }else{
                        *to<<"add "<<startid<<"-"<<curid<<" "<<cbeds<<std::endl;
                    }
                }
            }while(ind < sorted->length());
        }

       static void printState(unique_ptr<ArrayList<RoomStateEvent>> const& rooms, std::ostream* to){
            if(rooms->length()==0) return;
            unique_ptr<ArrayList<RoomStateEvent>> sorted = rooms
                ->sort([](RoomStateEvent const& r1, RoomStateEvent const& r2){return r1.to < r2.from;});
            sorted
                ->foreach([to](RoomStateEvent const& rse) mutable {
                              *to<<rse;
                          });
       }
    };
}
#endif //OOPPROJECT_HTLPRETTYPRINTER_HPP
