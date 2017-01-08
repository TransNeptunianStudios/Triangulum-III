import Phaser from 'phaser'

export default class Player extends Phaser.Sprite {
  constructor(game) {
    super(game, 0, 0, 'player')

    this.game = game;
    this.anchor.setTo(0.5);

    this.animations.add('idle', [0, 1]);

    this.game.physics.enable(this, Phaser.Physics.ARCADE);
    this.body.collideWorldBounds = true;

    // position should come from the server..
    this.x = this.game.world.randomX;
    this.y = this.game.world.randomY;
  }

  update() {
    this.animations.play('idle', 10, true);
  }
}
