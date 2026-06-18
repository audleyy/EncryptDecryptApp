#include "ConsoleUI.h"
#include <iostream>
#include <string>

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
                } else if (parseResult.errorCode != Success) {
                    cout << "Ошибка парсинга: " << GetErrorText(parseResult.errorCode) << "\n";
                } else {
                    if (parseResult.options.useText && parseResult.options.textValue.empty()) {
                        if (parseResult.options.operation == OperationType::Decrypt) {
                            cout << "Введите HEX-шифротекст:\n> ";
                        } else {
                            cout << "Введите открытый текст:\n> ";
                        }
                        cout << "Для завершения ввода введите " << TextEndMarker << "\n";
                        parseResult.options.textValue = ReadConsoleTextUntilExit();
                    }

                    if (parseResult.options.operation == OperationType::GenerateKey) {
                        cout << "Генерация ключа по пути: " << parseResult.options.keyFilePath << "...\n";
                    }

                    errorCode = RunCore(parseResult.options);
                    
                    if (errorCode == Success) {
                        cout << "[Успешно выполнено]\n";
                    } else {
                        cout << "Ошибка выполнения: " << GetErrorText(errorCode) << "\n";
                        if (!LastErrorDetails.empty()) {
                            cout << LastErrorDetails << "\n";
                        }
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