import THREE = require("three");

class BaseObject {

    protected m_x: number;
    protected m_y: number;
    protected m_z: number;
    protected m_speed: number;
    protected m_angle: number;
    protected m_screenWidth: number;
    protected m_screenHeight: number;
    protected m_scale: THREE.Vector3;
    protected m_geom: THREE.Mesh;
    protected m_scaleCounter: number;
    protected m_name: string;
    protected m_expired: boolean = false;
    protected m_radians: number = Math.PI / 180;

    constructor() {
        this.Reset();
    }

    public get Scale(): THREE.Vector3 {
        return this.m_scale;
    }

    public get Geometry(): THREE.Mesh {
        return this.m_geom;
    }

    public set Name(value: string) {
        this.m_name = value;
    }

    public get Name(): string {
        return this.m_name;
    }

    public get IsExpired(): boolean {
        return this.m_expired;
    }

    public set IsExpired(value: boolean) {
        this.m_expired = value;
    }

    public get Position(): THREE.Vector3 {
        return this.m_geom.position;
    }

    public get RotationZ(): number {
        return this.m_geom.rotation.z;
    }

    public Reset(): void {
        this.m_x = 0;
        this.m_y = 0;
        this.m_z = 0;
        this.m_speed = 0.25;
        this.m_angle = (Math.random() * 360);
        this.m_screenWidth = 400;
        this.m_screenHeight = 300;
        this.m_scale = new THREE.Vector3(0, 0, 0);
        this.m_scaleCounter = 0;
    }
}

export = BaseObject;