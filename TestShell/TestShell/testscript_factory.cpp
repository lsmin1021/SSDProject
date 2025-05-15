#include "testscript_factory.h"
#include "testscript_interface.h"
#include "dll_main.h"

class DummyTestScript :public TsInterface {
public :
	DummyTestScript() : TsInterface("dumy", 0, nullptr) {}
	virtual void checkInvalidTs(const vector<string>& tokens) {}
	virtual void excuteTs(const vector<string>& tokens) {}
};


TsInterface* TsInterface::getInstance(AppCb* appCb) {
	return nullptr;
}

TestScriptFactory& TestScriptFactory::getInstance()
{
	static TestScriptFactory instance;
	return instance;
}

TsInterface* TestScriptFactory::getTs(const string& tsName) const {
	for (auto ts : m_supportedTs) {
		if (tsName == ts->getName() || tsName == ts->getShortCutName()) return ts;
	}
	throw std::invalid_argument("Invalid command: " + tsName);
}
