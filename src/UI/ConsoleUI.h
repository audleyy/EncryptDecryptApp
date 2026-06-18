#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "../common/CommonTypes.h"
#include "CliParser.h"
#include "../common/ErrorText.h"
#include "../core/Core.h"
#include <iostream>

ErrorCode RunConsoleUI();
string ReadConsoleTextUntilExit();

#endif
