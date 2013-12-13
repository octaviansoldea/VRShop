#ifndef VR_SCENE_STRUCTURE_ITEM_H
#define VR_SCENE_STRUCTURE_ITEM_H

#include <QList>
#include <QVariant>
#include <QVector>
#include <QModelIndex>

namespace VR	{

	class SceneStructureItem {

	public:
		SceneStructureItem(const QVariant & aarrData, SceneStructureItem *parent = 0);
		~SceneStructureItem();

		SceneStructureItem * parent();
		SceneStructureItem * child(int anRowNumber);

		QVariant data() const;
		bool setData(const QVariant &value);

		int childCount() const;

		int row() const;

		void insertChild(SceneStructureItem * apChild);
		
	private:
		QList <SceneStructureItem*> m_arrChildren;
		QVariant m_parrItemData;
		SceneStructureItem * m_pParent;
	};
}
#endif //VR_SCENE_STRUCTURE_ITEM_H