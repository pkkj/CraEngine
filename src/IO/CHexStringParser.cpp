/*
 * CHexStringParser.cpp
 *
 *  Created on: 2010-12-25
 *      Author: pkkj
 */

#include "CHexStringParser.h"
namespace IO {
byte CHexStringParser::ParseHexChar(char ch) {
	if ('0' <= ch && ch <= '9')
		return ch - '0';
	if ('a' <= ch && ch <= 'f')
		return ch - 'a' + 10;
	return ch - 'A' + 10;
}
void CHexStringParser::ParseByte2(char *str, byte *buf) {
	ParseByte1(str, buf);
	ParseByte1(str + 2, buf + 1);
}
void CHexStringParser::ParseByte4(char *str, byte *buf) {
	ParseByte1(str, buf);
	ParseByte1(str + 2, buf + 1);
	ParseByte1(str + 4, buf + 2);
	ParseByte1(str + 6, buf + 3);
}
void CHexStringParser::ParseByte8(char *str, byte *buf) {
	ParseByte1(str, buf);
	ParseByte1(str + 2, buf + 1);
	ParseByte1(str + 4, buf + 2);
	ParseByte1(str + 6, buf + 3);
	ParseByte1(str + 8, buf + 4);
	ParseByte1(str + 10, buf + 5);
	ParseByte1(str + 12, buf + 6);
	ParseByte1(str + 14, buf + 7);
}

void CHexStringParser::ParseByte1(char *str, byte *buf) {
	byte x = ParseHexChar(*str);
	str++;
	byte y = ParseHexChar(*str);
	str++;
	*buf = x * 16 + y;
}
}
