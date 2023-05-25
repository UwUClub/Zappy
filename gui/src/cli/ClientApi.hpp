#include "ServerData.hpp"
#include "ParserData.hpp"
#include <netinet/in.h>
#include <string>
#include <unordered_map>

namespace Zappy::GUI {
class ClientApi
{
  public:
    ClientApi(std::string aAddress, unsigned int aPort, std::string aTeamName);
    ~ClientApi();

    void joinGame();
    void disconnect();

    int getConnectStatus() const;
    int getServerFd() const;
    int update();

    class ClientException : public std::exception
    {
      public:
        explicit ClientException(const std::string &aMessage) : _message(aMessage) {}

        ~ClientException() override = default;

        [[nodiscard]] const char *what() const noexcept override { return _message.c_str(); }

      private:
        std::string _message;
    };

  private:
    struct sockaddr_in getSockaddr(in_addr_t aAddress, unsigned int aPort);
    void readFromServer();
    void writeToServer();
    char *concatStr(char *aStr1, const char *aStr2);

    char *_address;
    unsigned int _port;
    std::string _teamName;
    int _connectStatus;
    char *_readBuffer;
    char *_writeBuffer;
    int _serverFd;
    ServerData _serverData;
};
}// namespace Zappy::GUI
