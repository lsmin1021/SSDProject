#include "testscript_interface.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

const string TsInterface::NOT_CHECK_RESULT = "NOT_CHECK_RESULT";
vector<string> TsInterface::m_cbTokens;
string TsInterface::m_checkString;

TsInterface::TsInterface(const string& name, int numToken, AppCb* appCb) : m_name(name), m_numToken(numToken), m_appCb(*appCb){
    UpdateShortCutName();
}

bool TsInterface::executeCmd(const vector<string>& cppTokens, const string& checkString) {
    m_cbTokens = cppTokens;
    m_checkString = checkString;
    return m_appCb.excueteCmd(m_cbTokens, m_checkString);
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