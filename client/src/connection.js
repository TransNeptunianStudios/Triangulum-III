export default class Connection {
    constructor(serverAdress) {
        // Open socket
        this.socket = new WebSocket(serverAdress);
        this.socket.onOpen = this.connectionOpened;
        this.socket.onmessage = this.serverResponded;
        this.socket.onerror = this.onerror;
    }

    onerror(error) {
        console.log('WebSocket Error ' + error);
    };

    connectionOpened() {
        console.log('WebSocket Opened.');
    }

    serverResponded(e) {
        var response = JSON.parse(e.data);
        switch (response.type) {
            case "login_response":
                console.log("Got login responCe.")
                this.loginCallback(response.success, response.id);
                break;
            default:
                console.log("Unknown server response.")
        }
    }

    sendInputs(inputMask){
      this.socket.send(JSON.stringify(inputMask));
    }

    login(username, callback) {
        var login = {
            "type": "login",
            "user": username,
            "color": "#AA00BB"
        };
        this.loginCallback = callback;
        this.socket.send(JSON.stringify(login))
    }
}
