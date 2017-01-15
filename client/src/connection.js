export default class Connection {
    constructor(serverAdress) {
        // Open socket
        this.socket = new WebSocket(serverAdress);
        this.socket.onOpen = this.connectionOpened;
        this.socket.onmessage = this.serverResponded;
        this.socket.onerror = this.onerror;

        this.socket.parent = this;
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
            case "login_resp":
                console.log("Got login responCe.")
                this.parent.loginCallback.call( this.parent.loginCallbackContext,
                                                response.status == "success",
                                                response.id)
                break;
            default:
                console.log("Unknown server response.")
        }
    }

    sendInputs(inputMask){
      this.socket.send(JSON.stringify(inputMask));
    }

    login(username, callback, obj) {
        var login = {
            "type": "login",
            "name": username,
            "color": "#AA00BB"
        };
        this.loginCallback = callback;
        this.loginCallbackContext = obj // How can I do this... but nice?
        this.socket.send(JSON.stringify(login))
    }
}
