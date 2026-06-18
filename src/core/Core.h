#ifndef CORE_H
#define CORE_H

#include "../common/CommonTypes.h"
#include "DllProcessor.h"
#include "StreamProcessor.h"
#include "../../libs/algorithms/RsaKeygen/RsaKeygen.h"
#include "../../libs/algorithms/ShamirKeygen/ShamirKeygen.h"
#include "../../libs/algorithms/ElGamalKeygen/ElGamalKeygen.h"
#include "../../libs/algorithms/CaesarKeygen/CaesarKeygen.h"
#include "../../libs/algorithms/ChaCha20Keygen/ChaCha20Keygen.h"
#include "../../libs/helpers/ConvertUtils.h"
#include "../../libs/helpers/KeyFile/KeyFile.h"
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

ErrorCode ClassifyRuntimeError(const runtime_error& error);
void EncryptTextByOptions(const CoreOptions& options);
void DecryptTextByOptions(const CoreOptions& options);
ErrorCode GenerateKeyByOptions(const CoreOptions& options);
ErrorCode EncryptByOptions(const CoreOptions& options);
ErrorCode DecryptByOptions(const CoreOptions& options);

ErrorCode RunCore(const CoreOptions& options);

#endif
