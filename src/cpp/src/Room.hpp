//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_ROOM_HPP
#define OOPPROJECT_ROOM_HPP

#include "Date.hpp"

namespace Hotel {

    /**
     * Describes the state a room is in.
     * A room is either free, taken or unavailable.
     * Only a free room can be checked-into.
     * Only a taken room can be checked-out of.
     * Only a free room may be marked unavailable.
     * If state is unknown then something went horribly wrong.
     */
    enum class RoomState {
        FREE,
        TAKEN,
        UNAVAILABLE,
        UNKNOWN = -1
    };

    /**
     * TODO: Refactor this class to store all assigned state rather than the most recent one
     * A room described by a number.
     * It also has a specific amount of beds.
     * And a state as well as a range for how long the state applies.
     * Free state can be indefinite unless there is a different state scheduled in the future.
     * States can also have a note attached to them.
     */
    struct Room {
        int id{};
        int beds{};

        Room(int _id, int _beds){
            id = _id;
            beds = _beds;
        }

        Room(){
            id = -1;
            beds = 0;
        }

        /**
         * Checks if the provided room is the same as this one.
         * Rooms with the same number are treated as if they were the same
         * regardless of the rest of their state.
         * @param other the other room
         * @return is the other room the same as this one
         */
        bool operator==(Room const &other) const {
            return id == other.id;
        }

        bool operator!=(Room const &other) const {
            return !(*this == other);
        }

    };

    class RoomStateEvent {
    private:
        char *note{};
        bool noteFreed = true;

        /**
         * Frees the memory associated with the note
         */
        void freeNote() {
            if (!noteFreed) {
                noteFreed = true;
                delete[] note;
            }
        }

        /**
         * Safely copies a different room state event to this one
         * @param other the room state event to copy
         */
        void copy(RoomStateEvent const& other);

        void init(RoomState const& _state,
                  Room const& _room,
                  Date const& _from,
                  Date const& _to,
                  const char* _note);

    public:


        RoomState state;
        Room room;
        Date from;
        Date to;

        RoomStateEvent();

        RoomStateEvent(RoomState const& _state,
                       Room const& _room,
                       Date const& _from,
                       Date const& _to);

        RoomStateEvent(RoomState const& _state,
                       Room const& _room,
                       Date const& _from,
                       Date const& _to,
                       const char* _note);


        RoomStateEvent(RoomStateEvent const &other);

        RoomStateEvent &operator=(RoomStateEvent const &other);

        ~RoomStateEvent() {
            freeNote();
        }

        /**
         * Set the note attached to this room state event
         * @param note the note
         */
        void setNote(const char *note);

        /**
         * The note attached to this room state event
         * @return the note
         */
        char *getNote() const { return note; }


        bool operator==(RoomStateEvent const& other) const;
        bool operator!=(RoomStateEvent const& other) const;
        bool operator>(RoomStateEvent const& other) const;
        bool operator>=(RoomStateEvent const& other) const;
        bool operator<(RoomStateEvent const& other) const;
        bool operator<=(RoomStateEvent const& other) const;

    };

}
#endif //OOPPROJECT_ROOM_HPP
