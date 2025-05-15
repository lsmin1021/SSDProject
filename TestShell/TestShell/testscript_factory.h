#pragma once
#include <vector>
#include <string>

using std::string;
using std::vector;

class TsInterface;
#include "testscript_interface.h"
class TestScriptFactory {
public:
	TestScriptFactory() = default;
	~TestScriptFactory() = default;

	static TestScriptFactory& getInstance();

	void registerTs(TsInterface* ts) {
		m_supportedTs.push_back(ts);
	}

	TsInterface* getTs(const string& tsName) const;
	const vector<TsInterface*>& getSsupportedCmds() const {
		return m_supportedTs;
	}
private:
	vector<TsInterface*> m_supportedTs;

};