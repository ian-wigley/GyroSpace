using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace GyroSpace
{
    public partial class Bullet : MovingObject
    {

        private int m_screenCentreX;
        private int m_screenCentreY;
        private int m_distance;
        private int m_x0;
        private int m_x1;
        private int m_y0;
        private int m_y1;

        private float m_time;

        private float m_radians;

        public Bullet(Texture2D _bitmap, Vector2 xyPos, float radians)
        {
            this.m_bitmap = _bitmap;
            this.m_xyPos = xyPos;
            this.m_radians = radians;

            //this.m_rotation = 0.0;
            //this.m_starSpeed = 0.4;
            //this.m_screenWidth = 800;
            //this.m_screenHeight = 600;
            this.m_x0 = 0;
            this.m_x1 = 0;
            this.m_y0 = 0;
            this.m_y1 = 0;
            this.m_time = 0;

            this.m_screenCentreX = (int)this.m_screenWidth / 2;
            this.m_screenCentreY = (int)this.m_screenHeight / 2;
            this.m_distance = 1000;

            //Reset();
        }


        // This method updates the bullet position
        public int Update()
        {
            //this.m_speed += this.m_speed;

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
                return 1;
            }

            return 0;
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(
            this.m_bitmap,
            this.m_xyPos,
            new Rectangle(0, 0, 1, 10),
            Color.White,
            this.m_radians,
            new Vector2(16, 16),
            Vector2.One,
            SpriteEffects.None,
            0f);
        }
    }
}
