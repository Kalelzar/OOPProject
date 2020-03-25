//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_ROOMLIST_HPP
#define OOPPROJECT_ROOMLIST_HPP

#include "Room.hpp"

namespace Hotel {

    class RoomList {
    private:
        static const unsigned DEFAULT_RESERVED_SPACE = 16;
        Room *rooms;
        unsigned reserved;
        unsigned elemCount;

        void expand();

        void free();

        void create(unsigned reserve);

        void copy(RoomList const &other);

    public:
        RoomList();

        RoomList(unsigned reserved);

        RoomList(RoomList const &other);

        RoomList &operator=(RoomList const &other);

        ~RoomList() {
            free();
        }

        void add(Room const &room);

        void addAll(RoomList const &rl);

        void remove(Room room);

        Room get(unsigned index) const;

        unsigned length() const { return elemCount; }

        unsigned capacity() const { return reserved; }

        static unsigned getDefaultReservedSpace() { return DEFAULT_RESERVED_SPACE; };
    };

}


#endif //OOPPROJECT_ROOMLIST_HPP
