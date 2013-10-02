#ifndef MODEL_3D_H
#define MODEL_3D_H

#include <osg/Group>

#include "BaseModel.h"

class Model3D : public BaseModel, public osg::Group {
public:
	Model3D();

	void setColor(osg::Vec4 aVec4);
	void setTexture(const char * apchFileName);
};
#endif //MODEL_3D_H