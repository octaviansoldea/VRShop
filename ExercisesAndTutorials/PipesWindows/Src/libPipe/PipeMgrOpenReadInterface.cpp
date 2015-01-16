#include "PipeMgrOpenReadInterface.h"

bool PipeMgrOpenReadInterface::openPipe() {
	return(PipeMgrOpen::openPipe(GENERIC_READ));
}