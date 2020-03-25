//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_HOTELSTATE_HPP
#define OOPPROJECT_HOTELSTATE_HPP

#include "Date.hpp"
#include "Room.hpp"
#include "RoomList.hpp"

namespace Hotel {
    class HotelState {
    private:
        RoomList rl;
        char *filepath;
        bool modified;
    public:

        void load();

        void save();

        void saveAs(const char *path);

        void add(Room r);

        void remove(Room r);

        void checkin(int roomid, Date start, Date end, const char* note);

        void available(){ available(Date::today()); }

        void available(Date date);

        void checkout(int roomid);

        void report(Date from, Date to);

        void find(int beds, Date from, Date to);

        void findForce(int beds, Date from, Date to);

        void unavailable(int roomid, Date from, Date to, const char* note);

    };
}

#endif //OOPPROJECT_HOTELSTATE_HPP
