import THREE = require("three");
import BaseObject = require("BaseObject")
import TextureAnimator = require("TextureAnimator");

class AnimatedObject extends BaseObject {

    protected m_startPosition: THREE.Vector3;
    protected animation: TextureAnimator;
    protected hex: number = 0xff0000;
    protected m_box: THREE.BoundingBoxHelper;
    protected animComplete: boolean = false;

    constructor() {
        super();
    }

    public ConfigureAnimated(image: string, scene: THREE.Scene, one: number, two: number, three: number, four: number): void {
        var texture = THREE.ImageUtils.loadTexture(image);
        this.animation = new TextureAnimator(texture, one, two, three, four);// 64, 1, 63, 75);
        var material = new THREE.MeshBasicMaterial({ map: texture, side: THREE.DoubleSide });
        var plane = new THREE.PlaneGeometry(20, 20, 1, 1);
        this.m_geom = new THREE.Mesh(plane, material);
        this.m_geom.position.set(this.m_startPosition.x, this.m_startPosition.y, 0);
        scene.add(this.m_geom);

        this.m_box = new THREE.BoundingBoxHelper(this.m_geom, this.hex);
        this.m_box.update();
        scene.add(this.m_box);
    }

    public UpdateAnimation(time: number, onePass: boolean): void {
        this.animComplete =  this.animation.update(time, onePass);
        this.m_box.update();
    }
}

export = AnimatedObject;