#include "BaseModel.h"

BaseModel::BaseModel() : m_bIsTargetPick(false) {
}

//--------------------------------------------------------------------------

void BaseModel::setIsTargetPick(bool abIsTargetPick)	{
	m_bIsTargetPick = abIsTargetPick;
}

//--------------------------------------------------------------------------

bool BaseModel::getIsTargetPick() const	{
	return m_bIsTargetPick;
}

