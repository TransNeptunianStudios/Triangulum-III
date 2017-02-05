import Phaser from 'phaser'

export default class Entity extends Phaser.Sprite {
    constructor(game, sprite, dwidth, dheight) {
	super(game, 0, 0, sprite)
	this.anchor.setTo(0.5)
	this.scale.setTo(dwidth / this.width, dheight / this.height)
    }

    update() {}
}
