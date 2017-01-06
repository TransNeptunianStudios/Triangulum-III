import Phaser from 'phaser'

export default class extends Phaser.State {
    init() {}

    preload() {
    }

    create() {
        console.log("Splash create");

        this.game.camera

        this.logo = this.game.add.sprite(this.game.width/2, this.game.height/2, 'TNSlogo');
        this.logo.anchor.set(0.5);
        this.logo.alpha = 0;

        var fadeTween = this.game.add.tween(this.logo).to({
            alpha: 1
        }, 2000, Phaser.Easing.Linear.None, true, 1000);
        fadeTween.yoyo(true, 2000);
        fadeTween.onComplete.addOnce(this.showMainMenu, this);

        this.game.input.onDown.addOnce(this.showMainMenu, this);
    }

    showMainMenu() {
        this.state.start('MainMenu')
    }
}
