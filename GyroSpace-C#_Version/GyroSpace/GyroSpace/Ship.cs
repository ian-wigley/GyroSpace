using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;

namespace GyroSpace
{
    public class Ship : AnimatedObjects
    {

        private float m_incrementer;
        private int m_screenCentreX;
        private int m_screenCentreY;
        private int m_circleHeight;
        private int m_circleWidth;
        private int m_shipSpeed;
        private int m_distance;
        private bool m_flyToPlanet;
        private bool m_arrived;
        private int m_shipRectLeft;
        private int m_shipRectRight;

        private int m_x0;
        private int m_x1;
        private int m_y0;
        private int m_y1;

        private float m_time;
        private float m_radians;

        private Texture2D m_bulletTexture;
        private List<Bullet> m_bulletList = new List<Bullet>();
        private Bullet m_bullet;

        public Ship(Texture2D _shipTexture, Texture2D _bulletTexture)
        {

            this.m_bitmap = _shipTexture;
            this.m_bulletTexture = _bulletTexture;
            this.m_circleHeight = 135;
            this.m_circleWidth = 135;
            this.m_distance = 1000;
            this.m_totalFrames = 6;
            this.m_currentFrame = 1;

            this.m_animWidth = 22;


            this.m_x0 = 0;
            this.m_x1 = 0;
            this.m_y0 = 0;
            this.m_y1 = 0;
            this.m_time = 0;

            //this.m_screenWidth = 800;
            //this.m_screenHeight = 600;
            this.m_screenCentreX = (int)this.m_screenWidth / 2;
            this.m_screenCentreY = (int)this.m_screenHeight / 2;
            this.m_angle = 0;
            Reset();
        }

        // This method updates the ships animation and interpolation
        public void Update()
        {
            this.m_currentFrame = (this.m_currentFrame + 1) % this.m_totalFrames;
            this.m_shipRectLeft = this.m_currentFrame * this.m_animWidth;

            // Move the ship into the centre of the screen using linear interpolation
            if (this.m_flyToPlanet)
            {
                // Move the ship into the centre of the screen using Lerp
                if ((int)this.m_xyPos.X != this.m_screenCentreX && (int)this.m_xyPos.Y != this.m_screenCentreY)
                {
                    this.m_x0 = (int)this.m_xyPos.X;
                    this.m_x1 = this.m_screenCentreX;
                    this.m_y0 = (int)this.m_xyPos.Y;
                    this.m_y1 = this.m_screenCentreY;
                    this.m_xyPos.X += (this.m_x1 - this.m_x0) * (this.m_time / this.m_distance);
                    this.m_xyPos.Y += (this.m_y1 - this.m_y0) * (this.m_time / this.m_distance);
                    this.m_time = this.m_time + 1 % this.m_distance;
                }
                else
                {
                    this.m_arrived = true;
                }
            }


            List<Bullet> delList = new List<Bullet>();
            foreach (Bullet bullet in m_bulletList)
            {
                int listValue = bullet.Update();
                if (listValue > 0)
                {
                    // Add the bullet into the deletion list
                    delList.Add(bullet);
                }
            }

            foreach (Bullet bullet in delList)
            {
                m_bulletList.Remove(bullet);
            }
        }


        // This method updates the ships position through 360 degrees
        public void Update(float counter, int angle)
        {
            this.m_incrementer += counter;
            this.m_angle += angle % 360;
            this.m_xyPos.X = (float)(m_circleWidth * 1.5 * Math.Cos(m_incrementer * m_shipSpeed * Math.PI / 180)) + this.m_screenCentreX;
            this.m_xyPos.Y = (float)(m_circleHeight * 1.5 * Math.Sin(m_incrementer * m_shipSpeed * Math.PI / 180)) + this.m_screenCentreY;
            this.m_radians = (float)(Math.PI * this.m_angle / 180);
        }


        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(
            this.m_bitmap,
            this.m_xyPos,
            new Rectangle(m_shipRectLeft, 0, 22, 21),
            Color.White,
            m_radians,
            new Vector2(16, 16),
            Vector2.One,
            SpriteEffects.None,
            0f);

            // Update the bullets
            foreach (Bullet bullet in m_bulletList)
            {
                bullet.Draw(spriteBatch);
            }
        }


        // Reset the ships position as they go off screen
        private new void Reset()
        {
            //this.m_screenCentreX = (int)this.m_screenWidth / 2;
            //this.m_screenCentreY = (int)this.m_screenHeight / 2;
            this.m_xyPos.X = (float)this.m_screenCentreX;
            this.m_xyPos.Y = (float)this.m_screenCentreY + 20;

            this.m_angle = 0;
            this.m_shipSpeed = 61;
            this.m_incrementer = 90;

            this.m_arrived = false;
            this.m_flyToPlanet = false;
        }

        internal void FireBullet()
        {
            m_bullet = new Bullet(this.m_bulletTexture, this.m_xyPos, this.m_radians);
            m_bulletList.Add(m_bullet);
        }

        public void FlyToPlanet()
        {
            this.m_flyToPlanet = true;

        }
    }
}
