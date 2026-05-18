#ifndef ACTION_WRITER_H
#define ACTION_WRITER_H

#include <fstream>
#include <string>

#include "Room.h"
#include "BotState.h"
#include "Resources.h"

class ActionWriter {
private:
    std::ofstream& output;
public:
    ActionWriter(std::ofstream& outputFile);
    void writeGo(int roomNumber);
    void writeCollect(ResourceType resource);
    void writeState(const Room& room);
    void writeResult(const BotState& bot);
    void writeInvalidLine(const std::string& line);
};

#endif //ACTION_WRITER_H
