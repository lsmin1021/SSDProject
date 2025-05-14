#include "testscript_interface.h"
#include "testscript_factory.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

TsInterface::TsInterface(const string& name, int numToken) : m_numToken(numToken) {
    m_names.push_back(name.substr(0, 2));
    m_names.push_back(name);
    TestScriptFactory::getInstance().registerTs(this);
}

int TsInterface::converTokenCpptoC(const vector<string>& cppTokens, char* cTokens[]) {
    int index = 0;
    for (auto cppToken : cppTokens){
        std::cout << cppToken << cppToken.c_str() << "\n";
        cTokens[index] = (char*)cppToken.c_str();
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