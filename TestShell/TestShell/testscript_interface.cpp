#include "testscript_interface.h"
#include "testscript_factory.h"
#include <fstream>
#include <stdexcept>


TsInterface::TsInterface(const string& name, int numToken) : m_numToken(numToken) {
    m_names.push_back(name.substr(0, 2));
    TestScriptFactory::getInstance().registerCmd(this);
}

string TsInterface::getReadResult() const {
    std::ifstream file("ssd_output.txt");

    if (!file.is_open()) {
        return "";
    }

    string result;
    getline(file, result);
    file.close();

    return result;
}