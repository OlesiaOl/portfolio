#include "Resources.h"

bool isValidResource(ResourceType resource) {
    int resourceIndex = static_cast<int>(resource);

    if (resourceIndex < 0) {
        return false;
    }

    if (resourceIndex >= RESOURCE_COUNT) {
        return false;
    }

    return true; 
}

int getResourceValue(ResourceType resource, ResourceType targetResource) {
    if (!isValidResource(resource)) {
        return 0;
    }

    if (!isValidResource(targetResource)) {
        return 0;
    }

    int resourceValue = RESOURCE_VALUES[resource];

    if (resource == targetResource) {
        resourceValue = resourceValue * 2;
    }

    return resourceValue;
}

std::string resourceToString(ResourceType resource) {
    if (!isValidResource(resource)) {
        return "";
    }

    return RESOURCE_NAMES[resource];
}

bool stringToResource(const std::string& text, ResourceType& resource) {
    for (int i = 0; i < RESOURCE_COUNT; i++) {
        if (text == RESOURCE_NAMES[i]) {
            resource = static_cast<ResourceType>(i);
            return true;
        }
    }

    return false;
}
