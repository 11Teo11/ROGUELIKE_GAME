#pragma once
#include"GameException.h"

class AssetsLoadException : public GameException 
{
public:
    AssetsLoadException(const std::string& msg)
        : GameException("AssetsLoadException: " + msg) {}
};
