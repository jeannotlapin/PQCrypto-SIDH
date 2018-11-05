/********************************************************************************************
* SIDH: an efficient supersingular isogeny cryptography library
*
* Abstract: benchmarking/testing isogeny-based key encapsulation mechanism SIKEp503
*********************************************************************************************/ 

#include <stdio.h>
#include <string.h>
#include "test_extras.h"
#include "sidh/P503_api.h"


#define SCHEME_NAME    "SIKEp503"

#define crypto_kem_keypair            crypto_kem_keypair_SIKEp503
#define crypto_kem_enc                crypto_kem_enc_SIKEp503
#define crypto_kem_dec                crypto_kem_dec_SIKEp503

#define CRYPTO_SECRETKEYBYTES	SIKEp503_SECRETKEYBYTES
#define CRYPTO_PUBLICKEYBYTES	SIKEp503_PUBLICKEYBYTES
#define CRYPTO_BYTES		SIKEp503_SHAREDBYTES
#define CRYPTO_CIPHERTEXTBYTES	SIKEp503_CIPHERTEXTBYTES

#include "test_sike.c"
