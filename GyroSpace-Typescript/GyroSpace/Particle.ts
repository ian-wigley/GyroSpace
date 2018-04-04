import THREE = require("three");

class Particle {

    //https://codepen.io/Xanmia/pen/DoljI
    movementSpeed = 80;
    totalObjects = 1000;
    objectSize = 10;
    sizeRandomness = 4000;
    colors = [0xFF0FFF, 0xCCFF00, 0xFF000F, 0x996600, 0xFFFFFF];

    dirs = [];
    parts = [];
    status: boolean = true;
    object;

    constructor(x, y, scene) {
        var geometry = new THREE.Geometry();

        for (var i = 0; i < this.totalObjects; i++) {
            var vertex = new THREE.Vector3();
            vertex.x = x;
            vertex.y = y;
            vertex.z = 0;

            geometry.vertices.push(vertex);
            this.dirs.push({ x: (Math.random() * this.movementSpeed) - (this.movementSpeed / 2), y: (Math.random() * this.movementSpeed) - (this.movementSpeed / 2), z: (Math.random() * this.movementSpeed) - (this.movementSpeed / 2) });
        }
        var material = new THREE.ParticleBasicMaterial({ size: this.objectSize, color: this.colors[Math.round(Math.random() * this.colors.length)] });
        var particles = new THREE.ParticleSystem(geometry, material);

        this.object = particles;

        var xDir = (Math.random() * this.movementSpeed) - (this.movementSpeed / 2);
        var yDir = (Math.random() * this.movementSpeed) - (this.movementSpeed / 2);
        var zDir = (Math.random() * this.movementSpeed) - (this.movementSpeed / 2);

        scene.add(this.object);
    }

    public Update(): void {
        if (this.status == true) {
            var pCount = this.totalObjects;
            while (pCount--) {
                var particle = this.object.geometry.vertices[pCount]
                particle.y += this.dirs[pCount].y;
                particle.x += this.dirs[pCount].x;
                particle.z += this.dirs[pCount].z;
            }
            this.object.geometry.verticesNeedUpdate = true;
        }
    }

    //parts.push(new ExplodeAnimation(0, 0));
    //function render() {
    //    var pCount = parts.length;
    //    while (pCount--) {
    //        parts[pCount].update();
    //    }
    //}

}

export = Particle;