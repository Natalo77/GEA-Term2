using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleDynamics
{
    class World
    {
        public List<RigidBody> mDynamicPropList = new List<RigidBody>();
        public List<RigidBody> mStaticPropList = new List<RigidBody>();
        public List<SpringJoint> mSpringList = new List<SpringJoint>();
        public RigidBody Ground { get; set; }
        public InvertedPendulum mInvertedPendulum { get; set; }
        private Random mRandom;
        public Vector2D Gravity { get; set; }
        private const float mMaxSpeed = 200.0f;
        private Shape mDefaultCircle;
        
        public World()
        {
            Gravity = new Vector2D(0.0f, 98.0f);
            Ground = new RigidBody();
            Ground.Shape = new Box(
                new Vector2D(-640, -20),
                new Vector2D(640, -20),
                new Vector2D(640, 20),
                new Vector2D(-640, 20)
                );
            
            //the ground is a static object
            Ground.Position = new Vector2D(640, 600);
            mStaticPropList.Add(Ground);

            mInvertedPendulum = new InvertedPendulum();

            mRandom = new Random();
            mDefaultCircle = new Circle();
        }

        private void RemoveOutOfBoundRigidBody()
        {
            foreach (var prop in mDynamicPropList)
            {
                if (prop.Position.X < 0 || prop.Position.X > 1280)
                {
                    mDynamicPropList.Remove(prop);
                    break;
                }

                if (prop.Position.Y < 0 || prop.Position.Y > 720)
                {
                    mDynamicPropList.Remove(prop);
                    break;
                }

            }
        }
        public void Step(float dt)
        {
            RemoveOutOfBoundRigidBody();

            //Apply force from joints
            //Currently only spring joints are modelled
            foreach(var spring in mSpringList)
            {
               spring.ApplyForce();
            }

            //Step all rigidbody props and update their position
            foreach ( var prop in mDynamicPropList )
            {
                prop.Step(dt, this);
            }

            mInvertedPendulum.Step(dt, this);

            //TODO: Check and resolve collision
        }

        //Add a new rigid body at a given position with random attributes
        public void AddNewBodyRandom(Vector2D pos)
        {
            RigidBody newBody = new RigidBody();

            newBody.Shape = this.mDefaultCircle;
            newBody.Position = pos;

            float angle = (float)(Math.PI * mRandom.NextDouble());
            float speed = mMaxSpeed * ((float)(mRandom.NextDouble()));

            Vector2D rb_velocity = new Vector2D();
            rb_velocity.X = speed*(float)(Math.Cos(angle));
            rb_velocity.Y = -speed*(float)(Math.Sin(angle));

            newBody.LinearVelocity = rb_velocity;
 
            mDynamicPropList.Add(newBody);
        }

        //Add spring joint
        public void AddSpringJoint(Vector2D pos)
        {
            RigidBody[] newBodies = new RigidBody[2];
            SpringJoint spring = new SpringJoint();
            
            newBodies[0] = new RigidBody();
            newBodies[1] = new RigidBody();
            newBodies[0].Shape = mDefaultCircle;
            newBodies[1].Shape = mDefaultCircle;
            
            newBodies[0].Position = pos;
            newBodies[1].Position = pos + new Vector2D(0.0f, spring.RestLength+10.0f);
            
            foreach (var body in newBodies)
            {
                float angle = (float)(Math.PI * mRandom.NextDouble());
                float speed = 0.1f*mMaxSpeed* ((float)(mRandom.NextDouble()));

                Vector2D rb_velocity = new Vector2D();
                rb_velocity.X = speed * (float)(Math.Cos(angle));
                rb_velocity.Y = -speed * (float)(Math.Sin(angle));

                body.LinearVelocity = rb_velocity;
            }

            mStaticPropList.Add(newBodies[0]);
            mDynamicPropList.Add(newBodies[1]);
            
            spring.BodyA = newBodies[0];
            spring.BodyB = newBodies[1];
            
            
            mSpringList.Add(spring);
        }
    }
}
