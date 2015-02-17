#ifndef VR_EXTERNAL_OBJECT_H
#define VR_EXTERNAL_OBJECT_H

#include <string>

#include "VRAbstractObject.h"

namespace VR {
	struct ExternalObjectParams : public AbstractObjectParams	{
		std::string m_strFileName;
		ExternalObjectParams();
	};

	class ExternalObject : public AbstractObject	{
	public:
		ExternalObject(const ExternalObjectParams & aExternalObjectParams);
		ExternalObject(const ExternalObject & aExternalObject,const osg::CopyOp& copyop=osg::CopyOp::DEEP_COPY_ALL);
		virtual ~ExternalObject();

		virtual const char* className() const;
		virtual osg::Object* cloneType() const;
		virtual osg::Object* clone(const osg::CopyOp& copyop) const;

		static osg::ref_ptr<ExternalObject> readFromFile(const std::string & astrFileName);
		static osg::ref_ptr<ExternalObject> createObject(std::string & astrData);

		void setParams(const ExternalObjectParams & aExternalObjectParams);
		void getParams(ExternalObjectParams & aExternalObjectParams) const;

	private:
		std::string m_strFileName;

		//DECLARATION OF PURE VIRTUAL FUNCTIONS
		virtual void setColor(const std::vector < float > & aarrflColor);
		virtual void setTexture(const std::string & astrFileName);

		virtual void initFromSQLData(const std::string & astrSQLData);
		virtual void predefinedObject();
		virtual std::string prepareRowData(const std::string & astrParentName="");
		//END DECLARATION OF PURE VIRTUAL FUNCTIONS

	};
}
#endif //VR_EXTERNAL_OBJECT_H