//
// Created by Kalelzar on 25/03/2020.
//

#include "RoomList.hpp"

Hotel::RoomList::RoomList() {
    create(getDefaultReservedSpace());
}

void Hotel::RoomList::create(unsigned reserve) {
    rooms = new Room[reserve];
    reserved = reserve;
    elemCount = 0;
}

void Hotel::RoomList::free() {
    delete [] rooms;
}

Hotel::RoomList::RoomList(unsigned reserved) {
    create(reserved);
}

Hotel::RoomList::RoomList(const Hotel::RoomList &other) {
    if(&other != this)
        copy(other);
}

void Hotel::RoomList::copy(const Hotel::RoomList &other) {
    delete [] rooms;
    rooms = new Room[other.capacity()];
    reserved = other.capacity();
    elemCount = 0;
    addAll(other);
}

Hotel::RoomList &Hotel::RoomList::operator=(const Hotel::RoomList &other) {
    if (&other != this)
        copy(other);
    return *this;
}

void Hotel::RoomList::expand() {
    unsigned newCapacity = capacity()*2;
    Room* newRooms = new Room[newCapacity];

    for(int i = 0; i < length(); i++){
        newRooms[i] = get(i);
    }

    delete [] rooms;
    rooms = newRooms;
}

void Hotel::RoomList::add(Hotel::Room room) {
    if(elemCount + 1 >= capacity()){
        expand();
    }
    rooms[elemCount] = room;
    elemCount++;
}

void Hotel::RoomList::addAll(const Hotel::RoomList &rl) {
    for(int i = 0; i < rl.length(); i++){
        add(rl.get(i));
    }
}

Hotel::Room Hotel::RoomList::get(unsigned index) const {
    if(index >= length()) return rooms[length() - 1];
    return rooms[index];
}
