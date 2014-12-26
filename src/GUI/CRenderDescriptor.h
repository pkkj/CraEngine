/*
 * CRenderDescriptor.h
 *
 *  Created on: 2011-1-28
 *      Author: pkkj
 */

#ifndef CRENDERDESCRIPTOR_H_
#define CRENDERDESCRIPTOR_H_
#include <QPainter>
namespace GUI{
class CRenderDescriptor{
public:
	CRenderDescriptor();
	~CRenderDescriptor();

	QPainter* painter;
private:

};
}

#endif /* CRENDERDESCRIPTOR_H_ */
