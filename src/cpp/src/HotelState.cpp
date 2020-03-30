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
    modified = false;
    filepath = new char[strlen(_filepath) + 1];
    strcpy(filepath, _filepath);
}

Hotel::HotelState::HotelState() {
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

void Hotel::HotelState::find(int beds, Hotel::Date from, Hotel::Date to) const {

}

void Hotel::HotelState::report(Hotel::Date from, Hotel::Date to) {

}

void Hotel::HotelState::checkout(int roomid) {

}

void Hotel::HotelState::available(Hotel::Date date) const {

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

    bool cannotCheckIn =  tree.inRange(start, end)
            ->filter([](RoomStateEvent const& rse){return rse.state != RoomState::FREE;})
            ->map<Room>([](RoomStateEvent const& rse){return rse.room;})
            ->contains(room->get());

    if(cannotCheckIn){
        throw InvalidArgumentException("Room with the provided number, is taken or unavailable.");
    }

    tree.populateWithRange(start, end,
                           {state, room->get(), start, end, note});
}
