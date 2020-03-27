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
