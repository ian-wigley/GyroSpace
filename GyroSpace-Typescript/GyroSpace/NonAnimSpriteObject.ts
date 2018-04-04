import THREE = require("three");
import BaseObject = require("BaseObject");

class NonAnimSpriteObject extends BaseObject {

    protected m_star: THREE.Sprite;

    constructor() {
        super();
    }

    public ConfigureNonAnimated(image: string, scene: THREE.Scene): void {
        var texture = THREE.ImageUtils.loadTexture(image);
        var material = new THREE.SpriteMaterial({ map: texture, color: 0x222222 });
        this.m_star = new THREE.Sprite(material);
        this.m_star.position.set(0, 0, 0);
        scene.add(this.m_star);
    }

}
export = NonAnimSpriteObject;