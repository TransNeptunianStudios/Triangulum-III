/* globals __DEV__ */
import Phaser from 'phaser'
import {
    setResponsiveWidth
} from '../utils'

export default class extends Phaser.State {
    init() {}
    preload() {}

    create() {
        console.log("MainMenu create");
        this.game.add.text(this.game.world.centerX, this.game.world.height * 0.5, "Triangulum III", {
            font: "40px Arial",
            fill: "#FFFFFF"
        }).anchor.set(0.5)

    }

    update() {}
}
