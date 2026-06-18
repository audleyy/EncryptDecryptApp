#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include "../common/CommonTypes.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct CliParseResult {
    bool needHelp;
    bool needMan;
    string manTopic;
    ErrorCode errorCode;
    CoreOptions options;
};

CliParseResult ParseCliArguments(int argc, char* argv[]);
CliParseResult ParseCliLine(const string& line);
void PrintHelp();
void PrintMan(const string& topic = "");

#endif
