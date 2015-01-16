#include "PipeMgrCreateConnectWriteInterface.h"

bool PipeMgrCreateConnectWriteInterface::createAndConnect() {
	return(PipeMgrCreateConnect::createAndConnect(PIPE_ACCESS_OUTBOUND));
}