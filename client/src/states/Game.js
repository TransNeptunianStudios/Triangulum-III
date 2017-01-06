/* globals __DEV__ */
import Phaser from 'phaser'


export default class extends Phaser.State {
    init( player ) {
      this.player = player;
    }
    preload() {}
    create() {
        console.log("Game create");

        // add brackground
        this.game.add.tileSprite(0, 0, this.game.world.width, this.game.world.height, 'starfield');

        // simple Physics
        this.game.physics.startSystem(Phaser.Physics.ARCADE);

        this.game.add.existing(this.player);
        this.game.camera.follow(this.player);
    }
    update() {

    }
}
