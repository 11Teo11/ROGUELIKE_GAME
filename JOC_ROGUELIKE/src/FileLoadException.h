#pragma once
#include "GameException.h"

class FileLoadException : public GameException
{
public:
    FileLoadException(const std::string& msg)
        : GameException("Eroare citire fisier: " + msg) {}
};