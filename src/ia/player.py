from connection import Connection
import time

myListObject = ["player", "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]
myLevelCondition = [[1, 7, 1, 0, 0, 0, 0, 0],
                    [2, 7, 1, 1, 1, 0, 0, 0],
                    [2, 7, 2, 0, 1, 0, 2, 0],
                    [4, 7, 1, 1, 2, 0, 1, 0],
                    [4, 7, 1, 2, 1, 3, 0, 0],
                    [6, 7, 1, 2, 3, 0, 1, 0],
                    [6, 7, 2, 2, 2, 2, 2, 1]]

## @brief Class that contains the player information
class Player:
    ## @brief Constructor
    def __init__(self):
        self._socket = None
        self._name = ""
        self._functionIndex = 0
        self._functionList = [self.goToLevel2, self.goToLevel3, self.goToLevel4, self.goToLevel5, self.goToLevel6, self.goToLevel7, self.goToLevel8]
        self._lookTiles = []
        self._inventory = [0, 0, 0, 0, 0, 0, 0]
        self._lastReceivedMessage = ""
        self._direction = 0
        self._parsedMessage = ""
        self._nbFunctInList = 0

    ## @brief Connect to the server
    ## @param info The connection information
    def connect(self, aInfo):
        self._socket = Connection(aInfo._host, int(aInfo._port))
        return self._socket.connect()

    ## @brief Send data to the server
    ## @param data The data to send
    def send(self, aData):
        self._nbFunctInList += 1
        if (self._nbFunctInList == 10):
            time.sleep(1)
        self._socket.send(aData)

    ## @brief Receive data from the server
    ## @return The data received
    def receive(self):
        nbMessage = 0
        message = self._socket.receive()
        for i in range(len(message)):
            if (message[i] == '\n'):
                nbMessage += 1
        if (nbMessage > 1):
            message = message.split('\n')
            message.remove('')
            print(message)
            for i in range(nbMessage):
                if (message[i] == "dead\n"):
                    print("Dead")
                    self.disconnect()
                    exit(0)
                if (message[i][0:7] == "message"):
                    self._lastReceivedMessage = message[i]
                    message.remove(message[i])
                    self._nbFunctInList -= 1
                    print (message[0].join("\n"))
                    return message[0].join("\n")
        if (message == "dead\n"):
            print("Dead")
            self.disconnect()
            exit(0)
        if (message[0:7] == "message"):
            self._lastReceivedMessage = message
            return self.receive()
        return message

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
            return ("Error: Forward")
        return (myForward)

    ## @brief Send left command
    ## @return None
    def left(self):
        self.send("Left")
        myLeft = self.receive()
        if myLeft != "ok\n":
            print ("Error: Left rotation")
            return ("Error: Left rotation")
        return (myLeft)

    ## @brief Send right command
    ## @return None
    def right(self):
        self.send("Right")
        myRight = self.receive()
        if myRight != "ok\n":
            print ("Error: Right rotation")
            return ("Error: Right rotation")
        return (myRight)

    ## @brief Send take command
    ## @return None
    def take(self, aRessource):
        self.send("Take " + aRessource)
        myTake = self.receive()
        if myTake == "ko\n":
            print ("Object not found", aRessource)
            return ("Object not found " + aRessource)
        elif myTake == "ok\n":
            print ("Object", aRessource, "taken")
            return ("Object " + aRessource + " taken")

    ## @brief Send set command
    ## @return None
    def set(self, aRessource):
        self.send("Set " + aRessource)
        mySet = self.receive()
        if mySet == "ko\n":
            print ("Error: Set", aRessource)
            return ("Error: Set " + aRessource)
        elif mySet == "ok\n":
            print ("Object", aRessource, "set")
            return ("Object " + aRessource + " set")

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
            return (int(myConnectNbr[-2]))

    ## @brief Send look command and receive the map content
    ## @return the map content
    def look(self):
        self.send("Look")
        myLook = self.receive()
        if myLook == "ko\n":
            print ("Error: Look")
            return ("")
        else:
            print ("Look:", myLook)
            return (myLook)

    ## @brief Crypt the message
    ## @return the crypted message
    def cryptMessage(self, aMessage):
        myCryptedMessage = ""
        for i in range(len(aMessage)):
            myCryptedMessage += chr(ord(aMessage[i]) + 5)
        return (myCryptedMessage)

    ## @brief Decrypt the message
    ## @return the decrypted message
    def decryptMessage(self, aMessage):
        myDecryptedMessage = ""
        for i in range(len(aMessage) - 1):
            myDecryptedMessage += chr(ord(aMessage[i]) - 5)
        return (myDecryptedMessage)

    ## @brief Send broadcast command
    ## @return None
    def broadcast(self, aMessage):
        myMessage = self.cryptMessage(aMessage)
        print ("Broadcast:", myMessage)
        self.send("Broadcast " + myMessage)
        myBroadcast = self.receive()
        if myBroadcast == "ko\n":
            print ("Error: Broadcast")
            return ("Error: Broadcast")
        else:
            print ("Broadcast:", myBroadcast)
            return ("Broadcast: " + self.decryptMessage(myBroadcast))

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
            print("Error: Incantation")
            return (False)
        else:
            return (True)

    ## @brief Send Fork command
    ## @return None
    def fork(self):
        self.send("Fork")
        myFork = self.receive()
        if myFork == "ko\n":
            print ("Error: Fork")
            return ("Error: Fork")
        else:
            print ("Fork:", myFork)
            return ("Fork: " + myFork)

    ## @brief Parse the look command
    ## @return the look tiles
    def parseLook(self, aLook : str):
        self._lookTiles = []
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
            myResoucesOnTile.append(x.count('player'))
            myResoucesOnTile.append(x.count('food'))
            myResoucesOnTile.append(x.count('linemate'))
            myResoucesOnTile.append(x.count('deraumere'))
            myResoucesOnTile.append(x.count('sibur'))
            myResoucesOnTile.append(x.count('mendiane'))
            myResoucesOnTile.append(x.count('phiras'))
            myResoucesOnTile.append(x.count('thystame'))
            self._lookTiles.append(myResoucesOnTile)
        return (self._lookTiles)

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

    ## @brief Finds the best tile to go to
    ## @param aTile The tile to reach
    ## @return The tile with most ressources useful to level up
    def findBestTile(self):
        myTilesToGo = []
        myNbRessources = 0
        mytile = 0
        for i in range(len(self._lookTiles)):
            for j in range(len(self._lookTiles[i])):
                if (self._lookTiles[i][j] > myLevelCondition[self._functionIndex][j]):
                    myNbRessources += 1
            myTilesToGo.append(myNbRessources)
            myNbRessources = 0
        myTile = myTilesToGo.index(max(myTilesToGo))
        return (myTile)

    ## @brief Finds the tile with most ressources
    ## @param aRessource The return of a look() parsed command
    ## @return The tile with most ressources
    def findRessource(self):
        myNbMax = 0
        myTile = 0
        for i in range(len(self._lookTiles)):
            myNb = 0
            for j in range(1, len(self._lookTiles[i])):
                myNb += self._lookTiles[i][j]
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

    ## @brief Set the ressources on the tile for the incantation
    ## @return None
    def setElevationRessources(self):
        for i in range(2, len(myListObject)):
            for j in range(myLevelCondition[self._functionIndex][i]):
                self.set(myListObject[i])

    ## @brief Verify if the incantation is possible
    ## @return True if the incantation is possible, False otherwise
    def verifyIncantation(self):
        for i in range(1, len(self._inventory)):
            if (self._inventory[i - 1] < myLevelCondition[self._functionIndex][i]):
                return (False)
        return (True)

    ## @brief Parse the inventory command
    ## @return the inventory
    def parseInventory(self, aInventory : str):
        idx = 0
        myInventory = aInventory.split(",")
        for x in myInventory:
            x = str(x)
            if x.find('[') != -1:
                x = x.replace("[", "")
            if x.find(']') != -1:
                x = x.replace("]", "")
            if x.find('\n') != -1:
                x = x.replace("\n", "")
            if x == '':
                continue
            myInventory = x.split(" ")
            for y in myInventory:
                y = str(y)
                if y == '':
                    myInventory.remove(y)
            self._inventory[idx] = int(myInventory[1])
            idx+=1
        return (self._inventory)

    ## @brief Receive broadcast message
    ## @return The broadcast message
    def parseReceiveBroadcast(self):
        if (self._lastReceivedMessage == ""):
            return
        myMessage = self._lastReceivedMessage[11:]
        print ("Message received:", myMessage)
        self._parsedMessage = self.decryptMessage(myMessage)
        if (len(self._parsedMessage) != 9):
            return
        if (int(self._parsedMessage[8]) == self._functionIndex + 1):
            self._direction = int(self._lastReceivedMessage[8])
        print ("Message received:", self._parsedMessage)
        self._lastReceivedMessage = ""

    ## @brief Try to evolve to level 2
    ## @return None
    def goToLevel2(self):
        print(self.parseReceiveBroadcast())
        self.parseLook(self.look())
        myTile = self.findBestTile()
        self.goTo(myTile)
        self.takeAll(self._lookTiles[myTile])
        self.parseInventory(self.inventory())
        if (self.verifyIncantation()):
            if self.parseLook(self.look())[0][0] == myLevelCondition[self._functionIndex][0]:
                self.setElevationRessources()
                if (self.incantation()):
                    self._functionIndex += 1
                    if (self.connectNbr() == 0):
                        self.fork()

    ## @brief Try to evolve to level 3
    ## @return None
    def goToLevel3(self):
        self.parseReceiveBroadcast()
        self.parseLook(self.look())
        myTile = self.findRessource()
        self.goTo(myTile)
        self.takeAll(self._lookTiles[myTile])
        self.parseInventory(self.inventory())
        if (self._parsedMessage == "regroup 2"):
            self.findPlayer()
            print("Found")
            myReceivedMessage = ""
            while (myReceivedMessage != "Current level: 3\n" and myReceivedMessage != "ko\n"):
                myReceivedMessage = self.receive()
                if (myReceivedMessage == "Current level: 3\n"):
                    self._functionIndex += 1
                    self.fork()
                    return
        if (self.verifyIncantation() and self._parsedMessage != "regroup 2"):
            self.broadcast("regroup 2")
            mySelfTile = self.parseLook(self.look())[0][0]
            while mySelfTile != myLevelCondition[self._functionIndex][0]:
                mySelfTile = self.parseLook(self.look())[0][0]
                time.sleep(1)
                self.broadcast("regroup 2")
            self.setElevationRessources()
            if (self.incantation()):
                self._functionIndex += 1
                self.fork()

    ## @brief Try to evolve to level 4
    ## @return None
    def goToLevel4(self):
        self.parseReceiveBroadcast()
        self.parseLook(self.look())
        myTile = self.findRessource()
        self.goTo(myTile)
        self.takeAll(self._lookTiles[myTile])
        self.parseInventory(self.inventory())
        if (self._parsedMessage == "regroup 3"):
            self.findPlayer()
            print("Found")
            myReceivedMessage = ""
            while (myReceivedMessage != "Current level: 4\n" and myReceivedMessage != "ko\n"):
                myReceivedMessage = self.receive()
                if (myReceivedMessage == "Current level: 4\n"):
                    self._functionIndex += 1
                    self.fork()
                    return
        if (self.verifyIncantation() and self._parsedMessage != "regroup 3"):
            self.broadcast("regroup 3")
            mySelfTile = self.parseLook(self.look())[0][0]
            while mySelfTile != myLevelCondition[self._functionIndex][0]:
                mySelfTile = self.parseLook(self.look())[0][0]
                time.sleep(1)
                self.broadcast("regroup 3")
            self.setElevationRessources()
            if (self.incantation()):
                self._functionIndex += 1
                self.fork()

    ## @brief Try to evolve to level 5
    ## @return None
    def goToLevel5(self):
        self.parseReceiveBroadcast()
        self.parseLook(self.look())
        myTile = self.findRessource()
        self.goTo(myTile)
        self.takeAll(self._lookTiles[myTile])
        self.parseInventory(self.inventory())
        if (self._parsedMessage == "regroup 4"):
            self.findPlayer()
            print("Found")
            myReceivedMessage = ""
            while (myReceivedMessage != "Current level: 5\n" and myReceivedMessage != "ko\n"):
                myReceivedMessage = self.receive()
                if (myReceivedMessage == "Current level: 5\n"):
                    self._functionIndex += 1
                    self.fork()
                    return
        if (self.verifyIncantation() and self._parsedMessage != "regroup 4"):
            self.broadcast("regroup 4")
            mySelfTile = self.parseLook(self.look())[0][0]
            while mySelfTile != myLevelCondition[self._functionIndex][0]:
                mySelfTile = self.parseLook(self.look())[0][0]
                time.sleep(1)
                self.broadcast("regroup 4")
            self.setElevationRessources()
            if (self.incantation()):
                self._functionIndex += 1
                self.fork()

    ## @brief Try to evolve to level 6
    ## @return None
    def goToLevel6(self):
        self.parseReceiveBroadcast()
        self.parseLook(self.look())
        myTile = self.findRessource()
        self.goTo(myTile)
        self.takeAll(self._lookTiles[myTile])
        self.parseInventory(self.inventory())
        if (self._parsedMessage == "regroup 5"):
            self.findPlayer()
            print("Found")
            myReceivedMessage = ""
            while (myReceivedMessage != "Current level: 6\n" and myReceivedMessage != "ko\n"):
                myReceivedMessage = self.receive()
                if (myReceivedMessage == "Current level: 6\n"):
                    self._functionIndex += 1
                    self.fork()
                    return
        if (self.verifyIncantation() and self._parsedMessage != "regroup 5"):
            self.broadcast("regroup 5")
            mySelfTile = self.parseLook(self.look())[0][0]
            while mySelfTile != myLevelCondition[self._functionIndex][0]:
                mySelfTile = self.parseLook(self.look())[0][0]
                time.sleep(1)
                self.broadcast("regroup 5")
            self.setElevationRessources()
            if (self.incantation()):
                self._functionIndex += 1
                self.fork()

    ## @brief Try to evolve to level 7
    ## @return None
    def goToLevel7(self):
        self.parseReceiveBroadcast()
        self.parseLook(self.look())
        myTile = self.findRessource()
        self.goTo(myTile)
        self.takeAll(self._lookTiles[myTile])
        self.parseInventory(self.inventory())
        if (self._parsedMessage == "regroup 6"):
            self.findPlayer()
            print("Found")
            myReceivedMessage = ""
            while (myReceivedMessage != "Current level: 7\n" and myReceivedMessage != "ko\n"):
                myReceivedMessage = self.receive()
                if (myReceivedMessage == "Current level: 7\n"):
                    self._functionIndex += 1
                    self.fork()
                    return
        if (self.verifyIncantation() and self._parsedMessage != "regroup 6"):
            self.broadcast("regroup 6")
            mySelfTile = self.parseLook(self.look())[0][0]
            while mySelfTile != myLevelCondition[self._functionIndex][0]:
                mySelfTile = self.parseLook(self.look())[0][0]
                time.sleep(1)
                self.broadcast("regroup 6")
            self.setElevationRessources()
            if (self.incantation()):
                self._functionIndex += 1
                self.fork()

    ## @brief Try to evolve to level 8
    ## @return None
    def goToLevel8(self):
        self.parseReceiveBroadcast()
        self.parseLook(self.look())
        myTile = self.findRessource()
        self.goTo(myTile)
        self.takeAll(self._lookTiles[myTile])
        self.parseInventory(self.inventory())
        if (self._parsedMessage == "regroup 7"):
            self.findPlayer()
            print("Found")
            myReceivedMessage = ""
            while (myReceivedMessage != "Current level: 8\n" and myReceivedMessage != "ko\n"):
                myReceivedMessage = self.receive()
                if (myReceivedMessage == "Current level: 8\n"):
                    self._functionIndex += 1
                    self.fork()
                    return
        if (self.verifyIncantation() and self._parsedMessage != "regroup 7"):
            self.broadcast("regroup 7")
            mySelfTile = self.parseLook(self.look())[0][0]
            while mySelfTile != myLevelCondition[self._functionIndex][0]:
                mySelfTile = self.parseLook(self.look())[0][0]
                time.sleep(1)
                self.broadcast("regroup 7")
            self.setElevationRessources()
            if (self.incantation()):
                self._functionIndex += 1
                self.fork()