import THREE = require("three");
import AnimatedObject = require("AnimatedObjects");

class Meteor extends AnimatedObject {

    constructor(startPosition: THREE.Vector3, scale: THREE.Vector3) {
        super();
        this.m_startPosition = startPosition;
        this.m_x = startPosition.x;
        this.m_y = startPosition.y;
    }

    public Update(): void {
        this.m_speed += 0.01;
        this.m_x = (Math.cos(this.m_angle) * this.m_speed) + this.m_x;
        this.m_y = (Math.sin(this.m_angle) * this.m_speed) + this.m_y;
        this.m_scaleCounter += 0.015;
        this.m_geom.position.set(this.m_x, this.m_y, 0);
        this.m_geom.scale.set(this.m_scaleCounter, this.m_scaleCounter, this.m_scaleCounter);

        // If the Meteor goes off screen, reset the position
        if (this.m_x < -400 || this.m_x > this.m_screenWidth || this.m_y < -300 || this.m_y > this.m_screenHeight) {
            this.Reset();
        }
    }
}

export = Meteor;