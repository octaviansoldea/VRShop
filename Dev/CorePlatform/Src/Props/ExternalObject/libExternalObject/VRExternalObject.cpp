#include "BasicStringDefinitions.h"
#include <fstream>

#include <osg/Geometry>
#include <osg/Geode>

#include "VRExternalObject.h"

using namespace VR;
using namespace osg;
using namespace std;

ExternalObjectParams::ExternalObjectParams() : 
m_strFileName(""), AbstractObjectParams()	{
}

//==============================================================================

ExternalObject::ExternalObject(const ExternalObjectParams & aExternalObjectParams) : 
AbstractObject(aExternalObjectParams)	{
	setName("ExternalObject_"+tostr(getAbstractObjectNo()));
	m_strFileName = aExternalObjectParams.m_strFileName;
}

//-----------------------------------------------------------------------------

ExternalObject::ExternalObject(const ExternalObject & aExternalObject,const CopyOp& copyop) :
AbstractObject(aExternalObject,copyop)	{
	ExternalObjectParams eop;
	aExternalObject.getParams(eop);
	this->setParams(eop);

	setName("ExternalObject_"+tostr(getAbstractObjectNo()));
}

//-----------------------------------------------------------------------------

ExternalObject::~ExternalObject()	{
}

//==============================================================================

const char* ExternalObject::className() const	{
	return "ExternalObject";
}

//-----------------------------------------------------------------------

Object* ExternalObject::cloneType() const	{
	ExternalObjectParams pExternalObjectParams;
	return new ExternalObject(pExternalObjectParams);
}

//-----------------------------------------------------------------------

Object* ExternalObject::clone(const CopyOp& copyop) const	{
	ExternalObject * pExternalObject = new ExternalObject(*this,copyop);

	return pExternalObject;
}

//------------------------------------------------------------------------------

ref_ptr<ExternalObject> ExternalObject::readFromFile(const string & astrFileName)	{
	ExternalObjectParams eop;
	eop.m_strFileName = astrFileName;

	ref_ptr<Vec3Array> pPoints = new Vec3Array();
	ref_ptr<DrawElementsUInt> pTriangleSets = new DrawElementsUInt(GL_TRIANGLES);

	pPoints->push_back(Vec3d(0,0,0));

	ifstream input(astrFileName);
	string strLine;
	while (getline(input, strLine))	{
		string strType = strLine.substr(0,2);
		char* pchLine = new char[strLine.size()+1];
		memcpy(pchLine, strLine.c_str(), strLine.size()+1);

		strtok(pchLine, " ");
		if (strType.compare("v ") == 0)	{
			float flX = atof(strtok(NULL, " "));
			float flY = atof(strtok(NULL, " "));
			float flZ = atof(strtok(NULL, " "));
			pPoints->push_back(Vec3d(flX,flY,flZ));
		} else if (strType.compare("f ") == 0)	{
			int nX = atoi(strtok(NULL, " "));
			int nY = atoi(strtok(NULL, " "));
			int nZ = atoi(strtok(NULL, " "));

			pTriangleSets->push_back(nX);
			pTriangleSets->push_back(nY);
			pTriangleSets->push_back(nZ);
		} else if (strType.compare("vt") == 0)	{
			//TEXTURE COORDINATES
		} else if (strType.compare("vn") == 0)	{
			//NORMALS COORDINATES
		}
		delete [] pchLine;
	}
	input.close();

	ref_ptr<Geometry> pGeometry = new Geometry;
	pGeometry->setVertexArray(pPoints.get());
	pGeometry->addPrimitiveSet(pTriangleSets);
	ref_ptr<Geode> pGeode = new Geode;
	pGeode->addDrawable(pGeometry);

	ref_ptr<ExternalObject> pNewObject = new ExternalObject(eop);

	pNewObject->addChild(pGeode);

	return pNewObject;
}

//------------------------------------------------------------------------------

