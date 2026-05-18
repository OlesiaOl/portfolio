#include "Dungeon.h"

Dungeon::Dungeon() {}

void Dungeon::resize(int roomCount) {
    rooms.clear();

    if (roomCount <= 0) {
        return;
    }

    rooms.resize(roomCount);
    
    for (int i = 0; i < roomCount; i++) {
        rooms[i].setNumber(i);
    }
}

int Dungeon::getRoomCount() const {
    return static_cast<int>(rooms.size());
}

Room& Dungeon::getRoom(int roomNumber) {
    return rooms[roomNumber];
}

const Room& Dungeon::getRoom(int roomNumber) const {
    return rooms[roomNumber];
}

bool Dungeon::isValidRoom(int roomNumber) const {
    if (roomNumber < 0 ) {
        return false;
    }

    if (roomNumber >= getRoomCount()) {
        return false;
    }

    return true;
}
