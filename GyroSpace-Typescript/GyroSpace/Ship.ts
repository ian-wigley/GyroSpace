import AnimatedObject = require("AnimatedObjects");

class Ship extends AnimatedObject {

    private m_incrementer: number = -90;
    private m_circleWidth: number = 225;
    private m_circleHeight: number = 225;
    private m_shipSpeed: number = 1;

    constructor(startPosition: THREE.Vector3, scale: THREE.Vector3) {
        super();
        this.m_startPosition = startPosition;
        this.m_x = startPosition.x;
        this.m_y = startPosition.y;
    }

    public Update(counter: number): void {
        this.m_incrementer += counter;
        this.m_x = (this.m_circleWidth * 1.5 * Math.cos(this.m_incrementer * this.m_shipSpeed * this.m_radians)) / 4;
        this.m_y = (this.m_circleHeight * 1.5 * Math.sin(this.m_incrementer * this.m_shipSpeed * this.m_radians)) / 4;
        this.m_geom.position.set(this.m_x, this.m_y, 0);
        document.getElementById("info").innerHTML = "max speed = " + counter;
    }

    public Rotate(value: number): void {
        this.m_geom.rotation.z += (value * this.m_radians);
    }


}

export = Ship;