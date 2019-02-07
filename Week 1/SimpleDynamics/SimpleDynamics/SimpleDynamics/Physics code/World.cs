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
        public List<RigidBody> mNBodyPropList = new List<RigidBody>();
        public List<SpringJoint> mSpringList = new List<SpringJoint>();
        public ImpulseCollisionResponder mCollisionResponder = new ImpulseCollisionResponder();
        public RigidBody Ground { get; set; }
        public InvertedPendulum mInvertedPendulum { get; set; }
        private Random mRandom;
        public Vector2D Gravity { get; set; }
        private const float mMaxSpeed = 200.0f;//20.0f;
        private Shape mDefaultCircle;
        
        public World()
        {
            Gravity = new Vector2D(0.0f, 98.0f);
            Ground = new RigidBody(true);
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

            //Calculate force on all NBody props
            foreach (var prop in mNBodyPropList)
            {
                Vector2D forceVector = new Vector2D(0, 0);
                foreach (var otherProp in mNBodyPropList)
                {
                    //don't apply force to same particle.
                    if (prop != otherProp)
                    {
                        forceVector += prop.getForceTo(otherProp);
                    }
                }

                prop.Force = forceVector;
            }

            //Step all nBody props
            foreach(var prop in mNBodyPropList)
            {
                prop.Step(dt, this);
            }

            //Step all rigidbody props and update their position
            foreach ( var prop in mDynamicPropList )
            {
                prop.Step(dt, this);
            }

            if (mInvertedPendulum != null)
            {
                mInvertedPendulum.Step(dt, this);
            }

            //Check and resolve collision
            SimpleDetectCollision();
        }

        //Add a new rigid body at a given position with random attributes
        public void AddNewBodyRandom(Vector2D pos, bool ignoreGravity)
        {
            RigidBody newBody = new RigidBody(ignoreGravity);

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

        public void AddNBodyRandom(Vector2D pos)
        {
            RigidBody newBody = new RigidBody(true);

            newBody.Shape = this.mDefaultCircle;
            newBody.Position = pos;

            float angle = (float)(Math.PI * mRandom.NextDouble());
            float speed = mMaxSpeed * ((float)(mRandom.NextDouble()));

            Vector2D rb_velocity = new Vector2D();
            rb_velocity.X = speed * (float)(Math.Cos(angle));
            rb_velocity.Y = -speed * (float)(Math.Sin(angle));

            newBody.LinearVelocity = rb_velocity;

            mNBodyPropList.Add(newBody);
        }

        //Add spring joint
        public void AddSpringJoint(Vector2D pos)
        {
            RigidBody[] newBodies = new RigidBody[2];
            SpringJoint spring = new SpringJoint();
            
            newBodies[0] = new RigidBody(true);
            newBodies[1] = new RigidBody(true);
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


        //Create an N-Body simulation.
        public void NBodySimulation(Vector2D pos)
        {
            //Clear the proplist.
            mDynamicPropList.Clear();
            mStaticPropList.Clear();
            mSpringList.Clear();
            mInvertedPendulum = null;

            //For a specified number of particles.
            for(int x = 0; x < 100; x++)
            {
                AddNBodyRandom(new Vector2D(pos.X + mRandom.Next(-250, 250), pos.Y + mRandom.Next(-100, 100)));
            }
        }

        private void SimpleDetectCollision()
        {
            //Testing collision against the top edge of the GROUND rectangle
            foreach (var prop in mDynamicPropList)
            {
                if (prop.Position.Y > 560.0)
                {
                    CollisionPairData pair = new CollisionPairData();
                    pair.BodyA = prop;
                    pair.BodyB = Ground;
                    pair.ContactNormal = new Vector2D(0, -1);
                    pair.ContactPoint = prop.Position;
                    pair.ContactPoint.Y -= ((Circle)(prop.Shape)).Radius;

                    mCollisionResponder.Resolve(pair);
                    Ground.LinearVelocity.X = 0.0f;
                    Ground.LinearVelocity.Y = 0.0f;
                }
            }

            //Brute force N^2 pairwise circle-circle intersection test
            for (int i = mDynamicPropList.Count - 1; i >= 0; i--)
            {
                RigidBody a = mDynamicPropList[i];

                for (int j = mDynamicPropList.Count - 1; j >= 0; j--)
                {
                    if (i != j)
                    {
                        RigidBody b = mDynamicPropList[j];

                        float d = (a.Position - b.Position).Length();

                        if (d < 30) //N.B. since all circles have a radius of 15
                        {
                            Vector2D normal = (a.Position - b.Position);
                            CollisionPairData pair = new CollisionPairData();
                            pair.BodyA = a;
                            pair.BodyB = b;
                            pair.ContactNormal = normal;

                            mCollisionResponder.AddCollisionPair(pair);
                        }
                    }
                }

                mCollisionResponder.ResolveAllPairs();
            }
        }

    }
}

