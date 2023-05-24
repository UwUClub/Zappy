import socket


## @brief Debug mode
debug = False


## @brief Class that contains the connection information
class Connection:
    ## @brief Constructor
    def __init__(self, a_host, a_port):
        self._socket = None
        self._host = a_host
        self._port = a_port

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
    def send(self, a_data):
        if debug:
            print("Sending data: {}".format(a_data))
        self._socket.send(str.encode(a_data + "\n"))

    ## @brief Receive data from the server
    ## @return The data received
    def receive(self):
        myData = self._socket.recv(2048).decode()
        if debug:
            print("Received data: {}".format(myData))
        return myData
