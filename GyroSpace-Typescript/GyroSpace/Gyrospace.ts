///<reference path="three.d.ts"/>

import Bullet = require("Bullet");
import Fuel = require("Fuel");
import Meteor = require("Meteor");
import Ship = require("Ship");
import Star = require("Star");
import Input = require("Input");
import Explosion = require("Explosion");
import Planet = require("Planet");
import Display = require("RotatingDisplayObject");

import THREE = require("three");

class Gyrospace {

    private canvas: HTMLCanvasElement;

    private renderer: THREE.WebGLRenderer;
    private scene: THREE.Scene;
    private camera: THREE.Camera;

    private m_gameOn: boolean = true;

    private container: HTMLElement;
    private controls;
    private stats;
    private uniforms;
    private plane;

    // Objects
    private m_bullet: Bullet;
    private m_fuel: Fuel;
    private m_meteor: Meteor;
    private m_star: Star;
    private m_ship: Ship;
    private m_explosion: Explosion;
    private m_planet: Planet;

    private gameOver;
    private m_bulletTexture: THREE.Texture;

    // Collections
    private m_bulletCollection = new Array();
    private m_meteorCollection = new Array();
    private m_metTexCollection = new Array();
    private m_starCollection = new Array();
    private m_starTexCollection = new Array();
    private m_explosionCollection = new Array();
    private m_planetCollection = new Array();
    private m_fuelCollection = new Array();

    private m_lives: number = 3;
    private m_score: number = 0;
    private m_inertia: number = 0;
    private m_maxSpeed: number = 2.5;
    private m_countUp: boolean = false;
    private m_countDown: boolean = false;
    private m_wasLeft: boolean = false;
    private m_wasRight: boolean = false;

    private ianMeteor;
    private ianExplosion;

    private delta: number = 0;
    private clock = new THREE.Clock();

    private m_fired: boolean = false;
    private m_ctrl: Input = new Input();

    constructor() {

        this.container = <HTMLElement>document.getElementById("ThreeJS");

        document.getElementById("lives").innerHTML = "Lives = " + this.m_lives;
        document.getElementById("score").innerHTML = "Score = " + this.m_score;

        // SCENE
        this.scene = new THREE.Scene();
        var WIDTH = window.innerWidth,
            HEIGHT = window.innerHeight;
        this.camera = new THREE.PerspectiveCamera(45, WIDTH / HEIGHT, 0.1, 10000);
        this.scene.add(this.camera);
        this.camera.position.z = 300;

        var geometry = new THREE.PlaneGeometry(210, 210);

        this.uniforms = {
            time: { type: "f", value: 1.0 },
            scale: { type: "f", value: 3.0 },
            resolution: { type: "v2", value: new THREE.Vector2() }
        };

        var material = new THREE.ShaderMaterial({
            uniforms: this.uniforms,
            vertexShader: document.getElementById('vertexShader').textContent,
            fragmentShader: document.getElementById('fragmentShader').textContent
        });

        this.plane = new THREE.Mesh(geometry, material);
        this.plane.position.set(0, 60, -10);
        this.scene.add(this.plane);

        this.m_bulletTexture = THREE.ImageUtils.loadTexture("images/bullet.png");

        //-- Animation images --//

        // Create the Ship
        this.m_ship = new Ship(new THREE.Vector3(0, -75, 0), new THREE.Vector3(0, 0, 0));
        this.m_ship.ConfigureAnimated("images/ship.png", this.scene, 6, 1, 5, 75);

        this.ianMeteor = new Meteor(new THREE.Vector3(-50, 25, 0), new THREE.Vector3(0, 0, 0));
        this.ianMeteor.ConfigureAnimated("images/meteor1.png", this.scene, 64, 1, 63, 75);

        // Create an collection of Meteors
        for (var i = 0; i < 5; i++) {
            this.m_meteor = new Meteor(new THREE.Vector3(), new THREE.Vector3(0.25, 0.25, 0.25));
            this.m_meteor.Name = "meteor";
            this.m_meteor.ConfigureAnimated("images/meteor0.png", this.scene, 16, 1, 15, 75);
            this.m_meteorCollection.push(this.m_meteor);
        }

        ////-- Non Animated images --//

        // Create an collection of Stars
        for (var i = 0; i < 80; i++) {
            this.m_star = new Star();
            this.m_star.ConfigureNonAnimated("images/star.png", this.scene);
            this.m_starCollection.push(this.m_star);
        }

        this.m_fuel = new Fuel();
        this.m_fuel.ConfigureNonAnimated("images/fuel.png", this.scene);
        this.m_fuelCollection.push(this.m_fuel);

        var alienPlanet = new Planet();
        alienPlanet.ConfigureNonAnimated("images/alien.png", this.scene);
        this.m_planetCollection.push(alienPlanet);

        //var icePlanet = new Planet();
        //icePlanet.ConfigureNonAnimated("images/alien.png", this.scene);
        //this.m_planetCollection.push(icePlanet);

        //var earthPlanet = new Planet();
        //icePlanet.ConfigureNonAnimated("images/earth.png", this.scene);
        //this.m_planetCollection.push(icePlanet);


        ///*var*/ this.gameOver = new Display(new THREE.Vector3(0, 0, 0), new THREE.Vector3(0, 0, 0));
        //this.gameOver.ConfigureNonAnimated("images/gameover.png", this.scene);

        this.renderer = new THREE.WebGLRenderer({ antialias: true });
        this.renderer.setSize(WIDTH, HEIGHT);
        document.body.appendChild(this.renderer.domElement);
        document.body.style.overflow = "hidden";

        window.onresize = this.onWindowResize.bind(this);
    }

