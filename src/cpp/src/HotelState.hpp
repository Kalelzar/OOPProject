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
        RangeBinaryTree<DateRange, shared_ptr<RoomStateEvent>> tree{};
        char *filepath;
        bool modified;

        bool open = false;
        void copy(HotelState const &state);

        shared_ptr<Hotel::RoomStateEvent> setRoomState(RoomState state, int roomid,
                          Hotel::Date from, Hotel::Date to,
                          const char *note, int extra = -1);

        unique_ptr<ArrayList<shared_ptr<RoomStateEvent>>> roomEventsCovering(Date d) const;

        unique_ptr<ArrayList<Room>> roomsAvailableFrom(Date from, Date to) const;

        unique_ptr<Nullable<Hotel::Room>> findBackend(int beds, Date from,
                                                      Date to) const;

        void free();

    public:

        bool isOpen() const {
            return open;
        }

        bool checkOpen() const {
            if(isOpen()) return true;
            std::cerr<<"You must open a file first!"<<std::endl;
            return false;
        }

        HotelState(const char *filepath);

        HotelState();

        HotelState(HotelState const &state);

        HotelState &operator=(HotelState const &other);

        ~HotelState();

        void clear();

        void setFile(const char* path);
        const char* getFile() const;

        void load();

        void close();

        void save();

        void saveAs(const char *path);

        void add(Room r);

        void remove(Room r);

        void checkin(int roomid, Date start, Date end, const char *note, int people);

        void available() const { available(Date::today()); }

        void available(Date date) const;

        void checkout(int roomid);

        void report(Date from, Date to);

        bool find(int beds, Date from, Date to) const;

        void findForce(int beds, Date from, Date to);

        void unavailable(int roomid, Date from, Date to, const char *note);

    };
}

#endif //OOPPROJECT_HOTELSTATE_HPP
