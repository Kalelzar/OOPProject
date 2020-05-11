//
// Created by Kalelzar on 25/03/2020.
//

#include "HotelState.hpp"
#include "InvalidArgumentException.hpp"
#include "io/HTLPrettyPrinter.hpp"
#include "parser/CommandList.hpp"
#include "parser/Scanner.hpp"
#include "parser/HTLInterpreter.hpp"
#include <fstream>

void Hotel::HotelState::add(Room r){
    if(!checkOpen()) return;
    modified = true;
    rl.put(r.id, r);
}

void Hotel::HotelState::remove(Room r) {
    if(!checkOpen()) return;
    modified = true;
    if(!rl.contains(r.id)){
        std::cerr<<"Room with id "<<r.id<<" does not exist."<<std::endl;
    }else rl.remove(r.id);
}

void Hotel::HotelState::checkin(int roomid, Date start, Date end,
                                const char *note, int people) {
    if(!checkOpen()) return;
    modified = true;
    if(people == -1) {
        people = rl.get(roomid)->getOrElse(Room{0, 0}).beds;
    }else{
        int bedCount = rl.get(roomid)->getOrElse(Room{0, 0}).beds;
        if( people > bedCount ){
            std::cerr<<"Cannot fit " << people << " people in a room with "
                     << bedCount << " beds. " << std::endl;
            return;
        }
    }
    unique_ptr<Nullable<Room>> room = rl.get(roomid);
    if (room->isEmpty()) {
        throw NoValueException("Room with the provided number does not exist!");
    }
    if(room->get().checkedIn){
        std::cerr<<"Room "<<roomid<<" is already checked into."<<std::endl;
        return;
    }
    auto rse= setRoomState(RoomState::TAKEN, roomid, start, end, note, people);

    auto rroom = room->get();
    rroom.checkedIn = true;
    rroom.rse = rse;
    rl.put(roomid, rroom);
}

Hotel::HotelState::HotelState(const char *_filepath) {
    rl = {};
    tree = {};
    modified = false;
    filepath = new char[strlen(_filepath) + 1];
    strcpy(filepath, _filepath);
}

Hotel::HotelState::HotelState() {
    rl = {};
    tree = {};
    modified = false;
    filepath = new char[1];
    strcpy(filepath, "");
}

void Hotel::HotelState::free(){
    //Save a back-up of the current state

    if (isOpen() && modified) {
        int len = strlen(filepath);
        char *path = new char[len + 2];
        strcpy(path, filepath);
        path[len] = '~';
        path[len + 1] = '\0';
        saveAs(path);
        delete[] path;
    }

    delete[] filepath;
}

void Hotel::HotelState::clear(){
    rl = {};
    tree = {};
    modified = false;
    open = false;
}

Hotel::HotelState::HotelState(const Hotel::HotelState &other) {
    if (this != &other)
        copy(other);
}

Hotel::HotelState &Hotel::HotelState::operator=(const Hotel::HotelState &other) {
    if (this != &other){
        delete [] filepath;
        copy(other);
    }
    return *this;
}

Hotel::HotelState::~HotelState() {
    free();
}

void Hotel::HotelState::load() {
    if(strcmp(filepath, "") == 0){
        std::cerr<<"Open called with empty path."<<std::endl;
    }else{
        ifstream file(filepath);
        if(file.is_open()){
            clear();
            Scanner fileScanner{ScannerContext::FILE, &file,
                                CommandList::getCommandList()};
            shared_ptr<ArrayList<Token>> fileTokens = fileScanner.scan();
            if(fileScanner.error) {
                std::cerr<<"File '"<<filepath<<"' contains errors: "<<std::endl;
                fileTokens->filter([](Token const& token){
                                       return token.t == TokenType::ERROR;
                                   })
                    ->foreach([](Token const& token){
                                  std::cerr<<"Error("<<token.line<<") : " << token.lexeme << std::endl;
                              });
                setFile("");
                return;
            }
            HTLInterpreter interpreter(fileTokens);
            open = true;
            interpreter.parse(*this);
            if(interpreter.errorflag){
                std::cerr<<"File could not be opened because it contained errors. "<<std::endl;
                clear();
                setFile("");
                open = false;
            }
            modified = false;
        }else{
            clear();
            setFile("");
            open = false;
            std::cerr<<"Failed to open the file for read."<<std::endl;
        }
    }
}

