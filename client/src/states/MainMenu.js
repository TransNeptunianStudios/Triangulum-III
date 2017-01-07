/* globals __DEV__ */
import Phaser from 'phaser'
import Player from '../player.js'

export default class extends Phaser.State {
    init() { }

    preload() {}

    create() {
        console.log("MainMenu create");

        this.game.add.text(this.game.width/2, this.game.height/2, "Triangulum III", {
            font: "40px Arial",
            fill: "#FFFFFF"
        }).anchor.set(0.5)

        var input = this.game.add.inputField(0, 0);
        input.x = this.game.width/2 - input.width/2
        input.y = this.game.height/2- input.height/2 + 150

        this.game.add.text(input.x, input.y-25, "Player name:", {
            font: "20px Arial",
            fill: "#FFFFFF"
        })

        var button = game.add.button(this.game.width/2, input.y +50, 'enterButton', this.startGame, this, 2, 1, 0);
        button.anchor.set(0.5)

        this.player = new Player(this.game);
        this.player.login("Krabban");
        //this.game.input.onDown.addOnce(this.startGame, this);
    }

    update() {}

    startGame() {
      this.state.start('Game', true, false, this.player)
    }
}
