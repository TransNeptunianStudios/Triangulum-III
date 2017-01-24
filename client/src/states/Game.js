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

	// Set up our controls.
	// TODO: HELP ME, it's horrible
	this.Thrust1 = this.game.input.keyboard.addKey(Phaser.Keyboard.W);
	this.Thrust2 = this.game.input.keyboard.addKey(Phaser.Keyboard.UP);
	this.Reverse1 = this.game.input.keyboard.addKey(Phaser.Keyboard.S);
	this.Reverse2 = this.game.input.keyboard.addKey(Phaser.Keyboard.DOWN);
	this.StrafeLeft1 = this.game.input.keyboard.addKey(Phaser.Keyboard.A);
	this.StrafeLeft2 = this.game.input.keyboard.addKey(Phaser.Keyboard.LEFT);
	this.StrafeRight1 = this.game.input.keyboard.addKey(Phaser.Keyboard.D);
	this.StrafeRight2 = this.game.input.keyboard.addKey(Phaser.Keyboard.RIGHT);
	this.RotLeft = this.game.input.keyboard.addKey(Phaser.Keyboard.Q);
	this.RotRight = this.game.input.keyboard.addKey(Phaser.Keyboard.E);
	this.Fire = this.game.input.keyboard.addKey(Phaser.Keyboard.SPACE);
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

		if(serverEntity.id == this.playerId)
		    this.game.camera.follow(this.entities[this.playerId])
	    }
	    clientEntity.x = serverEntity.x
   	    clientEntity.y = serverEntity.y
	    clientEntity.body.velocity.x = serverEntity.vx
	    clientEntity.body.velocity.y = serverEntity.vy
	    clientEntity.body.rotation = serverEntity.r
	    console.log("ROT: " + serverEntity.r);
	}
    }
    
    update() {

	// Collect inputs from the player
	// This is big and ugly, ideas?
        var inputMask = Handy.getbitMask([
            this.Thrust1.isDown || this.Thrust2.isDown,
	    this.Reverse1.isDown || this.Reverse2.isDown,
	    this.StrafeLeft1.isDown || this.StrafeLeft2.isDown,
	    this.StrafeRight1.isDown || this.StrafeRight2.isDown,
            this.RotLeft.isDown,
            this.RotRight.isDown, 
            this.Fire.isDown, // Fire
            false]); // spare

        // Only send if input changed
        if (inputMask != this.lastInput)
            this.connection.sendInputs(inputMask);

        this.lastInput = inputMask;
    }
}
