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
        this.input.blockInput = false;
        this.input.startFocus();

        this.game.add.text(this.input.x, this.input.y - 25, "Player", {
            font: "20px Arial",
            fill: "#FFFFFF"
        })

	this.versionText = this.game.add.text(this.game.width-10, this.game.height-20, "Version. 0.1", {
	    font: "15px Arial",
	    fill: "#FFFFFF"
	});
	this.versionText.anchor.set(1, 0);

        this.connection = new Connection('ws://10.66.66.52:8080');
        this.attemptingLogin = false;

        var button = game.add.button(this.game.width / 2, this.input.y + 50, 'enterButton', this.loginAttempt, this, 2, 1, 0);
        button.anchor.set(0.5)

        this.game.input.keyboard.addKey(Phaser.Keyboard.ENTER).onDown.addOnce(this.loginAttempt, this);

    }

    loginAttempt() {
        if (!this.attemptingLogin) {
            this.attemptingLogin = true;
            this.connection.login(this.input.value, this.loginResponse, this);
        }
    }

    update() {
        this.input.update();
    }

    loginResponse(success, id) {
        this.attemptingLogin = false;
        if (success == "success") {
            this.input.endFocus();
            this.state.start('Game', true, false, this.connection, id)
        } else
            console.log("Login failed");
    }
}
