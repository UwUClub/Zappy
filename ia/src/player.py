from .connection import Connection


class Player:
    # Constructor
    def __init__(self):
        self.socket = None
        self.name = ""
        self.map_width = 0
        self.map_height = 0

    # Connection
    def connect(self, info):
        self.socket = Connection(info.host, int(info.port))
        return self.socket.connect()

    def send(self, data):
        self.socket.send(data)

    def receive(self):
        return self.socket.receive()

    def disconnect(self):
        self.socket.disconnect()

    # Core functions
    def preliminaries(self):
        self.receive()
        self.send(self.name)
        self.receive()

    def set_team_name(self, name):
        self.name = name

    # Commands
    def msz(self):
        self.send("msz")
        msz = self.receive()
        msz = msz.split(" ")
        if msz[0] == "msz":
            msz = msz[1:]
        self.map_width = int(msz[0])
        self.map_height = int(msz[1])
