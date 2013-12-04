#ifndef VR_SCENE_STRUCTURE_ITEM_H
#define VR_SCENE_STRUCTURE_ITEM_H

#include <QList>
#include <QVariant>
#include <QVector>
#include <QModelIndex>

namespace VR	{

	class SceneStructureItem {

	public:
		SceneStructureItem(const QList <QVariant> &aarrData, SceneStructureItem *parent = 0);
		~SceneStructureItem();

		SceneStructureItem * parent();
		SceneStructureItem * child(int anRowNumber);

		QVariant data(int column) const;
		bool setData(int column, const QVariant &value);


		int childCount() const;
		int columnCount() const;

		int row() const;

		void insertChild(SceneStructureItem * apChild);
		
	private:
		QList <SceneStructureItem*> m_arrChildren;
		QList <QVariant> m_parrItemData;
		SceneStructureItem * m_pParent;
	};
}
#endif //VR_SCENE_STRUCTURE_ITEM_H