    private onWindowResize(event: UIEvent): void {
        //this.camera.aspect = window.innerWidth / window.innerHeight;
        //this.camera.updateMatrixWorld(true);//.updateProjectionMatrix();
        this.renderer.setSize(window.innerWidth, window.innerHeight);
    }

    public Run(): void {
        this.Initialize();
    }

    private Initialize(): void {
        this.AddHitListener(this.canvas);
        setInterval(() => this.Animate(), 10);
    }

    private AddHitListener(element: HTMLElement) {
        window.addEventListener("keydown", (event) => {
            this.onKeyPress(event);
            return null;
        });

        window.addEventListener("keyup", (event) => {
            this.onKeyUp(event);
            return null;
        });
    }

    private onKeyPress(event: KeyboardEvent) {
        event.preventDefault();
        this.onKeyboardPress(event, false);
    }

    private onKeyUp(event: KeyboardEvent) {
        event.preventDefault();
        this.onKeyboardRelease(event, false);
    }

    private onKeyboardPress(event: Event, touchDevice: boolean) {
        switch (((<number>(<KeyboardEvent>event).keyCode | 0))) {
            case 17:
                if (!this.m_fired) {
                    this.m_ctrl.fire = true;
                    this.m_fired = true;
                }
                break;
            case 37:
                this.m_ctrl.left = true;
                this.m_countUp = true;
                this.m_countDown = false;
                break;
            case 38:
                break;
            case 39:
                this.m_ctrl.right = true;
                this.m_countUp = true;
                this.m_countDown = false;
                break;
            case 40:
                break;
        }
    }

    private onKeyboardRelease(event: Event, touchDevice: boolean) {
        switch (((<number>(<KeyboardEvent>event).keyCode | 0))) {
            case 17:
                this.m_ctrl.fire = false;
                this.m_fired = false;
                break;
            case 37:
                this.m_ctrl.left = false;
                this.m_countDown = true;
                this.m_countUp = false;
                break;
            case 38:
                break;
            case 39:
                this.m_ctrl.right = false;
                this.m_countDown = true;
                this.m_countUp = false;
                break;
            case 40:
                break;
            default:
                break;
        }
    }

    private CalculateInertia(): void {
        if (this.m_inertia >= 4.5) {
            this.m_inertia += 0.01;
        }
    }

