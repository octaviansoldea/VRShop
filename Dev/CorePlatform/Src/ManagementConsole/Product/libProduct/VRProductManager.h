#ifndef VR_PRODUCT_MANAGER_H
#define VR_PRODUCT_MANAGER_H

#include <string>
#include <vector>
#include <list>

#include <osg/Group>

#include <QObject>

namespace VR	{
	class AddProduct_GUI;
	class ProductShopEditor;
	struct ProductShopEditorParams;
	class AbstractObject;

	class DatabaseInterface;
	struct DatabaseInterfaceParams;


	class ProductManager : public QObject {
		Q_OBJECT
	public:
		ProductManager(QObject * apParent = 0);
		virtual ~ProductManager();

		const char* className() const;

		osg::Node * getProductsRepresentation();

		osg::Node * getChild(const std::string & astrChildName);

		ProductShopEditor * getProduct(const AbstractObject * apAbstractObject);

		void addNewProduct();
		void productMoreSettings(const std::string & astrProductCode);
		bool removeProduct(const std::string & astrProductCode);

		void addNewProduct(ProductShopEditor * apProductShopEditor);
		void removeProduct(ProductShopEditor * apProductShopEditor);

		void preparedObjectData(std::vector<std::string> &avecItems, std::string & astrParent);
		void initFromSQLData(std::vector<std::string> & avecstrSQLData);

		enum OPERATION_TYPE	{
			INSERT_PRODUCT = 0,
			MODIFY_PRODUCT,
			PRODUCT_FROM_DB,
			NEW_PRODUCT_INSERT,
			PRODUCT_QUANTITY_PRICE_REQUEST,
			PRODUCT_NAME_CODE_REQUEST,
			MODIFY_QUANTITY_PRICE,
			REMOVE_PRODUCT,
			FILL_PRODUCT_CATEGORY
		};

		void setActiveWidget(const OPERATION_TYPE & aenumSetActiveWidget);

	private:
		osg::ref_ptr<osg::Group> m_pgrpProductsRepresentation;

		AddProduct_GUI * m_pAddProduct_GUI;

		std::list<ProductShopEditor*> m_lstProducts;

		std::vector<std::pair<std::string,std::string>> getDBElements();
		void createProductDB();

		void databaseRequest(ProductShopEditor * apProductShopEditor, OPERATION_TYPE aenumOperationType);
		ProductShopEditorParams initProduct();

	private:
		static DatabaseInterface m_DIProductEditor;

		static DatabaseInterfaceParams getDBParams();
		static std::string getTableName();
		static std::string getDatabaseName();

		static DatabaseInterface * getDatabaseInterface();

	private slots:
		void slotUpdateCombo();
		void slotBoxFrameChanged();
		void slotSelectTexture();
		void slotSetTexture();

	public:
		std::list<std::string> requestData(
			const OPERATION_TYPE & aenumOperationType, 
			std::vector<std::string> & avecstrProductMgrParams
		);

	};
}
#endif //VR_PRODUCT_MANAGER_H