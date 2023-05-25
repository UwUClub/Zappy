#include <iostream>

namespace Zappy::GUI {
class ParserData
{
  public:
    ParserData(std::string address, int port, std::string teamName);
    ~ParserData() = default;

    void parseData(int argc, char **argv);

    std::string getAddress() const;
    int getPort() const;
    std::string getMachineName() const;

    class ParserException : public std::exception
    {
      public:
        explicit ParserException(const std::string &aMessage) : _message(aMessage) {}

        ~ParserException() override = default;

        [[nodiscard]] const char *what() const noexcept override { return _message.c_str(); }

      private:
        std::string _message;
    };

  private:
    std::string _address;
    int _port;
    std::string _machineName;
};
}// namespace Zappy::GUI