import Phaser from 'phaser'

export default class extends Phaser.State {
    init() {}

    preload() {
        this.logo = this.game.add.sprite(this.game.world.centerX, this.game.world.centerY, 'TNSlogo');
        this.logo.anchor.set(0.5);
    }

    create() {
        console.log("Splash create");

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
