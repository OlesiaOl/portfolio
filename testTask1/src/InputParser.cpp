#include "InputParser.h"

#include <fstream>
#include <sstream>
#include <algorithm>

InputParser::InputParser() {}

bool InputParser::parseInteger( const std::string& text, int& value ) const {
    if (text.empty()) {
        return false;
    }

    int result = 0;

    for (int i = 0; i < static_cast<int>(text.size()); i++) {
        char symbol = text[i];

        if (symbol < '0' || symbol > '9') {
            return false;
        }

        int digit = symbol - '0';

        if (result > (MAX_INPUT_NUMBER - digit) / 10) {
            return false;
        }

        result = result * 10 + digit;
    }

    value = result;
    return true;
}

bool InputParser::parseNeighbourList( const std::string& text, int maxRoomNumber, std::vector<int>& neighbours) const {
    neighbours.clear();

    if (text.empty()) {
        return false;
    }

    if (text[0] == ',' || text[text.size() - 1] == ',') {
        return false;
    }

    std::stringstream stream(text);
    std::string part;

    while (std::getline(stream, part, ',')) {
        if (part.empty()) {
            return false;
        }

        int neighbour = 0;

        if (!parseInteger(part, neighbour)) {
            return false;
        }

        if (neighbour < 0 || neighbour > maxRoomNumber) {
            return false;
        }

        if (std::find(neighbours.begin(), neighbours.end(), neighbour) != neighbours.end()) {
            return false;
        }

        neighbours.push_back(neighbour);
    }

    if (neighbours.empty()) {
        return false;
    }

    return true;
}

bool InputParser::parseRoomLine(
    const std::string& line,
    int maxRoomNumber,
    Dungeon& dungeon,
    std::vector<bool>& roomWasDefined,
    int& parsedRoomNumber
) const {
    std::stringstream stream(line);

    std::string roomNumberText;
    std::string neighboursText;

    if (!(stream >> roomNumberText)) {
        return false;
    }

    if (!(stream >> neighboursText)) {
        return false;
    }

    int roomNumber = 0;

    if (!parseInteger(roomNumberText, roomNumber)) {
        return false;
    }

    if (roomNumber < 0 || roomNumber > maxRoomNumber) {
        return false;
    }

    if (roomWasDefined[roomNumber]) {
        return false;
    }

    parsedRoomNumber = roomNumber;

    std::vector<int> neighbours;

    if (!parseNeighbourList(neighboursText, maxRoomNumber, neighbours)) {
        return false;
    }

    for (int i = 0; i < static_cast<int>(neighbours.size()); i++) {
        if (neighbours[i] == roomNumber) {
            return false;
        }
    }

    int resourceAmounts[RESOURCE_COUNT];

    for (int i = 0; i < RESOURCE_COUNT; i++) {
        resourceAmounts[i] = 0;
    }

    for (int i = 0; i < RESOURCE_COUNT; i++) {
        std::string resourceText;

        if (!(stream >> resourceText)) {
            if (roomNumber == 0) {
                break;
            }

            return false;
        }

        if (!parseInteger(resourceText, resourceAmounts[i])) {
            return false;
        }

        if (resourceAmounts[i] < 0 || resourceAmounts[i] > MAX_INPUT_NUMBER) {
            return false;
        }
    }

    std::string extraToken;

    if (stream >> extraToken) {
        return false;
    }

    Room& room = dungeon.getRoom(roomNumber);

    room.setNumber(roomNumber);

    for (int i = 0; i < static_cast<int>(neighbours.size()); i++) {
        room.addNeighbour(neighbours[i]);
    }

    for (int i = 0; i < RESOURCE_COUNT; i++) {
        ResourceType resource = static_cast<ResourceType>(i);

        room.setResourceAmount(resource, resourceAmounts[i]);
    }

    roomWasDefined[roomNumber] = true;

    return true;
}

bool InputParser::parseLastLine( const std::string& line, int& startFood, ResourceType& targetResource ) const { 
    std::stringstream stream(line);

    std::string foodText;
    std::string resourceText;
    std::string extraToken;

    if (!(stream >> foodText)) {
        return false;
    }

    if (!(stream >> resourceText)) {
        return false;
    }

    if (stream >> extraToken) {
        return false;
    }

    if (!parseInteger(foodText, startFood)) {
        return false;
    }

    if (startFood < 2 || startFood > 255) {
        return false;
    }

    if (!stringToResource(resourceText, targetResource)) {
        return false;
    }

    return true;
}

bool InputParser::validateUndirectedEdges( const Dungeon& dungeon, const std::vector<std::string>& roomLines, std::string& invalidLine ) const {
    int roomCount = dungeon.getRoomCount();

    for (int roomNumber = 0; roomNumber < roomCount; roomNumber++) {
        const Room& room = dungeon.getRoom(roomNumber);
        const std::vector<int>& neighbours = room.getNeighbours();

        for (int i = 0; i < static_cast<int>(neighbours.size()); i++) {
            int neighbour = neighbours[i];

            const Room& neighbourRoom = dungeon.getRoom(neighbour);
            const std::vector<int>& reverseNeighbours = neighbourRoom.getNeighbours();

            if (std::find(reverseNeighbours.begin(), reverseNeighbours.end(), roomNumber) == reverseNeighbours.end()) {
                invalidLine = roomLines[roomNumber];
                return false;
            }
        }
    }

    return true;
}

bool InputParser::parse( const std::string& fileName, Dungeon& dungeon, int& startFood, ResourceType& targetResource, std::string& invalidLine ) const {
    std::ifstream input(fileName);

    if (!input.is_open()) {
        invalidLine = "";
        return false;
    }

    std::string line;

    if (!std::getline(input, line)) {
        invalidLine = "";
        return false;
    }

    int maxRoomNumber = 0;

    if (!parseInteger(line, maxRoomNumber)) {
        invalidLine = line;
        return false;
    }

    if (maxRoomNumber < MIN_ROOM_NUMBER || maxRoomNumber > MAX_INPUT_NUMBER) {
        invalidLine = line;
        return false;
    }

    int roomCount = maxRoomNumber + 1;

    dungeon.resize(roomCount);

    std::vector<bool> roomWasDefined(roomCount, false);
    std::vector<std::string> roomLines(roomCount);

    for (int roomIndex = 0; roomIndex < roomCount; roomIndex++) {
        if (!std::getline(input, line)) {
            invalidLine = "";
            return false;
        }

        std::string currentLine = line;
        int parsedRoomNumber = -1;

        if (!parseRoomLine(
                currentLine,
                maxRoomNumber,
                dungeon,
                roomWasDefined,
                parsedRoomNumber
            )) {
            invalidLine = currentLine;
            return false;
        }

        roomLines[parsedRoomNumber] = currentLine;
    }

    for (int roomNumber = 0; roomNumber < roomCount; roomNumber++) {
        if (!roomWasDefined[roomNumber]) {
            invalidLine = "";
            return false;
        }
    }

    if (!std::getline(input, line)) {
        invalidLine = "";
        return false;
    }

    if (!parseLastLine(line, startFood, targetResource)) {
        invalidLine = line;
        return false;
    }

    std::string extraLine;

    if (std::getline(input, extraLine)) {
        invalidLine = extraLine;
        return false;
    }

    if (!validateUndirectedEdges(dungeon, roomLines, invalidLine)) {
        return false;
    }

    return true;
}