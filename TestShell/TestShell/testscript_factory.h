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
	static void generateTs();

	void registerTs(TsInterface* ts) {
		m_supportedTs.push_back(ts);
	}

	TsInterface* getTs(const string& name) const;
	const vector<TsInterface*>& getSsupportedCmds() const {
		return m_supportedTs;
	}
private:
	vector<TsInterface*> m_supportedTs;

};