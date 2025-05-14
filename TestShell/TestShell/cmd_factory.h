#pragma once
#include <vector>
#include <string>

using std::string;
using std::vector;

class CmdInterface;
class SsdInterface;

class CmdFactory {
public:
	CmdFactory() = default;
	~CmdFactory() = default;

	static CmdFactory& getInstance();

	void registerCmd(CmdInterface* cmd) {
		m_supportedCmds.push_back(cmd);
	}

	void setSdd(SsdInterface* sdd);

	CmdInterface* getCmd(const string& name) const;

	const vector<CmdInterface*>& getSsupportedCmds() const{
		return m_supportedCmds;
	}
private :
	vector<CmdInterface*> m_supportedCmds;
};