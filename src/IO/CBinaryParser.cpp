/*
 * CBinaryParser.cpp
 *
 *  Created on: 2010-12-25
 *      Author: pkkj
 */

#include "CBinaryParser.h"

namespace IO {

long long CBinaryParser::readInt64(const byte * buf, ENDIAN endian) {
	long long ret = 0;
	if (endian == ENDIAN_BIG)
		ret = ((long long) (buf[0] & 0xff) << 56LL) | ((long long) (buf[1] & 0xff) << 48LL)
				| ((long long) (buf[2] & 0xff) << 40LL) | ((long long) (buf[3] & 0xff) << 32LL)
				| ((long long) (buf[4] & 0xff) << 24LL) | ((long long) (buf[5] & 0xff) << 16LL)
				| ((long long) (buf[6] & 0xff) << 8LL) | ((long long) buf[7] & 0xff);
	else
		ret = ((long long) (buf[7] & 0xff) << 56LL) | ((long long) (buf[6] & 0xff) << 48LL)
				| ((long long) (buf[5] & 0xff) << 40LL) | ((long long) (buf[4] & 0xff) << 32LL)
				| ((long long) (buf[3] & 0xff) << 24LL) | ((long long) (buf[2] & 0xff) << 16LL)
				| ((long long) (buf[1] & 0xff) << 8LL) | ((long long) buf[0] & 0xff);
	return ret;
}
void CBinaryParser::writeInt64(byte *buf, long long x, ENDIAN endian) {
	if (endian == ENDIAN_BIG) {
		buf[0] = (byte) (x >> 56LL);
		buf[1] = (byte) (x >> 48LL);
		buf[2] = (byte) (x >> 40LL);
		buf[3] = (byte) (x >> 32LL);
		buf[4] = (byte) (x >> 24LL);
		buf[5] = (byte) (x >> 16LL);
		buf[6] = (byte) (x >> 8LL);
		buf[7] = (byte) x;
	} else {
		buf[0] = (byte) x;
		buf[1] = (byte) (x >> 8LL);
		buf[2] = (byte) (x >> 16LL);
		buf[3] = (byte) (x >> 24LL);
		buf[4] = (byte) (x >> 32LL);
		buf[5] = (byte) (x >> 40LL);
		buf[6] = (byte) (x >> 48LL);
		buf[7] = (byte) (x >> 56LL);
	}
}

double CBinaryParser::readDouble(const byte *buf, ENDIAN endian) {
	long long i64 = readInt64(buf, endian);
	double ret;
	std::memcpy(&ret, &i64, sizeof(double));
	return ret;
}

void CBinaryParser::writeDouble(byte *buf, double x, ENDIAN endian) {
	long long i64;
	std::memcpy(&i64, &x, sizeof(long long));
	writeInt64(buf, i64, endian);
}

byte CBinaryParser::readByte(const byte *buf) {
	return buf[0];
}
void CBinaryParser::writeByte(byte *buf, byte x) {
	buf[0] = x;
}

int CBinaryParser::readInt(const byte * buf, ENDIAN endian) {
	int ret = 0;
	if (endian == ENDIAN_BIG)
		ret = ((int) (buf[0] & 0xff) << 24) | ((int) (buf[1] & 0xff) << 16)
				| ((int) (buf[2] & 0xff) << 8) | ((int) buf[3] & 0xff);
	else
		ret = ((int) (buf[3] & 0xff) << 24) | ((int) (buf[2] & 0xff) << 16)
				| ((int) (buf[1] & 0xff) << 8) | ((int) buf[0] & 0xff);
	return ret;
}
void CBinaryParser::writeInt(byte *buf, int x, ENDIAN endian) {
	if (endian == ENDIAN_BIG) {
		buf[0] = (byte) (x >> 24);
		buf[1] = (byte) (x >> 16);
		buf[2] = (byte) (x >> 8);
		buf[3] = (byte) x;
	} else {
		buf[0] = (byte) x;
		buf[1] = (byte) (x >> 8);
		buf[2] = (byte) (x >> 16);
		buf[3] = (byte) (x >> 24);
	}
}

unsigned short CBinaryParser::readUInt16(const byte * buf, ENDIAN endian) {
	unsigned short ret;
	if (endian == ENDIAN_BIG)
		ret = ((unsigned short) (buf[0] & 0xff) << 8) | ((unsigned short) buf[1] & 0xff);
	else
		ret = ((unsigned short) (buf[1] & 0xff) << 8) | ((unsigned short) buf[0] & 0xff);
	return ret;

}
void CBinaryParser::writeIUnt16(byte *buf, unsigned short x, ENDIAN endian) {
	if (endian == ENDIAN_BIG) {
		buf[0] = (byte) (x >> 8);
		buf[1] = (byte) x;
	} else {
		buf[1] = (byte) (x >> 8);
		buf[0] = (byte) x;
	}
}
}
