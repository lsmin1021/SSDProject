#include "help_cmd.h"
#include "cmd_factory.h"
#include "iostream"
#include "msg_handler.h"

using std::cout;

void HelpCmd::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
}
void HelpCmd::excuteCmd(const vector<string>& tokens)  {
    MSG_PRINT("[Team Name] Clean Code\n\n");
    MSG_PRINT(".######..##.......########....###....##....##.....######...#######..########..######## \n");
    MSG_PRINT(".##....##.##.......##.........##.##...###...##....##....##.##.....##.##.....##.##......\n");
    MSG_PRINT(".##.......##.......##........##...##..####..##....##.......##.....##.##.....##.##......\n");
    MSG_PRINT(".##.......##.......######...##.....##.##.##.##....##.......##.....##.##.....##.######..\n");
    MSG_PRINT(".##.......##.......##.......#########.##..####....##.......##.....##.##.....##.##......\n");
    MSG_PRINT(".##....##.##.......##.......##.....##.##...###....##....##.##.....##.##.....##.##......\n");
    MSG_PRINT("..######..########.########.##.....##.##....##.....######...#######..########..########\n\n");
    MSG_PRINT("[Team Member] : leedoyoung1234 lsmin1021 akachoochoo CHANGHEE-H \n\n");
    MSG_PRINT("[command usage]\n");

    const vector<CmdInterface*>& supportedCmds = CmdFactory::getInstance().getSsupportedCmds();
    for (auto cmd : supportedCmds) {
        cmd->helpCmd();
    }
}
void HelpCmd::helpCmd() const {
    MSG_PRINT("  help                     Show this help message\n");
}