#include "AES.h"

void AES::AES_Encrypt_CBC(uint8_t* message, uint64_t messageLength, uint8_t* Initialization_Vector, AES_Type keyLength) {

	//XOR with IV
	for (int i = 0; i < 16; i++)
		message[i] ^= Initialization_Vector[i];

	AES_Encrypt_Block(message, keyLength);

	for (uint64_t encryptedBytes = 16; encryptedBytes < messageLength; encryptedBytes += 16) {
		for (uint64_t i = 0; i < 16; i++)
			message[encryptedBytes + i] ^= Initialization_Vector[encryptedBytes - 16 + i];

		AES_Encrypt_Block(message + encryptedBytes, keyLength);
	}


}
void AES::AES_Decrypt_CBC(uint8_t* message, unsigned int messageLengthInBytes, uint8_t* Initialization_Vector, AES_Type keyLength) {
	if (Initialization_Vector == message) {
		return;
	}



	uint8_t* cipherText = new uint8_t[messageLengthInBytes];
	for (unsigned int i = 0; i < messageLengthInBytes; i++)
		cipherText[i] = message[i];


	AES_Decrypt_Block(message, keyLength);
	//XOR with IV
	for (uint8_t i = 0; i < 16; i++)
		message[i] ^= Initialization_Vector[i];


	for (uint64_t decryptedBytes = 16; decryptedBytes < messageLengthInBytes; decryptedBytes += 16) {
		AES_Decrypt_Block(&message[decryptedBytes], keyLength);

		for (uint8_t i = 0; i < 16; i++)
			message[decryptedBytes + i] ^= cipherText[decryptedBytes - 16 + i];

	}

	delete[] cipherText;
}