#include "BasicBotStrategy.h"

#include <algorithm>
#include <queue>

BasicBotStrategy::BasicBotStrategy() {}

void BasicBotStrategy::updateKnowledgeAfterVisit(
    const Dungeon& dungeon, BotState& bot, int roomNumber) {
    bot.markRoomKnown(roomNumber);

    const Room& visitedRoom = dungeon.getRoom(roomNumber);
    const std::vector<int>& neighbours = visitedRoom.getNeighbours();

    bot.setKnownNeighbours(roomNumber, neighbours);

    for (int neighbourIndex = 0; neighbourIndex < static_cast<int>(neighbours.size()); neighbourIndex++) {
        int visibleRoomNumber = neighbours[neighbourIndex];

        bot.markRoomKnown(visibleRoomNumber);

        const Room& visibleRoom = dungeon.getRoom(visibleRoomNumber);
        const std::vector<int>& visibleNeighbours = visibleRoom.getNeighbours();

        bot.setKnownNeighbours(visibleRoomNumber, visibleNeighbours);

        for (
            int visibleNeighbourIndex = 0;
            visibleNeighbourIndex < static_cast<int>(visibleNeighbours.size());
            visibleNeighbourIndex++
        ) {
            int numberedRoom = visibleNeighbours[visibleNeighbourIndex];

            bot.markRoomKnown(numberedRoom);
        }
    }
}

int BasicBotStrategy::chooseBestResource(const Room& room, ResourceType targetResource) const {
    int bestResource = -1;
    int bestValue = -1;

    for (int resourceIndex = 0; resourceIndex < RESOURCE_COUNT; resourceIndex++) {
        ResourceType resource = static_cast<ResourceType>(resourceIndex);

        if (room.hasAvailableResource(resource)) {
            int value = getResourceValue(resource, targetResource);

            if (value > bestValue) {
                bestValue = value;
                bestResource = resourceIndex;
            }
        }
    }

    return bestResource;
}

void BasicBotStrategy::collectResource(
    Dungeon& dungeon, BotState& bot,
    ActionWriter& writer, ResourceType resource) {
    if (!isValidResource(resource)) {
        return;
    }

    int currentRoomNumber = bot.getCurrentRoom();
    Room& room = dungeon.getRoom(currentRoomNumber);

    if (!room.hasAvailableResource(resource)) {
        return;
    }

    writer.writeCollect(resource);

    int amount = room.getResourceAmount(resource);
    bot.addCollectedResource(resource, amount);

    if (room.wasAnyResourceCollected()) {
        bot.spendFood(1);
    } else {
        room.markAnyResourceCollected();
    }

    room.markResourceCollected(resource);

    writer.writeState(room);
}

void BasicBotStrategy::goToRoom(
    Dungeon& dungeon, BotState& bot,
    ActionWriter& writer, int nextRoom) {
    writer.writeGo(nextRoom);

    bot.spendFood(1);
    bot.setCurrentRoom(nextRoom);
    bot.markRoomVisited(nextRoom);

    updateKnowledgeAfterVisit(dungeon, bot, nextRoom);

    if (nextRoom != 0) {
        writer.writeState(dungeon.getRoom(nextRoom));
    }
}

int BasicBotStrategy::chooseSmallestUnvisitedNeighbour(const BotState& bot) const {
    int currentRoomNumber = bot.getCurrentRoom();
    const std::vector<int>& neighbours = bot.getKnownNeighbours(currentRoomNumber);

    int bestRoom = -1;

    for (int neighbourIndex = 0; neighbourIndex < static_cast<int>(neighbours.size()); neighbourIndex++) {
        int neighbour = neighbours[neighbourIndex];

        if (bot.isRoomKnown(neighbour) && !bot.isRoomVisited(neighbour)) {
            if (bestRoom == -1 || neighbour < bestRoom) {
                bestRoom = neighbour;
            }
        }
    }

    return bestRoom;
}

std::vector<int> BasicBotStrategy::findPathToNearestUnvisited(const Dungeon& dungeon, const BotState& bot) const {
    int roomCount = dungeon.getRoomCount();
    int startRoom = bot.getCurrentRoom();

    std::vector<bool> used(roomCount, false);
    std::vector<int> parent(roomCount, -1);
    std::queue<int> roomsQueue;

    used[startRoom] = true;
    roomsQueue.push(startRoom);

    int targetRoom = -1;

    while (!roomsQueue.empty() && targetRoom == -1) {
        int levelSize = static_cast<int>(roomsQueue.size());
        std::vector<int> candidates;

        for (int levelIndex = 0; levelIndex < levelSize; levelIndex++) {
            int currentRoom = roomsQueue.front();
            roomsQueue.pop();

            std::vector<int> neighbours = bot.getKnownNeighbours(currentRoom);
            std::sort(neighbours.begin(), neighbours.end());

            for (int neighbourIndex = 0; neighbourIndex < static_cast<int>(neighbours.size()); neighbourIndex++) {
                int nextRoom = neighbours[neighbourIndex];

                if (!bot.isRoomKnown(nextRoom)) {
                    continue;
                }

                if (used[nextRoom]) {
                    continue;
                }

                used[nextRoom] = true;
                parent[nextRoom] = currentRoom;

                if (!bot.isRoomVisited(nextRoom)) {
                    candidates.push_back(nextRoom);
                } else {
                    roomsQueue.push(nextRoom);
                }
            }
        }

        if (!candidates.empty()) {
            targetRoom = candidates[0];

            for (int candidateIndex = 1; candidateIndex < static_cast<int>(candidates.size()); candidateIndex++) {
                if (candidates[candidateIndex] < targetRoom) {
                    targetRoom = candidates[candidateIndex];
                }
            }
        }
    }

    std::vector<int> path;

    if (targetRoom == -1) {
        return path;
    }

    int currentRoom = targetRoom;

    while (currentRoom != startRoom) {
        path.push_back(currentRoom);
        currentRoom = parent[currentRoom];
    }

    std::reverse(path.begin(), path.end());

    return path;
}

