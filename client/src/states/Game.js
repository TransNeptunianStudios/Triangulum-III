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

        /*this.game.input.keyboard.addKeys({
            'thrust': Phaser.KeyCode.W,
            'reverse': Phaser.KeyCode.S,
            'strafeLeft': Phaser.KeyCode.A,
            'strafeRight': Phaser.KeyCode.D,
            'turnLeft': Phaser.KeyCode.Q,
            'turnRight': Phaser.KeyCode.E,
            'fire': Phaser.KeyCode.SPACE
        });*/
        this.cursors = this.game.input.keyboard.createCursorKeys();
    }
    update() {
        // get world updates from the server
        //
        var inputMask = Handy.getbitMask([
            this.cursors.up.isDown,
            this.cursors.down.isDown,
            true, // strafe left
            false, // strafe right
            this.cursors.left.isDown,
            this.cursors.right.isDown,
            false, // fire
            false]); // spare

        // Only send if input changed
        if (this.lastInput && inputMask != this.lastInput)
            this.connection.sendInputs(inputMask);

        this.lastInput = inputMask;
    }
}
