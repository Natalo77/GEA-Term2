using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleDynamics
{
    class RigidBody
    {
        public Vector2D Position { get; set; }              //Position of the centre of mass
        public Vector2D LinearVelocity { get; set; }        //linear velocity, for translational motion
        public Vector2D Force { get; set; }                 //body force
        public float AngularVelocity { get; set; }          //angular velocity, for rotational motion
        public float Mass { get; set; }
        public float InvMass { get; set; }
        public float Inertia { get; set; }
        public float InvInertia { get; set; }
        public bool IgnoreGravity { get; set; }
        public Shape Shape { get; set; }

        //gravtiational constant.
        public const float GRAV = 6.67e-11f;
 
        public RigidBody(bool ignoreGravity)
        {
            Mass = 200.0f;
            InvMass = 1.0f / Mass;
            Position = new Vector2D();
            LinearVelocity = new Vector2D();
            Force = new Vector2D();
            IgnoreGravity = ignoreGravity;
        }

        public void Step(float dt, World world)
        {
            //Newton 2nd Law
            //Vector2D acceleration = Force * InvMass;
            Vector2D acceleration = new Vector2D(0, 0);
            
            if (IgnoreGravity)
            {

                //Create a force vector.
                Vector2D forceVector = new Vector2D(0,0);

                //Create a direction vector.
                Vector2D toOther = new Vector2D();

                //against each particle in the dynmic prop list.
                foreach (var particle in world.mDynamicPropList)
                {
                    //get the vector to the other particle.
                    toOther = particle.Position - this.Position;

                    //force = GMm/r^2
                    float force = GRAV * this.Mass * particle.Mass / toOther.LengthSqr();

                    //Normalise the vector as its length is no longer relevant.
                    toOther.X = toOther.X / toOther.Length();
                    toOther.Y = toOther.Y / toOther.Length();

                    //Apply the force to the vector.
                    toOther.X *= force;
                    toOther.Y *= force;

                    //add this vector to the resultant forcevector.
                    forceVector.X += toOther.X;
                    forceVector.Y += toOther.Y;

                }
                //Calculate the resultant acceleration.
                acceleration = forceVector * InvMass;

                LinearVelocity = LinearVelocity + acceleration * dt;
            }
            else
            {
                LinearVelocity = LinearVelocity + (world.Gravity + acceleration) * dt;
            }

            //Euler Integration
            Position = Position + LinearVelocity * dt;
        }
    }
}
