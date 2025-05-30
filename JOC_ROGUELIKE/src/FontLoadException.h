#pragma once
#include "GameException.h"

class FontLoadException : public GameException
{
public:
    FontLoadException(const std::string& msg)
        : GameException("Eroare font: " + msg) {}
};