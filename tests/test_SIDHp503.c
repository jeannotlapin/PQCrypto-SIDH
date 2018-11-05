/********************************************************************************************
* SIDH: an efficient supersingular isogeny cryptography library
*
* Abstract: benchmarking/testing isogeny-based key exchange SIDHp503
*********************************************************************************************/ 

#include <stdio.h>
#include <string.h>
#include "test_extras.h"
#include "sidh/P503_api.h"


#define SCHEME_NAME    "SIDHp503"

#define random_mod_order_A            random_mod_order_A_SIDHp503
#define random_mod_order_B            random_mod_order_B_SIDHp503
#define EphemeralKeyGeneration_A      EphemeralKeyGeneration_A_SIDHp503
#define EphemeralKeyGeneration_B      EphemeralKeyGeneration_B_SIDHp503
#define EphemeralSecretAgreement_A    EphemeralSecretAgreement_A_SIDHp503
#define EphemeralSecretAgreement_B    EphemeralSecretAgreement_B_SIDHp503

#define SIDH_SECRETKEYBYTES	SIDHp503_SECRETKEYBYTES
#define SIDH_PUBLICKEYBYTES	SIDHp503_PUBLICKEYBYTES
#define SIDH_BYTES		SIDHp503_SHAREDBYTES

#include "test_sidh.c"
