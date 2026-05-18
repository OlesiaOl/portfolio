#include "ActionWriter.h"

ActionWriter::ActionWriter(std::ofstream& outputFile) : output(outputFile) {}

void ActionWriter::writeGo(int roomNumber) {
    output << "go " << roomNumber << '\n';
}

void ActionWriter::writeCollect(ResourceType resource) {
    output << "collect " << resourceToString(resource) << '\n';
}

void ActionWriter::writeState(const Room& room) {
    output << "state " << room.getNumber();
    for (int i = 0; i < RESOURCE_COUNT; i++) {
        ResourceType resource = static_cast<ResourceType>(i);
        output << " ";

        if (room.isResourceCollected(resource)) {
            output << "_";
        } else {
            output << room.getResourceAmount(resource);
        }
    }

    output << '\n';
}

void ActionWriter::writeResult(const BotState& bot) {
    int totalValue = 0;

    output << "result";

    for (int resourceIndex = 0; resourceIndex < RESOURCE_COUNT; resourceIndex++) {
        ResourceType resource = static_cast<ResourceType>(resourceIndex);
        int amount = bot.getCollectedResourceAmount(resource);

        int resourceValue = getResourceValue(resource, bot.getTargetResource());
        int resourceTotalValue = amount * resourceValue;

        output << " " << amount;

        totalValue = totalValue + resourceTotalValue;
    }

    output << " " << totalValue << '\n';
}

void ActionWriter::writeInvalidLine(const std::string& line) {
    output << line << '\n';
}
