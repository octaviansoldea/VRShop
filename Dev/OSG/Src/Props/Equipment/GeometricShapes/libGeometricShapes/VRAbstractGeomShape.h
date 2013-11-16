#ifndef VR_ABSTRACT_GEOM_SHAPE_H
#define VR_ABSTRACT_GEOM_SHAPE_H

#include <string>

namespace VR {
	struct AbstractGeomShapeParams	{
		AbstractGeomShapeParams();
	};

	class AbstractGeomShape	{
	public:
		AbstractGeomShape();

		virtual void init(const AbstractGeomShapeParams & aAbstractGeomShapeParams) = 0;

		virtual std::string getSQLCommand(const AbstractGeomShapeParams & aAbstractGeomShapeParams) const = 0;
		virtual void initFromSQLData(const std::string & astrSQLData);

		virtual void setIsTargetPick(bool abIsTargetPick);
		virtual bool getIsTargetPick() const;

	private:
		bool m_bIsTargetPick;
	};
}
#endif //VR_ABSTRACT_GEOM_SHAPE_H