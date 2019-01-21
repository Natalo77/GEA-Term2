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
 
        public RigidBody()
        {
            Mass = 200.0f;
            InvMass = 1.0f / Mass;
            Position = new Vector2D();
            LinearVelocity = new Vector2D();
            Force = new Vector2D();
            IgnoreGravity = false;
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
            

            Position = Position + LinearVelocity * dt;
        }
    }
}
