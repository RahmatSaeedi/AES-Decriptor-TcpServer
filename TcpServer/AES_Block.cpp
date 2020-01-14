#include "AES.h"


void AES::AES_Encrypt_Block(uint8_t* message, AES_Type keyLength) {
	//Set Up
	switch (keyLength) {
	case AES_Type::AES_128:
		maxNumberOfRounds = 10;
		break;
	case AES_Type::AES_192:
		maxNumberOfRounds = 12;
		break;
	case AES_Type::AES_256:
		maxNumberOfRounds = 14;
		break;
	default:
		return;
	}

	state = &message[0];


	//Key Expansion performed outside 
	//KeyExpansion(key);


	//Initial Round
	AddRoundKey(expandedKeys);

	//Rounds
	for (uint8_t round = 1; round < maxNumberOfRounds; round++) {
		SubBytes();
		ShiftRows();
		MixColumns();
		AddRoundKey(expandedKeys + (uint64_t) 16 * round);
	}

	//Final Round
	SubBytes();
	ShiftRows();
	AddRoundKey(expandedKeys + (uint64_t) 16 * maxNumberOfRounds);

}
void AES::AES_Decrypt_Block(uint8_t* message, AES_Type keyLength) {
	//Set Up
	switch (keyLength) {
	case AES_Type::AES_128:
		maxNumberOfRounds = 10;
		break;
	case AES_Type::AES_192:
		maxNumberOfRounds = 12;
		break;
	case AES_Type::AES_256:
		maxNumberOfRounds = 14;
		break;
	default:
		return;
	}
	state = &message[0];

	//Key Expansion performed outside 
	//KeyExpansion(key);


	//Initial Round
	AddRoundKey(expandedKeys + (uint64_t) maxNumberOfRounds * 16);
	InverseShiftRows();
	InverseSubByte();
	//Rounds
	for (uint8_t round = (maxNumberOfRounds - 1); round > 0; round--) {
		AddRoundKey(expandedKeys + (uint64_t) round * 16);
		InverseMixColumns();
		InverseShiftRows();
		InverseSubByte();
	}

	//Final Round
	AddRoundKey(expandedKeys);

}
