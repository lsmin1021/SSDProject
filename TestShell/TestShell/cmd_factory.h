#pragma once
#include <vector>
#include <string>

using std::string;
using std::vector;

class CmdInterface;

class CmdFactory {
public:
	CmdFactory() = default;
	~CmdFactory() = default;

	static CmdFactory& getInstance();

	void registerCmd(CmdInterface* cmd) {
		m_supportedCmds.push_back(cmd);
	}

	CmdInterface* getCmd(const string& name) const;
private :
	vector<CmdInterface*> m_supportedCmds;

};