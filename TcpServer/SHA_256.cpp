#include "SHA_256.h"

uint32_t SHA_256::rotateRight(uint32_t in, uint8_t numberOfBits) {
	return 	((uint32_t)in >> numberOfBits) | ((uint32_t)in << (32 - numberOfBits));
}

//Hashes are valid as long as message ends in an increment of 8 bits
void SHA_256::compute(uint8_t* message, uint32_t numberOfBytes)
{
	//Initialize H & K
	for (int i = 0; i < 8; i++) {
		h[i] = h_ini[i];
	}
	for (int i = 0; i < 64; i++) {
		k[i] = k_ini[i];
	}


	//allocating multiple of 512 bits
	uint32_t paddedArraySize = numberOfBytes + 1 + 8 + (64 - ((numberOfBytes + 1 + 8) % 64));
	uint32_t nZeroBytes = paddedArraySize - numberOfBytes - 8 - 1;
	Data = new uint8_t[paddedArraySize];


	//copying the message
	for (uint64_t i = 0; i < numberOfBytes; i++) {
		Data[i] = message[i];
	}
	//appending a single '1' bit and padding with with K 0x0000 bits
	//adding a byte of 0b10000000
	Data[numberOfBytes] = 0x80;
	for (uint64_t i = (uint64_t) numberOfBytes + 1; i < ((uint64_t)numberOfBytes + 1 + nZeroBytes); i++) {
		Data[i] = 0;
	}
	//Appending original length
	int64_t numberOfBits = numberOfBytes << 3;
	Data[paddedArraySize - 8] = (numberOfBits >> 8 * 7) & 0xFF;
	Data[paddedArraySize - 7] = (numberOfBits >> 8 * 6) & 0xFF;
	Data[paddedArraySize - 6] = (numberOfBits >> 8 * 5) & 0xFF;
	Data[paddedArraySize - 5] = (numberOfBits >> 8 * 4) & 0xFF;
	Data[paddedArraySize - 4] = (numberOfBits >> 8 * 3) & 0xFF;
	Data[paddedArraySize - 3] = (numberOfBits >> 8 * 2) & 0xFF;
	Data[paddedArraySize - 2] = (numberOfBits >> 8 * 1) & 0xFF;
	Data[paddedArraySize - 1] = (numberOfBits >> 8 * 0) & 0xFF;

	for (uint64_t i = 0; i < (paddedArraySize / 64); i++) {
		//copy 512 bits content to message schedual array
		for (int j = 0; j < 16; j++) {
			scheduleArray[j] = (
				(uint32_t)Data[i * 64 + j * 4 + 0] << 8 * 3) |
				((uint32_t)Data[i * 64 + j * 4 + 1] << 8 * 2) |
				((uint32_t)Data[i * 64 + j * 4 + 2] << 8 * 1) |
				((uint32_t)Data[i * 64 + j * 4 + 3]);
		}


		//Extend the 16 word into the remainning 48 words
		for (int j = 16; j < 64; j++) {
			s0 = rotateRight(scheduleArray[j - 15], 7) ^ rotateRight(scheduleArray[j - 15], 18) ^ (scheduleArray[j - 15] >> 3);
			s1 = rotateRight(scheduleArray[j - 2], 17) ^ rotateRight(scheduleArray[j - 2], 19) ^ (scheduleArray[j - 2] >> 10);
			scheduleArray[j] = scheduleArray[j - 16] + s0 + scheduleArray[j - 7] + s1;
		}

		//working variables to hash values
		for (int j = 0; j < 8; j++) {
			state[j] = h[j];
		}

		//comperession function
		for (int j = 0; j < 64; j++) {
			s1 = rotateRight(state[4], 6) ^ rotateRight(state[4], 11) ^ rotateRight(state[4], 25);
			ch = (state[4] & state[5]) ^ (~state[4] & state[6]);
			temp1 = state[7] + s1 + ch + k[j] + scheduleArray[j];

			s0 = rotateRight(state[0], 2) ^ rotateRight(state[0], 13) ^ rotateRight(state[0], 22);
			ch = (state[0] & state[1]) ^ (state[0] & state[2]) ^ (state[1] & state[2]);
			temp2 = s0 + ch;

			state[7] = state[6];
			state[6] = state[5];
			state[5] = state[4];
			state[4] = state[3] + temp1;
			state[3] = state[2];
			state[2] = state[1];
			state[1] = state[0];
			state[0] = temp1 + temp2;
		}

		// add compression result to the hash
		for (int j = 0; j < 8; j++) {
			h[j] += state[j];
		}
	}
}

void SHA_256::assignResults() {
	Hash_as_uint32_t_array = h;

	for (int i = 0; i < 8; i++) {
		Hash_as_character_array[4 * i + 0] = (h[i] >> 8 * 3) & 0xFF;
		Hash_as_character_array[4 * i + 1] = (h[i] >> 8 * 2) & 0xFF;
		Hash_as_character_array[4 * i + 2] = (h[i] >> 8 * 1) & 0xFF;
		Hash_as_character_array[4 * i + 3] = (h[i] >> 8 * 0) & 0xFF;
	}
	Hash_as_character_array[32] = 0x00;
}


SHA_256::SHA_256(string message)
{
	compute((uint8_t*)message.c_str(), message.size());
	assignResults();
}

void SHA_256::Hash(string message) {
	compute((uint8_t*)message.c_str(), message.size());
	assignResults();
}

SHA_256::SHA_256(uint8_t* message, uint32_t numberOfBytes)
{
	compute(message, numberOfBytes);
	assignResults();
}

void SHA_256::Hash(uint8_t* message, uint32_t numberOfBytes) {
	compute(message, numberOfBytes);
	assignResults();
}

SHA_256::~SHA_256() {
	delete[] Data;
}