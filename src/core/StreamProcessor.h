#ifndef STREAM_PROCESSOR_H
#define STREAM_PROCESSOR_H

#include "../common/CommonTypes.h"

void EncryptRsaFileByStream(const CoreOptions& options);
void DecryptRsaFileByStream(const CoreOptions& options);

void EncryptShamirFileByStream(const CoreOptions& options);
void DecryptShamirFileByStream(const CoreOptions& options);

void EncryptElGamalFileByStream(const CoreOptions& options);
void DecryptElGamalFileByStream(const CoreOptions& options);

void EncryptCaesarFileByStream(const CoreOptions& options);
void DecryptCaesarFileByStream(const CoreOptions& options);

void EncryptChaCha20FileByStream(const CoreOptions& options);
void DecryptChaCha20FileByStream(const CoreOptions& options);

#endif
