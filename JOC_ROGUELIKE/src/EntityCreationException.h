#pragma once
#include "GameException.h"

class EntityCreationException : public GameException 
{
public:
    EntityCreationException(const std::string& entityType)
        : GameException("EntityCreationException: " + entityType) {}
};
