//
// Created by Kalelzar on 25/03/2020.
//

#include "HotelState.hpp"
#include "InvalidArgumentException.hpp"


void Hotel::HotelState::add(Room r) {
    rl.put(r.id, r);
}

void Hotel::HotelState::remove(Room r) {
    rl.remove(r.id);
}

void Hotel::HotelState::checkin(int roomid, Date start, Date end, const char *note) {
    setRoomState(RoomState::TAKEN, roomid, start, end, note);
}

Hotel::HotelState::HotelState(const char *_filepath) {
    rl = {};
    tree = {};
    modified = false;
    filepath = new char[strlen(_filepath) + 1];
    strcpy(filepath, _filepath);
}

Hotel::HotelState::HotelState() {
    rl = {};
    tree = {};
    modified = false;
    filepath = new char[1];
    strcpy(filepath, "");
}

Hotel::HotelState::HotelState(const Hotel::HotelState &other) {
    if(this != &other)
        copy(other);
}

Hotel::HotelState &Hotel::HotelState::operator=(const Hotel::HotelState &other){
    if(this != &other)
      copy(other);
    return *this;
}

Hotel::HotelState::~HotelState() {

    //Save a back-up of the current state
    if(modified) {
        int len = strlen(filepath);
        char* path = new char[len+2];
        strcpy(path, filepath);
        path[len-2]='~';
        path[len-1]='\0';
        saveAs(path);
        delete [] path;
    }

    delete [] filepath;
}

void Hotel::HotelState::load() {

}

void Hotel::HotelState::unavailable(int roomid, Hotel::Date from, Hotel::Date to, const char *note) {
    setRoomState(RoomState::UNAVAILABLE, roomid, from, to, note);
}

void Hotel::HotelState::findForce(int beds, Hotel::Date from, Hotel::Date to) {

}

unique_ptr<ArrayList<Hotel::Room>> Hotel::HotelState::roomsAvailableFrom(Date from, Date to) const {
    unique_ptr<ArrayList<RoomStateEvent>> range = tree.inRangeT<Hotel::Date>(from, to);

    if(range){

        unique_ptr<ArrayList<RoomStateEvent>> filtered = range->filter([](RoomStateEvent const& rse){return rse.state!=RoomState::FREE;});

        unique_ptr<ArrayList<Room>> rse = filtered
            ->map<Room>([](RoomStateEvent const& rse){return rse.room;});

        unique_ptr<ArrayList<Room>> freeRooms = rse->difference(*rl.values());
        return freeRooms;

    }else{
        return rl.values();
    }
}

void Hotel::HotelState::find(int beds, Hotel::Date from, Hotel::Date to) const {

    unique_ptr<ArrayList<Room>> list = roomsAvailableFrom(from, to)
        ->filter([beds](Room const& r){return r.beds >= beds;});

    if(list->length() == 0){
        std::cout<<"No suitable rooms found in the given time period."<<std::endl;
    }else{
        unique_ptr<ArrayList<Room>> slist =
            list->sort([](Room r1, Room r2){
                           return r1.beds < r2.beds;
                       });

        Room room = slist->get(0);
        std::cout<<"Room "<<room.id<<" has "<<room.beds<<
            " beds and is available in the time period from "<<from<<
            " to "<<to<<"."<<std::endl;
    }
}

void reportPrint(Hotel::RoomStateEvent const& rse){
    int delta = rse.from.daysBetween(rse.to);
    std::cout<<"  Room "<<rse.room.id<<" is "
             << (rse.state == Hotel::RoomState::TAKEN ? "taken" : "unavailable");
    if(delta == 1){
        std::cout<<" on "<<rse.from<<" for a single day";
    }else{
        std::cout<< " from " << rse.from << " to " << rse.to
                 << " for a total of "
                 << delta << " days";
    }

    std::cout<<". ("<<rse.getNote()<<")"<< std::endl;
}

void Hotel::HotelState::report(Hotel::Date from, Hotel::Date to) {
    unique_ptr<ArrayList<RoomStateEvent>> range = tree.inRangeT<Hotel::Date>(from, to);

    if(range){

        unique_ptr<ArrayList<RoomStateEvent>> filtered = range
            ->filter([](RoomStateEvent const& rse){return rse.state!=RoomState::FREE;})
            ->sort([](RoomStateEvent const& rse1, RoomStateEvent const& rse2){
                       if(rse1.room.id != rse2.room.id) return rse1.room.id < rse2.room.id;
                       else return rse1.from < rse2.from;
                   });

        if(filtered->length() == 0){
            std::cout<<"No rooms are in use for the time period from "<<from<<" to "<<to<<".";
            return;
        }

        std::cout<<"The following room"<<(filtered->length()==1 ? " is" : "s are")
                 <<" in use from " << from << " to " << to << "." <<std::endl;

        filtered->foreach(reportPrint);

    }else{
        std::cout<<"No rooms are in use for the time period from "<<from<<" to "<<to<<".";
    }
}

void Hotel::HotelState::checkout(int roomid){

}



void Hotel::HotelState::available(Hotel::Date date) const {
    unique_ptr<ArrayList<Room>> list = roomsAvailableFrom(date, date)
        ->sort([](Room const& r1, Room const& r2){return r1.id<r2.id;});
    if(list->length() > 0){
        std::cout<<"The following room"<<(list->length()==1 ? " is" : "s are")
                 <<" available on " << date << "." <<std::endl;
        list->foreach([](Room const& room){std::cout<<"  Room "<<room.id<<std::endl;});
    }else{
        std::cout<<"There are no free rooms on "<<date<<"."<<std::endl;
    }
}

void Hotel::HotelState::saveAs(const char *path) const {

}

void Hotel::HotelState::save() const {

}

void Hotel::HotelState::copy(const Hotel::HotelState &state) {

}

void Hotel::HotelState::setRoomState(Hotel::RoomState state, int roomid,
        Hotel::Date start, Hotel::Date end,
                                     const char *note) {
    unique_ptr<Nullable<Room>> room = rl.get(roomid);
    if(room->isEmpty()){
        throw NoValueException("Room with the provided number, does not exist!");
    }

    unique_ptr<ArrayList<RoomStateEvent>> events = tree.inRangeT<Hotel::Date>(start, end);
    bool cannotCheckIn = events && events
            ->filter([](RoomStateEvent const& rse){return rse.state != RoomState::FREE;})
            ->map<Room>([](RoomStateEvent const& rse){return rse.room;})
            ->contains(room->get());

    if(cannotCheckIn){
        throw InvalidArgumentException("Room with the provided number, is taken or unavailable.");
    }

    tree.populate({start, end},
                           {state, room->get(), start, end, note});
}
