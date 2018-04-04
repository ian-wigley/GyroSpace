using Microsoft.Xna.Framework.Graphics;

namespace GyroSpace
{
    public partial class Planet : MovingObject
    {
        public Planet(Texture2D _planetTexture)
        {
            this.m_bitmap = _planetTexture;
            //this.m_bulletTexture = _bulletTexture;
            //this.m_circleHeight = 135;
            //this.m_circleWidth = 135;
            //this.m_distance = 1000;
            //this.m_totalFrames = 6;
            //this.m_currentFrame = 1;

            //this.m_animWidth = 22;

            //this.m_x0 = 0;
            //this.m_x1 = 0;
            //this.m_y0 = 0;
            //this.m_y1 = 0;
            //this.m_time = 0;
            Reset();
        }
    }
}
