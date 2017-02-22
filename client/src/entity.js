import Phaser from 'phaser'

export default class Entity extends Phaser.Sprite {
    constructor(game, sprite, dwidth, dheight) {
	super(game, 0, 0, sprite)
	this.anchor.setTo(0.5)
	this.scale.setTo(dwidth / this.width, dheight / this.height)
    }

    sync( server_object, game_scale) {
	this.x = server_object.x * game_scale
	this.y = server_object.y * game_scale
	this.angle = server_object.r

	//clientEntity.body.velocity.x = serverEntity.vx
	//clientEntity.body.velocity.y = serverEntity.vy
    }
}