ref_ptr<ExternalObject> ExternalObject::createObject(string & astrData)	{
	char * pchData = &astrData[0];

	strtok(pchData, ";");
	string strClassName=strtok(NULL, ";");
	string strObjectName=strtok(NULL, ";");
	string strFileName=strtok(NULL, ";");
	string strObjectData=strtok(NULL, ";");

	ref_ptr<Vec3Array> pPoints = new Vec3Array();
	ref_ptr<DrawElementsUInt> pTriangleSets = new DrawElementsUInt(GL_TRIANGLES);

	pPoints->push_back(Vec3d(0,0,0));

	ifstream input(strFileName);
	string strLine;
	while (getline(input, strLine))	{
		string strType = strLine.substr(0,2);
		char* pchLine = new char[strLine.size()+1];
		memcpy(pchLine, strLine.c_str(), strLine.size()+1);
		
		strtok(pchLine, " ");
		if (strType.compare("v ") == 0)	{
			float flX = atof(strtok(NULL, " "));
			float flY = atof(strtok(NULL, " "));
			float flZ = atof(strtok(NULL, " "));
			pPoints->push_back(Vec3d(flX,flY,flZ));
		} else if (strType.compare("f ") == 0)	{
			int nX = atoi(strtok(NULL, " "));
			int nY = atoi(strtok(NULL, " "));
			int nZ = atoi(strtok(NULL, " "));

			pTriangleSets->push_back(nX);
			pTriangleSets->push_back(nY);
			pTriangleSets->push_back(nZ);
		} else if (strType.compare("vt") == 0)	{
			//TEXTURE COORDINATES
		} else if (strType.compare("vn") == 0)	{
			//NORMALS COORDINATES
		}
		delete [] pchLine;
	}
	input.close();

	ref_ptr<Geometry> pGeometry = new Geometry;
	pGeometry->setVertexArray(pPoints.get());
	pGeometry->addPrimitiveSet(pTriangleSets);
	ref_ptr<Geode> pGeode = new Geode;
	pGeode->addDrawable(pGeometry);

	char * pchObjectData = &*strObjectData.begin();
	ExternalObjectParams eop;
	eop.m_flPosX = atof(strtok(pchObjectData, "_"));
	eop.m_flPosY = atof(strtok(NULL, "_"));
	eop.m_flPosZ = atof(strtok(NULL, "_"));
	eop.m_flLenX = atof(strtok(NULL, "_"));
	eop.m_flLenY = atof(strtok(NULL, "_"));
	eop.m_flLenZ = atof(strtok(NULL, "_"));
	eop.m_flAngleYZ = atof(strtok(NULL, "_"));
	eop.m_flAngleXZ = atof(strtok(NULL, "_"));
	eop.m_flAngleXY = atof(strtok(NULL, "_"));

	ref_ptr<ExternalObject> pNewObject = new ExternalObject(eop);
	pNewObject->setName(strObjectName);

	pNewObject->addChild(pGeode);

	return pNewObject;
}

//------------------------------------------------------------------------------

void ExternalObject::setParams(const ExternalObjectParams & aExternalObjectParams)	{
	AbstractObject::setParams(aExternalObjectParams);
	m_strFileName = aExternalObjectParams.m_strFileName;
}

//------------------------------------------------------------------------------

void ExternalObject::getParams(ExternalObjectParams & aExternalObjectParams) const	{
	AbstractObject::getParams(aExternalObjectParams);
	aExternalObjectParams.m_strFileName = m_strFileName;
}

//------------------------------------------------------------------------------

void ExternalObject::setColor(const std::vector < float > & aarrflColor)	{
}

//------------------------------------------------------------------------------

void ExternalObject::setTexture(const std::string & astrFileName)	{
}

//------------------------------------------------------------------------------

void ExternalObject::initFromSQLData(const std::string & astrSQLData)	{
	//
	char* pchLine = new char[astrSQLData.size()+1];
	memcpy(pchLine, astrSQLData.c_str(), astrSQLData.size()+1);

	strtok(pchLine, ";");

}

//------------------------------------------------------------------------------

void ExternalObject::predefinedObject()	{
}

//------------------------------------------------------------------------------

string ExternalObject::prepareRowData(const string & astrParentName)	{
	string strEop = 
		m_strFileName + ";" +

		tostr(m_flPosX) + "_" +
		tostr(m_flPosY) + "_" +
		tostr(m_flPosZ) + "_" +

		tostr(m_flLenX) + "_" +
		tostr(m_flLenY) + "_" +
		tostr(m_flLenZ) + "_" +

		tostr(m_flAngleYZ) + "_" +
		tostr(m_flAngleXZ) + "_" +
		tostr(m_flAngleXY) + ";" +	

		astrParentName;

	return strEop;
}
