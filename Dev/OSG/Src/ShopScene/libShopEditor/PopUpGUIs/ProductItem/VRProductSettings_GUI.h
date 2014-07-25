    #ifndef VR_PRODUCT_SETTINGS_GUI_H
    #define VR_PRODUCT_SETTINGS_GUI_H
    
    #include <QDialog>
    
    #include "ui_VRProductSettings_GUI.h"
    
    namespace VR	{
    	class ProductController;
  	class ProductShopEditor;
    
    	class ProductSettings_GUI : public QDialog, public Ui::ProductSettings {
    	public:
    		ProductSettings_GUI();
 		ProductSettings_GUI(ProductShopEditor * apProductShopEditor);
    
    		~ProductSettings_GUI();
    
    	public slots:
    		void slotSetTexture();
    		void slotCreateRepresentation(const QString & aqstrFrameName);
    		virtual void accept();
    		virtual void close();
    
    	private:
    		Q_OBJECT
    
    		void buildConnections();
  		void initGUI(ProductShopEditor * apProductShopEditor);
    
    		QString m_qstrFileName;
    
  		ProductShopEditor * m_pProductShopEditor;
    	};
    }
    #endif //VR_PRODUCT_SETTINGS_GUI_H
