#ifndef PICO_HEADER_H
#define PICO_HEADER_H

/**
 * @file
 * Pico header format and definitions used in pico.
 */

#include "pico_errno.h"

// Define the magic string.
#define MAGIC (0x91c0)

// Define the version numbers.
#define VERSION_MAJOR 1
#define VERSION_MINOR 0

// Define the header types.  This is the only place you should
// need to worry with the size of header items other than the
// hash.
typedef uint16_t magic_t;
typedef uint16_t major_t;
typedef uint16_t minor_t;
typedef uint32_t offset_t;
typedef uint16_t keylen_t;

// Define header offsets.  Note that these are all compile-time
// constants.  The header must fit into a 32-bit address space.
#define MAGIC_POS 0
#define MAJOR_POS (MAGIC_POS + (uint32_t)sizeof(magic_t))
#define MINOR_POS (MAJOR_POS + (uint32_t)sizeof(major_t))
#define OFFSET_POS (MINOR_POS + (uint32_t)sizeof(minor_t))
#define HASH_POS (OFFSET_POS + (uint32_t)sizeof(offset_t))
#define HASH_LEN 16
#define KEYLEN_POS (HASH_POS + HASH_LEN)
#define KEY_POS (KEYLEN_POS + (uint32_t)sizeof(keylen_t))

// Re-package htonl, htons, ntohl, and ntohs to hide size issues.
#define NTOH(m_type, m_item) \
    (m_type)(sizeof(m_type) == 2 ? ntohs(m_item) : ntohl(m_item))
#define HTON(m_type, m_item) \
    (m_type)(sizeof(m_type) == 2 ? htons(m_item) : htonl(m_item))

/**
 * The Pico data structure.
 */
typedef struct {

    FILE * file;                //< Backing file stream.
    major_t major;              //< Version in header.
    minor_t minor;              //< Version in header.
    offset_t offset;            //< Zero-based offset to data.
    uint8_t hash[HASH_LEN];     //< Hash.
    bool hash_valid;            //< Whether the hash is valid.
    keylen_t key_length;        //< Key length.
    uint8_t * key;              //< Key.
    pico_errno errno;          //< Error code of last operation.
    char error_text[1024];      //< Error text.
    uint32_t md_length;         //< Reserved metadata length.
    size_t data_length;         //< Data length (unused).

} PICO;

#endif //PICO_HEADER_H
