#include "testscript_interface.h"
#include "testscript_factory.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <cstring>

char TsInterface::m_cbTokens[10][100] = {0,};
int TsInterface::m_numCbToken = 0;

TsInterface::TsInterface(const string& name, int numToken) : m_numToken(numToken) {
    m_names.push_back(name.substr(0, 2));
    m_names.push_back(name);
    TestScriptFactory::getInstance().registerTs(this);
}

int TsInterface::converTokenCpptoC(const vector<string>& cppTokens) {
    int index = 0;
    for (auto cppToken : cppTokens){
        strcpy_s(m_cbTokens[index], cppToken.size() + 1, cppToken.c_str());
        ++index;
    }
    return cppTokens.size();
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