using Microsoft.Xna.Framework.Graphics;

namespace GyroSpace
{
    public partial class Explosion : AnimatedObjects
    {

        public Explosion(Texture2D _shipTexture)
        {
            this.m_bitmap = _shipTexture;
            //this.m_bulletTexture = _bulletTexture;
            //this.m_circleHeight = 135;
            //this.m_circleWidth = 135;
            //this.m_distance = 1000;
            this.m_totalFrames = 6;
            this.m_currentFrame = 1;

            this.m_animWidth = 22;


            //this.m_x0 = 0;
            //this.m_x1 = 0;
            //this.m_y0 = 0;
            //this.m_y1 = 0;
            //this.m_time = 0;

            //this.m_screenWidth = 800;
            //this.m_screenHeight = 600;
            //this.m_screenCentreX = (int)this.m_screenWidth / 2;
            //this.m_screenCentreY = (int)this.m_screenHeight / 2;
            this.m_angle = 0;
            Reset();
        }


    }
}
