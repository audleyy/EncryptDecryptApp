#include "ErrorText.h"

string GetErrorText(ErrorCode errorCode) {
    string text;
    switch (errorCode) {
        case Success:
            text = "Ошибок нет";
            break;
        case InvalidInput:
            text = "Некорректные входные данные";
            break;
        case FileOpenError:
            text = "Не удалось открыть файл";
            break;
        case FileReadError:
            text = "Не удалось прочитать файл";
            break;
        case FileWriteError:
            text = "Не удалось записать файл";
            break;
        case KeyError:
            text = "Ошибка ключа";
            break;
        case CryptoError:
            text = "Ошибка шифрования или расшифрования";
            break;
        case BufferTooSmall:
            text = "Недостаточный размер буфера";
            break;
        default:
            text = "Неизвестная ошибка";
            break;
    }
    return text;
}