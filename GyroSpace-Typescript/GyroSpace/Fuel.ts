import THREE = require("three");
import NonAnimatedObject = require("NonAnimatedObject")

class Fuel extends NonAnimatedObject {

    constructor() {
        super();
    }

    public Update(): void {
        this.m_speed += .01;
        this.m_angle += .01;
        this.m_x = (Math.cos(this.m_angle) * this.m_speed + this.m_x);
        this.m_y = (Math.sin(this.m_angle) * this.m_speed + this.m_y);
        this.m_geom.position.x = this.m_x;
        this.m_geom.position.y = this.m_y;
        this.m_scaleCounter += 0.015;
        //this.m_scale.set(this.m_scaleCounter, this.m_scaleCounter, this.m_scaleCounter);
        this.m_geom.scale.set(this.m_scaleCounter, this.m_scaleCounter, this.m_scaleCounter);
		
        // If the Fuel goes off screen, reset the position
        if (this.m_x < -400 || this.m_x > 400 || this.m_y < -300 || this.m_y > 300) {
            this.Reset();
        }
    }
}

export = Fuel;