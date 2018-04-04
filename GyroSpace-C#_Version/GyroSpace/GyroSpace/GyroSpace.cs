using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System.Collections.Generic;

namespace GyroSpace
{
    /// <summary>
    /// This is the main type for your game.
    /// </summary>
    public class GyroSpace : Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        private Texture2D ballsTexture;
        private SpriteFont arial16Font;

        private Texture2D starTexture;
        private Texture2D shipTexture;
        private Texture2D bulletTexture;
        private Texture2D m_meteorTexture0;
        private Texture2D m_meteorTexture1;

        private KeyboardState currentKeyboardState;
        private MouseState mouseState;

        private readonly List<Keys> keys = new List<Keys>();

        private List<Star> m_stars = new List<Star>();
        private Ship m_ship;
        private List<MovingObject> m_movingObjects = new List<MovingObject>();
        private Meteor m_meteors;

        private bool m_rotateStarLeft;

        public GyroSpace()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            // TODO: Add your initialization logic here
            graphics.PreferredBackBufferWidth = 800;
            graphics.PreferredBackBufferHeight = 600;
            graphics.ApplyChanges();

            base.Initialize();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            // Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = new SpriteBatch(GraphicsDevice);

            // TODO: use this.Content to load your game content here
            //var starTexture = Content.Load<Texture2D>("star");
            //arial16Font = Content.Load<SpriteFont>("Arial16");


            starTexture = Content.Load<Texture2D>("star");


            for (int i = 0; i < 80; i++)
            {
                m_stars.Add(new Star(starTexture));//, i * 4));
            }

            shipTexture = Content.Load<Texture2D>("ship");
            bulletTexture = Content.Load<Texture2D>("bullet");
            m_ship = new Ship(shipTexture, bulletTexture);



            m_meteorTexture0 = Content.Load<Texture2D>("meteor0");
            m_meteorTexture1 = Content.Load<Texture2D>("meteor1");

            int _difficulty = 1;

            for (int i = 0; i < _difficulty * 2; i++)
            {
                this.m_meteors = new Meteor(m_meteorTexture0, 16, 32);//, m_renderTargetSize, 16, m_meteorFrame0, 32);
                this.m_movingObjects.Add(m_meteors);

                this.m_meteors = new Meteor(m_meteorTexture1, 64, 44);//, m_renderTargetSize, 64, m_meteorFrame1, 44);
                this.m_movingObjects.Add(m_meteors);
            }

        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// game-specific content.
        /// </summary>
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
                Exit();


            currentKeyboardState = Keyboard.GetState();

            // TODO: Add your update logic here
            // Get the current state of the keyboard
            //keyboardState = keyboard.GetState();
            //keyboardState.

            // Get the current state of the mouse
            //mouseState = mouse.GetState();

            // Move the space ship left
            if (currentKeyboardState.IsKeyDown(Keys.Left))
            {
                m_ship.Update(0.0327f, 2);
                m_rotateStarLeft = true;
            }

            // Move the space ship right
            if (currentKeyboardState.IsKeyDown(Keys.Right))
            {
                m_ship.Update(-0.0327f, -2);
                m_rotateStarLeft = false;
            }


            // Fire !
            if (currentKeyboardState.IsKeyDown(Keys.LeftControl))
            {
                m_ship.FireBullet();
            }

            // Quit !
            if (currentKeyboardState.IsKeyDown(Keys.Escape))
            {
                this.Exit();
            }

            m_ship.Update();

            int angle;
            // Update each star in the collection
            foreach (Star str in m_stars)
            {
                str.Update();
                str.RotateStars(angle = m_rotateStarLeft ? 2 : 1);
            }

            // Update each meteor in the collection
            foreach (Meteor mtr in m_movingObjects)
            {
                mtr.Update();
            }

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            // Use time in seconds directly
            var time = (float)gameTime.TotalGameTime.TotalSeconds;

            // Clears the screen with the Color.Black
            GraphicsDevice.Clear(Color.Black);

            // TODO: Add your drawing code here
            // Draw the stars
            spriteBatch.Begin();
            foreach (Star str in m_stars)
            {
                str.Draw(spriteBatch);
            }

            m_ship.Draw(spriteBatch);

            // Update each meteor in the collection
            foreach (Meteor mtr in m_movingObjects)
            {
                mtr.Draw(spriteBatch);
            }

            spriteBatch.End();

            base.Draw(gameTime);
        }
    }
}
