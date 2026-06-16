#include "ChaCha20Context.h"
#include "ChaCha20Core.h"
#include <cstring>

static const uint32_t SIGMA[4] = {
    0x61707865u, 0x3320646eu,
    0x79622d32u, 0x6b206574u
};

ChaCha20Context::ChaCha20Context()
    : buffer_pos(CHACHA20_BLOCK_SIZE)
{
    memset(state,  0, sizeof(state));
    memset(buffer, 0, sizeof(buffer));
}

ChaCha20Context::~ChaCha20Context() {
    ChaCha20Clear(*this);
}

void ChaCha20Init(
    ChaCha20Context& ctx,
    const uint8_t*   key,
    const uint8_t*   nonce,
    uint32_t         counter)
{
    memcpy(ctx.state, SIGMA, sizeof(SIGMA));

    for (int i = 0; i < 8; i++)
        ctx.state[4 + i] = load32LE(key + i * 4);

    ctx.state[12] = counter;

    for (int i = 0; i < 3; i++)
        ctx.state[13 + i] = load32LE(nonce + i * 4);

    ctx.buffer_pos = CHACHA20_BLOCK_SIZE;
}

void ChaCha20NextBlock(ChaCha20Context& ctx) {
    if (ctx.state[12] == CHACHA20_MAX_COUNTER)
        throw std::overflow_error(
            "ChaCha20: переполнение счётчика блоков"
        );

    uint32_t working[16];
    memcpy(working, ctx.state, sizeof(working));

    for (int round = 0; round < 10; round++) {
        quarterRound(working[0], working[4], working[8],  working[12]);
        quarterRound(working[1], working[5], working[9],  working[13]);
        quarterRound(working[2], working[6], working[10], working[14]);
        quarterRound(working[3], working[7], working[11], working[15]);
        quarterRound(working[0], working[5], working[10], working[15]);
        quarterRound(working[1], working[6], working[11], working[12]);
        quarterRound(working[2], working[7], working[8],  working[13]);
        quarterRound(working[3], working[4], working[9],  working[14]);
    }

    for (int i = 0; i < 16; i++)
        store32LE(ctx.buffer + i * 4, working[i] + ctx.state[i]);

    ctx.buffer_pos = 0;
    ctx.state[12]++;
}

void ChaCha20Xor(
    ChaCha20Context& ctx,
    const uint8_t*   input,
    uint8_t*         output,
    size_t           length)
{
    for (size_t i = 0; i < length; i++) {
        if (ctx.buffer_pos >= CHACHA20_BLOCK_SIZE)
            ChaCha20NextBlock(ctx);
        output[i] = input[i] ^ ctx.buffer[ctx.buffer_pos++];
    }
}

void ChaCha20Clear(ChaCha20Context& ctx) {
    volatile uint8_t* p =
        reinterpret_cast<volatile uint8_t*>(&ctx);
    for (size_t i = 0; i < sizeof(ctx); i++)
        p[i] = 0;
}

void ChaCha20Validate(
    const ByteVec& key,
    const ByteVec& nonce)
{
    if (key.size() != CHACHA20_KEY_SIZE)
        throw std::invalid_argument(
            "ChaCha20: ключ должен быть 32 байта, получено: "
            + std::to_string(key.size())
        );
    if (nonce.size() != CHACHA20_NONCE_SIZE)
        throw std::invalid_argument(
            "ChaCha20: nonce должен быть 12 байт, получено: "
            + std::to_string(nonce.size())
        );
}