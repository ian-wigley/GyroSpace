import THREE = require("three");
import BaseObject = require("BaseObject")

class NonAnimatedObject extends BaseObject {

    protected m_startPosition: THREE.Vector3;

    constructor() {
        super();
        this.m_startPosition = new THREE.Vector3();
    }

    public ConfigureNonAnimated(image: string, scene: THREE.Scene): void {
        var texture = THREE.ImageUtils.loadTexture(image);
        var material = new THREE.MeshBasicMaterial({ map: texture, side: THREE.DoubleSide });
        var plane = new THREE.PlaneGeometry(20, 20, 1, 1);
        this.m_geom = new THREE.Mesh(plane, material);
        this.m_geom.position.set(this.m_startPosition.x, this.m_startPosition.y, 0);
        scene.add(this.m_geom);
    }
}

export = NonAnimatedObject;