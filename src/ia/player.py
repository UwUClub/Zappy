from .connection import Connection


## @brief Class that contains the player information
class Player:
    ## @brief Constructor
    def __init__(self):
        self._socket = None
        self._name = ""
        self._mapWidth = 0
        self._mapHeight = 0
        self._lookTiles = []

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
        if myForward != "ok\n":
            print("Error: Forward")

    ## @brief Send left command
    ## @return None
    def left(self):
        self.send("Left")
        myLeft = self.receive()
        if myLeft != "ok\n":
            print ("Error: Left rotation")
    
    ## @brief Send right command
    ## @return None
    def right(self):
        self.send("Right")
        myRight = self.receive()
        if myRight != "ok\n":
            print ("Error: Right rotation")

    ## @brief Send take command
    ## @return None
    def take(self, aRessource):
        self.send("Take " + aRessource)
        myTake = self.receive()
        if myTake == "ko\n":
            print ("Object not found")
        elif myTake == "ok\n":
            print ("Object", aRessource, "taken")
        
    ## @brief Send set command
    ## @return None
    def set(self, aRessource):
        self.send("Set " + aRessource)
        mySet = self.receive()
        if mySet == "ko\n":
            print ("Error: Set", aRessource)
        elif mySet == "ok\n":
            print ("Object", aRessource, "set")

    ## @brief Send inventory command and receive the inventory
    ## @return the inventory
    def inventory(self):
        self.send("Inventory")
        myInventory = self.receive()
        if myInventory == "ko\n":
            print ("Error: Inventory")
            return (None)
        else:
            print ("Inventory:", myInventory)
            return (myInventory)

    ## @brief Send Connect_nbr command
    ## @return the number of free slots in the team
    def connectNbr(self):
        self.send("Connect_nbr")
        myConnectNbr = self.receive()
        if myConnectNbr == "ko\n":
            print ("Error: Connect_nbr")
            return (None)
        else:
            print ("Free slots:", myConnectNbr)
            return (int(myConnectNbr))
        
    ## @brief Send look command and receive the map content
    ## @return the map content
    def look(self):
        self.send("Look")
        myLook = self.receive()
        if myLook == "ko\n":
            print ("Error: Look")
            return (None)
        else:
            print ("Look:", myLook)
            return (myLook)

    ## @brief Send broadcast command
    ## @return None
    def broadcast(self, aMessage):
        self.send("Broadcast " + aMessage)
        myBroadcast = self.receive()
        if myBroadcast == "ko\n":
            print ("Error: Broadcast")
        else:
            print ("Broadcast:", myBroadcast)
    
    ## @brief Send Eject command
    ## @return None
    def eject(self):
        self.send("Eject")
        myEject = self.receive()
        if myEject == "ko\n":
            print ("Error: Eject")
        else:
            print ("Eject:", myEject)
  
    ## @brief Send Incantation command
    ## @return Incantation status
    def incantation(self):
        self.send("Incantation")
        myIncantation = self.receive()
        if myIncantation == "ko\n":
            print ("Error: Incantation")
            return (None)
        else:
            print ("Incantation:", myIncantation)
            return (myIncantation)
    ## @brief Parse the look command
    ## @return the look tiles
    def parseLook(self, aLook : str):
        myLook = aLook.split(",")
        for x in myLook:
            # the resources on the tile are stored in a list : [nb_players, food, linemate, deraumere, sibur, mendiane, phiras, thystame]
            myResoucesOnTile = []
            x = str(x)
            if x.find('[') != -1:
                x = x.replace("[", "")
            if x.find(']') != -1:
                x = x.replace("]", "")
            if x.find('\n') != -1:
                x = x.replace("\n", "")
            if x == '':
                continue
            myResoucesOnTile.append(x.count('player'))
            myResoucesOnTile.append(x.count('food'))
            myResoucesOnTile.append(x.count('linemate'))
            myResoucesOnTile.append(x.count('deraumere'))
            myResoucesOnTile.append(x.count('sibur'))
            myResoucesOnTile.append(x.count('mendiane'))
            myResoucesOnTile.append(x.count('phiras'))
            myResoucesOnTile.append(x.count('thystame'))
            self._lookTiles.append(myResoucesOnTile)
            print(x)
        print(f"Look tiles = {self._lookTiles}")
        return (self._lookTiles)