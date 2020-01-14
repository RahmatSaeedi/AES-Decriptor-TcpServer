#pragma once
#include "StreamBuffer.h"


uint8_t streamBuf::read_1_byte() {
	pointer_position += 1;
	return Buffer[pointer_position - 1];
}
uint16_t streamBuf::read_2_byte() {
	pointer_position += 2;
	return ((Buffer[pointer_position - 2] << 8 * 1) | Buffer[pointer_position - 1]);
}
uint32_t streamBuf::read_4_byte() {
	pointer_position += 4;
	return (
		(Buffer[pointer_position - 4] << 8 * 3) | (Buffer[pointer_position - 3] << 8 * 2) |
		(Buffer[pointer_position - 2] << 8 * 1) | Buffer[pointer_position - 1]);
}
uint64_t streamBuf::read_8_byte() {
	pointer_position += 8;
	return (
		((uint64_t)Buffer[pointer_position - 8] << 8 * 7) | ((uint64_t)Buffer[pointer_position - 7] << 8 * 6) |
		((uint64_t)Buffer[pointer_position - 6] << 8 * 5) | ((uint64_t)Buffer[pointer_position - 5] << 8 * 4) |
		((uint64_t)Buffer[pointer_position - 4] << 8 * 3) | ((uint64_t)Buffer[pointer_position - 3] << 8 * 2) |
		((uint64_t)Buffer[pointer_position - 2] << 8 * 1) | (uint64_t)Buffer[pointer_position - 1]);
}


void streamBuf::append(uint8_t value, int numberOfTimes) {
	for (int i = 0; i < numberOfTimes; i++) {
		Buffer[pointer_position] = value;
		pointer_position++;
	}
}
void streamBuf::append(uint8_t* value, int numberOfBytes) {
	for (int i = 0; i < numberOfBytes; i++) {
		Buffer[pointer_position] = value[i];
		pointer_position++;
	}
}
void streamBuf::append(uint16_t value) {
	Buffer[pointer_position] = (value >> (8 * 1)) & 0xFF;
	Buffer[pointer_position + 1] = (value >> (8 * 0)) & 0xFF;
	pointer_position += 2;
}
void streamBuf::append(uint32_t value) {
	Buffer[pointer_position] = (value >> (8 * 3)) & 0xFF;
	Buffer[pointer_position + 1] = (value >> (8 * 2)) & 0xFF;
	Buffer[pointer_position + 2] = (value >> (8 * 1)) & 0xFF;
	Buffer[pointer_position + 3] = (value >> (8 * 0)) & 0xFF;
	pointer_position += 4;
}
void streamBuf::append(uint64_t value) {
	Buffer[pointer_position] = (value >> (8 * 7)) & 0xFF;
	Buffer[pointer_position + 1] = (value >> (8 * 6)) & 0xFF;
	Buffer[pointer_position + 2] = (value >> (8 * 5)) & 0xFF;
	Buffer[pointer_position + 3] = (value >> (8 * 4)) & 0xFF;
	Buffer[pointer_position + 4] = (value >> (8 * 3)) & 0xFF;
	Buffer[pointer_position + 5] = (value >> (8 * 2)) & 0xFF;
	Buffer[pointer_position + 6] = (value >> (8 * 1)) & 0xFF;
	Buffer[pointer_position + 7] = (value >> (8 * 0)) & 0xFF;
	pointer_position += 8;
}
void streamBuf::append_n_byte(uint8_t* value, int n) {
	for (int i = 0; i < n; i++) {
		Buffer[pointer_position] = value[i];
		pointer_position++;
	}
}



uint16_t streamBuf::BufferSize() {
	return pointer_position;
}
void streamBuf::zeroBufferSize() {
	pointer_position = 0;
}
void streamBuf::bufferAddress(uint8_t* address) {
	Buffer = address;
	pointer_position = 0;
}



streamBuf::streamBuf()
{
	pointer_position = 0;
}

