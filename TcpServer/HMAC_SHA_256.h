#pragma once
#include <cstdint>
#include "SHA_256.h"

class HMAC_SHA_256
{
private:
	SHA_256 hasher;
public:
	char* HMAC_SHA256;
	HMAC_SHA_256(uint8_t*, uint32_t, uint8_t*, uint32_t);
};



HMAC_SHA_256::HMAC_SHA_256(uint8_t* key, uint32_t keyLengthInBytes, uint8_t* message, uint32_t messageLengthInBytes)
{
	char modifiedKey[64];
	char* ipad = new char[(uint64_t) 64 + messageLengthInBytes];
	char opad[64 + 32];
	uint64_t modifiedKeyLength;

	//Zero it out
	for (int i = 0; i < 64; i++) {
		modifiedKey[i] = 0x00;
	}

	if (keyLengthInBytes > 64) {
		hasher.Hash(key, keyLengthInBytes);
		strcpy_s((char*)modifiedKey, 32, hasher.Hash_as_character_array);
		modifiedKeyLength = 32;
	}
	else if (keyLengthInBytes < 64) {
		for (uint32_t i = 0; i < keyLengthInBytes; i++) {
			modifiedKey[i] = key[i];
		}
	}
	for (int i = 0; i < 64; i++) {
		ipad[i] = modifiedKey[i] ^ (0x36);
		opad[i] = modifiedKey[i] ^ (0x5c);
	}



	//append message to end of inner pad key
	for (uint32_t i = 0; i < messageLengthInBytes; i++) {
		ipad[64 + i] = message[i];
	}

	hasher.Hash((uint8_t*)ipad, 64 + messageLengthInBytes);

	//append hashed value to end of outter pad
	for (int i = 0; i < 32; i++) {
		opad[64 + i] = hasher.Hash_as_character_array[i];
	}

	hasher.Hash((uint8_t*)opad, 64 + 32);
	HMAC_SHA256 = hasher.Hash_as_character_array;


	delete[] ipad;
}