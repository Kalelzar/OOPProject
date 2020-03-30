//
// Created by Kalelzar on 25/03/2020.
//

#include "HotelState.hpp"


void Hotel::HotelState::add(Room r){
    rl.append(r);
}

void Hotel::HotelState::remove(Room r){
    rl.remove(r);
}

void Hotel::HotelState::checkin(int roomid, Date start, Date end, const char *note){
    //tree.populate(start)
}
