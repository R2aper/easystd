#ifndef HASH_H
#define HASH_H

/*
This file contain SHA256 hash function
It was inspired by this repo:
https://github.com/LekKit/sha256
*/

#include <stddef.h>
#include <stdint.h>

#define SHA256_HASH_SIZE 32
#define SHA256_HEX_SIZE ((SHA256_HASH_SIZE * 2) + 1)

typedef struct sha256_buff {
  uint64_t data_size;
  uint32_t h[8];
  uint8_t last_chunk[64];
  uint8_t chunk_size;

} sha256_buff;

// Streaming API
void sha256_init(sha256_buff *buff);
void sha256_update(sha256_buff *buff, const void *data, size_t size);
void sha256_finalize(sha256_buff *buff);
void sha256_read(const sha256_buff *buff, uint8_t out_hash[SHA256_HASH_SIZE]);

// One-shot API
void sha256_hash(const void *data, size_t size, uint8_t out_hash[SHA256_HASH_SIZE]);
void sha256_hash_hex(const void *data, size_t size, char out_hex[SHA256_HEX_SIZE]);

#endif // HASH_H
