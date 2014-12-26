/*
 * CFeatureClass.h
 *
 *  Created on: 2011-1-7
 *      Author: pkkj
 */

#ifndef CFEATURECLASS_H_
#define CFEATURECLASS_H_

#include "CFields.h"
#include "CFeature.h"
#include "CGeometry.h"
#include "CFeatureCursor.h"
#include "CQueryFilter.h"
#include "CSpatialFilter.h"
#include "CRectangle.h"
#include "CDataClass.h"

using namespace Core;
namespace DataSource {

class CFeatureClass : public CDataClass {
	friend class CFeatureCursor;
public:
	CFeatureClass();
	virtual ~CFeatureClass();
public:

	string TableName;
	CFields Fields;

	int SRID;
public:
	virtual void loadField() = 0;
	virtual CFeature *createFeature() = 0;
	virtual bool addFeature(CFeature *pFeat) = 0;

	virtual bool deleteFeature(int featID) =0;
	bool deleteFeature(vector<int> featID);

	virtual bool updateFeature(CFeature *pFeat) = 0;
	bool updateFeature(vector<CFeature *> featID);

	virtual bool search(CQueryFilter *filter, CFeatureCursor &cursor) = 0;
	virtual bool featureByID(int fid, CFeature &feature, bool fetchGeometry = true, string subFields = "")=0;
	virtual bool addField(CField field) = 0;
	virtual bool addGeometryField(string name, int srid, Core::COpenGISType::OPENGIS_TYPE type, int dimension = 2) = 0;
	virtual bool deleteField(int fieldID) = 0;
	virtual string getSpatialRefFuncByType(CSpatialFilter::SPATIAL_RELATION rel,CSpatialFilter::SPATIAL_REL_TYPE &type) = 0;
	bool deleteField(string name);

	int FieldCount();

	Core::COpenGISType::OPENGIS_TYPE GetShapeType();
	virtual Geometry::CRectangle getExtent() = 0;
	bool GetHasM();
	bool GetHasZ();

protected:
	Core::COpenGISType::OPENGIS_TYPE GeometryType;
	bool HasM;
	bool HasZ;
protected:
	virtual void getGeometryType() = 0;
	string SQLInsertString(string str);
	virtual bool getFeature(CFeatureCursor *cursor, int featnum) = 0;

};

}
#endif /* CFEATURECLASS_H_ */