int BasicBotStrategy::chooseNextRoom(const Dungeon& dungeon, const BotState& bot) const {
    int neighbour = chooseSmallestUnvisitedNeighbour(bot);

    if (neighbour != -1) {
        return neighbour;
    }

    std::vector<int> path = findPathToNearestUnvisited(dungeon, bot);

    if (path.empty()) {
        return -1;
    }

    return path[0];
}

void BasicBotStrategy::explorationPhase(Dungeon& dungeon, BotState& bot, ActionWriter& writer) {
    int startFood = bot.getFood();
    int foodForExploration = startFood / 2;
    int minimumFoodAfterExploration = startFood - foodForExploration;

    while (bot.getFood() > minimumFoodAfterExploration) {
        int nextRoom = chooseNextRoom(dungeon, bot);

        if (nextRoom == -1) {
            break;
        }

        goToRoom(dungeon, bot, writer, nextRoom);

        Room& currentRoom = dungeon.getRoom(bot.getCurrentRoom());

        int bestResourceIndex = chooseBestResource(
            currentRoom,
            bot.getTargetResource()
        );

        if (bestResourceIndex != -1) {
            bool collectionIsFree = !currentRoom.wasAnyResourceCollected();

            if (collectionIsFree || bot.getFood() > minimumFoodAfterExploration) {
                ResourceType bestResource = static_cast<ResourceType>(bestResourceIndex);
                collectResource(dungeon, bot, writer, bestResource);
            }
        }
    }
}

std::vector<int> BasicBotStrategy::findPathToStart(const Dungeon& dungeon, const BotState& bot) const {
    int roomCount = dungeon.getRoomCount();
    int startRoom = bot.getCurrentRoom();
    int targetRoom = 0;

    std::vector<bool> used(roomCount, false);
    std::vector<int> parent(roomCount, -1);
    std::queue<int> roomsQueue;

    used[startRoom] = true;
    roomsQueue.push(startRoom);

    while (!roomsQueue.empty()) {
        int currentRoom = roomsQueue.front();
        roomsQueue.pop();

        if (currentRoom == targetRoom) {
            break;
        }

        std::vector<int> neighbours = bot.getKnownNeighbours(currentRoom);
        std::sort(neighbours.begin(), neighbours.end());

        for (int neighbourIndex = 0; neighbourIndex < static_cast<int>(neighbours.size()); neighbourIndex++) {
            int nextRoom = neighbours[neighbourIndex];

            if (!bot.isRoomVisited(nextRoom)) {
                continue;
            }

            if (used[nextRoom]) {
                continue;
            }

            used[nextRoom] = true;
            parent[nextRoom] = currentRoom;
            roomsQueue.push(nextRoom);
        }
    }

    std::vector<int> path;

    if (!used[targetRoom]) {
        return path;
    }

    int currentRoom = targetRoom;

    while (currentRoom != startRoom) {
        path.push_back(currentRoom);
        currentRoom = parent[currentRoom];
    }

    std::reverse(path.begin(), path.end());

    return path;
}

void BasicBotStrategy::collectExtraResourcesOnWayBack(
    Dungeon& dungeon, BotState& bot,
    ActionWriter& writer, int remainingStepsToStart) {
    Room& room = dungeon.getRoom(bot.getCurrentRoom());

    while (true) {
        int bestResourceIndex = chooseBestResource(
            room,
            bot.getTargetResource()
        );

        if (bestResourceIndex == -1) {
            break;
        }

        bool collectionIsFree = !room.wasAnyResourceCollected();
        int extraFood = bot.getFood() - remainingStepsToStart;

        if (!collectionIsFree && extraFood <= 0) {
            break;
        }

        ResourceType resource = static_cast<ResourceType>(bestResourceIndex);
        collectResource(dungeon, bot, writer, resource);
    }
}

void BasicBotStrategy::returnPhase(Dungeon& dungeon, BotState& bot, ActionWriter& writer) {
    std::vector<int> path = findPathToStart(dungeon, bot);

    for (int pathIndex = 0; pathIndex < static_cast<int>(path.size()); pathIndex++) {
        int remainingStepsToStart = static_cast<int>(path.size()) - pathIndex;

        collectExtraResourcesOnWayBack(
            dungeon,
            bot,
            writer,
            remainingStepsToStart
        );

        int nextRoom = path[pathIndex];
        goToRoom(dungeon, bot, writer, nextRoom);
    }
}

void BasicBotStrategy::run(Dungeon& dungeon, BotState& bot, ActionWriter& writer) {
    updateKnowledgeAfterVisit(dungeon, bot, 0);

    explorationPhase(dungeon, bot, writer);

    returnPhase(dungeon, bot, writer);

    writer.writeResult(bot);
}