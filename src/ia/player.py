from .connection import Connection
import time
import random

myListObject = ["player", "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]
myLevelCondition = [[1, 7, 1, 0, 0, 0, 0, 0],
                    [2, 15, 1, 1, 1, 0, 0, 0],
                    [2, 15, 2, 0, 1, 0, 2, 0],
                    [4, 20, 1, 1, 2, 0, 1, 0],
                    [4, 20, 1, 2, 1, 3, 0, 0],
                    [6, 25, 1, 2, 3, 0, 1, 0],
                    [6, 25, 2, 2, 2, 2, 2, 1]]

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
        self._direction = -1
        self._parsedMessage = ""
        self._nbFunctInList = 0
        self._id = random.randint(8, 9999)


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
                elif (message[i][0:7] == "message"):
                    self._lastReceivedMessage = message[i]
                    self.parseReceiveBroadcast()
                else:
                    return message[i]+"\n"
            return self.receive()
        if (message == "dead\n"):
            print("Dead")
            self.disconnect()
            exit(0)
        if (message[0:7] == "message"):
            self._lastReceivedMessage = message
            self.parseReceiveBroadcast()
            return self.receive()
        return message

    ## @brief Receive data from the server
    ## @return The data received
    def receive2(self):
        message = self._socket.receive()
        if (message == "dead\n"):
            print("Dead")
            self.disconnect()
            exit(0)
        if (message[0:7] == "message"):
            self._lastReceivedMessage = message
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
            print ("Object not found", aRessource)
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
            return
        else:
            return (myInventory)

    ## @brief Send Connect_nbr command
    ## @return the number of free slots in the team
    def connectNbr(self):
        self.send("Connect_nbr")
        myConnectNbr = self.receive()
        if myConnectNbr == "ko\n":
            print ("Error: Connect_nbr")
            return
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
        if myIncantation == "Elevation underway\n":
            myIncantation = self.receive()
            if myIncantation == "ko\n":
                print("Error: Incantation")
                return (False)
            else:
                return (True)
        else:
            return (False)

    ## @brief Send Fork command
    ## @return None
    def fork(self):
        self.send("Fork")
        myFork = self.receive()
        if myFork == "ko\n":
            print ("Error: Fork")
        else:
            print ("Fork:", myFork)

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
        if (myNbMax == 0):
            self.forward()
        return (myTile)

    ## @brief Take all the ressources on the tile
    ## @param aTile The tile to take the ressources from
    ## @return None
    def takeAll(self, aTile):
        print(self.parseLook(self.look())[0][0])
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
        self._parsedMessage = self.decryptMessage(myMessage)
        if (self._parsedMessage == "found"):
            self._direction = int(self._lastReceivedMessage[8])
        if (len(self._parsedMessage) < 9):
            return
        if (int(self._parsedMessage[8:]) == self._id):
            self._direction = int(self._lastReceivedMessage[8])
        self._lastReceivedMessage = ""
        
    ## @brief Try to found the player who sent the broadcast message
    ## @return None
    def findPlayer(self):
        if (self._direction == -1):
            return (False)
        myTile = self.parseLook(self.look())[0][0]
        myTimeOut = 0
        while (self._direction != 0 or myTile == 1):
            if (myTimeOut == 20):
                self._direction = -1
                return (False)
            print("Direction1:", self._direction)
            if (self._direction == 1):
                self.forward()
            elif (self._direction == 2 or self._direction == 3):
                self.left()
                self.forward()
                self._direction -= 2
            elif (self._direction == 4 or self._direction == 5):
                self.left()
                self.left()
                self.forward()
                self._direction -= 4
            elif (self._direction == 6 or self._direction == 7 or self._direction == 8):
                self.right()
                self.forward()
                self._direction -= 6
            if (self._direction == 0):
                self._direction = 8
            self.take("food")
            print("Direction2:", self._direction)
            self.parseReceiveBroadcast()
            myTile = self.parseLook(self.look())[0][0]
            if (myTile > 1):
                time.sleep(1)
            myTimeOut += 1
        self._direction = -1
        return (True)

    ## @brief Try to evolve to level 2
    ## @return None
    def goToLevel2(self):
        print(self.parseReceiveBroadcast())
        self.parseLook(self.look())
        myTile = self.findRessource()
        self.goTo(myTile)
        self.takeAll(self._lookTiles[myTile])
        self.parseInventory(self.inventory())
        if (self.verifyIncantation()):
            if self.parseLook(self.look())[0][0] == myLevelCondition[self._functionIndex][0]:
                self.setElevationRessources()
                if (self.incantation()):
                    self._functionIndex += 1
                    self.fork()

    ## @brief Try to evolve to level 3
    ## @return None
    def goToLevel3(self):
        self.parseLook(self.look())
        myTile = self.findRessource()
        self.goTo(myTile)
        self.takeAll(self._lookTiles[myTile])
        self.parseInventory(self.inventory())
        if ((self._parsedMessage == "regroup 2" or self._parsedMessage == "regroup "+str(self._id)) and self._inventory[0] > 10):
            self.broadcast("regroup "+str(self._id))
            myTimeOut = 0
            while (self.findPlayer() == False):
                if (myTimeOut == 5):
                    return
                self.broadcast("regroup "+str(self._id))
                self.parseLook(self.look())
                myTile = self.findRessource()
                self.goTo(myTile)
                self.takeAll(self._lookTiles[myTile])
                myTimeOut += 1
            print("Found")
            self.broadcast("found")
            myReceivedMessage = ""
            while (myReceivedMessage != "Current level: 3\n" and myReceivedMessage != "ko\n"):
                myReceivedMessage = self.receive()
                if (myReceivedMessage == "Current level: 3\n"):
                    self._functionIndex += 1
                    self.fork()
                    return
        myMateId = ""
        if (self.verifyIncantation() and (self._parsedMessage == "" or self._parsedMessage == "done")):
            mySelfTile = ""
            while (myMateId == ""):
                self.broadcast("regroup 2")
                myMateId = self._parsedMessage[8:]
                self.parseInventory(self.inventory())
                print ("MateId:", myMateId)
                if (self._inventory[0] < 6):
                    return
                if (myMateId != ""):
                   if ((int(myMateId) > 1 and int(myMateId) < 8)):
                        return
            while mySelfTile != myLevelCondition[self._functionIndex][0] or self._parsedMessage != "found":
                mySelfTile = self.parseLook(self.look())[0][0]
                self.broadcast("regroup "+myMateId)
                self.parseInventory(self.inventory())
                if (self._inventory[0] < 6):
                    return
            self.setElevationRessources()
            if (self.incantation()):
                self.broadcast("done")
                self._parsedMessage = "done"
                self._functionIndex += 1
                if (random.randint(0, 1) == 1):
                    self.left()
                else:
                    self.right()
                self.fork()
            else:
                self.broadcast("done")
                self._parsedMessage = "done"
                if (random.randint(0, 1) == 1):
                    self.left()
                else:
                    self.right()
    
    ## @brief Try to evolve to level 4
    ## @return None
    def goToLevel4(self):
        self.parseLook(self.look())
        myTile = self.findRessource()
        self.goTo(myTile)
        self.takeAll(self._lookTiles[myTile])
        self.parseInventory(self.inventory())
        if ((self._parsedMessage == "regroup 3" or self._parsedMessage == "regroup "+str(self._id)) and self._inventory[0] > 10):
            self.broadcast("regroup "+str(self._id))
            myTimeOut = 0
            while (self.findPlayer() == False):
                if (myTimeOut == 5):
                    return
                self.parseLook(self.look())
                myTile = self.findRessource()
                self.goTo(myTile)
                self.takeAll(self._lookTiles[myTile])
                myTimeOut += 1
            print("Found")
            self.broadcast("found")
            myReceivedMessage = ""
            while (myReceivedMessage != "Current level: 4\n" and myReceivedMessage != "ko\n"):
                myReceivedMessage = self.receive()
                if (myReceivedMessage == "Current level: 4\n"):
                    self._functionIndex += 1
                    self.fork()
                    return
        myMateId = ""
        if (self.verifyIncantation() and (self._parsedMessage == "" or self._parsedMessage == "done")):
            mySelfTile = ""
            while (myMateId == ""):
                self.broadcast("regroup 3")
                myMateId = self._parsedMessage[8:]
                self.parseInventory(self.inventory())
                print ("MateId:", myMateId)
                if (self._inventory[0] < 6):
                    return
                if (myMateId != ""):
                   if ((int(myMateId) > 1 and int(myMateId) < 8)):
                        return
            while mySelfTile != myLevelCondition[self._functionIndex][0] or self._parsedMessage != "found":
                mySelfTile = self.parseLook(self.look())[0][0]
                self.broadcast("regroup "+myMateId)
                self.parseInventory(self.inventory())
                if (self._inventory[0] < 6):
                    return
            self.setElevationRessources()
            if (self.incantation()):
                self.broadcast("done")
                self._parsedMessage = "done"
                self._functionIndex += 1
                if (random.randint(0, 1) == 1):
                    self.left()
                else:
                    self.right()
                self.fork()
            else:
                self.broadcast("done")
                self._parsedMessage = "done"
                if (random.randint(0, 1) == 1):
                    self.left()
                else:
                    self.right()

    ## @brief Try to evolve to level 5
    ## @return None
    def goToLevel5(self):
        self.parseLook(self.look())
        myTile = self.findRessource()
        self.goTo(myTile)
        self.takeAll(self._lookTiles[myTile])
        self.parseInventory(self.inventory())
        if ((self._parsedMessage == "regroup 4" or self._parsedMessage == "regroup "+str(self._id)) and self._inventory[0] > 15):
            self.broadcast("regroup "+str(self._id))
            myTimeOut = 0
            while (self.findPlayer() == False):
                if (myTimeOut == 5):
                    return
                self.parseLook(self.look())
                myTile = self.findRessource()
                self.goTo(myTile)
                self.takeAll(self._lookTiles[myTile])
                myTimeOut += 1
            print("Found")
            self.broadcast("found")
            myReceivedMessage = ""
            while (myReceivedMessage != "Current level: 5\n" and myReceivedMessage != "ko\n"):
                myReceivedMessage = self.receive()
                if (myReceivedMessage == "Current level: 5\n"):
                    self._functionIndex += 1
                    self.fork()
                    return
        myMateId = []
        if (self.verifyIncantation() and (self._parsedMessage == "" or self._parsedMessage == "done")):
            mySelfTile = ""
            while (len(myMateId) < 3):
                self.broadcast("regroup 4")
                if (self._parsedMessage[8:] not in myMateId):
                    myMateId.append(self._parsedMessage[8:])
                self.parseInventory(self.inventory())
                print ("MateId:", myMateId)
                if (self._inventory[0] < 6):
                    return
                for i in range(len(myMateId)):
                    if (myMateId != ['']):
                        if ((int(myMateId[i]) > 1 and int(myMateId[i]) < 8)):
                            return
            while mySelfTile != myLevelCondition[self._functionIndex][0] or self._parsedMessage != "found":
                mySelfTile = self.parseLook(self.look())[0][0]
                for i in range (len(myMateId)):
                    self.broadcast("regroup "+myMateId[i])
                self.parseInventory(self.inventory())
                if (self._inventory[0] < 6):
                    return
            self.setElevationRessources()
            if (self.incantation()):
                self.broadcast("done")
                self._parsedMessage = "done"
                self._functionIndex += 1
                if (random.randint(0, 1) == 1):
                    self.left()
                else:
                    self.right()
                self.fork()
            else:
                self.broadcast("done")
                self._parsedMessage = "done"
                if (random.randint(0, 1) == 1):
                    self.left()
                else:
                    self.right()
    
    ## @brief Try to evolve to level 6
    ## @return None
    def goToLevel6(self):
        self.parseLook(self.look())
        myTile = self.findRessource()
        self.goTo(myTile)
        self.takeAll(self._lookTiles[myTile])
        self.parseInventory(self.inventory())
        if ((self._parsedMessage == "regroup 5" or self._parsedMessage == "regroup "+str(self._id)) and self._inventory[0] > 15):
            self.broadcast("regroup "+str(self._id))
            myTimeOut = 0
            while (self.findPlayer() == False):
                if (myTimeOut == 5):
                    return
                self.parseLook(self.look())
                myTile = self.findRessource()
                self.goTo(myTile)
                self.takeAll(self._lookTiles[myTile])
                myTimeOut += 1
            print("Found")
            self.broadcast("found")
            myReceivedMessage = ""
            while (myReceivedMessage != "Current level: 6\n" and myReceivedMessage != "ko\n"):
                myReceivedMessage = self.receive()
                if (myReceivedMessage == "Current level: 6\n"):
                    self._functionIndex += 1
                    self.fork()
                    return
        myMateId = []
        if (self.verifyIncantation() and (self._parsedMessage == "" or self._parsedMessage == "done")):
            mySelfTile = ""
            while (len(myMateId) < 3):
                self.broadcast("regroup 5")
                if (self._parsedMessage[8:] not in myMateId):
                    myMateId.append(self._parsedMessage[8:])
                self.parseInventory(self.inventory())
                print ("MateId:", myMateId)
                if (self._inventory[0] < 6):
                    return
                for i in range(len(myMateId)):
                    if (myMateId != ['']):
                        if ((int(myMateId[i]) > 1 and int(myMateId[i]) < 8)):
                            return
            while mySelfTile != myLevelCondition[self._functionIndex][0] or self._parsedMessage != "found":
                mySelfTile = self.parseLook(self.look())[0][0]
                for i in range (len(myMateId)):
                    self.broadcast("regroup "+myMateId[i])
                self.parseInventory(self.inventory())
                if (self._inventory[0] < 6):
                    return
            self.setElevationRessources()
            if (self.incantation()):
                self.broadcast("done")
                self._parsedMessage = "done"
                self._functionIndex += 1
                if (random.randint(0, 1) == 1):
                    self.left()
                else:
                    self.right()
                self.fork()
            else:
                self.broadcast("done")
                self._parsedMessage = "done"
                if (random.randint(0, 1) == 1):
                    self.left()
                else:
                    self.right()
                
    
    ## @brief Try to evolve to level 7
    ## @return None
    def goToLevel7(self):
        self.parseLook(self.look())
        myTile = self.findRessource()
        self.goTo(myTile)
        self.takeAll(self._lookTiles[myTile])
        self.parseInventory(self.inventory())
        if ((self._parsedMessage == "regroup 6" or self._parsedMessage == "regroup "+str(self._id)) and self._inventory[0] > 15):
            self.broadcast("regroup "+str(self._id))
            myTimeOut = 0
            while (self.findPlayer() == False):
                if (myTimeOut == 5):
                    return
                self.parseLook(self.look())
                myTile = self.findRessource()
                self.goTo(myTile)
                self.takeAll(self._lookTiles[myTile])
                myTimeOut += 1
            print("Found")
            self.broadcast("found")
            myReceivedMessage = ""
            while (myReceivedMessage != "Current level: 7\n" and myReceivedMessage != "ko\n"):
                myReceivedMessage = self.receive()
                if (myReceivedMessage == "Current level: 7\n"):
                    self._functionIndex += 1
                    self.fork()
                    return
        myMateId = []
        if (self.verifyIncantation() and (self._parsedMessage == "" or self._parsedMessage == "done")):
            mySelfTile = ""
            while (len(myMateId) < 5):
                self.broadcast("regroup 6")
                if (self._parsedMessage[8:] not in myMateId):
                    myMateId.append(self._parsedMessage[8:])
                self.parseInventory(self.inventory())
                print ("MateId:", myMateId)
                if (self._inventory[0] < 6):
                    return
                for i in range(len(myMateId)):
                    if (myMateId != ['']):
                        if ((int(myMateId[i]) > 1 and int(myMateId[i]) < 8)):
                            return
            while mySelfTile != myLevelCondition[self._functionIndex][0] or self._parsedMessage != "found":
                mySelfTile = self.parseLook(self.look())[0][0]
                for i in range (len(myMateId)):
                    self.broadcast("regroup "+myMateId[i])
                self.parseInventory(self.inventory())
                if (self._inventory[0] < 6):
                    return
            self.setElevationRessources()
            if (self.incantation()):
                self.broadcast("done")
                self._parsedMessage = "done"
                self._functionIndex += 1
                if (random.randint(0, 1) == 1):
                    self.left()
                else:
                    self.right()
                self.fork()
            else:
                self.broadcast("done")
                self._parsedMessage = "done"
                if (random.randint(0, 1) == 1):
                    self.left()
                else:
                    self.right()
    
    ## @brief Try to evolve to level 8
    ## @return None
    def goToLevel8(self):
        self.parseLook(self.look())
        myTile = self.findRessource()
        self.goTo(myTile)
        self.takeAll(self._lookTiles[myTile])
        self.parseInventory(self.inventory())
        if ((self._parsedMessage == "regroup 7" or self._parsedMessage == "regroup "+str(self._id)) and self._inventory[0] > 15):
            self.broadcast("regroup "+str(self._id))
            myTimeOut = 0
            while (self.findPlayer() == False):
                if (myTimeOut == 5):
                    return
                self.parseLook(self.look())
                myTile = self.findRessource()
                self.goTo(myTile)
                self.takeAll(self._lookTiles[myTile])
                myTimeOut += 1
            print("Found")
            self.broadcast("found")
            myReceivedMessage = ""
            while (myReceivedMessage != "Current level: 8\n" and myReceivedMessage != "ko\n"):
                myReceivedMessage = self.receive()
                if (myReceivedMessage == "Current level: 8\n"):
                    self._functionIndex += 1
                    self.fork()
                    return
        myMateId = []
        if (self.verifyIncantation() and (self._parsedMessage == "" or self._parsedMessage == "done")):
            mySelfTile = ""
            while (len(myMateId) < 5):
                self.broadcast("regroup 7")
                if (self._parsedMessage[8:] not in myMateId):
                    myMateId.append(self._parsedMessage[8:])
                self.parseInventory(self.inventory())
                print ("MateId:", myMateId)
                if (self._inventory[0] < 6):
                    return
                for i in range(len(myMateId)):
                    if (myMateId != ['']):
                        if ((int(myMateId[i]) > 1 and int(myMateId[i]) < 8)):
                            return
            while mySelfTile != myLevelCondition[self._functionIndex][0] or self._parsedMessage != "found":
                mySelfTile = self.parseLook(self.look())[0][0]
                for i in range (len(myMateId)):
                    self.broadcast("regroup "+myMateId[i])
                self.parseInventory(self.inventory())
                if (self._inventory[0] < 6):
                    return
            self.setElevationRessources()
            if (self.incantation()):
                self.broadcast("done")
                self._parsedMessage = "done"
                self._functionIndex += 1
                if (random.randint(0, 1) == 1):
                    self.left()
                else:
                    self.right()
                self.fork()
            else:
                self.broadcast("done")
                self._parsedMessage = "done"
                if (random.randint(0, 1) == 1):
                    self.left()
                else:
                    self.right()