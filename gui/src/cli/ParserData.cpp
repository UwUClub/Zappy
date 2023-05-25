#include "ParserData.hpp"

namespace Zappy::GUI {
ParserData::ParserData(std::string address, int port, std::string teamName)
{
    _address = address;
    _port = port;
    _machineName = teamName;
}

void ParserData::parseData(int argc, char **argv)
{
    std::string firstOpt;
    std::string secondOpt;

    if (argc < 3) { throw ParserException("Not enough arguments"); }
    if (argv[1] == NULL || argv[2] == NULL) { throw ParserException("Invalid arguments given"); }
    firstOpt = argv[1];
    if (firstOpt.compare("-p") != 0 && firstOpt.compare("-h") != 0) {
        throw ParserException("Invalid arguments given");
    }
    if (firstOpt.compare("-p") == 0) {
        firstOpt = argv[2];
        _port = std::stoi(firstOpt);
    } else if (firstOpt.compare("-h") == 0) {
        firstOpt = argv[2];
        _machineName = firstOpt;
    }
    if (argc > 3) {
        if (argv[3] != NULL && argv[4] != NULL) {
            secondOpt = argv[3];
            if (secondOpt.compare("-h") != 0 && secondOpt.compare("-p") != 0) {
                throw ParserException("Invalid arguments given");
            }
            if (secondOpt.compare("-h") == 0) {
                _machineName = argv[4];
            } else if (secondOpt.compare("-p") == 0) {
                _port = std::stoi(argv[4]);
            }
        }
    }
    if (_port == 0) { throw ParserException("Invalid port given"); }
    if (_machineName.empty()) { _machineName = "localhost"; }
}

std::string ParserData::getAddress() const { return _address; }

int ParserData::getPort() const { return _port; }

std::string ParserData::getMachineName() const { return _machineName; }
}// namespace Zappy::GUI