from .connection import Connection


## @brief Class that contains the player information
class Player:
    ## @brief Constructor
    def __init__(self):
        self._socket = None
        self._name = ""
        self._mapWidth = 0
        self._mapHeight = 0
        self._posX = 0
        self._posY = 0
        self._orientation = 0

    ## @brief Connect to the server
    ## @param info The connection information
    def connect(self, aInfo):
        self._socket = Connection(aInfo._host, int(aInfo._port))
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
        self._mapWidth = int(myMsz[0])
        self._mapHeight = int(myMsz[1])

    ## @brief Send forward command
    ## @return None
    def forward(self):
        self.send("Forward")
        myForward = self.receive()
        if myForward == "ok":
            if (self._orientation == 0):
                self._posY -= 1
            elif (self._orientation == 90):
                self._posX += 1
            elif (self._orientation == 180):
                self._posY += 1
            elif (self._orientation == 270):
                self._posX -= 1
        else:
            print("Error: Forward")

    ## @brief Send left command
    ## @return None
    def left(self):
        self.send("Left")
        myLeft = self.receive()
        if myLeft == "ok":
            self._orientation += 90
        else:
            print ("Error: Left rotation")
        if (self._orientation == 360):
            self._orientation = 0
    
    ## @brief Send right command
    ## @return None
    def right(self):
        self.send("Right")
        myRight = self.receive()
        if myRight == "ok":
            self._orientation -= 90
        else:
            print ("Error: Right rotation")
        if (self._orientation == -90):
            self._orientation = 270
        

