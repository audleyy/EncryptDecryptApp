#include "ConsoleUI.h"
#include "CliParser.h"
#include "../common/ErrorText.h"
#include "../core/Core.h"
#include <iostream>

using namespace std;

ErrorCode RunConsoleUI() {
    ErrorCode errorCode = Success;
    try {
        cout << "Введите команду с флагами или --help:\n";
        cout << "Для выхода введите exit\n";
        bool isRunning = true;
        while (isRunning) {
            string line{};
            cout << "> ";
            if (!getline(cin, line)) {
                isRunning = false;
            } else if (line == "exit") {
                isRunning = false;
                errorCode = Success;
            } else if (!line.empty()) {
                CliParseResult parseResult = ParseCliLine(line);
                if (parseResult.needHelp) {
                    PrintHelp();
                    errorCode = Success;
                } else if (parseResult.errorCode != Success) {
                    errorCode = parseResult.errorCode;
                    cout << GetErrorText(errorCode) << "\n";
                } else {
                    if (parseResult.options.useText) {
                        if (parseResult.options.operation == OperationType::Decrypt) {
                            cout << "Введите HEX-шифротекст:\n";
                        } else {
                            cout << "Введите текст:\n";
                        }
                        cout << "> ";
                        getline(cin, parseResult.options.textValue);
                    }
                    errorCode = RunCore(parseResult.options);
                    cout << GetErrorText(errorCode) << "\n";
                    if (errorCode != Success && !LastErrorDetails.empty()) {
                        cout << LastErrorDetails << "\n";
                    }
                }
            }
        }
    } catch (const invalid_argument&) {
        errorCode = InvalidInput;
    } catch (const exception&) {
        errorCode = UnknownError;
    }
    return errorCode;
}
