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
            this.parent.loginCallback(response.status, response.id)
            break;
	case "update":
            //console.log("Got update.")
	    if(this.parent.updateCallback)
		this.parent.updateCallback(response)
            break;
        default:
            console.log("Unknown server response.")
        }
    }

    sendInputs(inputMask){
	var inputMsg = {"type" : "control", "input_mask" : inputMask}
	this.socket.send(JSON.stringify(inputMsg));
    }

    login(username, callback, obj) {
        var login = {
            "type": "login",
            "name": username,
            "color": "#AA00BB"
        };
        this.loginCallback = callback.bind(obj)
        this.socket.send(JSON.stringify(login))
    }

    registerForUpdates(callback, obj) {
	this.updateCallback = callback.bind(obj)
    }
}