    // Method to update and animate the objects
    private Animate(): void {
        requestAnimationFrame(this.Animate);

        //--------------------------------------------------------------------------------------->
        if (this.m_gameOn) {

            this.delta = this.clock.getDelta();

            var _this = this;

            // Update the object collections
            this.m_starCollection.forEach(function (delta, index, m_starCollection) {
                m_starCollection[index].Update();
            });

            this.m_meteorCollection.forEach(function (delta, index, m_meteorCollection) {
                m_meteorCollection[index].Update();
                m_meteorCollection[index].UpdateAnimation(1000 * _this.delta);
            });

            this.m_explosionCollection.forEach(function (delta, index, m_explosionCollection) {
                m_explosionCollection[index].Update(1000 * _this.delta);
            });

            this.m_fuelCollection.forEach(function (delta, index, m_fuelCollection) {
                m_fuelCollection[index].Update();
            });

            var updatedBulletCollection = [];
            this.m_bulletCollection.forEach(function (value, index, m_bulletCollection) {
                m_bulletCollection[index].Update();

                for (var i = 0; i < _this.m_meteorCollection.length; i++) {
                    var collide = _this.CollisionCheck(_this.m_meteorCollection[i], m_bulletCollection[index], i);
                    if (collide) {
                        m_bulletCollection[index].IsExpired = true;
                        var explosion = new Explosion(new THREE.Vector3(m_bulletCollection[index].Position.x, m_bulletCollection[index].Position.y, m_bulletCollection[index].Position.z), new THREE.Vector3(0, 0, 0), _this.scene);
                        explosion.ConfigureAnimated("images/explosion.png", _this.scene, 17, 1, 16, 75);
                        _this.m_explosionCollection.push(explosion);
                        _this.m_meteorCollection[i].Reset();
                        _this.m_score += 100;
                    }
                }

                if (!m_bulletCollection[index].IsExpired) {
                    updatedBulletCollection.push(m_bulletCollection[index]);
                }
                else {
                    _this.scene.remove(m_bulletCollection[index].Geometry);
                }
            });
            this.m_bulletCollection = [];
            this.m_bulletCollection = updatedBulletCollection;

            this.m_ship.UpdateAnimation(1000 * this.delta, false);

            this.m_planetCollection[0].Update();

            //this.gameOver.Update();

            if (this.m_countUp) {
                this.m_inertia += 0.01;
                if (this.m_inertia >= this.m_maxSpeed) {
                    this.m_countUp = false;
                    this.m_inertia = this.m_maxSpeed;
                }
            }

            if (this.m_countDown) {
                this.m_inertia -= 0.01;
                if (this.m_inertia <= 0) {
                    this.m_countDown = false;
                    this.m_inertia = 0;
                    this.m_wasLeft = false;
                    this.m_wasRight = false;
                }
            }

            if (this.m_ctrl.left || this.m_wasLeft) {
                this.m_ship.Update(this.m_inertia * -1);
                this.m_ship.Rotate(this.m_inertia * -1);
                this.m_wasLeft = true;
                this.m_wasRight = false;
            }

            if (this.m_ctrl.right || this.m_wasRight) {
                this.m_ship.Update(this.m_inertia);
                this.m_ship.Rotate(this.m_inertia);
                this.m_wasRight = true;
                this.m_wasLeft = false;
            }

            if (this.m_ctrl.fire) {
                this.m_bullet = new Bullet(this.m_ship.Position);
                this.m_bullet.Name = "bullet";
                this.m_bullet.ConfigureBullet(this.m_bulletTexture, this.scene, this.m_ship.RotationZ);
                this.m_bulletCollection.push(this.m_bullet);
                this.m_ctrl.fire = false;
            }
            this.render();
        }
    }

    // Method to render all the objects
    private render(): void {
        this.renderer.render(this.scene, this.camera);
    }

    // Method to check collision detections
    private CollisionCheck(meteor, bullet, i): boolean {

        var boxOne = new THREE.Box3().setFromObject(bullet.Geometry);
        var boxTwo = new THREE.Box3().setFromObject(meteor.Geometry);
        if (boxOne.intersectsBox(boxTwo)) {
            return true;
        }
        return false;
    }
}

export = Gyrospace;