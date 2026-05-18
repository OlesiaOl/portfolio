#ifndef BOT_STATE_H
#define BOT_STATE_H

#include <vector>

#include "Resources.h"

class BotState {
private:
    int currentRoom;
    int food;

    std::vector<bool> visited;
    std::vector<bool> knownRooms;
    std::vector<std::vector<int>> knownNeighbours;

    int collectedResources[RESOURCE_COUNT];

    ResourceType targetResource;

public:
    BotState();

    void initialize(int roomCount, int startFood, ResourceType target);

    int getCurrentRoom() const;
    void setCurrentRoom(int roomNumber);

    int getFood() const;
    void spendFood(int amount);

    bool isRoomVisited(int roomNumber) const;
    void markRoomVisited(int roomNumber);

    bool isRoomKnown(int roomNumber) const;
    void markRoomKnown(int roomNumber);

    void setKnownNeighbours(int roomNumber, const std::vector<int>& neighbours);
    const std::vector<int>& getKnownNeighbours(int roomNumber) const;

    void addCollectedResource(ResourceType resource, int amount);
    int getCollectedResourceAmount(ResourceType resource) const;

    ResourceType getTargetResource() const;
};

#endif // BOT_STATE_H
