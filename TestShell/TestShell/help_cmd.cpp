#include "help_cmd.h"
#include "cmd_factory.h"
#include "iostream"


using std::cout;

void HelpCmd::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
}
void HelpCmd::excuteCmd(const vector<string>& tokens)  {
    cout << "[Team Name] Clean Code\n\n";
    cout << ".######..##.......########....###....##....##.....######...#######..########..######## \n";
    cout << ".##....##.##.......##.........##.##...###...##....##....##.##.....##.##.....##.##......\n";
    cout << ".##.......##.......##........##...##..####..##....##.......##.....##.##.....##.##......\n";
    cout << ".##.......##.......######...##.....##.##.##.##....##.......##.....##.##.....##.######..\n";
    cout << ".##.......##.......##.......#########.##..####....##.......##.....##.##.....##.##......\n";
    cout << ".##....##.##.......##.......##.....##.##...###....##....##.##.....##.##.....##.##......\n";
    cout << "..######..########.########.##.....##.##....##.....######...#######..########..########\n\n";

    cout << "[Team Member] : leedoyoung1234 lsmin1021 akachoochoo CHANGHEE-H \n\n";
    cout << "[command usage]\n";

    const vector<CmdInterface*>& supportedCmds = CmdFactory::getInstance().getSsupportedCmds();
    for (auto cmd : supportedCmds) {
        cmd->helpCmd();
    }
}
void HelpCmd::helpCmd() const {
    cout << "  help                     Show this help message\n";
}