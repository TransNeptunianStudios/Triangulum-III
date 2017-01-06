/* globals __DEV__ */
import Phaser from 'phaser'

export default class extends Phaser.State {
    init() {
      // Html5 sockets
      var socket= new WebSocket('ws://localhost:8080//');
      socket.onopen= function() {
          socket.send('Far out man');
      };
      socket.onmessage= function(s) {
          console.log('Server: '+s.data);
      };
    }
    preload() {}

    create() {
        console.log("MainMenu create");

        this.game.add.text(this.game.width/2, this.game.height/2, "Triangulum III", {
            font: "40px Arial",
            fill: "#FFFFFF"
        }).anchor.set(0.5)

        this.game.input.onDown.addOnce(this.startGame, this);
    }

    update() {}

    startGame() {
      this.state.start('Game')
    }
}
