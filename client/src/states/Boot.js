import Phaser from 'phaser'
//@HACK: ensures Fabrique fron "phaser-input" gets exposed to window.
import * as PhaserInput from '@orange-games/phaser-input/build/phaser-input.js'

export default class extends Phaser.State {
  init() {
    this.game.add.plugin(Fabrique.Plugins.InputField);
    this.game.world.setBounds(0, 0, 2000, 2000)
  }

  preload() {
    this.load.image('TNSlogo', './assets/images/TNS_logo.png');
    this.load.image('starfield', './assets/images/tileable-classic-nebula-space-patterns-3.jpg');
    this.load.image('enterButton', './assets/images/EnterButton.png');
    this.load.image('basic_green_bullet', './assets/images/basic_green_shoot.png');
    this.load.image('asteroid', './assets/images/asteroid.png');

    this.load.spritesheet('player', './assets/images/ship.png', 32, 32, 13);
  }

  create() {
    console.log("Boot create");

    this.state.start('MainMenu')
  }
}
