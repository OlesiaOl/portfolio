#include "BotState.h"

BotState::BotState() {
    currentRoom = 0;
    food = 0;
    targetResource = IRON;

    for (int i = 0; i < RESOURCE_COUNT; i++) {
        collectedResources[i] = 0;
    }
}

void BotState::initialize(int roomCount, int startFood, ResourceType target) {
    currentRoom = 0;
    food = startFood;

    if (isValidResource(target)) {
        targetResource = target;
    }

    visited.clear();
    visited.resize(roomCount, false);

    knownRooms.clear();
    knownRooms.resize(roomCount, false);

    knownNeighbours.clear();
    knownNeighbours.resize(roomCount);

    if (roomCount > 0) {
        visited[0] = true;
        knownRooms[0] = true;
    }

    for (int i = 0; i < RESOURCE_COUNT; i++) {
        collectedResources[i] = 0;
    }
}

int BotState::getCurrentRoom() const {
    return currentRoom;
}

void BotState::setCurrentRoom(int roomNumber) {
    currentRoom = roomNumber;
}

int BotState::getFood() const {
    return food;
}

void BotState::spendFood(int amount) {
    food = food - amount;
}

bool BotState::isRoomVisited(int roomNumber) const {
    if (roomNumber < 0) {
        return false;
    }

    if (roomNumber >= static_cast<int>(visited.size())) {
        return false;
    }

    return visited[roomNumber];
}

void BotState::markRoomVisited(int roomNumber) {
    if (roomNumber < 0) {
        return;
    }

    if (roomNumber >= static_cast<int>(visited.size())) {
        return;
    }

    visited[roomNumber] = true;
}

bool BotState::isRoomKnown(int roomNumber) const {
    if (roomNumber < 0) {
        return false;
    }

    if (roomNumber >= static_cast<int>(knownRooms.size())) {
        return false;
    }

    return knownRooms[roomNumber];
}

void BotState::markRoomKnown(int roomNumber) {
    if (roomNumber < 0) {
        return;
    }

    if (roomNumber >= static_cast<int>(knownRooms.size())) {
        return;
    }

    knownRooms[roomNumber] = true;
}

void BotState::setKnownNeighbours(int roomNumber, const std::vector<int>& neighbours) {
    if (roomNumber < 0) {
        return;
    }

    if (roomNumber >= static_cast<int>(knownNeighbours.size())) {
        return;
    }

    knownNeighbours[roomNumber] = neighbours;
}

const std::vector<int>& BotState::getKnownNeighbours (int roomNumber) const {
    return knownNeighbours[roomNumber];
}

void BotState::addCollectedResource(ResourceType resource, int amount) {
    collectedResources[resource] = collectedResources[resource] + amount;
}

int BotState::getCollectedResourceAmount(ResourceType resource) const {
    return collectedResources[resource];
}

ResourceType BotState::getTargetResource() const {
    return targetResource;
}
