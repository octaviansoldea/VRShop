#ifndef VR_DATA_STRUCTURE_ITEM_H
#define VR_DATA_STRUCTURE_ITEM_H

#include <QList>
#include <QVariant>
#include <QVector>
#include <QModelIndex>

namespace VR	{

	class DataStructureItem {

	public:
		DataStructureItem(const QVariant & aarrData="", DataStructureItem *parent = 0);
		~DataStructureItem();

		DataStructureItem * parent();
		DataStructureItem * child(int anRowNumber);

		QVariant data() const;
		bool setData(const QVariant &value);

		int childCount() const;

		int row() const;

		void insertChild(DataStructureItem * apChild);
		bool insertChildren(int position, int count);
		bool removeChildren(int position, int count);
		
	private:
		QList <DataStructureItem*> m_arrChildren;
		QVariant m_parrItemData;
		DataStructureItem * m_pParent;
	};
}
#endif //VR_DATA_STRUCTURE_ITEM_H