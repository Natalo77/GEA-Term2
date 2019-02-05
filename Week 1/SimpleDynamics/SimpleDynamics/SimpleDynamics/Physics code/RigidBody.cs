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
            Mass = 500000000000.0f;
            InvMass = 1.0f / Mass;
            Position = new Vector2D();
            LinearVelocity = new Vector2D();
            Force = new Vector2D();
            IgnoreGravity = ignoreGravity;
        }

        public void Step(float dt, World world)
        {

            //Newton 2nd Law
            Vector2D acceleration = Force * InvMass;
            
            
            if (IgnoreGravity)
            {
                LinearVelocity = LinearVelocity + acceleration * dt;
            }
            else
            {
                LinearVelocity = LinearVelocity + (world.Gravity + acceleration) * dt;
            }

            //Euler Integration
            EulerIntegration(dt);

            //Midpoint Integration.
            //MidpointIntegration(world, acceleration, dt);

            //RungeKutta integration.
            //RungeKuttaIntegration(acceleration, world, dt);
        }

        public Vector2D getForceTo(RigidBody body)
        {
            //Create a force vector.
            Vector2D forceVector = new Vector2D(0,0);

            //Create a direction vector.
            Vector2D toOther = new Vector2D();

            //get the vector to the other particle.
            toOther = body.Position - this.Position;

            //force = GMm/r^2
            float force = GRAV * this.Mass * body.Mass / toOther.LengthSqr();

            //Normalise the vector as its length is no longer relevant.
            toOther.X = toOther.X / toOther.Length();
            toOther.Y = toOther.Y / toOther.Length();

            //Apply the force to the vector.
            toOther.X *= force;
            toOther.Y *= force;

            return toOther;
        }

        private void EulerIntegration(float dt)
        {
            Position = Position + LinearVelocity * dt;
        }

        private void MidpointIntegration(World world, Vector2D acceleration, float dt)
        {
            //Calculate the mid point of the velocity.
            Vector2D midVelocity = LinearVelocity + (acceleration + world.Gravity) * 0.5f * dt;

            //Calculate the new velocity.
            LinearVelocity = midVelocity * dt;

            //Update the position.
            Position = Position + LinearVelocity * dt;
        }

        private void RungeKuttaIntegration(Vector2D acceleration, World world, float dt)
        {
            Vector2D k1 = LinearVelocity + (acceleration + world.Gravity) * dt;
            Vector2D k2 = LinearVelocity + (k1 * 0.5f * dt);
            Vector2D k3 = LinearVelocity + (k2 * 0.5f * dt);
            Vector2D k4 = LinearVelocity + k3 * dt;

            Position = Position + (k1 + k2 * 2.0f + k3 * 2.0f + k4) * (1.0f/6.0f) * dt;

        }
    }

}
