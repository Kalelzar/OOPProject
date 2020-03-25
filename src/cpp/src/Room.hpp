//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_ROOM_HPP
#define OOPPROJECT_ROOM_HPP

#include "Date.hpp"
namespace Hotel {

    enum class RoomState {
        FREE,
        TAKEN,
        UNAVAILABLE,
        UNKNOWN = -1
    };

    class Room {
    private:
        int id;
        char *note;
        RoomState state;
        Date stateFrom;
        Date stateTo;

        void init(int id);
    public:
        Room();
        Room(int id);
        ~Room(){ delete [] note; }

        int getID() const { return id; }

        bool operator==(Room const& other){
            return getID() == other.getID();
        }

        void setNote(const char* note);
        char* getNote() const { return note; }

        void setState(RoomState state, Date from, Date to);
        RoomState getState() const { return state; }
        Date getStateFrom() const { return stateFrom; }
        Date getStateTo() const { return stateTo; }


    };

}
#endif //OOPPROJECT_ROOM_HPP
