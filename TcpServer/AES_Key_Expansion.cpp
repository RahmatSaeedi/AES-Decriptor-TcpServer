#include "AES.h"

void AES::KeyExpansionCore(uint8_t* in, int i) {
	//Rotate Left & replace with substitution-box values
	uint8_t temp = in[0];
	in[0] = Rijndael_substitution_box[in[1]];
	in[1] = Rijndael_substitution_box[in[2]];
	in[2] = Rijndael_substitution_box[in[3]];
	in[3] = Rijndael_substitution_box[temp];

	//RCon
	in[0] ^= Rcon[i];
}

void AES::KeyExpansion_AES_128(uint8_t* inputKey) {
	//Original 16-byte Key as the first key
	for (uint8_t i = 0; i < 16; i++) {
		expandedKeys[i] = inputKey[i];
	}

	uint16_t bytesGenerated = 16;
	uint8_t rConIterationNumber = 1;
	uint8_t temp[4];

	//Generate 4 more bytes
	while (bytesGenerated < 176) {
		//Read the last 4 bytes of generated generated
		temp[0] = expandedKeys[bytesGenerated - 4];
		temp[1] = expandedKeys[bytesGenerated - 3];
		temp[2] = expandedKeys[bytesGenerated - 2];
		temp[3] = expandedKeys[bytesGenerated - 1];

		//Perform Core once every 16  byte is generated
		if ((bytesGenerated % 16) == 0) {
			KeyExpansionCore(temp, rConIterationNumber);
			rConIterationNumber++;
		}

		//XOR & store in ExpandedKeys
		expandedKeys[bytesGenerated] = expandedKeys[bytesGenerated - 16] ^ temp[0];
		expandedKeys[bytesGenerated + 1] = expandedKeys[bytesGenerated - 15] ^ temp[1];
		expandedKeys[bytesGenerated + 2] = expandedKeys[bytesGenerated - 14] ^ temp[2];
		expandedKeys[bytesGenerated + 3] = expandedKeys[bytesGenerated - 13] ^ temp[3];
		bytesGenerated += 4;
	}
	expandedKeysLength = 176;
}
void AES::KeyExpansion_AES_192(uint8_t* inputKey) {
	//Original 24-bytes of the Key left unchanged
	for (uint8_t i = 0; i < 24; i++) {
		expandedKeys[i] = inputKey[i];
	}

	uint16_t bytesGenerated = 24;
	uint8_t rConIterationNumber = 1;
	uint8_t temp[4];

	//Generate 4 more bytes
	while (bytesGenerated < 208) {
		//Read the last 4 bytes of generated generated
		temp[0] = expandedKeys[bytesGenerated - 4];
		temp[1] = expandedKeys[bytesGenerated - 3];
		temp[2] = expandedKeys[bytesGenerated - 2];
		temp[3] = expandedKeys[bytesGenerated - 1];

		//Perform Core once every 24  byte is generated
		if ((bytesGenerated % 24) == 0) {
			KeyExpansionCore(temp, rConIterationNumber);
			rConIterationNumber++;
		}

		//XOR & store in ExpandedKeys
		expandedKeys[bytesGenerated] = expandedKeys[bytesGenerated - 24] ^ temp[0];
		expandedKeys[bytesGenerated + 1] = expandedKeys[bytesGenerated - 23] ^ temp[1];
		expandedKeys[bytesGenerated + 2] = expandedKeys[bytesGenerated - 22] ^ temp[2];
		expandedKeys[bytesGenerated + 3] = expandedKeys[bytesGenerated - 21] ^ temp[3];
		bytesGenerated += 4;
	}
	expandedKeysLength = 208;
}
void AES::KeyExpansion_AES_256(uint8_t* inputKey) {
	//Original 24-bytes of the Key left unchanged
	for (uint8_t i = 0; i < 32; i++) {
		expandedKeys[i] = inputKey[i];
	}


	uint16_t bytesGenerated = 32;
	uint8_t rConIterationNumber = 1;
	uint8_t temp[4];

	//Generate 4 more bytes
	while (bytesGenerated < 240) {
		//Read the last 4 bytes of generated generated
		temp[0] = expandedKeys[bytesGenerated - 4];
		temp[1] = expandedKeys[bytesGenerated - 3];
		temp[2] = expandedKeys[bytesGenerated - 2];
		temp[3] = expandedKeys[bytesGenerated - 1];

		//Perform Core once every 32  byte is generated
		if ((bytesGenerated % 32) == 0) {
			KeyExpansionCore(temp, rConIterationNumber);
			rConIterationNumber++;
		}


		//Additional S-Box on bytes 16, 17, 18, 19 MOD32
		if (((bytesGenerated % 32) == 16)) {
			temp[0] = Rijndael_substitution_box[temp[0]];
			temp[1] = Rijndael_substitution_box[temp[1]];;
			temp[2] = Rijndael_substitution_box[temp[2]];;
			temp[3] = Rijndael_substitution_box[temp[3]];;
		}


		//XOR & store in ExpandedKeys
		expandedKeys[bytesGenerated] = expandedKeys[bytesGenerated - 32] ^ temp[0];
		expandedKeys[bytesGenerated + 1] = expandedKeys[bytesGenerated - 31] ^ temp[1];
		expandedKeys[bytesGenerated + 2] = expandedKeys[bytesGenerated - 30] ^ temp[2];
		expandedKeys[bytesGenerated + 3] = expandedKeys[bytesGenerated - 29] ^ temp[3];
		bytesGenerated += 4;
	}
	expandedKeysLength = 240;
}

void AES::KeyExpansion(uint8_t* inputKey, AES_Type keyLength) {
	switch (keyLength) {
	case AES_Type::AES_128:
		KeyExpansion_AES_128(inputKey);
		break;
	case AES_Type::AES_192:
		KeyExpansion_AES_192(inputKey);
		break;
	case AES_Type::AES_256:
		KeyExpansion_AES_256(inputKey);
		break;
	default:
		return;
	}
}