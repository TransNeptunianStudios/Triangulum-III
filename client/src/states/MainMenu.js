/* globals __DEV__ */
import Phaser from 'phaser'
import Connection from '../connection.js'

export default class extends Phaser.State {
    init() {}

    preload() {}

    create() {
        console.log("MainMenu create");

        this.game.add.text(this.game.width / 2, this.game.height / 2, "Triangulum III", {
            font: "40px Arial",
            fill: "#FFFFFF"
        }).anchor.set(0.5)

        this.input = this.game.add.inputField(0, 0);
        this.input.x = this.game.width / 2 - this.input.width / 2
        this.input.y = this.game.height / 2 - this.input.height / 2 + 150

        this.game.add.text(this.input.x, this.input.y - 25, "Player name:", {
            font: "20px Arial",
            fill: "#FFFFFF"
        })

        this.connection = new Connection('ws://localhost:8080');

        var button = game.add.button(this.game.width / 2, this.input.y + 50, 'enterButton', this.loginAttempt, this, 2, 1, 0);
        button.anchor.set(0.5)
    }

    loginAttempt () {
	this.connection.login(this.input.value, this.loginResponse);
    }

    update() {
        this.input.update();
    }    

    loginResponse(success, id) {
        if (success) // all is ok, come on in-responce from server
            this.state.start('Game', true, false, this.connection, id)
        else
            console.log("Login failed");
    }
}
