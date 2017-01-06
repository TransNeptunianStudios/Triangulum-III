import Phaser from 'phaser'

export default class Player extends Phaser.Sprite {
  constructor(game) {
    super(game, 0, 0, 'player')

    this.game = game;
    this.anchor.setTo(0.5);

    this.animations.add('idle', [0, 1]);

    this.game.physics.enable(this, Phaser.Physics.ARCADE);
    this.body.collideWorldBounds = true;

    this.cursors = this.game.input.keyboard.createCursorKeys();
  }

  login(userName) {
    var socket = new WebSocket('ws://localhost:8080//');
    socket.onopen = function() {
      socket.send(userName + ' wants to log in.');
    };
    socket.onmessage = function(s) {
      console.log('Server: ' + s.data);
    };

    // position should come from the server..
    this.x = this.game.world.randomX;
    this.y = this.game.world.randomY;
  }

  update() {
    this.animations.play('idle', 10, true);

    // this should just send commands to the server, not actually move
    if (this.cursors.up.isDown) {
      this.y -= 4
    } else if (this.cursors.down.isDown) {
      this.y += 4
    }

    if (this.cursors.left.isDown) {
      this.x -= 4
    } else if (this.cursors.right.isDown) {
      this.x += 4
    }
  }
}
