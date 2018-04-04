import THREE = require("three");
import AnimatedObject = require("AnimatedObjects");
import Particle = require("Particle");

class Explosion extends AnimatedObject {

    private m_particle: Particle;
    private m_frames = 16;
    private m_counter = 0;
    private m_scene: THREE.Scene;
    private m_delay: number = 0;

    constructor(startPosition: THREE.Vector3, scale: THREE.Vector3, scene) {
        super();
        this.m_startPosition = startPosition;
        this.m_x = startPosition.x;
        this.m_y = startPosition.y;
        this.m_scene = scene;
        //this.m_particle = new Particle(startPosition.x, startPosition.y, scene);
    }

    public Update(time: number): void {
        //if (this.m_counter < this.m_frames) {
        //    if (this.m_delay++ > 150) {
        //        this.m_counter++;
        //        this.UpdateAnimation(time);
        //        //this.m_particle.Update();
        //        this.m_delay = 0;
        //    }

        //}
        //else {
        //    this.m_scene.remove(this.m_geom);
        //    this.m_scene.remove(this.m_box);
        //    this.m_expired = true;
        //}
        this.UpdateAnimation(time, true);
        if (this.animComplete) {
            //var alldone = true;
            this.m_scene.remove(this.m_geom);
            this.m_scene.remove(this.m_box);
        }
    }

}

export = Explosion;