#include <fstream>
#include <string>

#include "Dungeon.h"
#include "BotState.h"
#include "ActionWriter.h"
#include "BasicBotStrategy.h"
#include "InputParser.h"

int main(int argc, char* argv[]) {
    std::ofstream output("result.txt");

    if (!output.is_open()) {
        return 1;
    }

    ActionWriter writer(output);

    if (argc != 2) {
        writer.writeInvalidLine("");
        return 0;
    }

    Dungeon dungeon;
    int startFood = 0;
    ResourceType targetResource = IRON;
    std::string invalidLine;

    InputParser parser;

    if (!parser.parse(argv[1], dungeon, startFood, targetResource, invalidLine)) {
        writer.writeInvalidLine(invalidLine);
        return 0;
    }

    BotState bot;
    bot.initialize(dungeon.getRoomCount(), startFood, targetResource);

    BasicBotStrategy strategy;
    strategy.run(dungeon, bot, writer);

    return 0;
}
