#ifndef VR_SHOPPING_PLACE_H
#define VR_SHOPPING_PLACE_H

#include <QString>
#include <osg/ref_ptr>


namespace VR	{
	class OSGQT_Widget;
	class Scene;
	class Grid;

	struct ShoppingPlace {
		ShoppingPlace(OSGQT_Widget * apOSGQTWidget);

		~ShoppingPlace();

		void gridOnOff(bool abIndicator);

		osg::ref_ptr<Scene> getScene() const;

	private:
		OSGQT_Widget * m_pOSGQTWidget;

		osg::ref_ptr<Scene> m_pScene;

		QString m_strDBFileName;

		osg::ref_ptr<Grid> m_pGridlines;
	};
}
#endif //VR_SHOPPING_PLACE_H