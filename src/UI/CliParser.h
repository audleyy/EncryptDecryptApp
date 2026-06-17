#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include "../common/CommonTypes.h"

struct CliParseResult {
    bool needHelp;
    ErrorCode errorCode;
    CoreOptions options;
};

CliParseResult ParseCliArguments(int argc, char* argv[]);
CliParseResult ParseCliLine(const string& line);
void PrintHelp();

#endif
