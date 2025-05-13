#pragma once
#include <vector>
#include <string>

using std::string;
using std::vector;

class TsInterface;

class TestScriptFactory {
public:
	TestScriptFactory() = default;
	~TestScriptFactory() = default;

	static TestScriptFactory& getInstance();

	void registerCmd(TsInterface* cmd) {
		m_supportedTs.push_back(cmd);
	}

	TsInterface* getCmd(const string& name) const;
	const vector<TsInterface*>& getSsupportedCmds() const {
		return m_supportedTs;
	}
private:
	vector<TsInterface*> m_supportedTs;

};