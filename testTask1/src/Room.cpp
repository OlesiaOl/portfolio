#include "Room.h"

Room::Room() {
    number = 0;
    hasCollectedAnyResource = false;

    for (int i = 0; i < RESOURCE_COUNT; i++) {
        resources[i] = 0;
        collected[i] = false;
    }
}

int Room::getNumber() const {
    return number;
}

void Room::setNumber(int roomNumber) {
    number = roomNumber;
}

void Room::addNeighbour(int neighbour) {
    neighbors.push_back(neighbour);
}

const std::vector<int>& Room::getNeighbours() const {
    return neighbors;
}

void Room::setResourceAmount(ResourceType resource, int amount) {
    if (!isValidResource(resource)) {
        return;
    }

    resources[resource] = amount;
}

int Room::getResourceAmount(ResourceType resource) const {
    if (!isValidResource(resource)) {
        return -1;
    }

    return resources[resource];
}

bool Room::isResourceCollected(ResourceType resource) const {
    if (!isValidResource(resource)) {
        return false;
    }

    return collected[resource];
}

void Room::markResourceCollected(ResourceType resource) {
    if (!isValidResource(resource)) {
        return;
    }

    collected[resource] = true;
}

bool Room::wasAnyResourceCollected() const {
    return hasCollectedAnyResource;
}

void Room::markAnyResourceCollected() {
    hasCollectedAnyResource = true;
}

bool Room::hasAvailableResource(ResourceType resource) const {
    if (!isValidResource(resource)) {
        return false;
    }

    return resources[resource] > 0 && !collected[resource];
}
