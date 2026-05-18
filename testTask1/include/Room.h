#ifndef ROOM_H
#define ROOM_H

#include <vector>

#include "Resources.h"

class Room {
private:
    int number;
    std::vector<int> neighbors;
    int resources[RESOURCE_COUNT];
    bool collected[RESOURCE_COUNT];

    bool hasCollectedAnyResource;

public:
    Room();
    int getNumber() const;
    void setNumber(int roomNumber);
    
    void addNeighbour(int neighbour);
    const std::vector<int>& getNeighbours() const;

    void setResourceAmount(ResourceType resource, int amount);
    int getResourceAmount(ResourceType resource) const;
    
    bool isResourceCollected(ResourceType resource) const;
    void markResourceCollected(ResourceType resource);
    
    bool wasAnyResourceCollected() const;
    void markAnyResourceCollected(); 

    bool hasAvailableResource(ResourceType resource) const;
};

#endif //ROOM_H
