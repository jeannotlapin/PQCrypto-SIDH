/********************************************************************************************
* SIDH: an efficient supersingular isogeny cryptography library
*
* Abstract: benchmarking/testing isogeny-based key exchange SIDHp751
*********************************************************************************************/ 

#include <stdio.h>
#include <string.h>
#include "test_extras.h"
#include "sidh/P751_api.h"


#define SCHEME_NAME    "SIDHp751"

#define random_mod_order_A            random_mod_order_A_SIDHp751
#define random_mod_order_B            random_mod_order_B_SIDHp751
#define EphemeralKeyGeneration_A      EphemeralKeyGeneration_A_SIDHp751
#define EphemeralKeyGeneration_B      EphemeralKeyGeneration_B_SIDHp751
#define EphemeralSecretAgreement_A    EphemeralSecretAgreement_A_SIDHp751
#define EphemeralSecretAgreement_B    EphemeralSecretAgreement_B_SIDHp751

#define SIDH_SECRETKEYBYTES	SIDHp751_SECRETKEYBYTES
#define SIDH_PUBLICKEYBYTES	SIDHp751_PUBLICKEYBYTES
#define SIDH_BYTES		SIDHp751_SHAREDBYTES

#include "test_sidh.c"
