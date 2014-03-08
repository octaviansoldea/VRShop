#ifndef VR_SCENE_STRUCTURE_MODEL_H
#define VR_SCENE_STRUCTURE_MODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QList>

#include <vector>
#include <string>

#include "VRSceneStructureItem.h"


namespace VR	{

	struct SceneStructureModelParams	{
		QList <QString> data;
		QVariant aqvarRootHeader;
		QObject *parent;
		SceneStructureModelParams();
	};

	class SceneStructureModel : public QAbstractItemModel {

		Q_OBJECT

	public:
		SceneStructureModel();
		SceneStructureModel(const SceneStructureModelParams & aSceneStructureModelParams);
		~SceneStructureModel();

		virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
		virtual QModelIndex parent(const QModelIndex &index) const;

		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
		
		virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
		virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

		virtual QVariant data(const QModelIndex &index, int role = Qt::EditRole) const;

		//reimplementation of setData() & flags() required to let editing
		virtual bool setData(const QModelIndex& index, const QVariant& value,int role = Qt::EditRole);
		virtual Qt::ItemFlags flags(const QModelIndex& index) const;

		void setupDataElements(const QList <QString> & aarrstrSceneData, SceneStructureItem *apParent);

	private:
		SceneStructureItem * m_pRootItem;
	};
}
#endif //VR_SCENE_STRUCTURE_MODEL_H