using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleDynamics
{
    class InvertedPendulum
    {
        public RigidBody Cart { get; set; }
        public RigidBody Pendulum { get; set; }
        private Vector2D Offset;
        private float rod_length;
        public InvertedPendulum()
        {
            Cart = new RigidBody(true);
            
            //The position of the centre of mass of the cart.
            //This is also where the pendulum rod attached to the cart
            Cart.Position = new Vector2D(640, 540);

            Cart.Shape = new Box(
                new Vector2D(-50, -20),
                new Vector2D(50, -20),
                new Vector2D(50, 20),
                new Vector2D(-50, 20)
                );
            
            //offset of the pendulum mass from the centre of the cart
            //aka, the position of the pendulum relative to the cart
            Offset = new Vector2D(0.0f, -200.0f);

            rod_length = Offset.Length();

            Pendulum = new RigidBody(true);
            Pendulum.Shape = new Circle();
            //position of the pendulum based on the offset
            Pendulum.Position = Cart.Position + Offset;
        }

        public void Step(float dt, World world)
        {
            //The vector from cart to the pendulum, i.e
            Vector2D pendulum_rod = Pendulum.Position - Cart.Position;

            //TODO: Calculate the torque exerted on the pendulum
            // - Note: At the moment, the only force is the gravity in world
            //T - orque = r-> cross F->
            float torque = pendulum_rod.Cross(world.Gravity);

            
            //TODO: Calculate the angular acceleration from the torque
            // - Note: You can approximate the moment of inertia using the pendulum's mass for now
            // - Ttotal = Ia
            // - a = Ttotal/I
            float angular_acc = torque / Pendulum.Mass;

            //TODO: Update the angular velocity based on angular_acc
            //dV = a * dt
            Pendulum.AngularVelocity += angular_acc * dt;

            //TODO: Caculate the angle of rotation based on the AngularVelocity of the Pendulum
            // - dtheta = w * dt
            float dtheta = Pendulum.AngularVelocity * dt;

            //Build a rotation matrix based on the current dtheta
            Matrix2 rotation = new Matrix2();
            rotation.SetRotation(dtheta);

            //Rotate the pendulum and update its world position
            Offset = rotation * Offset;
            Pendulum.Position = Cart.Position + Offset;
            
            //Tick the Cart physics
            Cart.Step(dt, world);

            //We don't have collision detection yet hack it.
            if(Cart.Position.Y > 540)
            {
                Cart.Position.Y = 540.0f;
            }
        }

        public void AccelerateCart(Vector2D vel)
        {
            Cart.LinearVelocity += vel;
        }

        public void SuddenBrake()
        {
            Cart.LinearVelocity.X = 0.0f;
            Cart.LinearVelocity.Y = 0.0f;
        }
    }
}
