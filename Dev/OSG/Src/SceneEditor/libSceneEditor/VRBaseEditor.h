#ifndef VR_BASE_OBJECT_H
#define VR_BASE_OBJECT_H

#include "VRQOSGWidget.h"

#include "VRDatabaseMgr.h"

namespace VR	{
	class BaseEditor	{
	public:
		BaseEditor();
		~BaseEditor();

		void setQOSGWidgets(QOSGWidget * apQOSGWidget);

	protected:
		DatabaseMgr *pDatabaseMgr;
		QOSGWidget * m_pQOSGWidget;	
	};
}
#endif //VR_BASE_OBJECT_H