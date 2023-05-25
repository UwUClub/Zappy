#include <netinet/in.h>
#include <string>
#include "ServerData.hpp"
#include <unordered_map>

namespace Zappy::GUI {
    class ClientApi
    {
        public:
            ClientApi(std::string aAddress, unsigned int aPort, std::string aTeamName);
            ~ClientApi();

            /**
             * @brief Connect to the server
             */
            void joinGame();
            /**
             * @brief Disconnect from the server
             */
            void disconnect();
            /**
             * @brief Get connection status: 0 if not connected, 1 if connected
             * @return Status
             */
            int getConnectStatus() const;
            /**
             * @brief Get the file descriptor used to write to the server
             * @return File descriptor
             */
            int getServerFd() const;
            /**
             * @brief Execute read / write flow with the server
             * @return Update status
             */
            int update();

            class ClientException : public std::exception
            {
                public:
                    explicit ClientException(const std::string &aMessage) : _message(aMessage)
                    {}

                    ~ClientException() override = default;

                    [[nodiscard]] const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }

                private:
                    std::string _message;
            };

        private:
            /**
             * @brief Get a sockaddr_in structure
             * @param aAddress Address
             * @param aPort Port
             * @return sockaddr_in structure
             */
            struct sockaddr_in getSockaddr(in_addr_t aAddress, unsigned int aPort);
            /**
             * @brief Read from the server and append the result to the read buffer
             */
            void readFromServer();
            /**
             * @brief Write to the server and remove the written data from the write buffer
             */
            void writeToServer();
            /**
             * @brief Concatenate two char *
             * @param aStr1 First string
             * @param aStr2 Second string
             * @return Concatenated string
             */
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
} // namespace Zappy::GUI
