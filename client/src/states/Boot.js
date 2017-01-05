import Phaser from 'phaser'

export default class extends Phaser.State {
    init() {
    }

    preload() {
        this.load.image('TNSlogo', './assets/images/TNS_logo.png');
    }

    create() {
      console.log("Boot create");

      //this.state.start('Splash')
      this.state.start('MainMenu')
    }
}
