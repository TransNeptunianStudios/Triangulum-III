import Phaser from 'phaser'

export default class Entity extends Phaser.Sprite {
  constructor(game, sprite) {
    super(game, 0, 0, sprite)

    this.game = game;
    this.anchor.setTo(0.5);

    //this.animations.add('idle', [0, 1]);

    this.game.physics.enable(this, Phaser.Physics.ARCADE);
    this.body.collideWorldBounds = true;
  }

  update() {}
}