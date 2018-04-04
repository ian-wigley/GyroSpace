using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace GyroSpace
{
    public class Star : MovingObject
    {
        private double m_rotation;
        private double m_starSpeed;

        public Star(Texture2D _bitmap)
        {
            this.m_bitmap = _bitmap;
            this.m_rotation = 0.0;
            this.m_starSpeed = 0.4;
            //this.m_screenWidth = 800;
            //this.m_screenHeight = 600;
            Reset();
        }


        // This method updates each stars position
        public void Update()
        {
            this.m_speed += this.m_starSpeed;
            this.m_angle += this.m_rotation;

            this.m_xyPos.X = (float)(Math.Cos(this.m_angle) * this.m_speed) + this.m_xyPos.X;
            this.m_xyPos.Y = (float)(Math.Sin(this.m_angle) * this.m_speed) + this.m_xyPos.Y;

            // If the Star goes off screen, reset the positions
            if (this.m_xyPos.X < 0 || this.m_xyPos.X > this.m_screenWidth || this.m_xyPos.Y < 0 || this.m_xyPos.Y > this.m_screenHeight)
            {
                Reset();
                this.m_speed = 0.2;
            }
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(
            this.m_bitmap,
            this.m_xyPos,
            new Rectangle(0, 0, 1, 1),
            Color.White,
            0.0f,
            new Vector2(16, 16),
            Vector2.One,
            SpriteEffects.None,
            0f);
        }

        // Set the Rotation amount
        public void RotateStars(int _angle)
        {
            //_angle == 2 ? this.m_rotation = -0.02 : this.m_rotation = 0.02;
            this.m_rotation = (_angle == 2) ? -0.02 : 0.02;
        }
    }
}
