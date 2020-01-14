#pragma once
#include <cstdint>

class streamBuf
{
private:
	uint16_t pointer_position;
public:
	uint8_t read_1_byte();
	uint16_t read_2_byte();
	uint32_t read_4_byte();
	uint64_t read_8_byte();


	void append(uint8_t value, int numberOfTimes = 1);
	void append(uint8_t* value, int numberOfBytes);
	void append(uint16_t value);
	void append(uint32_t value);
	void append(uint64_t value);
	void append_n_byte(uint8_t* value, int n);


	uint8_t* Buffer;

	void bufferAddress(uint8_t* address);
	streamBuf();


	uint16_t BufferSize();
	void zeroBufferSize();
};




