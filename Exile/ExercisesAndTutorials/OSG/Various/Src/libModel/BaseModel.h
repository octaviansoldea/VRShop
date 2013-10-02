#ifndef BASE_MODEL_H
#define BASE_MODEL_H

class BaseModel {
public:
	BaseModel();

	virtual void setIsTargetPick(bool abIsTargetPick);
	virtual bool getIsTargetPick() const;

protected:
	bool m_bIsTargetPick;
};
#endif //BASE_MODEL_H