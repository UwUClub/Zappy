#pragma once

#include <functional>
#include <netinet/in.h>
#include <string>
#include <utility>
#include <vector>
#include "ServerData.hpp"
#include "Subscriber.hpp"
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
            ClientApi(std::string aAddress, unsigned int aPort, std::string aTeamName);

            /**
             * @brief ClientApi destructor
             */
            ~ClientApi();

            /**
             * @brief run the client, update the server data, must be called in another thread, use disconnect to stop
             */
            void run();

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
             * @brief geting the server data
             * @return serverData
             */
            [[nodiscard]] const ServerData &getServerData() const;

            /**
             * @brief register a subscriber
             * @param aSubscriber
             */
            void registerSubscriber(Subscriber &aSubscriber);

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
                    explicit ClientException(std::string aMessage)
                        : _message(std::move(aMessage))
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
             * @brief notify subscribers
             * @param aNotification
             */
            void notifySubscribers(std::string &aNotification);

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
             * @param aResponse
             */
            void ReceiveWelcome(const std::string &aResponse);

            /**
             * @brief parse all the error responses, can't be made static because of the unordered_map
             * @param aResponse
             */
            void ReceiveError(const std::string &aResponse);

            /**
             * @brief parse msz response
             * @param aResponse
             */
            void ReceiveMsz(const std::string &aResponse);

            /**
             * @brief parse bct response
             * @param aResponse
             */
            void ReceiveBct(const std::string &aResponse);

            /**
             * @brief parse tna response
             * @param aResponse
             */
            void ReceiveTna(const std::string &aResponse);

            /**
             * @brief parse ppo response
             * @param aResponse
             */
            void ReceivePpo(const std::string &aResponse);

            /**
             * @brief parse plv response
             * @param aResponse
             */
            void ReceivePlv(const std::string &aResponse);

            /**
             * @brief parse pnw response
             * @param aResponse
             */
            void ReceivePnw(const std::string &aResponse);

            /**
             * @brief parse sgt response
             * @param aResponse
             */
            void ReceiveSgt(const std::string &aResponse);

            // Attributes
            std::string _address;
            unsigned int _port;
            std::string _teamName;
            int _connectStatus;
            std::string _readBuffer;
            std::string _writeBuffer;
            int _serverFd;
            ServerData _serverData;
            std::vector<std::reference_wrapper<Subscriber>> _subscribers;
    };
} // namespace Zappy::GUI
