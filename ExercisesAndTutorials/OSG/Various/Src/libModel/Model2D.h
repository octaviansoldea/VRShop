#ifndef MODEL_2D_H
#define MODEL_2D_H

#include <osg/Geode>
#include <osg/Geometry>

#include "BaseModel.h"

class Model2D : public BaseModel, public osg::Geode {
public:
	Model2D();

	void setColor(osg::Vec4 aVec4);
	void setTexture(const char * apchFileName);

private:
	osg::ref_ptr<osg::Geometry> m_pGeometry;
};
#endif //MODEL_2D_H