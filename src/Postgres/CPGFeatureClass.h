/*
 * CPGFeatClass.h
 *
 *  Created on: 2010-12-28
 *      Author: pkkj
 */

#ifndef CPGFEATURECLASS_H_
#define CPGFEATURECLASS_H_
#include <cstring>
#include <cstdlib>
#include <string>
#include <libpq-fe.h>
using namespace std;

#include "CPGConnection.h"
#include "CFeatureClass.h"
#include "CFeature.h"
#include "COpenGISInfo.h"
#include "CEWKBReader.h"
namespace DataSource {
class CPGFeatClass: public CFeatureClass {
	friend class CFeattureCursor;
public:
	CPGFeatClass();
	~CPGFeatClass();
public:
	void loadField();
	CFeature *createFeature();
	bool addFeature(CFeature *pFeat);
	bool deleteFeature(int featID);
	bool updateFeature(CFeature *pFeat);
	bool connect(Core::CPropertySet dbInfo);
	bool disconnect();

	bool search(CQueryFilter *filter, CFeatureCursor &cursor);
	bool featureByID(int fid, CFeature &feature, bool fetchGeometry, string subFields);

	/**
	 * Get the actually spatial relation function name or operator in the database system
	 * @param rel the standard relation operation
	 * @param
	 * @return the function/operator's name
	 */
	string getSpatialRefFuncByType(CSpatialFilter::SPATIAL_RELATION rel,CSpatialFilter::SPATIAL_REL_TYPE &type);
	string consSpatialWhere(CSpatialFilter *filter);

	bool addField(CField field);
	bool addGeometryField(string name, int srid, Core::COpenGISType::OPENGIS_TYPE type, int dimension);
	bool deleteField(int fieldID);

public:
	FIELD_TYPE getPgFieldTypeByName(const char *data_type);
	string getPgFieldNameByType(const FIELD_TYPE type);
	string insertFieldExp(string fieldName, FIELD_TYPE type);
	Geometry::CRectangle getExtent();

private:

	void refreshClass();

private:
	CPGConnection *mConnRead;
	CPGConnection *mConnWrite;

protected:
	void getGeometryType();
	bool getFeature(CFeatureCursor *cursor, int featnum);
};

}
#endif /* CPGFEATURECLASS_H_ */
