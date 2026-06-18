#include "src/UI/CliParser.h"
#include "src/UI/ConsoleUI.h"
#include "src/common/ErrorText.h"
#include "src/core/Core.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        return RunConsoleUI();
    }
    CliParseResult parseResult = ParseCliArguments(argc, argv);
    if (parseResult.needMan) {
        PrintMan(parseResult.manTopic);
        return Success;
    }
    if (parseResult.needHelp) {
        PrintHelp();
        return Success;
    }
    if (parseResult.errorCode != Success) {
        cout << GetErrorText(parseResult.errorCode) << "\n";
        PrintHelp();
        return parseResult.errorCode;
    }
    if (parseResult.options.useText) {
        cout << "Для завершения ввода введите exit_for_text\n";
        parseResult.options.textValue = ReadConsoleTextUntilExit();
    }
    ErrorCode errorCode = RunCore(parseResult.options);
    cout << GetErrorText(errorCode) << "\n";
    if (errorCode != Success && !LastErrorDetails.empty()) {
        cout << LastErrorDetails << "\n";
    }
    return errorCode;
}
