#include "ParserData.hpp"

namespace Zappy::GUI {
ParserData::ParserData(std::string address, int port, std::string teamName)
{
    _address = address;
    _port = port;
    _teamName = teamName;
}

void ParserData::parseData(int argc, char **argv)
{
    std::string portStr;

    if (argc < 3) { throw ParserException("Not enough arguments"); }
    if (argv[1] == NULL || argv[2] == NULL) { throw ParserException("Invalid arguments given"); }
    portStr = argv[2];
    _port = std::stoi(portStr);
    if (argv[3] != NULL && argv[4] != NULL) {
        _teamName = argv[3];
    } else {
        _teamName = "localhost";
    }
}

std::string ParserData::getAddress() const { return _address; }

int ParserData::getPort() const { return _port; }

std::string ParserData::getTeamName() const { return _teamName; }
}// namespace Zappy::GUI