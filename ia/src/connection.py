import socket


## @brief Debug mode
debug = False


## @brief Class that contains the connection information
class Connection:
    ## @brief Constructor
    def __init__(self, aHost, aPort):
        self._socket = None
        self._host = aHost
        self._port = aPort

    ## @brief Connect to the server
    ## @return 0 if the connection is successful, -1 otherwise
    def connect(self):
        if debug:
            print("Connecting to {} on port {}".format(self._host, self._port))
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self._socket.connect((self._host, self._port))
        except Exception as myException:
            print("Error: {}".format(myException))
            return -1
        return 0

    ## @brief Disconnect from the server
    ## @return None
    def disconnect(self):
        if debug:
            print("Disconnecting from {} on port {}".format(self._host, self._port))
        self._socket.close()
        self._socket = None

    ## @brief Send data to the server
    ## @param data The data to send
    def send(self, aData):
        if debug:
            print("Sending data: {}".format(aData))
        self._socket.send(str.encode(aData + "\n"))

    ## @brief Receive data from the server
    ## @return The data received
    def receive(self):
        myData = self._socket.recv(2048).decode()
        if debug:
            print("Received data: {}".format(myData))
        return myData
