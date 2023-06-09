from .connection import Connection

myListObject = ["player", "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]
myLevelCondition = [[1, 5, 1, 0, 0, 0, 0, 0],
                    [2, 5, 1, 1, 1, 0, 0, 0],
                    [2, 5, 2, 0, 1, 0, 2, 0],
                    [4, 5, 1, 1, 2, 0, 1, 0],
                    [4, 5, 1, 2, 1, 3, 0, 0],
                    [6, 5, 1, 2, 3, 0, 1, 0],
                    [6, 5, 2, 2, 2, 2, 2, 1]]

## @brief Class that contains the player information
class Player:
    ## @brief Constructor
    def __init__(self):
        self._socket = None
        self._name = ""
        self._inventory = [0, 0, 0, 0, 0, 0, 0]
        self._lastLook = []
        self._functionIndex = 0
        self._functionList = []

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

    ## @brief Send Fork command
    ## @return None
    def fork(self):
        self.send("Fork")
        myFork = self.receive()
        if myFork == "ko\n":
            print ("Error: Fork")
        else:
            print ("Fork:", myFork)
    
    ## @brief Finds the shortest path to a tile
    ## @param aTile The tile to reach
    ## @return None
    def goTo(self, aTile):
        myMinTile = 1
        myNbToAdd = 1
        myMiddleTile = 0
        myNbMiddleToAdd = 2
        while (aTile > myMinTile):
            self.forward()
            myNbToAdd += 2
            myMinTile += myNbToAdd
            myMiddleTile += myNbMiddleToAdd
            myNbMiddleToAdd += 2
        myNbOfForward = aTile - myMiddleTile
        if (myNbOfForward < 0):
            self.left()
            myNbOfForward = -myNbOfForward
        elif (myNbOfForward > 0):
            self.right()
        for i in range(myNbOfForward):
            self.forward()

    ## @brief Finds the tile with most ressources
    ## @param aRessource The return of a look() parsed command
    ## @return The tile with most ressources
    def findRessource(self, aRessource):
        myNbMax = 0
        myTile = 0
        for i in range(len(aRessource)):
            myNb = 0
            for j in range(len(aRessource[i])):
                myNb += aRessource[i][j]
            if (myNb > myNbMax):
                myNbMax = myNb
                myTile = i
        return (myTile)
    
    ## @brief Take all the ressources on the tile
    ## @param aTile The tile to take the ressources from
    ## @return None
    def takeAll(self, aTile):
        for i in range(1, len(aTile)):
            for j in range(aTile[i]):
                self.take(myListObject[i])

    ## @brief Verify if the incantation is possible
    ## @return True if the incantation is possible, False otherwise
    def verifyIncantation(self):
        if self.parseLook(self.look())[0][0] != myLevelCondition[self._functionIndex][0]:
            return (False)
        for i in range(1, len(self._inventory)):
            if (self._inventory[i - 1] < myLevelCondition[self._functionIndex][i]):
                return (False)
        return (True)

    ## @brief Try to evolve to level 2
    ## @return None
    def level2(self):
        self.parseLook(self.look())
        myTile = self.findRessource()
        self.goTo(myTile)
        self.takeAll(myTile)
        self.inventory()
        if (self.verifyIncantation()):
            self.set("linemate")
            self.incantation()
        else:



