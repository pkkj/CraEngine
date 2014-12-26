/*
 * CLayer.cpp
 *
 *  Created on: 2011-1-27
 *      Author: pkkj
 */

#include "CLayer.h"
#include "CMapScreenConvert.h"
namespace GUI {

CLayer::CLayer() {

}

CLayer::~CLayer() {

}

CMapScreenConvert* CLayer::getMapScreenConvert(){
	return mConvert;
}
void CLayer::setMapScreenConvert(CMapScreenConvert *convert) {
	mConvert = convert;
}

void CLayer::setMap(CMap *map){
	mMap = map;
}
}
