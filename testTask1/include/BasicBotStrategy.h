#ifndef BASIC_BOT_STRATEGY_H
#define BASIC_BOT_STRATEGY_H

#include <vector>

#include "Dungeon.h"
#include "BotState.h"
#include "ActionWriter.h"
#include "Resources.h"

class BasicBotStrategy {
private:
    void updateKnowledgeAfterVisit(
        const Dungeon& dungeon, BotState& bot, int roomNumber
    );

    int chooseBestResource(
        const Room& room, ResourceType targetResource
    ) const;

    void collectResource(
        Dungeon& dungeon, BotState& bot,
        ActionWriter& writer, ResourceType resource
    );

    void goToRoom(
        Dungeon& dungeon, BotState& bot,
        ActionWriter& writer, int nextRoom
    );

    int chooseSmallestUnvisitedNeighbour(
        const BotState& bot
    ) const;

    std::vector<int> findPathToNearestUnvisited(
        const Dungeon& dungeon, const BotState& bot
    ) const;

    int chooseNextRoom(
        const Dungeon& dungeon, const BotState& bot
    ) const;

    void explorationPhase(
        Dungeon& dungeon, BotState& bot, ActionWriter& writer
    );

    std::vector<int> findPathToStart(
        const Dungeon& dungeon, const BotState& bot
    ) const;

    void collectExtraResourcesOnWayBack(
        Dungeon& dungeon, BotState& bot,
        ActionWriter& writer, int remainingStepsToStart
    );

    void returnPhase(
        Dungeon& dungeon, BotState& bot, ActionWriter& writer
    );

public:
    BasicBotStrategy();

    void run(
        Dungeon& dungeon, BotState& bot, ActionWriter& writer
    );
};

#endif // BASIC_BOT_STRATEGY_H