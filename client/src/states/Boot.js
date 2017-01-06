import Phaser from 'phaser'

export default class extends Phaser.State {
    init() {
      this.game.world.setBounds(0, 0, 2000, 2000)
    }

    preload() {
        this.load.image('TNSlogo', './assets/images/TNS_logo.png');
        this.load.image('starfield', './assets/images/tileable-classic-nebula-space-patterns-3.jpg');
    }

    create() {
      console.log("Boot create");

      this.state.start('Splash')
    }
}
