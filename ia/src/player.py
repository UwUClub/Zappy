from .connection import Connection


## @brief Class that contains the player information
class Player:
    ## @brief Constructor
    def __init__(self):
        self._socket = None
        self._name = ""
        self._map_width = 0
        self._map_height = 0

    ## @brief Connect to the server
    ## @param info The connection information
    def connect(self, aInfo):
        self._socket = Connection(aInfo.host, int(aInfo.port))
        return self._socket.connect()

    ## @brief Send data to the server
    ## @param data The data to send
    def send(self, aData):
        self._socket.send(aData)

    ## @brief Receive data from the server
    ## @return The data received
    def receive(self):
        return self._socket.receive()

    ## @brief Disconnect from the server
    ## @return None
    def disconnect(self):
        self._socket.disconnect()

    ## @brief Send the team name and receive the welcome message
    ## @return None
    def preliminaries(self):
        self.receive()
        self.send(self._name)
        self.receive()

    ## @brief Set the team name
    ## @param name The team name
    def setTeamName(self, aName):
        self._name = aName

    ## @brief Get the map size
    ## @return None
    def msz(self):
        self.send("msz")
        myMsz = self.receive()
        myMsz = myMsz.split(" ")
        if myMsz[0] == "msz":
            my_msz = myMsz[1:]
        self._map_width = int(myMsz[0])
        self._map_height = int(myMsz[1])
