/* globals __DEV__ */
import Phaser from 'phaser'

var player;
var cursors;

export default class extends Phaser.State {
    init() {
    }
    preload() {}
    create() {
        console.log("Game create");

        // add brackground
        this.game.add.tileSprite(0, 0, this.game.world.width, this.game.world.height, 'starfield');

        // simple Physics
        this.game.physics.startSystem(Phaser.Physics.ARCADE);

        // create sprite player, set body
        player = game.add.sprite(this.game.world.centerX, this.game.world.centerY, 'player');
        this.game.physics.enable(player, Phaser.Physics.ARCADE);
        player.body.collideWorldBounds=true;

        cursors = this.game.input.keyboard.createCursorKeys();
        this.game.camera.follow(player);
    }
    update() {

      if (cursors.up.isDown)
      {
          player.y -=4
      }
      else if (cursors.down.isDown)
      {
          player.y +=4
      }

      if (cursors.left.isDown)
      {
          player.x -=4
      }
      else if (cursors.right.isDown)
      {
          player.x +=4
      }
    }
}
