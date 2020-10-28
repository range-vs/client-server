#pragma once

#include <algorithm>

#include "../shared/TransportData.h"


TransportBlock::TransportBlock() :msg() {}

void TransportBlock::copyHeader(const TYPE_OPERATION& to, int not_used)
{
	unsigned num = static_cast<unsigned>(to);
	msg[0] = (num >> 24) & 0xFF;
	msg[1] = (num >> 16) & 0xFF;
	msg[2] = (num >> 8) & 0xFF;
	msg[3] = num & 0xFF;
	//std::copy(h, h + strlen(h), msg.begin()); // HEADER_LENGTH ?
}

void TransportBlock::copyData(const char* d)
{
	std::copy(d, d + strlen(d), msg.begin() + HEADER_LENGTH);
}

char* TransportBlock::data()
{
	return msg.data();
}

size_t TransportBlock::size()
{
	return DATA_LENGTH + HEADER_LENGTH;
}

size_t TransportBlock::sizeHeader()
{
	return HEADER_LENGTH;
}

size_t TransportBlock::sizeBlock()
{
	return DATA_LENGTH;
}

char* TransportBlock::dataHeader()
{
	return msg.data();
}

char* TransportBlock::dataBlock()
{
	return msg.data() + HEADER_LENGTH;
}