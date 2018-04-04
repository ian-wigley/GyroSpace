import NonAnimatedObject = require("NonAnimatedObject")

class RotatingDisplayObject extends NonAnimatedObject {
    private t: number = 0;

    constructor(startPosition: THREE.Vector3, scale: THREE.Vector3) {
        super();
        this.m_scale = scale;
    }

    public Update(): void {
        this.m_geom.position.set(this.m_x, this.m_y, 50);//this.m_z)
        this.m_geom.scale.set(5, 5, 5);//this.m_x, this.m_y, this.m_z);
        this.m_geom.rotation.set(0, this.t += 0.01 ,0);
    }

}

export = RotatingDisplayObject;