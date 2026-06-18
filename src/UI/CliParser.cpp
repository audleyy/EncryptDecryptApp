#include "CliParser.h"
#include "ManualPages.h"

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
    } else if (value == "chacha20") {
        algorithm = AlgorithmType::ChaCha20;
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
    result.needMan = false;
    result.manTopic = "";
    result.errorCode = Success;
    result.options.useText = false;
    bool hasAlgorithm = false;
    bool hasOperation = false;
    for (int index = 1; index < argc; index++) {
        string argument = argv[index];
        if (argument == "--help" || argument == "-h") {
            result.needHelp = true;
        } else if (argument == "--man") {
            result.needMan = true;
            result.manTopic = ReadFlagValue(argc, argv, index);
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
    if (words.size() >= 2 && words[1] == "man") {
        words[1] = "--man";
    }
    vector<char*> argv;
    argv.reserve(words.size());
    for (string& value : words) {
        argv.push_back(&value[0]);
    }
    return ParseCliArguments(argv.size(), argv.data());
}

void PrintHelp(){
    cout << "\033[31mИСПОЛЬЗОВАНИЕ:\033[0m\n";
    cout << "  ./app --help\n";
    cout << "  ./app --man\n";
    cout << "  ./app --man mode|algorithm|key|input|output|text|all\n";
    cout << "  man mode\n";
    cout << "  ./app --mode generate-key --algorithm rsa|shamir|elgamal|caesar|chacha20 --key key.bin\n";
    cout << "  ./app --mode encrypt --algorithm rsa|shamir|elgamal|caesar|chacha20 --input in.bin --output out.bin --key key.bin\n";
    cout << "  ./app --mode decrypt --algorithm rsa|shamir|elgamal|caesar|chacha20 --input in.bin --output out.bin --key key.bin\n";
    cout << "  ./app --mode encrypt --algorithm rsa|shamir|elgamal|caesar|chacha20 --text --key key.bin\n";
    cout << "  ./app --mode decrypt --algorithm rsa|shamir|elgamal|caesar|chacha20 --text --key key.bin\n";
    cout << "  ./app -m encrypt -a rsa -i in.bin -o out.bin -k key.bin\n";
    cout << "\n";
    cout << "\033[31mФЛАГИ:\033[0m\n";
    cout << "  --help, -h       показать справку\n";
    cout << "  --man            показать полное руководство\n";
    cout << "  man <topic>      показать подробное описание темы\n";
    cout << "  --mode, -m       generate-key, encrypt или decrypt\n";
    cout << "  --algorithm, -a  rsa, shamir, elgamal, caesar или chacha20\n";
    cout << "  --input, -i      входной файл для encrypt/decrypt\n";
    cout << "  --output, -o     выходной файл для encrypt/decrypt\n";
    cout << "  --key, -k        файл ключа .bin\n";
    cout << "  --text, -text    ввод текста из консоли вместо файла\n";
    cout << "  exit             выйти из интерактивного режима\n";
    cout << "\n";
    cout << "Для --text при encrypt программа выводит HEX-шифротекст.\n";
    cout << "Для --text при decrypt нужно ввести HEX-шифротекст.\n";
    cout << "Ввод текста завершается строкой exit_for_text.\n";
}

void PrintMan(const string& topic) {
    if (PrintManualPage(topic)) {
        return;
    }
    if (!topic.empty() && topic != "all") {
        cout << "Нет страницы man для темы: " << topic << "\n";
        cout << "Доступные темы: mode, algorithm, key, input, output, text, all\n";
        return;
    }

    cout << "\n";
    cout << "\033[31mОПИСАНИЕ\033[0m\n";
    cout << "  Программа шифрования и расшифрования данных с поддержкой нескольких\n";
    cout << "  криптографических алгоритмов. Поддерживает генерацию ключей,\n";
    cout << "  шифрование/расшифрование текста и файлов.\n";
    cout << "\n";
    cout << "\033[31mРЕЖИМЫ РАБОТЫ\033[0m\n";
    cout << "  1. Командная строка (CLI)   — передача аргументов при запуске\n";
    cout << "  2. Интерактивный режим      — запуск без аргументов, ввод команд в консоли\n";
    cout << "\n";

    cout << "\033[31mАЛГОРИТМЫ\033[0m\n";
    cout << "\n";
    cout << "RSA\n";
    cout << "  Асимметричный алгоритм. Использует пару ключей: открытый (publicKey)\n";
    cout << "  для шифрования и закрытый (privateKey) для расшифрования.\n";
    cout << "  Входные данные разбиваются на блоки по 8 байт, каждый блок\n";
    cout << "  шифруется отдельно. Размер выходных данных кратен 8 байтам.\n";
    cout << "  Параметры ключа: publicKey, privateKey, moduleValue (p * q).\n";
    cout << "\n";
    cout << "Шаммир\n";
    cout << "  Трехпроходный протокол Шамира. Не требует обмена ключами — каждый\n";
    cout << "  участник использует свою пару (c, d) при общем простом модуле prime.\n";
    cout << "  Шифрование: ca -> cb, расшифрование: da -> db.\n";
    cout << "  Параметры ключа: primeValue, caValue, cbValue, daValue, dbValue.\n";
    cout << "  Размер выходных данных кратен 8 байтам.\n";
    cout << "\n";
    cout << "Эль-Гамаль\n";
    cout << "  Асимметричный алгоритм на основе проблемы дискретного логарифма.\n";
    cout << "  Каждый блок шифротекста состоит из двух половин (firstHalf, secondHalf),\n";
    cout << "  размер блока — 16 байт. Размер выходных данных при шифровании\n";
    cout << "  увеличивается в 2 раза относительно открытого текста.\n";
    cout << "  Параметры ключа: primeModulus, generatorValue, publicKey, privateKey.\n";
    cout << "\n";
    cout << "Цезарь\n";
    cout << "  Шифр Цезаря. Каждый байт входных данных сдвигается на значение shift\n";
    cout << "  по модулю 256. Размер входных и выходных данных совпадает.\n";
    cout << "  Параметры ключа: shift (0-255).\n";
    cout << "  Внимание: обеспечивает минимальную защиту, только для ознакомления.\n";
    cout << "\n";
    cout << "ChaCha20\n";
    cout << "  Поточный шифр ChaCha20. Использует ключ (32 байта), nonce (12 байт)\n";
    cout << "  и счётчик (4 байта). Размер входных и выходных данных совпадает.\n";
    cout << "  При файловом шифровании счётчик автоматически увеличивается\n";
    cout << "  между чанками. Размер чанка — 4096 байт.\n";
    cout << "\n";

    cout << "\033[31mФОРМАТ КЛЮЧЕВЫХ ФАЙЛОВ\033[0m\n";
    cout << "\n";
    cout << "Все ключевые файлы имеют бинарный формат. Первые 8 байт — идентификатор\n";
    cout << "алгоритма (uint64_t):\n";
    cout << "  1 — RSA\n";
    cout << "  2 — Шаммир\n";
    cout << "  3 — Эль-Гамаль\n";
    cout << "  4 — Цезарь\n";
    cout << "  5 — ChaCha20\n";
    cout << "\n";
    cout << "Далее следуют параметры ключа (каждый как uint64_t):\n";
    cout << "  RSA:       [id] moduleValue, publicKey, privateKey (24 байта данных)\n";
    cout << "  Шаммир:    [id] primeValue, caValue, cbValue, daValue, dbValue (40 байт данных)\n";
    cout << "  Эль-Гамаль:   [id] primeModulus, generatorValue, publicKey, privateKey (32 байта данных)\n";
    cout << "  Цезарь:    [id] shift (8 байт данных)\n";
    cout << "  ChaCha20:  [id] counter, key[32], nonce[12] (48 байт данных)\n";
    cout << "\n";

    cout << "\033[31mПРИМЕРЫ ИСПОЛЬЗОВАНИЯ\033[0m\n";
    cout << "\n";
    cout << "Генерация ключа:\n";
    cout << "  ./app -m generate-key -a rsa -k rsa_key.bin\n";
    cout << "  ./app --mode generate-key --algorithm shamir --key shamir_key.bin\n";
    cout << "\n";
    cout << "Шифрование файла:\n";
    cout << "  ./app -m encrypt -a rsa -i plain.txt -o cipher.bin -k rsa_key.bin\n";
    cout << "\n";
    cout << "Расшифрование файла:\n";
    cout << "  ./app -m decrypt -a rsa -i cipher.bin -o decrypted.txt -k rsa_key.bin\n";
    cout << "\n";
    cout << "Шифрование текста (ввод с консоли):\n";
    cout << "  ./app -m encrypt -a caesar --text -k caesar_key.bin\n";
    cout << "  Программа выведет \"> \" и ожидает ввод строки. Результат — в HEX.\n";
    cout << "\n";
    cout << "Расшифрование текста (ввод HEX):\n";
    cout << "  ./app -m decrypt -a caesar --text -k caesar_key.bin\n";
    cout << "  Программа ожидает ввод HEX-строки. Результат — расшифрованный текст.\n";
    cout << "\n";
    cout << "Интерактивный режим:\n";
    cout << "  ./app\n";
    cout << "  > --help\n";
    cout << "  > --mode generate-key --algorithm rsa --key my_key.bin\n";
    cout << "  > --mode encrypt --algorithm rsa --input f.txt --output f.enc --key my_key.bin\n";
    cout << "  > exit\n";
    cout << "\n";

    cout << "\033[31mФОРМАТ ВХОДНЫХ/ВЫХОДНЫХ ДАННЫХ\033[0m\n";
    cout << "\n";
    cout << "  При шифровании/расшифровании файлов (--input/--output) данные\n";
    cout << "  читаются и записываются в бинарном режиме.\n";
    cout << "\n";
    cout << "  При работе с текстом (--text):\n";
    cout << "    encrypt: вход — строка в кодировке UTF-8, выход — HEX-строка\n";
    cout << "    decrypt: вход — HEX-строка, выход — строка в кодировке UTF-8\n";
    cout << "\n";

    cout << "\033[31mКОДЫ ОШИБОК\033[0m\n";
    cout << "\n";
    cout << "  0 — Success (успех)\n";
    cout << "  1 — InvalidInput (некорректные аргументы)\n";
    cout << "  2 — FileOpenError (не удалось открыть файл)\n";
    cout << "  3 — FileReadError (не удалось прочитать файл)\n";
    cout << "  4 — FileWriteError (не удалось записать файл)\n";
    cout << "  5 — KeyError (ошибка ключа)\n";
    cout << "  6 — CryptoError (ошибка шифрования/расшифрования)\n";
    cout << "  7 — BufferTooSmall (недостаточный размер буфера)\n";
    cout << "      UnknownError (неизвестная ошибка)\n";
    cout << "\n";

    cout << "\033[31mЗАМЕЧАНИЯ\033[0m\n";
    cout << "\n";
    cout << "  - Алгоритмы реализованы в отдельных\n";
    cout << "    динамических библиотеках (.so).\n";
    cout << "  - Для ChaCha20 размер чанка при потоковой обработке — 4096 байт.\n";
    cout << "  - Счётчик ChaCha20 автоматически увеличивается между чанками.\n";
    cout << "  - Алгоритмы RSA и Шаммир расшифровывают данные блоками по 8 байт.\n";
    cout << "  - Эль-Гамаль оперирует блоками по 16 байт (два uint64_t).\n";
    cout << "  - Цезарь сдвигает каждый байт на shift (mod 256).\n";
    cout << "\n";
}
