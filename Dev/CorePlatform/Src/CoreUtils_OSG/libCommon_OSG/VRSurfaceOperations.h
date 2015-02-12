#ifndef VR_SURFACE_OPERATIONS_H
#define VR_SURFACE_OPERATIONS_H

namespace VR {
	class AbstractObject;

	class SurfaceOperations	{
		public:
			SurfaceOperations();

			static void setTransparency(AbstractObject * apAO, float aflTransparencyFactor);
	};
}
#endif //VR_SURFACE_OPERATIONS_H