#include "CliParser.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool IsFlag(const string& value) {
    return value.rfind("--", 0) == 0;
}

string ReadFlagValue(int argc, char* argv[], int& index) {
    string value;
    if (index + 1 < argc && !IsFlag(argv[index + 1])) {
        index++;
        value = argv[index];
    }
    return value;
}

bool ParseAlgorithm(const string& value, AlgorithmType& algorithm) {
    bool isParsed = true;
    if (value == "rsa") {
        algorithm = AlgorithmType::Rsa;
    } else if (value == "shamir") {
        algorithm = AlgorithmType::Shamir;
    } else if (value == "elgamal") {
        algorithm = AlgorithmType::ElGamal;
    } else if (value == "caesar") {
        algorithm = AlgorithmType::Caesar;
    } else {
        isParsed = false;
    }
    return isParsed;
}

bool ParseOperation(const string& value, OperationType& operation) {
    bool isParsed = true;
    if (value == "generate-key") {
        operation = OperationType::GenerateKey;
    } else if (value == "encrypt") {
        operation = OperationType::Encrypt;
    } else if (value == "decrypt") {
        operation = OperationType::Decrypt;
    } else {
        isParsed = false;
    }
    return isParsed;
}

ErrorCode ValidateOptions(const CoreOptions& options, bool hasAlgorithm, bool hasOperation) {
    ErrorCode errorCode = Success;
    if (!hasAlgorithm || !hasOperation) {
        errorCode = InvalidInput;
    } else if (options.operation == OperationType::GenerateKey) {
        if (options.keyFilePath.empty()) {
            errorCode = InvalidInput;
        }
    } else if (options.operation == OperationType::Encrypt || options.operation == OperationType::Decrypt) {
        if (options.keyFilePath.empty()) {
            errorCode = InvalidInput;
        } else if (!options.useText && (options.inputFilePath.empty() || options.outputFilePath.empty())) {
            errorCode = InvalidInput;
        } else if (!options.useText && options.inputFilePath == options.outputFilePath) {
            errorCode = InvalidInput;
        }
    }
    return errorCode;
}

CliParseResult ParseCliArguments(int argc, char* argv[]) {
    CliParseResult result;
    result.needHelp = false;
    result.errorCode = Success;
    result.options.useText = false;
    bool hasAlgorithm = false;
    bool hasOperation = false;
    for (int index = 1; index < argc; index++) {
        string argument = argv[index];
        if (argument == "--help" || argument == "-h") {
            result.needHelp = true;
        } else if (argument == "--algorithm" || argument == "-a") {
            string value = ReadFlagValue(argc, argv, index);
            hasAlgorithm = ParseAlgorithm(value, result.options.algorithm);
            if (!hasAlgorithm) {
                result.errorCode = InvalidInput;
            }
        } else if (argument == "--mode" || argument == "-m") {
            string value = ReadFlagValue(argc, argv, index);
            hasOperation = ParseOperation(value, result.options.operation);
            if (!hasOperation) {
                result.errorCode = InvalidInput;
            }
        } else if (argument == "--input" || argument == "-i") {
            result.options.inputFilePath = ReadFlagValue(argc, argv, index);
        } else if (argument == "--output" || argument == "-o") {
            result.options.outputFilePath = ReadFlagValue(argc, argv, index);
        } else if (argument == "--key" || argument == "-k") {
            result.options.keyFilePath = ReadFlagValue(argc, argv, index);
        } else if (argument == "--text" || argument == "-text") {
            result.options.useText = true;
        } else {
            result.errorCode = InvalidInput;
        }
    }
    if (!result.needHelp && result.errorCode == Success) {
        result.errorCode = ValidateOptions(result.options, hasAlgorithm, hasOperation);
    }
    return result;
}

CliParseResult ParseCliLine(const string& line) {
    vector<string> words;
    string word{};
    istringstream stream(line);
    words.push_back("app");
    while (stream >> word) {
        words.push_back(word);
    }
    vector<char*> argv;
    argv.reserve(words.size());
    for (string& value : words) {
        argv.push_back(&value[0]);
    }
    return ParseCliArguments(argv.size(), argv.data());
}

void PrintHelp(){
    cout << "Использование:\n";
    cout << "  ./app --help\n";
    cout << "  ./app --mode generate-key --algorithm rsa|shamir|elgamal|caesar --key key.bin\n";
    cout << "  ./app --mode encrypt --algorithm rsa|shamir|elgamal|caesar --input in.bin --output out.bin --key key.bin\n";
    cout << "  ./app --mode decrypt --algorithm rsa|shamir|elgamal|caesar --input in.bin --output out.bin --key key.bin\n";
    cout << "  ./app --mode encrypt --algorithm rsa|shamir|elgamal|caesar --text --key key.bin\n";
    cout << "  ./app --mode decrypt --algorithm rsa|shamir|elgamal|caesar --text --key key.bin\n";
    cout << "  ./app -m encrypt -a rsa -i in.bin -o out.bin -k key.bin\n";
    cout << "\n";
    cout << "Флаги:\n";
    cout << "  --help, -h       показать справку\n";
    cout << "  --mode, -m       generate-key, encrypt или decrypt\n";
    cout << "  --algorithm, -a  rsa, shamir, elgamal или caesar\n";
    cout << "  --input, -i      входной файл для encrypt/decrypt\n";
    cout << "  --output, -o     выходной файл для encrypt/decrypt\n";
    cout << "  --key, -k        файл ключа .bin\n";
    cout << "  --text, -text    ввод текста из консоли вместо файла\n";
    cout << "  exit             выйти из интерактивного режима\n";
    cout << "\n";
    cout << "Для --text при encrypt программа выводит HEX-шифротекст.\n";
    cout << "Для --text при decrypt нужно ввести HEX-шифротекст.\n";
}
