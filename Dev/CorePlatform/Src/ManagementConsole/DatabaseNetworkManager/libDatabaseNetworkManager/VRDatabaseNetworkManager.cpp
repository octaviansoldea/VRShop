#include "BasicStringDefinitions.h"
#include <QDataStream>

#include "VRAppData.h"

#include <iostream>
#include <fstream>

#include "VRServerClientCommands.h"

#include "VRAvatarManagerServer.h"
#include "VRUserAccount.h"
#include "VRProductManagerServer.h"
#include "VRCashierManagerServer.h"
#include "VRCashierServer.h"
#include "VRVisitorManagerServer.h"

#include "VRBasketServer.h"

#include "VRDatabaseNetworkManager.h"

using namespace VR;
using namespace std;

//=====================================================================

QByteArray DatabaseNetworkManager::databaseRequest(QByteArray & aData)	{
	string strPFileError = AppData::getFPathLog() + "errors.txt";
	ofstream outFileError;
	outFileError.open(strPFileError,ios::app);

	//Request
	QDataStream in(&aData,QIODevice::ReadOnly);
	in.setVersion(QDataStream::Qt_4_8);

	//Initialize parameters
	quint8 nType;
	in >> nType;

	//Respond
	QByteArray output;
	QDataStream out(&output, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);


	out << quint64(0) << nType;	//Size of the package

	switch (nType)	{
	case ServerClientCommands::NEW_USER_REGISTER:
		{
			QString qstrIP;
			int nUserID;

			in >> qstrIP >> nUserID;

			VisitorManagerServer vms;
			vms.registerVisitor(qstrIP.toStdString(), nUserID);

			break;
		}
	case ServerClientCommands::PRODUCT_REQUEST:
		{
			QString qstrRequest;
			in >> qstrRequest;

			ProductManagerServer pms;
			QString qstrProductData = pms.getProductDataFromDB(qstrRequest.toStdString()).c_str();

			out << qstrProductData;
			break;
		}
	case ServerClientCommands::PRODUCT_TO_BASKET_REQUEST:
		{
			QString qstrProductName;
			QString qstrUserIDName;
			float flProductQuantity;

			in >> qstrUserIDName >> qstrProductName >> flProductQuantity;

			ProductManagerServer pms;
			ProductManagerServer::ProductManagerServerParams pmsp;
			pmsp.m_strUserIDName = qstrUserIDName.toStdString();
			pmsp.m_strProductName = qstrProductName.toStdString();
			pmsp.m_flProductQuantity = flProductQuantity;

			float flQuantity = pms.tryAddProduct2Basket(pmsp);	//Returns approved quantities

			out << flQuantity;

			//Give allocated products to the "OrdersReserved" table in the Cashier DB
			CashierManagerServer cms;
			CashierManagerServer::CashierManagerServerParams cmsp;
			cmsp.m_strUserIDName = qstrUserIDName.toStdString();
			cmsp.m_strProductName = qstrProductName.toStdString();
			cmsp.m_flProductQuantity = flQuantity;

			bool bRes = cms.addProduct2OrdersReserved(cmsp);

			break;
		}
	case ServerClientCommands::REMOVE_PRODUCT_REQUEST:
	case ServerClientCommands::REMOVE_FROM_CASHIER_REQUEST:
		{
			QString qstrUserIDName;
			QString qstrProductName;
			float flProductQuantity;

			in >> qstrUserIDName >> qstrProductName >> flProductQuantity;

			ProductManagerServer pms;
			ProductManagerServer::ProductManagerServerParams pmsp;
			pmsp.m_strUserIDName = qstrUserIDName.toStdString();
			pmsp.m_strProductName = qstrProductName.toStdString();
			pmsp.m_flProductQuantity = flProductQuantity;

			bool bRes = pms.removeProduct(pmsp);

			out << bRes;

			//Remove from "Reserved" list
			CashierManagerServer cms;
			CashierManagerServer::CashierManagerServerParams cmsp;
			cmsp.m_strUserIDName = qstrUserIDName.toStdString();
			cmsp.m_strProductName = qstrProductName.toStdString();

			bRes = cms.removeProductFromOrdersReserved(cmsp);

			break;
		}
	case ServerClientCommands::MODIFY_PRODUCT_REQUEST:
		{
			QString qstrUserIDName;
			QString qstrProductName;
			float flProductQuantity;
			float flProductNewQuantity;

			in >> qstrUserIDName >> qstrProductName >> flProductQuantity >> flProductNewQuantity;

			ProductManagerServer pms;
			ProductManagerServer::ProductManagerServerParams pmsp;
			pmsp.m_strUserIDName = qstrUserIDName.toStdString();
			pmsp.m_strProductName = qstrProductName.toStdString();
			pmsp.m_flProductQuantity = flProductQuantity;
			pmsp.m_flProductNewQuantity = flProductNewQuantity;

			float flNewQuantity = pms.modifyProductQuantity(pmsp);

			out << flNewQuantity;

			//Update the quantity from the "Reserved" list
			CashierManagerServer cms;
			CashierManagerServer::CashierManagerServerParams cmsp;
			cmsp.m_strUserIDName = qstrUserIDName.toStdString();
			cmsp.m_strProductName = qstrProductName.toStdString();
			cmsp.m_flProductQuantity = flNewQuantity;

			bool bRes = cms.removeProductFromOrdersReserved(cmsp);

			break;
		}
	case ServerClientCommands::AVATAR_REGISTER:
		{
			QString qstrAvatarName;
			QString qstrAvatarMatrix;
			in >> qstrAvatarName >> qstrAvatarMatrix;

			AvatarManagerServer ams;
			ams.registerAvatar(qstrAvatarName.toStdString(), qstrAvatarMatrix.toStdString());
			break;
		}
	case ServerClientCommands::AVATAR_UPDATE:
		{
			QString qstrAvatarName;
			QString qstrAvatarMatrix;
			in >> qstrAvatarName >> qstrAvatarMatrix;

			AvatarManagerServer ams;
			ams.updateAvatarData(qstrAvatarName.toStdString(), qstrAvatarMatrix.toStdString());
			break;
		}
	case ServerClientCommands::OTHER_AVATARS_REQUEST:
		{
			QString qstrAvatarNames;
			in >> qstrAvatarNames;

			AvatarManagerServer ams;
			list<string> lstOtherAvatarsData = ams.getAvatarsDataFromDB();
			string strResult;

			if (lstOtherAvatarsData == list<string>())	{
				strResult = "";
			} else {
				list<string>::iterator it = lstOtherAvatarsData.begin();
				for (it; it != lstOtherAvatarsData.end(); it++)	{
					strResult += (*it) + ";";
				}
				strResult.pop_back();
			}

			QString qstrResult = strResult.c_str();
			out << qstrResult;
			break;
		}
	case ServerClientCommands::SIGN_IN_REQUEST:
		{
			QString qstrUser;
			QString qstrPsw;
			in >> qstrUser >> qstrPsw;

			UserAccount ua;
			int nRes = ua.trySignIn(qstrUser.toStdString(), qstrPsw.toStdString()) 
				? ServerClientCommands::PASSED : ServerClientCommands::FAILED;

			out << nRes;
			break;
		}
	case ServerClientCommands::SIGN_UP_REQUEST:
		{
			QString qstrEMail;
			QString qstrPsw;
			QString qstrFirstName;
			QString qstrLastName;

			in >> qstrFirstName >> qstrLastName >> qstrEMail >> qstrPsw;

			UserAccount::UserAccountParams uap;
			uap.m_strEMail = qstrEMail.toStdString();
			uap.m_strFirstName = qstrFirstName.toStdString();
			uap.m_strLastName = qstrLastName.toStdString();
			uap.m_strPsw = qstrPsw.toStdString();

			UserAccount ua;
			int nRes = ua.trySignUp(uap) ? ServerClientCommands::PASSED : ServerClientCommands::FAILED;

			out << nRes;
			break;
		}
	case ServerClientCommands::SIGN_OUT_REQUEST: 
		{
			QString qstrUser;
			in >> qstrUser;

			UserAccount ua;
			int nRes = ua.trySignOut(qstrUser.toStdString()) ? ServerClientCommands::PASSED : ServerClientCommands::FAILED;
			out << nRes;
			break;
		}
	case ServerClientCommands::MODIFY_USER_ACCOUNT_REQUEST: 
		{
			QString qstrUserIDName;
			QString qstrEMail;
			QString qstrPsw;
			QString qstrFirstName;
			QString qstrLastName;
			in >> qstrUserIDName >> qstrFirstName >> qstrLastName >> qstrEMail >> qstrPsw;

			UserAccount::UserAccountParams uap;
			uap.m_strEMail = qstrEMail.toStdString();
			uap.m_strFirstName = qstrFirstName.toStdString();
			uap.m_strLastName = qstrLastName.toStdString();
			uap.m_strPsw = qstrPsw.toStdString();

			UserAccount ua;
			int nRes = ua.tryModifyUserAccount(uap) ? ServerClientCommands::PASSED : ServerClientCommands::FAILED;
			out << nRes;

			break;
		}
	case ServerClientCommands::PURCHASE_REQUEST:
		{
			QString qstrVisitorName;
			QString qstrBasketProdQty;
			in >> qstrVisitorName >> qstrBasketProdQty;

			//User checked
			bool bAccountValid = UserAccount::checkUserAccountValidity(qstrVisitorName.toStdString());

			outFileError << "qstrVisitorName: " << qstrVisitorName.toStdString() << " ";
			outFileError << "qstrBasketProdQty: " << qstrBasketProdQty.toStdString() << " ";
			outFileError << "ServerClientCommands::PURCHASE_REQUEST: " << bAccountValid << endl;

			if (bAccountValid==false)	{
				int nRes = ServerClientCommands::AUTHENTICATION_FAILED;
				out << nRes;
				break;
			}

			//Basket checked
			ProductManagerServer productMgr;
			bool bCanMeetRequest = productMgr.canFullfilRequest(qstrBasketProdQty.toStdString());
			if (bCanMeetRequest==false)	{
				//REPORT THAT QUANTITIES ARE LIMITED
				break;
			}

			//PREPARE INFORMATIONAL RECEIPT; SEND IT INTO CONFIRMATION
			//REAL RECEIPT IS SENT ALONG WITH THE GOODS
			CashierServer cashier;
//			cashier.prepareReceipt(basket);

			break;
		}
	case ServerClientCommands::USER_CONFIRMS_PURCHASE:
		{
			CashierServer cashier;

			//NOT YET IMPLEMENTED

			break;
		}
	case ServerClientCommands::PRODUCT_INFO_REQUEST:
		{
			QString qstrRequest;
			in >> qstrRequest;

			ProductManagerServer pms;
			QString qstrProductData = pms.getProductInfo(qstrRequest.toStdString()).c_str();

			out << qstrProductData;
			break;
		}
	}

	outFileError.close();

	return output;
}