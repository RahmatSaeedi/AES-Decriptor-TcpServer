#include "AES.h"


uint8_t AES::MULx2(uint8_t v) {
	return (uint8_t)(v < 0x80 ? v << 1 : ((v << 1) ^ 0x1b));
}
uint8_t AES::MULx3(uint8_t v) {
	return (uint8_t)(MULx2(v) ^ v);
}
uint8_t AES::MULx4(uint8_t v) {
	return (uint8_t)MULx2(MULx2(v));
}
uint8_t AES::MULx8(uint8_t v) {
	return (uint8_t)MULx2(MULx2(MULx2(v)));
}
uint8_t AES::MULx9(uint8_t v) {
	return (uint8_t)(MULx8(v) ^ v);
}
uint8_t AES::MULxB(uint8_t v) {
	return (uint8_t)(MULx8(v) ^ MULx2(v) ^ v);
}
uint8_t AES::MULxD(uint8_t v) {
	return (uint8_t)(MULx8(v) ^ MULx4(v) ^ v);
}
uint8_t AES::MULxE(uint8_t v) {
	return (uint8_t)(MULx8(v) ^ MULx4(v) ^ MULx2(v));
}
void AES::SubBytes() {
	// Substituting 
	state[0] = Rijndael_substitution_box[state[0]];
	state[1] = Rijndael_substitution_box[state[1]];
	state[2] = Rijndael_substitution_box[state[2]];
	state[3] = Rijndael_substitution_box[state[3]];

	state[4] = Rijndael_substitution_box[state[4]];
	state[5] = Rijndael_substitution_box[state[5]];
	state[6] = Rijndael_substitution_box[state[6]];
	state[7] = Rijndael_substitution_box[state[7]];

	state[8] = Rijndael_substitution_box[state[8]];
	state[9] = Rijndael_substitution_box[state[9]];
	state[10] = Rijndael_substitution_box[state[10]];
	state[11] = Rijndael_substitution_box[state[11]];

	state[12] = Rijndael_substitution_box[state[12]];
	state[13] = Rijndael_substitution_box[state[13]];
	state[14] = Rijndael_substitution_box[state[14]];
	state[15] = Rijndael_substitution_box[state[15]];

}
void AES::InverseSubByte() {
	state[0] = Rijndael_inverse_substitution_box[state[0]];
	state[1] = Rijndael_inverse_substitution_box[state[1]];
	state[2] = Rijndael_inverse_substitution_box[state[2]];
	state[3] = Rijndael_inverse_substitution_box[state[3]];

	state[4] = Rijndael_inverse_substitution_box[state[4]];
	state[5] = Rijndael_inverse_substitution_box[state[5]];
	state[6] = Rijndael_inverse_substitution_box[state[6]];
	state[7] = Rijndael_inverse_substitution_box[state[7]];

	state[8] = Rijndael_inverse_substitution_box[state[8]];
	state[9] = Rijndael_inverse_substitution_box[state[9]];
	state[10] = Rijndael_inverse_substitution_box[state[10]];
	state[11] = Rijndael_inverse_substitution_box[state[11]];

	state[12] = Rijndael_inverse_substitution_box[state[12]];
	state[13] = Rijndael_inverse_substitution_box[state[13]];
	state[14] = Rijndael_inverse_substitution_box[state[14]];
	state[15] = Rijndael_inverse_substitution_box[state[15]];
}
void AES::ShiftRows() {
	uint8_t temp;

	//Row 1, not shifted

	//Row 2, shifted 1 left
	temp = state[1];
	state[1] = state[5];
	state[5] = state[9];
	state[9] = state[13];
	state[13] = temp;

	//Row 3, shifted 2 left
	temp = state[2];
	state[2] = state[10];
	state[10] = temp;

	temp = state[6];
	state[6] = state[14];
	state[14] = temp;

	//Row 4, shifted 3 left
	temp = state[3];
	state[3] = state[15];
	state[15] = state[11];
	state[11] = state[7];
	state[7] = temp;
}
void AES::InverseShiftRows() {
	uint8_t temp;

	//Row 1, not shifted

	//Row 2, shifted 1 right
	temp = state[1];
	state[1] = state[13];
	state[13] = state[9];
	state[9] = state[5];
	state[5] = temp;

	//Row 3, shifted 2 right
	temp = state[2];
	state[2] = state[10];
	state[10] = temp;

	temp = state[6];
	state[6] = state[14];
	state[14] = temp;

	//Row 4, shifted 3 right
	temp = state[3];
	state[3] = state[7];
	state[7] = state[11];
	state[11] = state[15];
	state[15] = temp;
}
void AES::MixColumns() {
	uint8_t temp[16];
	temp[0] = (uint8_t)(MULx2(state[0]) ^ MULx3(state[1]) ^ state[2] ^ state[3]);
	temp[1] = (uint8_t)(state[0] ^ MULx2(state[1]) ^ MULx3(state[2]) ^ state[3]);
	temp[2] = (uint8_t)(state[0] ^ state[1] ^ MULx2(state[2]) ^ MULx3(state[3]));
	temp[3] = (uint8_t)(MULx3(state[0]) ^ state[1] ^ state[2] ^ MULx2(state[3]));

	temp[4] = (uint8_t)(MULx2(state[4]) ^ MULx3(state[5]) ^ state[6] ^ state[7]);
	temp[5] = (uint8_t)(state[4] ^ MULx2(state[5]) ^ MULx3(state[6]) ^ state[7]);
	temp[6] = (uint8_t)(state[4] ^ state[5] ^ MULx2(state[6]) ^ MULx3(state[7]));
	temp[7] = (uint8_t)(MULx3(state[4]) ^ state[5] ^ state[6] ^ MULx2(state[7]));

	temp[8] = (uint8_t)(MULx2(state[8]) ^ MULx3(state[9]) ^ state[10] ^ state[11]);
	temp[9] = (uint8_t)(state[8] ^ MULx2(state[9]) ^ MULx3(state[10]) ^ state[11]);
	temp[10] = (uint8_t)(state[8] ^ state[9] ^ MULx2(state[10]) ^ MULx3(state[11]));
	temp[11] = (uint8_t)(MULx3(state[8]) ^ state[9] ^ state[10] ^ MULx2(state[11]));

	temp[12] = (uint8_t)(MULx2(state[12]) ^ MULx3(state[13]) ^ state[14] ^ state[15]);
	temp[13] = (uint8_t)(state[12] ^ MULx2(state[13]) ^ MULx3(state[14]) ^ state[15]);
	temp[14] = (uint8_t)(state[12] ^ state[13] ^ MULx2(state[14]) ^ MULx3(state[15]));
	temp[15] = (uint8_t)(MULx3(state[12]) ^ state[13] ^ state[14] ^ MULx2(state[15]));


	for (int i = 0; i < 16; i++)
		state[i] = temp[i];
}
void AES::InverseMixColumns() {
	uint8_t temp[16];
	temp[0] = (uint8_t)(MULxE(state[0]) ^ MULxB(state[1]) ^ MULxD(state[2]) ^ MULx9(state[3]));
	temp[1] = (uint8_t)(MULx9(state[0]) ^ MULxE(state[1]) ^ MULxB(state[2]) ^ MULxD(state[3]));
	temp[2] = (uint8_t)(MULxD(state[0]) ^ MULx9(state[1]) ^ MULxE(state[2]) ^ MULxB(state[3]));
	temp[3] = (uint8_t)(MULxB(state[0]) ^ MULxD(state[1]) ^ MULx9(state[2]) ^ MULxE(state[3]));

	temp[4] = (uint8_t)(MULxE(state[4]) ^ MULxB(state[5]) ^ MULxD(state[6]) ^ MULx9(state[7]));
	temp[5] = (uint8_t)(MULx9(state[4]) ^ MULxE(state[5]) ^ MULxB(state[6]) ^ MULxD(state[7]));
	temp[6] = (uint8_t)(MULxD(state[4]) ^ MULx9(state[5]) ^ MULxE(state[6]) ^ MULxB(state[7]));
	temp[7] = (uint8_t)(MULxB(state[4]) ^ MULxD(state[5]) ^ MULx9(state[6]) ^ MULxE(state[7]));

	temp[8] = (uint8_t)(MULxE(state[8]) ^ MULxB(state[9]) ^ MULxD(state[10]) ^ MULx9(state[11]));
	temp[9] = (uint8_t)(MULx9(state[8]) ^ MULxE(state[9]) ^ MULxB(state[10]) ^ MULxD(state[11]));
	temp[10] = (uint8_t)(MULxD(state[8]) ^ MULx9(state[9]) ^ MULxE(state[10]) ^ MULxB(state[11]));
	temp[11] = (uint8_t)(MULxB(state[8]) ^ MULxD(state[9]) ^ MULx9(state[10]) ^ MULxE(state[11]));

	temp[12] = (uint8_t)(MULxE(state[12]) ^ MULxB(state[13]) ^ MULxD(state[14]) ^ MULx9(state[15]));
	temp[13] = (uint8_t)(MULx9(state[12]) ^ MULxE(state[13]) ^ MULxB(state[14]) ^ MULxD(state[15]));
	temp[14] = (uint8_t)(MULxD(state[12]) ^ MULx9(state[13]) ^ MULxE(state[14]) ^ MULxB(state[15]));
	temp[15] = (uint8_t)(MULxB(state[12]) ^ MULxD(state[13]) ^ MULx9(state[14]) ^ MULxE(state[15]));


	for (int i = 0; i < 16; i++)
		state[i] = temp[i];
}
void AES::AddRoundKey(uint8_t* roundKey) {
	//Finite field addition modulus 2 (XOr Gate)
	state[0] ^= roundKey[0];
	state[1] ^= roundKey[1];
	state[2] ^= roundKey[2];
	state[3] ^= roundKey[3];

	state[4] ^= roundKey[4];
	state[5] ^= roundKey[5];
	state[6] ^= roundKey[6];
	state[7] ^= roundKey[7];

	state[8] ^= roundKey[8];
	state[9] ^= roundKey[9];
	state[10] ^= roundKey[10];
	state[11] ^= roundKey[11];

	state[12] ^= roundKey[12];
	state[13] ^= roundKey[13];
	state[14] ^= roundKey[14];
	state[15] ^= roundKey[15];
}