void Hotel::HotelState::unavailable(int roomid, Hotel::Date from, Hotel::Date to, const char *note) {
    if(!checkOpen()) return;
    modified = true;
    setRoomState(RoomState::UNAVAILABLE, roomid, from, to, note);
}

void Hotel::HotelState::findForce(int beds, Hotel::Date from, Hotel::Date to) {
    if(!checkOpen()) return;
    if(from > to){
        Date t = to;
        to = from;
        from = t;
    }

    auto res = findBackend(beds, from, to);

    if(res->isDefined()){
        Room room = res->get();
        std::cout << "Room " << room.id << " has " << room.beds <<
            " beds and is available in the time period from " << from <<
            " to " << to << "." << std::endl;
        return;
    }

    auto range = tree.inRangeT<Hotel::Date>(from, to);

    if (range) {
        // Find all taken rooms that are not at full capacity
        auto notFull = range
            ->filter([](shared_ptr<RoomStateEvent> const &rse)
                         { return rse->state == RoomState::TAKEN; })
            ->filter([](shared_ptr<RoomStateEvent> const &rse)
                         { return   rse->extra     < rse->room.beds
                                 && rse->extra     != -1; })
            ->sort([](shared_ptr<RoomStateEvent> const &rse1,
                      shared_ptr<RoomStateEvent> const &rse2) {
                       if (rse1->room.beds == rse2->room.beds)
                           return rse1->extra < rse2->extra;
                       else return rse1->room.beds < rse2->room.beds;
                   });

        // Find all rooms not at full capacity whose occupants
        // Can be moved to a free room that can full accomodate them
        auto directMovable = notFull
            ->filter([this, from, to](shared_ptr<RoomStateEvent> const &rse){
                         return findBackend(rse->extra, from, to)->isDefined();
                     });

        if(directMovable->length() == 0){
            std::cerr<< "Cannot find a way to fit " << beds
                     << " people in a room. " << std::endl;
            return;
        }

        // Is there a directly movable room that is big enough

        auto largeEnoughDirectMovable = directMovable
            ->filter([beds](shared_ptr<RoomStateEvent> const& rse){
                         return rse->room.beds >= beds;
                     });

        if(largeEnoughDirectMovable->length() > 0){
            RoomStateEvent rse = *largeEnoughDirectMovable->get(0);
            Room r = rse.room;
            // No need to check if the result is Null since we already
            // know that all items in the list pass that check
            Room room = findBackend(rse.extra, from,to)->get();
            std::cout<< "The occupants of room " << r.id
                     << " need to be moved to room " << room.id <<"."
                     << std::endl << "Then room "
                     << r.id << " with " << r.beds
                     << " beds, will be available in the time period from "
                     << from << " to " << to << "." << std::endl;
            return;
        }

        // Is there a notFull room that is big enough?
        auto largeEnoughNotFull = notFull
            ->filter([beds](shared_ptr<RoomStateEvent> const& rse){
                         return rse->room.beds >= beds;
                     });

        // Is there a largeEnoughNotFull room whose occupants
        // can be moved to a directMovableRoom
        for(unsigned i = 0; i < largeEnoughNotFull->length(); i++){
            auto nfrse = *largeEnoughNotFull->get(i);
            int people = nfrse.extra;
            auto directMovableLargeEnoughForNotFull =
                directMovable
                ->filter([people](shared_ptr<RoomStateEvent> const& rse){
                             return rse->room.beds >= people;
                         });
            if(directMovableLargeEnoughForNotFull->length() > 0){
                RoomStateEvent rse = *directMovableLargeEnoughForNotFull->get(0);
                Room r = rse.room;
                // No need to check if the result is Null since we already
                // know that all items in the list pass that check
                Room room = findBackend(rse.extra, from,to)->get();
                std::cout<< "The occupants of room " << r.id
                         << " need to be moved to room " << room.id <<"."
                         << std::endl << "Then the occupants of room "
                         << nfrse.room.id
                         << " need to be moved to room " << r.id
                         << "." << std::endl
                         << "Then room "
                         << nfrse.room.id << " with " << nfrse.room.beds
                         << " beds, will be available in the time period from "
                         << from << " to " << to << "." << std::endl;
                return;
            }
        }

    }

    std::cerr<< "Cannot find a way to fit " << beds
             << " people in a room. " << std::endl;

}

