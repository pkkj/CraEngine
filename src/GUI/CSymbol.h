/*
 * CSymbol.h
 *
 *  Created on: 2011-1-31
 *      Author: pkkj
 */

#ifndef CSYMBOL_H_
#define CSYMBOL_H_
#include <QPen>
#include <QBrush>
namespace GUI{
class CSymbol
{
public:
	CSymbol();
	CSymbol(const CSymbol &symbol);

	virtual ~CSymbol();
	virtual CSymbol* clone() const= 0;
	virtual QPen getPen() = 0;
	virtual QBrush getBrush() = 0;
};
}

#endif /* CSYMBOL_H_ */
