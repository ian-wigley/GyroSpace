using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;

namespace GyroSpace
{
    public class Meteor : AnimatedObjects
    {

        private int m_meteorRectLeft;
        private int m_meteorHeight;

        private BoundingBox m_boundingBox;

        private Vector3 m_start;
        private Vector3 m_end;

        public Meteor(Texture2D _bitmap, int _totalFrames, int _width)
        {
            this.m_bitmap = _bitmap;
            this.m_screenWidth = 800;
            this.m_screenHeight = 600;
            this.m_totalFrames = _totalFrames;
            this.m_animWidth = _width;
            this.m_meteorHeight = this.m_bitmap.Height;

            this.m_start = new Vector3(this.m_xyPos.X, this.m_xyPos.Y, 0);
            this.m_end = new Vector3(this.m_xyPos.X + this.m_animWidth, this.m_xyPos.Y + this.m_meteorHeight, 0);
            this.m_boundingBox = new BoundingBox(this.m_start, this.m_end);


            Reset();
        }

        public void Update()
        {
            this.m_currentFrame = (this.m_currentFrame + 1) % this.m_totalFrames;
            this.m_meteorRectLeft = this.m_currentFrame * this.m_animWidth;
            //this.m_shipRectRight = this.m_shipRectLeft + this.m_animWidth;
            this.m_xyPos.X = (float)(Math.Cos(this.m_angle) * this.m_speed) + this.m_xyPos.X;
            this.m_xyPos.Y = (float)(Math.Sin(this.m_angle) * this.m_speed) + this.m_xyPos.Y;

            // Update the bounding box Vector locations
            this.m_start.X = this.m_xyPos.X;
            this.m_start.Y = this.m_xyPos.Y;
            this.m_end.X = this.m_xyPos.X + this.m_animWidth;
            this.m_end.Y = this.m_xyPos.Y + this.m_meteorHeight;

            // If the meteor goes off screen, reset the positions
            if (this.m_xyPos.X < 0 || this.m_xyPos.X > this.m_screenWidth || this.m_xyPos.Y < 0 || this.m_xyPos.Y > this.m_screenHeight)
            {
                Reset();
            }
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(
            this.m_bitmap,
            this.m_xyPos,
            new Rectangle(m_meteorRectLeft, 0, m_animWidth, m_meteorHeight),
            Color.White,
            0.0f,
            new Vector2(16, 16),
            Vector2.One,
            SpriteEffects.None,
            1.0f);
        }

        public BoundingBox GetBBox()
        {
            return this.m_boundingBox;
        }
    }
}