unique_ptr<ArrayList<Hotel::Room>> Hotel::HotelState::roomsAvailableFrom(Date from, Date to) const {
    if(from > to){
        Date t = to;
        to = from;
        from = t;
    }
    unique_ptr<ArrayList<shared_ptr<RoomStateEvent>>> range = tree.inRangeT<Hotel::Date>(from, to);

    if (range) {

        unique_ptr<ArrayList<shared_ptr<RoomStateEvent>>> filtered = range->filter(
            [](shared_ptr<RoomStateEvent> const &rse) { return rse->state != RoomState::FREE; });

        unique_ptr<ArrayList<Room>> rse = filtered
            ->map<Room>([](shared_ptr<RoomStateEvent> const &rse) { return rse->room; });


        unique_ptr<ArrayList<Room>> freeRooms = rse->difference(*rl.values());
        return freeRooms;

    } else {
        return rl.values();
    }
}


unique_ptr<Nullable<Hotel::Room>>
Hotel::HotelState::findBackend(int beds, Hotel::Date from,
                               Hotel::Date to) const {

    unique_ptr<ArrayList<Room>> list = roomsAvailableFrom(from, to)
        ->filter([beds](Room const &r) { return r.beds >= beds; });

    if (list->length() == 0) {
        return make_unique<Null<Room>>();
    } else {
        unique_ptr<ArrayList<Room>> slist =
            list->sort([](Room r1, Room r2) {
                           return r1.beds < r2.beds;
                       });

        Room room = slist->get(0);
        return make_unique<NotNull<Room>>(room);
    }
}

bool Hotel::HotelState::find(int beds, Hotel::Date from, Hotel::Date to) const {
    if(!checkOpen()) return false;
    if(from > to){
        Date t = to;
        to = from;
        from = t;
    }

    auto res = findBackend(beds, from, to);

    if (res->isEmpty()) {
        std::cout << "No suitable rooms found in the given time period." << std::endl;
        return false;
    } else {
        Room room = res->get();
        std::cout << "Room " << room.id << " has " << room.beds <<
            " beds and is available in the time period from " << from <<
            " to " << to << "." << std::endl;
        return true;
    }

}

void reportPrint(shared_ptr<Hotel::RoomStateEvent> const &_rse) {
    auto rse = *_rse;
    int delta = rse.from.daysBetween(rse.to);
    std::cout << "  Room " << rse.room.id;
    switch (rse.state){
    case Hotel::RoomState::TAKEN:
        std::cout<<" is taken";
        break;
    case Hotel::RoomState::WAS_TAKEN:
        std::cout<<" was taken";
        break;
    case Hotel::RoomState::UNAVAILABLE:
        std::cout<<" is unavailable";
        break;
    case Hotel::RoomState::FREE:
    case Hotel::RoomState::UNKNOWN:
    default:
        std::cout<<" is an error ";
        break;
    }
    if (delta == 1) {
        std::cout << " on " << rse.from << " for a single day";
    } else {
        std::cout << " from " << rse.from << " to " << rse.to
                  << " for a total of "
                  << delta << " days";
        if(rse.extra != -1){
            std::cout<<" by " << rse.extra << " people out of "
                     << rse.room.beds << " beds";
        }
    }

    std::cout << ". (" << rse.getNote() << ")" << std::endl;
}

void Hotel::HotelState::report(Hotel::Date from, Hotel::Date to) {
    if(!checkOpen()) return;
    if(from > to){
        Date t = to;
        to = from;
        from = t;
    }
    unique_ptr<ArrayList<shared_ptr<RoomStateEvent>>> range = tree.inRangeT<Hotel::Date>(from, to);

    if (range) {

        unique_ptr<ArrayList<shared_ptr<RoomStateEvent>>> filtered = range
            ->filter([this](shared_ptr<RoomStateEvent> const &rse) { return rse->state != RoomState::FREE && rl.contains(rse->room.id); })
            ->sort([](shared_ptr<RoomStateEvent> const &rse1, shared_ptr<RoomStateEvent> const &rse2) {
                    if (rse1->from == rse2->from) return rse1->room.id < rse2->room.id;
                    else return rse1->from < rse2->from;
                });

        if (filtered->length() == 0) {
            std::cout << "No rooms are in use for the time period from " << from << " to " << to << "."<<std::endl;
            return;
        }

        std::cout << "The following room" << (filtered->length() == 1 ? " is" : "s are")
                  << " in use from " << from << " to " << to << "." << std::endl;

        filtered->foreach(reportPrint);

    } else {
        std::cout << "No rooms are in use for the time period from " << from << " to " << to << "."<<std::endl;
    }
}

