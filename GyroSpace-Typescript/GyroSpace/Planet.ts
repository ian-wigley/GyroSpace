import THREE = require("three");
import NonAnimatedObject = require("NonAnimatedObject");

class Planet extends NonAnimatedObject {

    constructor() {
        super();
        this.m_scaleCounter = 0;
    }

    public Update(): void {
        this.m_scaleCounter += 0.001;
        this.m_geom.position.set(this.m_x, this.m_y, 0);
        this.m_geom.scale.set(this.m_scaleCounter, this.m_scaleCounter, this.m_scaleCounter);
    }

}

export = Planet;