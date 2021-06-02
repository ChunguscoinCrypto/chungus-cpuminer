// Copyright (c) 2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CRYPTO_COMMON_H
#define BITCOIN_CRYPTO_COMMON_H

#if defined(HAVE_CONFIG_H)
#include "bitcoin-config.h"
#endif

#include <stdint.h>
#include <assert.h>

//#include "sodium.h"

#if (defined(_WIN16) || defined(_WIN32) || defined(_WIN64)) && !defined(__WINDOWS__)

#	define __WINDOWS__

#endif

#if defined(__linux__) || defined(__CYGWIN__)

#	include <endian.h>

#elif defined(__APPLE__)

#	include <libkern/OSByteOrder.h>

#	define htobe16(x) OSSwapHostToBigInt16(x)
#	define htole16(x) OSSwapHostToLittleInt16(x)
#	define be16toh(x) OSSwapBigToHostInt16(x)
#	define le16toh(x) OSSwapLittleToHostInt16(x)

#	define htobe32(x) OSSwapHostToBigInt32(x)
#	define htole32(x) OSSwapHostToLittleInt32(x)
#	define be32toh(x) OSSwapBigToHostInt32(x)
#	define le32toh(x) OSSwapLittleToHostInt32(x)

#	define htobe64(x) OSSwapHostToBigInt64(x)
#	define htole64(x) OSSwapHostToLittleInt64(x)
#	define be64toh(x) OSSwapBigToHostInt64(x)
#	define le64toh(x) OSSwapLittleToHostInt64(x)

#	define __BYTE_ORDER    BYTE_ORDER
#	define __BIG_ENDIAN    BIG_ENDIAN
#	define __LITTLE_ENDIAN LITTLE_ENDIAN
#	define __PDP_ENDIAN    PDP_ENDIAN

#elif defined(__OpenBSD__)

#	include <sys/endian.h>

#elif defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__)

#	include <sys/endian.h>

#	define be16toh(x) betoh16(x)
#	define le16toh(x) letoh16(x)

#	define be32toh(x) betoh32(x)
#	define le32toh(x) letoh32(x)

#	define be64toh(x) betoh64(x)
#	define le64toh(x) letoh64(x)

#elif defined(__WINDOWS__)

#	include <winsock2.h>
#	include <sys/param.h>

#	if BYTE_ORDER == LITTLE_ENDIAN

#		define htobe16(x) htons(x)
#		define htole16(x) (x)
#		define be16toh(x) ntohs(x)
#		define le16toh(x) (x)

#		define htobe32(x) htonl(x)
#		define htole32(x) (x)
#		define be32toh(x) ntohl(x)
#		define le32toh(x) (x)

#		define htobe64(x) htonl(x)
#		define htole64(x) (x)
#		define be64toh(x) ntohl(x)
#		define le64toh(x) (x)

#	elif BYTE_ORDER == BIG_ENDIAN

		/* that would be xbox 360 */
#		define htobe16(x) (x)
#		define htole16(x) __builtin_bswap16(x)
#		define be16toh(x) (x)
#		define le16toh(x) __builtin_bswap16(x)

#		define htobe32(x) (x)
#		define htole32(x) __builtin_bswap32(x)
#		define be32toh(x) (x)
#		define le32toh(x) __builtin_bswap32(x)

#		define htobe64(x) (x)
#		define htole64(x) __builtin_bswap64(x)
#		define be64toh(x) (x)
#		define le64toh(x) __builtin_bswap64(x)

#	else

#		error byte order not supported

#	endif

#	define __BYTE_ORDER    BYTE_ORDER
#	define __BIG_ENDIAN    BIG_ENDIAN
#	define __LITTLE_ENDIAN LITTLE_ENDIAN
#	define __PDP_ENDIAN    PDP_ENDIAN

#else

#	error platform not supported

#endif

//#if defined(NDEBUG)
//# error "Bitcoin cannot be compiled without assertions."
//#endif

uint16_t static inline ReadLE16(const unsigned char* ptr)
{
    return le16toh(*((uint16_t*)ptr));
}

uint32_t static inline ReadLE32(const unsigned char* ptr)
{
    return le32toh(*((uint32_t*)ptr));
}

uint64_t static inline ReadLE64(const unsigned char* ptr)
{
    return le64toh(*((uint64_t*)ptr));
}

void static inline WriteLE16(unsigned char* ptr, uint16_t x)
{
    *((uint16_t*)ptr) = htole16(x);
}

void static inline WriteLE32(unsigned char* ptr, uint32_t x)
{
    *((uint32_t*)ptr) = htole32(x);
}

void static inline WriteLE64(unsigned char* ptr, uint64_t x)
{
    *((uint64_t*)ptr) = htole64(x);
}

uint32_t static inline ReadBE32(const unsigned char* ptr)
{
    return be32toh(*((uint32_t*)ptr));
}

uint64_t static inline ReadBE64(const unsigned char* ptr)
{
    return be64toh(*((uint64_t*)ptr));
}

void static inline WriteBE32(unsigned char* ptr, uint32_t x)
{
    *((uint32_t*)ptr) = htobe32(x);
}

void static inline WriteBE64(unsigned char* ptr, uint64_t x)
{
    *((uint64_t*)ptr) = htobe64(x);
}

/*int inline init_and_check_sodium()
{
    if (sodium_init() == -1) {
        return -1;
    }

    // What follows is a runtime test that ensures the version of libsodium
    // we're linked against checks that signatures are canonical (s < L).
    const unsigned char message[1] = { 0 };

    unsigned char pk[crypto_sign_PUBLICKEYBYTES];
    unsigned char sk[crypto_sign_SECRETKEYBYTES];
    unsigned char sig[crypto_sign_BYTES];

    crypto_sign_keypair(pk, sk);
    crypto_sign_detached(sig, NULL, message, sizeof(message), sk);

    assert(crypto_sign_verify_detached(sig, message, sizeof(message), pk) == 0);

    // Copied from libsodium/crypto_sign/ed25519/ref10/open.c
    static const unsigned char L[32] =
      { 0xed, 0xd3, 0xf5, 0x5c, 0x1a, 0x63, 0x12, 0x58,
        0xd6, 0x9c, 0xf7, 0xa2, 0xde, 0xf9, 0xde, 0x14,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 };

    // Add L to S, which starts at sig[32].
    unsigned int s = 0;
    for (size_t i = 0; i < 32; i++) {
        s = sig[32 + i] + L[i] + (s >> 8);
        sig[32 + i] = s & 0xff;
    }

    assert(crypto_sign_verify_detached(sig, message, sizeof(message), pk) != 0);

    return 0;
}*/

#endif // BITCOIN_CRYPTO_COMMON_H
