#include "help_cmd.h"
#include "cmd_factory.h"
#include "iostream"


using std::cout;

void HelpCmd::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
}
void HelpCmd::excuteCmd(const vector<string>& tokens)  {
    LOG_PRINT("HelpCmd", "[Team Name] Clean Code\n\n");
    LOG_PRINT("HelpCmd", ".######..##.......########....###....##....##.....######...#######..########..######## \n");
    LOG_PRINT("HelpCmd", ".##....##.##.......##.........##.##...###...##....##....##.##.....##.##.....##.##......\n");
    LOG_PRINT("HelpCmd", ".##.......##.......##........##...##..####..##....##.......##.....##.##.....##.##......\n");
    LOG_PRINT("HelpCmd", ".##.......##.......######...##.....##.##.##.##....##.......##.....##.##.....##.######..\n");
    LOG_PRINT("HelpCmd", ".##.......##.......##.......#########.##..####....##.......##.....##.##.....##.##......\n");
    LOG_PRINT("HelpCmd", ".##....##.##.......##.......##.....##.##...###....##....##.##.....##.##.....##.##......\n");
    LOG_PRINT("HelpCmd", "..######..########.########.##.....##.##....##.....######...#######..########..########\n\n");

    LOG_PRINT("HelpCmd", "[Team Member] : leedoyoung1234 lsmin1021 akachoochoo CHANGHEE-H \n\n");
    LOG_PRINT("HelpCmd", "[command usage]\n");

    const vector<CmdInterface*>& supportedCmds = CmdFactory::getInstance().getSsupportedCmds();
    for (auto cmd : supportedCmds) {
        cmd->helpCmd();
    }
}
void HelpCmd::helpCmd() const {
    LOG_PRINT("HelpCmd", "  help                     Show this help message\n");
}