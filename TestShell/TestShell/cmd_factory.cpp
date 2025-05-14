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
#include "flush_cmd.h"

static WriteCmd writeCmd;
static ReadCmd readCmd;
static FullWriteCmd fullWriteCmd;
static FullReadCmd fullReadCmd;
static EraseCmd eraseCmd;
static EraseRangeCmd eraseRangeCmd;
static FlushCmd flushCmd;
static ExitCmd exitCmd;
static HelpCmd  helpCmd;

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
		if (name == cmd->getName()) {
			return cmd;
		}
	}
	return nullptr;
}

bool CmdFactory::isSsdCmd(const string& name) {
	for (auto& cmd : m_supportedCmds) {
		if (name == cmd->getName()) {
			return true;
		}
	}
	return false;
}