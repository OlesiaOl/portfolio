#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>

enum ResourceType {
    IRON = 0,
    GOLD = 1,
    GEMS = 2,
    EXP = 3,
    RESOURCE_COUNT = 4
};

inline const int RESOURCE_VALUES[RESOURCE_COUNT] = {
    7,   // iron
    11,  // gold
    23,  // gems
    1    // exp
};

inline const char* const RESOURCE_NAMES[RESOURCE_COUNT] = {
    "iron",
    "gold",
    "gems",
    "exp"
};

bool isValidResource(ResourceType resource);

int getResourceValue(ResourceType resource, ResourceType targetResource);

std::string resourceToString(ResourceType resource);
bool stringToResource(const std::string& text, ResourceType& resource);

#endif //RESOURCES_H
