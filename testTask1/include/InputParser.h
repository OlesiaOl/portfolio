#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <string>
#include <vector>

#include "Dungeon.h"
#include "Resources.h"

class InputParser {
private:
    static const int MIN_ROOM_NUMBER = 1;
    static const int MAX_INPUT_NUMBER = 255;

    bool parseInteger(
        const std::string& text, int& value
    ) const;

    bool parseNeighbourList(
        const std::string& text, int maxRoomNumber,
        std::vector<int>& neighbours
    ) const;

    bool parseRoomLine(
        const std::string& line, int maxRoomNumber,
        Dungeon& dungeon, std::vector<bool>& roomWasDefined,
        int& parsedRoomNumber
    ) const;

    bool parseLastLine(
        const std::string& line, int& startFood,
        ResourceType& targetResource
    ) const;

    bool validateUndirectedEdges(
        const Dungeon& dungeon, const std::vector<std::string>& roomLines,
        std::string& invalidLine
    ) const;

public:
    InputParser();

    bool parse(
        const std::string& fileName, Dungeon& dungeon,
        int& startFood, ResourceType& targetResource,
        std::string& invalidLine
    ) const;
};

#endif // INPUT_PARSER_H
