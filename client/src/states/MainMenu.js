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

        this.player = new Player(this.game);
        this.player.login("Krabban");
        this.game.input.onDown.addOnce(this.startGame, this);
    }

    update() {}

    startGame() {
      this.state.start('Game', true, false, this.player)
    }
}
