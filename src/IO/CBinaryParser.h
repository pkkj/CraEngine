/*
 * CBinaryParser.h
 *
 *  Created on: 2010-12-25
 *      Author: pkkj
 */

#ifndef CBINARYPARSER_H_
#define CBINARYPARSER_H_

#include "CIO.h"

namespace IO {

class CBinaryParser {
public:
	static double readDouble(const byte * buf, ENDIAN endian);
	static void writeDouble(byte *buf, double x, ENDIAN endian);

	static long long readInt64(const byte * buf, ENDIAN endian);
	static void writeInt64(byte *buf, long long x, ENDIAN endian);

	static byte readByte(const byte * buf);
	static void writeByte(byte *buf, byte x);

	static int readInt(const byte * buf, ENDIAN endian);
	static void writeInt(byte *buf, int x, ENDIAN endian);

	static unsigned short readUInt16(const byte * buf, ENDIAN endian);
	static void writeIUnt16(byte *buf, unsigned short x, ENDIAN endian);

};
}
#endif /* CBINARYPARSER_H_ */
