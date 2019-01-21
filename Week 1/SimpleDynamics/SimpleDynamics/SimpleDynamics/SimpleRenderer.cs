using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading.Tasks;

namespace SimpleDynamics
{
    class SimpleRenderer
    {
        private System.Drawing.SolidBrush mBrush;
        private System.Drawing.Pen mPen;

        public SimpleRenderer()
        {
            mBrush = new SolidBrush(Color.Black);
            mPen = new Pen(Color.LimeGreen, 4);
            mPen.Alignment = System.Drawing.Drawing2D.PenAlignment.Center;
        }

        public void Draw(RigidBody rb, Graphics g)
        {
            Shape shape = rb.Shape;
            
            if ( shape is Circle)
            {
                mBrush.Color = Color.MediumSlateBlue;
                float radius = ((Circle)shape).Radius;
                float diameter = radius * 2.0f; 
                g.FillEllipse(mBrush, 
                    rb.Position.X - radius,
                    rb.Position.Y - radius,
                    diameter,
                    diameter
                );

                DrawArrow(rb.Position, rb.Position + rb.LinearVelocity, g);
            }
            else if ( shape is Box )
            {
                PointF[] pts = new PointF[4];
                Box box = ((Box)shape);
                int index = 0;

                foreach(Vector2D vert in box.Vertices)
                {
                    pts[index].X = rb.Position.X + vert.X;
                    pts[index++].Y = rb.Position.Y + vert.Y;
                }

                mBrush.Color = Color.CadetBlue;
                g.FillPolygon(mBrush, pts);
            }
        }

        public void DrawLine(Vector2D p1, Vector2D p2, Graphics g)
        {
            mPen.Color = Color.LightSteelBlue;
            g.DrawLine(mPen,
                new Point((int)p1.X, (int)p1.Y),
            new Point((int)p2.X, (int)p2.Y));
        }

        public void DrawArrow(Vector2D p1, Vector2D p2, Graphics g)
        {
            mPen.Color = Color.LightSteelBlue;
            mPen.EndCap = System.Drawing.Drawing2D.LineCap.ArrowAnchor;

            g.DrawLine(mPen,
                new Point((int)p1.X, (int)p1.Y),
            new Point((int)p2.X, (int)p2.Y));

        }

        public void Draw(SpringJoint spring, Graphics g)
        {
            Vector2D posA = spring.BodyA.Position;
            Vector2D posB = spring.BodyB.Position;

            mPen.Color = Color.DarkGray;

            g.DrawLine(mPen, 
                new Point((int)posA.X, (int)posA.Y), 
                new Point((int)posB.X, (int)posB.Y)
                );

        }
    }
}
