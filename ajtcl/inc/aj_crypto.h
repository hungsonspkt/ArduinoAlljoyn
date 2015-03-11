#ifndef _AJ_CRYPTO_H
#define _AJ_CRYPTO_H

/**
 * @file aj_crypto.h
 * @defgroup aj_crypto Cryptographic Support
 * @{
 */
/******************************************************************************
 * Copyright (c) 2012-2014, AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "aj_target.h"
#include "aj_status.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Implements AES-CCM (Counter with CBC-MAC) encryption as described in RFC 3610. The message in
 * encrypted in place.
 *
 * @param key     The AES-128 encryption key
 * @param msg     The buffer containing the entire message that is to be encrypted, The buffer must
 *                have room at the end to append an authentication tag of length tagLen.
 * @param msgLen  The length of the entire message
 * @param hdrLen  The length of the header portion that will be authenticated but not encrypted
 * @param tagLen  The length of the authentication tag to be appended to the message
 * @param nonce   The nonce
 * @param nLen    The length of the nonce
 *
 * @return
 *         - AJ_OK if the CCM context is initialized
 *         - AJ_ERR_RESOURCES if the resources required are not available.
 */
AJ_Status AJ_Encrypt_CCM(const uint8_t* key,
                         uint8_t* msg,
                         uint32_t msgLen,
                         uint32_t hdrLen,
                         uint8_t tagLen,
                         const uint8_t* nonce,
                         uint32_t nLen);

/**
 * Implements AES-CCM (Counter with CBC-MAC) decryption as described in RFC 3610. The message in
 * decrypted in place.
 *
 * @param key     The AES-128 encryption key
 * @param msg     The buffer containing the entire message to be decrypted.
 * @param msgLen  The length of the entire message, excluding the tag.
 * @param hdrLen  The length of the header portion that will be authenticated but not encrypted
 * @param tagLen  The length of the authentication tag to be appended to the message
 * @param nonce   The nonce
 * @param nLen    The length of the nonce
 *
 * @return
 *         - AJ_OK if the CCM context is initialized
 *         - AJ_ERR_RESOURCES if the resources required are not available.
 */
AJ_Status AJ_Decrypt_CCM(const uint8_t* key,
                         uint8_t* msg,
                         uint32_t msgLen,
                         uint32_t hdrLen,
                         uint8_t tagLen,
                         const uint8_t* nonce,
                         uint32_t nLen);

/**
 * A pseudo-random function for generation of keying material. This function uses AES-CCM to
 * as the MAC function.
 *
 * @param inputs  Array of input data blocks
 * @param lengths The lengths of input data blocks
 * @param count   The number of input data blocks
 * @param out     The buffer to receive the keying material
 * @param outLen  The amount of keying materail to be generated.
 *
 * @return
 *         - AJ_OK if the PRF ran succesfully
 *         - AJ_ERR_RESOURCES if the resources required are not available.
 */
AJ_Status AJ_Crypto_PRF(const uint8_t** inputs,
                        const uint8_t* lengths,
                        uint32_t count,
                        uint8_t* out,
                        uint32_t outLen);

/**
 * Return a string of randomly generated bytes.
 *
 * @param rand  Pointer to a buffer to return the random data
 * @param len   The number of random bytes to return.
 */
void AJ_RandBytes(uint8_t* rand, uint32_t len);

/**
 * Return a random hexadecimal string of the requested length
 *
 * @param rand   Pointer to a buffer to return the random data
 * @param bufLen The length of the buffer. The buffer must be at
 *               least (len * 2) + 1 bytes.
 * @param len    The length of the hexadecimal string
 *
 * @return        Return AJ_Status
 *               - AJ_OK if the string was converted
 *               - AJ_ERR_RESOURCES if the hexLen is too small to fit the converted string.
 */
AJ_Status AJ_RandHex(char* rand, uint32_t bufLen, uint32_t len);

/**
 * Enable AES allocating any resources required
 *
 * @param key  The key in case this is required
 */
void AJ_AES_Enable(const uint8_t* key);

/**
 * Disable AES freeing any resources that were allocated
 */
void AJ_AES_Disable(void);

/**
 * AES counter mode encryption/decryption. Note that in CTR mode encrytion is its own inverse.
 *
 * @param key  The AES encryption key
 * @param in   The data to encrypt
 * @param out  The encrypted data
 * @param len  The length of the input data, must be multiple of 16
 * @param ctr  Pointer to a 16 byte counter block
 */
void AJ_AES_CTR_128(const uint8_t* key, const uint8_t* in, uint8_t* out, uint32_t len, uint8_t* ctr);

/**
 * AES CCM mode encryption
 *
 * @param key  The AES encryption key
 * @param in   The data to encrypt
 * @param out  The encrypted data
 * @param len  The length of the input data, must be multiple of 16
 * @param iv   Pointer to a 16 byte initialization vector
 */
void AJ_AES_CBC_128_ENCRYPT(const uint8_t* key, const uint8_t* in, uint8_t* out, uint32_t len, uint8_t* iv);


/**
 * Encrypt a single 16 byte block using AES in ECB mode
 *
 * @param key  The AES encryption key
 * @param in   The data to encrypt
 * @param out  The encrypted data
 */
void AJ_AES_ECB_128_ENCRYPT(const uint8_t* key, const uint8_t* in, uint8_t* out);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif