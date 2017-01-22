/* globals __DEV__ */
import Phaser from 'phaser'
import Entity from '../entity.js'

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

	// entities
	this.entities  = new Map();


	
	this.entities[this.playerId] = this.player
	
        this.game.camera.follow(this.entities[this.playerId])

        //this.game.input.keyboard.addKeys({ 'fire': Phaser.Keyboard.SPACEBAR});
        this.cursors = this.game.input.keyboard.createCursorKeys();
        this.lastInput = 0;

	this.connection.registerForUpdates(this.updateWorld, this);
    }

    updateWorld(response) {
	//console.log("Updating world.")

	// Uppdate all int
	for( var e in response.objects) {
	    
	    var serverEntity = response.objects[e]
	    var clientEntity = this.entities[serverEntity.id]
	    
	    if(!clientEntity){
		var newEntity = new Entity(this.game, serverEntity.sprite)
   		this.entities[serverEntity.id] = newEntity
		this.game.add.existing(newEntity)
		clientEntity = newEntity
	    }
	    clientEntity.x = serverEntity.x
   	    clientEntity.y = serverEntity.y
	    clientEntity.body.velocity.x = serverEntity.vx
	    clientEntity.body.velocity.y = serverEntity.vy	    	
	}
    }
    
    update() {

	// Collect inputs from the player
	// This is big and ugly, ideas?
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
