/* globals __DEV__ */
import Phaser from 'phaser'
import Entity from '../entity.js'

import Handy from '../handy.js'

export default class extends Phaser.State {
    init(connection, id) {
	this.connection = connection;
	this.playerId = id;
	this.score = 0

	// Client pixels per server meter
	this.gameScale = 32
    }
    preload() {}
    create() {
	console.log("Game create");

	// add brackground
	this.game.add.tileSprite(0, 0, this.game.world.width, this.game.world.height, 'starfield');

	// entities
	this.entities = new Map();

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
	this.Fire = this.game.input.keyboard.addKey(Phaser.Keyboard.SPACEBAR);
	this.lastInput = 0;

	this.connection.registerForUpdates(this.updateWorld, this);

	var HUD = this.game.add.group()
	HUD.fixedToCamera = true;
	this.score = this.game.add.text(this.game.width/2, 40, '0', {font:'24px Arial', fill: '#FF0000', align: 'center'});
	this.score.anchor.setTo(0.5)
	HUD.add(this.score);
    }

    add_to_world(server_object) {
	var newEntity = new Entity(this.game, server_object.sprite,
				   server_object.width * this.gameScale,
				   server_object.height * this.gameScale)
	this.entities[server_object.id] = newEntity
	this.game.add.existing(newEntity)

	if (server_object.id == this.playerId){
	    this.game.camera.follow(this.entities[this.playerId])
	}
	return newEntity
    }

    updateWorld(response) {
	//console.log("Updating world.")
	for (var e in response.objects) {

	    var serverEntity = response.objects[e]
	    var clientEntity = this.entities[serverEntity.id]

	    if (!clientEntity) {
		clientEntity = this.add_to_world(serverEntity)
	    }
	    else{
		clientEntity.sync(serverEntity, this.gameScale)
		if ( serverEntity.score )
		    this.score.text = serverEntity.score
	    }
	    clientEntity.updated = true
	}

	// Clean up
	for ( var e in this.entities) {
	    if(!this.entities[e].updated){
		//console.log("trying to remove obj " + e)
		this.entities[e].destroy()
		delete this.entities[e]

		if ( e == this.player.id ){
		    this.connection.disconnect()
		    this.state.start('MainMenu')
		}
	    }
	    else
		this.entities[e].updated = false
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
	    false
	]); // spare

	// Only send if input changed
	if (inputMask != this.lastInput)
	    this.connection.sendInputs(inputMask);

	this.lastInput = inputMask;
    }
}
