#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>

#include "Room.h"

class Dungeon {
private:
    std::vector<Room> rooms;
public:
    Dungeon();

    void resize(int roomCount);
    int getRoomCount() const;

    Room& getRoom(int roomNumber);
    const Room& getRoom(int roomNumber) const;

    bool isValidRoom(int roomNumber) const;
};

#endif //DUNGEON_H
