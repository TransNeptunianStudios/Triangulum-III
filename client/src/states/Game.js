/* globals __DEV__ */
import Phaser from 'phaser'
import Player from '../player.js'

import Handy from '../handy.js'

export default class extends Phaser.State {
    init(connection, id) {
        this.connection = connection;
        this.playerId = id;
    }
    preload() {}
    create() {
        console.log("Game create");

        // add brackground
        this.game.add.tileSprite(0, 0, this.game.world.width, this.game.world.height, 'starfield');

        // simple Physics
        this.game.physics.startSystem(Phaser.Physics.ARCADE);

        // player
        this.player = new Player(this.game);
        this.game.add.existing(this.player);
        this.game.camera.follow(this.player);

        //this.game.input.keyboard.addKeys({ 'fire': Phaser.Keyboard.SPACEBAR});
        this.cursors = this.game.input.keyboard.createCursorKeys();
        this.lastInput = 0;
    }
    update() {
        // get world updates from the server
        //
        var inputMask = Handy.getbitMask([
            this.cursors.up.isDown,
            this.cursors.down.isDown,
            this.cursors.left.isDown, // strafe left
            this.cursors.right.isDown,
            false, // turn left
            false, // turn left
            false, // Fire
            false]); // spare

        // Only send if input changed
        if (inputMask != this.lastInput)
            this.connection.sendInputs(inputMask);

        this.lastInput = inputMask;
    }
}
