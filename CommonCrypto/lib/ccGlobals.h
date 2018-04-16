/*
 * Copyright (c) 2012 Apple Inc. All Rights Reserved.
 * 
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*
 *  ccGlobals.h - CommonCrypto global DATA
 */

#ifndef CCGLOBALS_H
#define CCGLOBALS_H

#include <corecrypto/ccdh.h>
#include "CommonCryptorPriv.h"
#include "CommonRandomPriv.h"
#include "../libcn/basexx.h"

#include "../libcn/crc.h"
#include <CommonNumerics/CommonCRC.h>

#if defined(_WIN32)
    #define _LIBCOMMONCRYPTO_HAS_ALLOC_ONCE 0
#elif __has_include(<os/alloc_once_private.h>)
        #include <os/alloc_once_private.h>
        #if defined(OS_ALLOC_ONCE_KEY_LIBCOMMONCRYPTO)
            #define _LIBCOMMONCRYPTO_HAS_ALLOC_ONCE 1
        #endif
#else
    #define _LIBCOMMONCRYPTO_HAS_ALLOC_ONCE 0
#endif

#define CN_SUPPORTED_CRCS kCN_CRC_64_ECMA_182+1
#define CN_STANDARD_BASE_ENCODERS kCNEncodingBase16+1

struct cc_globals_s {
    // CommonCRC.c
    dispatch_once_t crc_init;
    crcInfo crcSelectionTab[CN_SUPPORTED_CRCS];
    
    dispatch_once_t basexx_init;
    BaseEncoderFrame encoderTab[CN_STANDARD_BASE_ENCODERS];

	// CommonDigest.c
	dispatch_once_t digest_info_init;
	const struct ccdigest_info **digest_info;
	
	// CommonRandom.c
	dispatch_once_t dev_random_init;
	dispatch_once_t drbg_init;
    
    ccInternalRandom dev_random;
    ccInternalRandom drbg;
	
    // CommonCryptor.c
    cipherMode cipherModeTab[CC_SUPPORTED_CIPHERS][CC_DIRECTIONS];

};
typedef struct cc_globals_s *cc_globals_t;

__attribute__((__pure__))
static inline cc_globals_t
_cc_globals(void) {
#if _LIBCOMMONCRYPTO_HAS_ALLOC_ONCE
    return (cc_globals_t) os_alloc_once(OS_ALLOC_ONCE_KEY_LIBCOMMONCRYPTO,
                                        sizeof(struct cc_globals_s),
                                        NULL);
#else
    extern struct cc_globals_s cc_globals_storage;
    return &cc_globals_storage;
#endif
}



#endif /* CCGLOBALS_H */