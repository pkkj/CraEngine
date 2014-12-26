/*
 * CFields.cpp
 *
 *  Created on: 2010-12-27
 *      Author: pkkj
 */

#include "CFields.h"


namespace DataSource {

int CFields::FindField(string FName){
	if(mMapFieldID.find(FName) != mMapFieldID.end())
		return mMapFieldID[FName];
	return -1;
}

CField& CFields::GetField(int idx){
	return mFields[idx];
}

size_t CFields::FieldCount(){
	return mFields.size();
}


}
