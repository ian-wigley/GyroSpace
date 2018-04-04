import NonAnimSpriteObject = require("NonAnimSpriteObject");

class Star extends NonAnimSpriteObject {

    constructor() {
        super();
    }

   public Update(): void {
        this.m_angle += .01;
        this.m_speed += 0.01;
        this.m_x = (Math.cos(this.m_angle) * this.m_speed) + this.m_x;
        this.m_y = (Math.sin(this.m_angle) * this.m_speed) + this.m_y;
        this.m_star.position.set(this.m_x, this.m_y, 0);

        // If the Star goes off screen, reset the position
        if (this.m_x < -400 || this.m_x > this.m_screenWidth || this.m_y < -300 || this.m_y > this.m_screenHeight) {
            this.Reset();
        }
    }
}

export = Star;