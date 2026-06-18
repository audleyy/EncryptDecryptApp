#include "ManualPages.h"

void PrintManMode() {
    cout << "NAME\n";
    cout << "     mode - выбор режима работы программы\n";
    cout << "\n";
    cout << "SYNOPSIS\n";
    cout << "     --mode generate-key\n";
    cout << "     --mode encrypt\n";
    cout << "     --mode decrypt\n";
    cout << "     -m generate-key\n";
    cout << "     -m encrypt\n";
    cout << "     -m decrypt\n";
    cout << "\n";
    cout << "DESCRIPTION\n";
    cout << "     Флаг --mode задает основное действие программы. Без этого флага\n";
    cout << "     команда считается некорректной, потому что программа должна понимать,\n";
    cout << "     что именно нужно выполнить: сгенерировать ключ, зашифровать данные\n";
    cout << "     или расшифровать данные.\n";
    cout << "\n";
    cout << "VALUES\n";
    cout << "     generate-key\n";
    cout << "             Генерирует ключ выбранного алгоритма и сохраняет его в файл,\n";
    cout << "             указанный через --key.\n";
    cout << "\n";
    cout << "     encrypt\n";
    cout << "             Шифрует файл или текст. Для файла нужны --input и --output.\n";
    cout << "             Для текста используется флаг --text.\n";
    cout << "\n";
    cout << "     decrypt\n";
    cout << "             Расшифровывает файл или HEX-строку. Для файла нужны --input\n";
    cout << "             и --output. Для текста используется флаг --text.\n";
    cout << "\n";
    cout << "EXAMPLES\n";
    cout << "     --mode generate-key --algorithm rsa --key rsa.bin\n";
    cout << "     --mode encrypt --algorithm chacha20 --input in.bin --output out.bin --key key.bin\n";
    cout << "     --mode decrypt --algorithm caesar --text --key caesar.bin\n";
    cout << "\n";
}

void PrintManAlgorithm() {
    cout << "NAME\n";
    cout << "     algorithm - выбор алгоритма шифрования\n";
    cout << "\n";
    cout << "SYNOPSIS\n";
    cout << "     --algorithm rsa|shamir|elgamal|caesar|chacha20\n";
    cout << "     -a rsa|shamir|elgamal|caesar|chacha20\n";
    cout << "\n";
    cout << "DESCRIPTION\n";
    cout << "     Флаг --algorithm выбирает алгоритм, для которого выполняется\n";
    cout << "     генерация ключа, шифрование или расшифрование.\n";
    cout << "\n";
    cout << "VALUES\n";
    cout << "     rsa       асимметричный алгоритм RSA\n";
    cout << "     shamir    трехпроходный протокол Шамира\n";
    cout << "     elgamal   алгоритм Эль-Гамаля\n";
    cout << "     caesar    учебный шифр Цезаря\n";
    cout << "     chacha20  потоковый шифр ChaCha20\n";
    cout << "\n";
}

void PrintManKey() {
    cout << "NAME\n";
    cout << "     key - путь к файлу ключа\n";
    cout << "\n";
    cout << "SYNOPSIS\n";
    cout << "     --key key.bin\n";
    cout << "     -k key.bin\n";
    cout << "\n";
    cout << "DESCRIPTION\n";
    cout << "     Флаг --key задает бинарный файл ключа. При generate-key файл\n";
    cout << "     создается. При encrypt/decrypt файл читается и проверяется по\n";
    cout << "     algorithm_id, чтобы ключ одного алгоритма не использовался другим.\n";
    cout << "\n";
}

void PrintManInputOutput() {
    cout << "NAME\n";
    cout << "     input, output - входной и выходной файлы\n";
    cout << "\n";
    cout << "SYNOPSIS\n";
    cout << "     --input input.bin --output output.bin\n";
    cout << "     -i input.bin -o output.bin\n";
    cout << "\n";
    cout << "DESCRIPTION\n";
    cout << "     Флаги используются для файлового encrypt/decrypt. Файлы открываются\n";
    cout << "     в бинарном режиме и обрабатываются частями по 4096 байт.\n";
    cout << "     Входной и выходной путь не должны совпадать.\n";
    cout << "\n";
}

void PrintManText() {
    cout << "NAME\n";
    cout << "     text - режим ввода текста из консоли\n";
    cout << "\n";
    cout << "SYNOPSIS\n";
    cout << "     --text\n";
    cout << "\n";
    cout << "DESCRIPTION\n";
    cout << "     При encrypt программа читает текст из консоли и выводит HEX.\n";
    cout << "     При decrypt программа ожидает HEX-строку и выводит восстановленный\n";
    cout << "     текст. Ввод может занимать несколько строк и завершается строкой\n";
    cout << "     exit_for_text. Данные шифруются как байты, поэтому поддерживаются любые\n";
    cout << "     языки при одинаковой кодировке ввода и вывода, например UTF-8.\n";
    cout << "\n";
}

bool PrintManualPage(const string& topic) {
    bool isPrinted = true;
    if (topic == "mode") {
        PrintManMode();
    } else if (topic == "algorithm") {
        PrintManAlgorithm();
    } else if (topic == "key") {
        PrintManKey();
    } else if (topic == "input" || topic == "output") {
        PrintManInputOutput();
    } else if (topic == "text") {
        PrintManText();
    } else {
        isPrinted = false;
    }
    return isPrinted;
}
