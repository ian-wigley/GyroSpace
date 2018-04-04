import THREE = require("three");
import NonAnimatedObject = require("NonAnimatedObject");

class Bullet extends NonAnimatedObject {

    private m_time: number = 0;
    private m_distance: number = 70;//1000;
    private m_rotation: number;

    constructor(startPosition: THREE.Vector3) {
        super();
        this.m_startPosition = startPosition;
        this.m_x = startPosition.x;
        this.m_y = startPosition.y;
        this.m_scaleCounter = 1;
    }

    public Update(): void {

        if (this.m_x != 0 || this.m_y != -3.7) {
            this.m_x += (0 - this.m_x) * (this.m_time / this.m_distance);
            this.m_y += (0 - this.m_y) * (this.m_time / this.m_distance);
            this.m_time = this.m_time + 1 % this.m_distance;
            this.m_geom.position.x = this.m_x;
            this.m_geom.position.y = this.m_y;
            this.m_scaleCounter -= 0.007;
            //this.m_scale.set(this.m_scaleCounter, this.m_scaleCounter, this.m_scaleCounter);
            this.m_geom.scale.set(this.m_scaleCounter, this.m_scaleCounter, this.m_scaleCounter);
        }
        else {
            this.m_expired = true;
        }

        if (this.m_time >= this.m_distance) {
            this.m_expired = true;
        }
    }

    public ConfigureBullet(texture: THREE.Texture, scene: THREE.Scene, rotation: number): void {
        //var texture = THREE.ImageUtils.loadTexture(image);
        var material = new THREE.MeshBasicMaterial({ map: texture, side: THREE.DoubleSide });
        var plane = new THREE.PlaneGeometry(20, 20, 1, 1);
        this.m_geom = new THREE.Mesh(plane, material);
        this.m_geom.position.set(this.m_startPosition.x, this.m_startPosition.y, 0);
        this.m_geom.rotation.z = rotation;// * this.m_radians;
        scene.add(this.m_geom);
    }



}
export = Bullet;


//import THREE = require("three");
//import NonAnimatedObject = require("NonAnimatedObject");

//class Bullet extends NonAnimatedObject {

//    private m_time: number = 0;
//    private m_distance: number = 1000;
//    private m_expired = false;

//    constructor(startPosition: THREE.Vector3) {
//        super();
//        this.m_startPosition = startPosition;
//        this.m_x = startPosition.x;
//        this.m_y = startPosition.y;
//    }

//    public Update(): void {

//        if (this.m_x != 0 || this.m_y != -3.7) {
//            this.m_x += (0 - this.m_x) * (this.m_time / this.m_distance);
//            this.m_y += (0 - this.m_y) * (this.m_time / this.m_distance);
//            this.m_time = this.m_time + 1 % this.m_distance;
//            this.geom.position.x = this.m_x;
//            this.geom.position.y = this.m_y;
//        }
//        else {
//            this.m_expired = true;
//        }


//        if (this.m_time >= this.m_distance) {
//            this.m_expired = true;
//        }
//    }

//    public get IsExpired(): boolean {
//        return this.m_expired;
//    }

//    public set IsExpired(value: boolean) {
//        this.m_expired = value;
//    }

//    public get Geometry(): THREE.Mesh {
//        return this.geom;
//    }

//}
//export = Bullet;