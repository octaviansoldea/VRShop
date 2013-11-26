#ifndef VR_FURNITURE_H
#define VR_FURNITURE_H

#include <string>
#include <osg/Group>

void loadAllFurnitures(osg::ref_ptr<osg::Group> pScene, const std::string & astrDatabase);

#endif //VR_FURNITURE_H