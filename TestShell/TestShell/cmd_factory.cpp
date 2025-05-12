#include "cmd_factory.h"

#include "write_cmd.h"
#include "read_cmd.h"
#include "full_write_cmd.h"
#include "full_read_cmd.h"
#include "help_cmd.h"
#include "exit_cmd.h"
#include "full_write_read_compare_ts.h"
#include "partial_lba_write_ts.h"
#include "write_read_aging_ts.h"
#include "ssd_interface.h"

static WriteCmd writeCmd;
static ReadCmd readCmd;
static FullWriteCmd fullWriteCmd;
static FullReadCmd fullReadCmd;
static ExitCmd exitCmd;
static HelpCmd  helpCmd;
static FullWriteAndReadCompareTs fullWriteAndReadCompareTs;
static PartialLbaWriteTs partialLbaWriteTs;
static WriteReadAging writeReadAging;

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
	throw std::invalid_argument("Invalid command: " + name);
}
