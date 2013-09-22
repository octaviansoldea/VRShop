#ifndef CUPBOARD_H
#define CUPBOARD_H

#include <vector>

#include "vtkSmartPointer.h"
#include "vtkAssembly.h"

class vtkTransform;

#include "Shelf.h"


class Cupboard : public vtkAssembly {
public:
	static Cupboard * New();

	~Cupboard();

	std::string getSQLPrintCommand() const;
	void initFromSQLData(const std::string & astrSQLData);

	void initCupboard();

	void AddShelf(Shelf * aShelf);
	//void AddPlateMargin(const Shelf & aShelf);	
private:
	Shelf * m_arrpShelf;
	Cupboard();

	std::vector < Shelf *> m_arrShelf;
	std::vector < Shelf	*> m_arrPlateMargin;
};

#endif //CUPBOARD_H