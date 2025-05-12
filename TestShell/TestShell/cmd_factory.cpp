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

static WriteCmd writeCmd;
static ReadCmd readCmd;
static FullWriteCmd fullWriteCmd;
static FullReadCmd fullReadCmd;
static HelpCmd  helpCmd;
static ExitCmd exitCmd;
static FullWriteAndReadCompareTs fullWriteAndReadCompareTs;
static PartialLbaWriteTs partialLbaWriteTs;
static WriteReadAging writeReadAging;

CmdFactory& CmdFactory::getInstance()
{
	static CmdFactory instance; 
	return instance;
}

CmdInterface* CmdFactory::getCmd(const string& name) const {
	for (auto& cmd : m_supportedCmds) {
		if (name == cmd->getName()) {
			return cmd;
		}
	}
	throw std::invalid_argument("Invalid command: " + name);
}
