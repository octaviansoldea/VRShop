    #ifndef VR_REMOVE_PRODUCT_GUI_H
    #define VR_REMOVE_PRODUCT_GUI_H
    
    #include <QDialog>
    
    #include <osg/Node>
    
    #include "ui_VRRemoveProduct_GUI.h"
    
    namespace VR	{
  	class ProductShopEditor;
    	class ProductController;
    
    	class RemoveProduct_GUI : public QDialog, public Ui::RemoveProduct {
    		Q_OBJECT
    	public:
    		RemoveProduct_GUI();
  		RemoveProduct_GUI(ProductShopEditor * apProductShopEditor);
    		~RemoveProduct_GUI();
    
    	public slots:
    		virtual void accept();
    		virtual void close();
    
    	private:
    		void buildConnections();
    
  		ProductShopEditor * m_pProductShopEditor;
    	};
    }
    #endif //VR_REMOVE_PRODUCT_GUI_H
