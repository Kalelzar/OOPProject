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
    class Room {
    private:
        int id{};
        int beds{};
        char *note{};
        RoomState state;
        Date stateFrom;
        Date stateTo;
        bool noteFreed = true;

        /**
         * Safely copies a different room to this one
         * @param other the room to copy
         */
        void copy(Room const &other);

        /**
         * Initializes the room with an id and bed count
         * @param _id the room number
         * @param _beds the bed count
         */
        void init(int _id, int _beds);

        /**
         * Frees the memory associated with the note
         */
        void freeNote() {
            if (!noteFreed) {
                noteFreed = true;
                delete[] note;
            }
        }

    public:

        /**
         * Initializes a room with number 0 and no beds.
         * Such a room is considered invalid hence needs to be marked unavailable
         */
        Room();

        /**
         * Initializes a room with a number and a specified amount of beds.
         * The default state is FREE unless beds are 0 in which case it is UNAVAILABLE
         * @param _id
         * @param _beds
         */
        Room(int _id, int _beds);

        ~Room() {
            freeNote();
        }

        Room(Room const &other);

        Room &operator=(Room const &other);

        /**
         * Returns the room number associated with this room.
         * That number should be unique to this room
         * @return the room number
         */
        int getID() const { return id; }
        /**
         * Returns the amount of beds in this room
         * @return the bed count
         */
        int getBeds() const { return beds; }

        /**
         * Checks if the provided room is the same as this one.
         * Rooms with the same number are treated as if they were the same
         * regardless of the rest of their state.
         * @param other the other room
         * @return is the other room the same as this one
         */
        bool operator==(Room const &other) const {
            return getID() == other.getID();
        }

        bool operator!=(Room const &other) const {
            return !(*this == other);
        }

        /**
         * Set the note attached to this room's state
         * @param note the note
         */
        void setNote(const char *note);

        /**
         * The note attached to this room
         * @return the note
         */
        char *getNote() const { return note; }

        /**
         * Sets the state of this room in the range provided
         * @param state the state
         * @param from when the state begins
         * @param to when the state ends
         */
        void setState(RoomState state, Date from, Date to);

        RoomState getState() const { return state; }

        Date getStateFrom() const { return stateFrom; }

        Date getStateTo() const { return stateTo; }
    };

}
#endif //OOPPROJECT_ROOM_HPP
