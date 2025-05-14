#include "msg_handler.h"
#include "output_handler_interface.h"

MsgHandler::MsgHandler() {
}

MsgHandler& MsgHandler::getInstance()
{
	static MsgHandler instance;
	return instance;
}

void MsgHandler::setMsgHandler(OutputHandlerInterface* msgHandler)
{
	m_outputHandler = msgHandler;
}

void MsgHandler::print(const string& msg)
{
	if (m_outputHandler)
		return m_outputHandler->print(msg);
}
