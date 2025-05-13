#include "cmd_factory.h"

#include "write_cmd.h"
#include "read_cmd.h"
#include "full_write_cmd.h"
#include "full_read_cmd.h"
#include "help_cmd.h"
#include "exit_cmd.h"
#include "erase_cmd.h"
#include "erase_range_cmd.h"
#include "ssd_interface.h"

static WriteCmd writeCmd;
static ReadCmd readCmd;
static FullWriteCmd fullWriteCmd;
static FullReadCmd fullReadCmd;
static ExitCmd exitCmd;
static HelpCmd  helpCmd;
static EraseCmd eraseCmd;
static EraseRangeCmd eraseRangeCmd;

CmdFactory& CmdFactory::getInstance()
{
	static CmdFactory instance; 
	return instance;
}

void CmdFactory::setSdd(SsdInterface* sdd) {
	for (auto cmd : m_supportedCmds){
		cmd->setSdd(sdd);
	}
}
CmdInterface* CmdFactory::getCmd(const string& name) const {
	for (auto& cmd : m_supportedCmds) {
		vector<string> names = cmd->getName();
		for(auto myName : names)
		if (name == myName) {
			return cmd;
		}
	}
	return nullptr;
}

CmdInterface* CmdFactory::getTs(const string& name) const {
	CmdInterface* tsObj = getCmd(name);
	if(tsObj == nullptr)throw std::invalid_argument("Invalid command: " + name);
	return tsObj;
}
