//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_HOTELSTATE_HPP
#define OOPPROJECT_HOTELSTATE_HPP

#include "DateRange.hpp"
#include "Date.hpp"
#include "Room.hpp"
#include "collection/HashMap.hpp"
#include "collection/RangeBinaryTree.hpp"
#include "RoomStateEvent.hpp"

namespace Hotel {
    class HotelState {
    private:
        HashMap<int, Room> rl{};
        RangeBinaryTree<DateRange, RoomStateEvent> tree{};
        char *filepath;
        bool modified;

        void copy(HotelState const &state);

        void setRoomState(RoomState state, int roomid,
                          Hotel::Date from, Hotel::Date to, const char *note);

        unique_ptr<ArrayList<RoomStateEvent>> roomEventsCovering(Date d) const;

        unique_ptr<ArrayList<Room>> roomsAvailableFrom(Date from, Date to) const;

    public:

        explicit HotelState(const char *filepath);

        HotelState();

        HotelState(HotelState const &state);

        HotelState &operator=(HotelState const &other);

        ~HotelState();

        void load();

        void save() const;

        void saveAs(const char *path) const;

        void add(Room r);

        void remove(Room r);

        void checkin(int roomid, Date start, Date end, const char *note);

        void available() const { available(Date::today()); }

        void available(Date date) const;

        void checkout(int roomid);

        void report(Date from, Date to);

        void find(int beds, Date from, Date to) const;

        void findForce(int beds, Date from, Date to);

        void unavailable(int roomid, Date from, Date to, const char *note);

    };
}

#endif //OOPPROJECT_HOTELSTATE_HPP
