/********************************************************************************************
* SIDH: an efficient supersingular isogeny cryptography library
*
* Abstract: benchmarking/testing isogeny-based key encapsulation mechanism SIKEp751
*********************************************************************************************/ 

#include <stdio.h>
#include <string.h>
#include "test_extras.h"
#include "sidh/P751_api.h"


#define SCHEME_NAME    "SIKEp751"

#define crypto_kem_keypair            crypto_kem_keypair_SIKEp751
#define crypto_kem_enc                crypto_kem_enc_SIKEp751
#define crypto_kem_dec                crypto_kem_dec_SIKEp751

#define CRYPTO_SECRETKEYBYTES	SIKEp751_SECRETKEYBYTES
#define CRYPTO_PUBLICKEYBYTES	SIKEp751_PUBLICKEYBYTES
#define CRYPTO_BYTES		SIKEp751_SHAREDBYTES
#define CRYPTO_CIPHERTEXTBYTES	SIKEp751_CIPHERTEXTBYTES

#include "test_sike.c"
