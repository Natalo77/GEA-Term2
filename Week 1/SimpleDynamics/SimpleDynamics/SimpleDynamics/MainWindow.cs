using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SimpleDynamics
{
    public partial class MainWindow : Form
    {
        private SimpleRenderer mRenderer;
        private World mWorld;
        private Timer mTimer;
    
        public MainWindow()
        {
            InitializeComponent();

            mRenderer = new SimpleRenderer();
            mWorld = new World();
            
            //Set a timer so that we can attempt to update the physics every 10 ms
            mTimer = new Timer();
            mTimer.Interval = 10;
            mTimer.Tick += new EventHandler(TickWorld);
            mTimer.Enabled = true;
        }

        private void MainWindow_Paint(object sender, PaintEventArgs e)
        {
            //This is the main renderer using Windows GDI 
            Graphics graphics = e.Graphics;

             foreach( var prop in mWorld.mDynamicPropList )
            {
                mRenderer.Draw(prop, graphics);
            }

            foreach (var prop in mWorld.mStaticPropList)
            {
                mRenderer.Draw(prop, graphics);
            }

            foreach( var spring in mWorld.mSpringList)
            {
                mRenderer.Draw(spring, graphics);
            }

            mRenderer.Draw(mWorld.mInvertedPendulum.Cart, graphics);
            mRenderer.Draw(mWorld.mInvertedPendulum.Pendulum, graphics);
            mRenderer.DrawLine(mWorld.mInvertedPendulum.Cart.Position,
                mWorld.mInvertedPendulum.Pendulum.Position, graphics);
        }
        
        private void TickWorld(object sender, EventArgs e)
        {
            mWorld.Step(0.01f);
            Invalidate();
        }

        private void MainWindow_MouseDown(object sender, MouseEventArgs e)
        {
            Point mouseloc = e.Location;

            switch (e.Button)
            {
                case System.Windows.Forms.MouseButtons.Right:
                    mWorld.AddNewBodyRandom(new Vector2D(mouseloc.X, mouseloc.Y));
                    break;

                case System.Windows.Forms.MouseButtons.Left:
                    mWorld.AddSpringJoint(new Vector2D(mouseloc.X, mouseloc.Y));
                    break;

                default:
                    break;
            }

            Invalidate();
        }

        private void MainWindow_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode )
            {
                case Keys.Left:
                    mWorld.mInvertedPendulum.AccelerateCart(new Vector2D(-10, 0));
                    break;
                case Keys.Right:
                    mWorld.mInvertedPendulum.AccelerateCart(new Vector2D(10, 0));
                    break;
                case Keys.Space:
                    mWorld.mInvertedPendulum.AccelerateCart(new Vector2D(0.0f, -20.0f));
                    break;
                default:
                    break;
            }

            Invalidate();
        }

        private void MainWindow_KeyUp(object sender, KeyEventArgs e)
        {
            mWorld.mInvertedPendulum.SuddenBrake();
            Invalidate();
        }
    }
}
