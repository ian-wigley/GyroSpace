using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;

namespace GyroSpace
{
    public class MovingObject
    {
        protected int m_size;
        protected Vector2 m_xyPos;
        protected int m_rect;
        protected Texture2D m_bitmap;

        protected int m_screenHeight;
        protected int m_screenWidth;
        protected double m_speed;
        protected double m_angle;

        protected static Random m_rand = new Random();

        internal MovingObject()
        {
            this.m_screenWidth = 800;
            this.m_screenHeight = 600;
        }

        // Reset the stars position as they go off screen
        protected void Reset()
        {
            int m_num = m_rand.Next();
            this.m_angle = m_num % 360;
            this.m_speed = 1.2;
            this.m_xyPos.X = (float)this.m_screenWidth / 2;
            this.m_xyPos.Y = (float)this.m_screenHeight / 2;
        }


    }
}
