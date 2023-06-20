from ..player import Player
from ..iaParser import parse, Config

#Test if the player is correctly initialized
def test_player_init():
    player = Player()
    assert player._socket == None
    assert player._name == ""
    assert player._functionIndex == 0
    assert player._functionList == [player.goToLevel2, player.goToLevel3, player.goToLevel4, player.goToLevel5, player.goToLevel6, player.goToLevel7, player.goToLevel8]
    assert player._lookTiles == []
    assert player._inventory == [0, 0, 0, 0, 0, 0, 0]
    assert player._lastReceivedMessage == ""
    assert player._direction == 0
    assert player._parsedMessage == ""

#Test if the player isn´t connected when sending None or a string that isn´t a ip address
def test_player_cant_connect():
    player = Player()
    aInfo = Config()
    aInfo._host = "localhost"
    aInfo._port = 4242
    aInfo._name = "test"
    assert player.connect(aInfo) == 0

#Test if the player is correctly connected
def test_player_connect():
    player = Player()
    config = Config()
    config._host = "localhost"
    config._port = 4242
    config._name = "test"
    assert player.connect(config) == 0
    assert player._socket != None

#Test if the parser is correctly initialized
def test_parser_init():
    args = ["./zappy_ia", "-p", "4242", "-n", "Team1", "-h", "localhost"]
    info = parse(args)
    assert info._host == "localhost"
    assert info._port == "4242"
    assert info._name == "Team1"

#Test the receive function
def test_connection_receive():
    config = Config()
    config._host = "localhost"
    config._port = 4242
    config._name = "test"
    player = Player()
    player.connect(config)
    assert player.receive() != "ko\n"

#Test the send function
def test_connection_send():
    config = Config()
    config._host = "localhost"
    config._port = 4242
    config._name = "test"
    player = Player()
    player.connect(config)
    player.receive()
    player.send("test")
    assert player.receive() == "ko\n"

#Test the setTeamName function
def test_player_setTeamName():
    player = Player()
    player.setTeamName("test")
    assert player._name == "test"

#Test the fork function
def test_player_fork():
    config = Config()
    config._host = "localhost"
    config._port = 4242
    config._name = "test"
    player = Player()
    player.connect(config)
    player.setTeamName("test")
    player.preliminaries()
    test = player.fork()
    player.disconnect()
    assert test == "Error: Fork"

#Test the forward function
def test_player_forward():
    config = Config()
    config._host = "localhost"
    config._port = 4242
    config._name = "test"
    player = Player()
    player.connect(config)
    player.setTeamName("test")
    player.preliminaries()
    test = player.forward()
    player.disconnect()
    assert test != "ok\n"

#Test the right function
def test_player_right():
    config = Config()
    config._host = "localhost"
    config._port = 4242
    config._name = "test"
    player = Player()
    player.connect(config)
    player.setTeamName("test")
    player.preliminaries()
    test = player.right()
    player.disconnect()
    assert test != "ok\n"

#Test the left function
def test_player_left():
    config = Config()
    config._host = "localhost"
    config._port = 4242
    config._name = "test"
    player = Player()
    player.connect(config)
    player.setTeamName("test")
    player.preliminaries()
    test = player.left()
    player.disconnect()
    assert test != "ok\n"

#Test the look function
def test_player_look():
    config = Config()
    config._host = "localhost"
    config._port = 4242
    config._name = "test"
    player = Player()
    player.connect(config)
    player.setTeamName("test")
    player.preliminaries()
    test = player.look()
    player.disconnect()
    assert test == ""

#Test the broadcast function
def test_player_broadcast():
    config = Config()
    config._host = "localhost"
    config._port = 4242
    config._name = "test"
    player = Player()
    player.connect(config)
    player.setTeamName("test")
    player.preliminaries()
    test = player.broadcast("test")
    player.disconnect()
    assert test == "Error: Broadcast"

#Test the crypt function
def test_player_crypt():
    player = Player()
    test : str = player.cryptMessage("test\n")
    print (test)
    assert test == 'yjxy\x0f'

#Test the decrypt function
def test_player_decrypt():
    player = Player()
    test : str = player.decryptMessage('yjxy\x0f')
    assert test == "test"