void Hotel::HotelState::checkout(int roomid) {
    if(!checkOpen()) return;
    modified = true;

    unique_ptr<Nullable<Room>> room = rl.get(roomid);
    if (room->isEmpty()) {
        throw NoValueException("Room with the provided number does not exist!");
    }

    if(!room->get().checkedIn){
        std::cerr<<"Room "<<roomid<<" is not checked into."<<std::endl;
        return;
    }


    auto rroom = room->get();
    auto rse = rroom.rse;
    rse->state = RoomState::WAS_TAKEN;
    rroom.checkedIn = false;
    rroom.rse = nullptr;
    rl.put(roomid, rroom);
}

void Hotel::HotelState::close(){
    if(!checkOpen()) return;
    free();
    filepath = new char[1];
    filepath[0]='\0';
    open = false;
}

void Hotel::HotelState::available(Hotel::Date date) const {
    if(!checkOpen()) return;
    unique_ptr<ArrayList<Room>> list = roomsAvailableFrom(date, date)
            ->sort([](Room const &r1, Room const &r2) { return r1.id < r2.id; });
    if (list->length() > 0) {
        std::cout << "The following room" << (list->length() == 1 ? " is" : "s are")
                  << " available on " << date << "." << std::endl;
        list->foreach([](Room const &room) { std::cout << "  Room " << room.id << std::endl; });
    } else {
        std::cout << "There are no free rooms on " << date << "." << std::endl;
    }
}

void Hotel::HotelState::saveAs(const char *path) {
    if(!checkOpen()) return;
    std::cout<<"Saving to "<<path<<std::endl;
    std::cout<<".";
    ofstream file(path);
    std::cout<<".";
    if(file.is_open()){
        Hotel::HTLPrettyPrinter::printRooms(rl.values(), &file);
        std::cout<<".";
        Hotel::HTLPrettyPrinter::printState(tree
                                         .getHead()
                                         ->collect()
                                         ->asList()
                                            ->map<ArrayList<shared_ptr<RoomStateEvent>>>(
                                                [](BinaryNode<DateRange,
                                                   shared_ptr<RoomStateEvent>>*node ){
                                                 return node->value;
                                             })
                                            ->flatten<shared_ptr<RoomStateEvent>>()
                                         , &file);
        std::cout<<".";
        file.close();
        std::cout<<std::endl;
        std::cout<<"File saved sucessfully"<<std::endl;
        modified=false;
        setFile(path);
    }else{
        std::cout<<std::endl;
        std::cout<<"Failed to open file for write."<<std::endl;
    }
}

void Hotel::HotelState::save(){
    if(!checkOpen()) return;
    if(!modified) {
        std::cout<<"No changes need to be saved."<<std::endl;
        return;
    }
    saveAs(filepath);
}

void Hotel::HotelState::setFile(const char* path){
    if(filepath == path) return;
    if(filepath) delete [] filepath;
    filepath = new char[strlen(path)+1];
    strcpy(filepath, path);
}

const char* Hotel::HotelState::getFile() const {
    return filepath;
}

void Hotel::HotelState::copy(const Hotel::HotelState &other) {
    rl = other.rl;
    tree = other.tree;
    filepath = new char[strlen(other.getFile())+1];
    strcpy(filepath, other.getFile());
    modified = other.modified;
}

shared_ptr<Hotel::RoomStateEvent> Hotel::HotelState::setRoomState(Hotel::RoomState state, int roomid,
                                     Hotel::Date start, Hotel::Date end,
                                     const char *note, int extra) {
    if(start > end){
        Date t = end;
        end = start;
        start = t;
    }
    unique_ptr<Nullable<Room>> room = rl.get(roomid);
    if (room->isEmpty()) {
        throw NoValueException("Room with the provided number does not exist!");
    }

    unique_ptr<ArrayList<shared_ptr<RoomStateEvent>>> events = tree.inRangeT<Hotel::Date>(start, end);
    bool cannotCheckIn = events && events
            ->filter([](shared_ptr<RoomStateEvent> const &rse) { return rse->state != RoomState::FREE; })
            ->map<Room>([](shared_ptr<RoomStateEvent> const &rse) { return rse->room; })
            ->contains(room->get());

    if (cannotCheckIn) {
        throw InvalidArgumentException("Room with the provided number is taken or unavailable.");
    }

    auto rse = make_shared<RoomStateEvent>(state, room->get(), start,
                                           end, note, extra);
    tree.populate({start, end}, rse);
    return rse;
}
