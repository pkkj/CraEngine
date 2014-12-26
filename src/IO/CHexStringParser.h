/*
 * CHexStringParser.h
 *
 *  Created on: 2010-12-25
 *      Author: pkkj
 */

#ifndef CHEXSTRINGPARSER_H_
#define CHEXSTRINGPARSER_H_
#include "CIO.h"
namespace IO {

class CHexStringParser {
public:
	static byte ParseHexChar(char ch);
	static void ParseByte4(char *str, byte *buf);
	static void ParseByte8(char *str, byte *buf);
	static void ParseByte2(char *str,byte *buf);
	static void ParseByte1(char *str,byte *buf);

};
}
#endif /* CHEXSTRINGPARSER_H_ */
