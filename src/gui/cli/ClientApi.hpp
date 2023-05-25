#include <netinet/in.h>
#include <string>
#include "ServerData.hpp"
#include <unordered_map>

namespace Zappy::GUI {
    class ClientApi
    {
        public:
            /**
             * @brief ClientApi constructor
             * @param aAddress
             * @param aPort
             * @param aTeamName
             */
            ClientApi(const std::string &aAddress, unsigned int aPort, const std::string &aTeamName);

            /**
             * @brief ClientApi destructor
             */
            ~ClientApi();

            /**
             * @brief joinGame
             */
            void joinGame();

            /**
             * @brief disconnect
             */
            void disconnect();

            /**
             * @brief geting the connect status
             * @return connectStatus
             */
            [[nodiscard]] int getConnectStatus() const;

            /**
             * @brief geting the server fd
             * @return serverFd
             */
            [[nodiscard]] int getServerFd() const;

            /**
             * @brief geting the server data
             * @return serverData
             */
            int update();
            /**
             * @brief Append a command to the write buffer
             * @param aCommand Command
             */
            void sendCommand(const std::string &aCommand);

            /**
             * @brief ClientException class
             */
            class ClientException : public std::exception
            {
                public:
                    /**
                     * @brief ClientException constructor
                     * @param aMessage
                     */
                    explicit ClientException(const std::string &aMessage) : _message(aMessage)
                    {}

                    /**
                     * @brief ClientException destructor
                     */
                    ~ClientException() override = default;

                    /**
                     * @brief Return the message of the exception
                     * @return message
                     */
                    [[nodiscard]] const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }

                private:
                    std::string _message;
            };

        private:
            /**
             * @brief get socket address
             * @param aAddress
             * @param aPort
             * @return sockaddr_in
             */
            static struct sockaddr_in getSockaddr(in_addr_t aAddress, unsigned int aPort);

            /**
             * @brief reading information from server
             */
            void readFromServer();

            /**
             * @brief writing information to server
             */
            void writeToServer();

            /**
             * @brief parse information from server
             */
            void ParseServerResponses();

            /**
             * @brief parse welcome response
             */
            void ReceiveWelcome(std::string aResponse);

            /**
             * @brief parse msz response
             */
            void ReceiveMsz(std::string aResponse);

            // Attributes
            char *_address;
            unsigned int _port;
            std::string _teamName;
            int _connectStatus;
            std::string _readBuffer;
            std::string _writeBuffer;
            int _serverFd;
            ServerData _serverData;
    };
} // namespace Zappy::GUI
