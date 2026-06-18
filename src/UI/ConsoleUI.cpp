#include "ConsoleUI.h"

using namespace std;

const string TextEndMarker = "exit_for_text";

string ReadConsoleTextUntilExit() {
    string text;
    string line;
    bool isFirstLine = true;
    bool isReading = true;
    while (isReading && getline(cin, line)) {
        if (line == TextEndMarker) {
            isReading = false;
        } else {
            if (!isFirstLine) {
                text += "\n";
            }
            text += line;
            isFirstLine = false;
        }
    }
    return text;
}

ErrorCode RunConsoleUI() {
    ErrorCode errorCode = Success;
    try {
        cout << "███╗   ██╗███████╗██████╗ ██████╗  █████╗\n";
        cout << "████╗  ██║██╔════╝██╔══██╗██╔══██╗██╔══██╗\n";
        cout << "██╔██╗ ██║█████╗  ██████╔╝██████╔╝███████║\n";
        cout << "\033[31m██║╚██╗██║██╔══╝  ██╔══██╗██╔═══╝ ██╔══██║\033[0m\n";
        cout << "\033[31m██║ ╚████║███████╗██║  ██║██║     ██║  ██║\033[0m\n";
        cout << "\033[31m╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝  ╚═╝\033[0m\n";

        cout << "Введите команду с флагами или --help, --man:\n";
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
                if (parseResult.needMan) {
                    PrintMan(parseResult.manTopic);
                    errorCode = Success;
                } else if (parseResult.needHelp) {
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
                        cout << "Для завершения ввода введите " << TextEndMarker << "\n";
                        parseResult.options.textValue = ReadConsoleTextUntilExit();
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
