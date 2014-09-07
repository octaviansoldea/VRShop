#ifndef VR_DATA_STRUCTURE_MODEL_H
#define VR_DATA_STRUCTURE_MODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QList>

#include <vector>
#include <string>

namespace VR	{
	class DataStructureItem;

	struct DataStructureModelParams	{
		QList <QString> data;
		QVariant aqvarRootHeader;
		QObject *parent;
		DataStructureModelParams();
	};

	class DataStructureModel : public QAbstractItemModel {

		Q_OBJECT

	public:
		DataStructureModel(const DataStructureModelParams & aDataStructureModelParams);
		~DataStructureModel();

		virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
		virtual QModelIndex parent(const QModelIndex &index) const;

		virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
		
		virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
		virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

		virtual QVariant data(const QModelIndex &index, int role = Qt::EditRole) const;

		//reimplementation of setData() & flags() required to let editing
		//called each time the a cell is edited
		virtual bool setData(const QModelIndex& index, const QVariant& value,int role = Qt::EditRole);
		virtual Qt::ItemFlags flags(const QModelIndex& index) const;

		//reimplemented for the sake of insertion/removal
		virtual bool insertRows(int position, int rows, const QModelIndex &parent);
		virtual bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());


		void setupDataElements(const QList <QString> & aarrstrSceneData, DataStructureItem *apParent);

		QVariant getPrevValue() const;

	private:
		DataStructureItem * m_pRootItem;
		QVariant m_PreviousValue;
	};
}
#endif //VR_DATA_STRUCTURE_MODEL_H