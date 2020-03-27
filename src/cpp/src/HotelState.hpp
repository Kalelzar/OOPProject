//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_HOTELSTATE_HPP
#define OOPPROJECT_HOTELSTATE_HPP

#include "Date.hpp"
#include "Room.hpp"
#include "ArrayList.hpp"
#include "ArraySet.hpp"
#include "LinkedList.hpp"

namespace Hotel {
    class HotelState {
    private:
        ArrayList<Room> rl{};
        char *filepath;
        bool modified;
        void copy(HotelState const& state);
    public:

        HotelState(const char* filepath);
        HotelState();
        HotelState(HotelState const& state);

        HotelState& operator=(HotelState const& other);

        ~HotelState();

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
