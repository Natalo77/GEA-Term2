using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleDynamics
{
    class SpringJoint
    {
        public RigidBody BodyA { get; set; }
        public RigidBody BodyB { get; set; }
        public float Stiffness { get; set; }
        public float RestLength { get; set; }
        public float Dampen { get; set; }

        public SpringJoint()
        {
            Stiffness = 1000.0f;  //stiffness of the spring
            RestLength = 50.0f;  //The rest length of the spring
            Dampen = 0.8f;      //Spring force dampen factor
        }

        public void ApplyForce()
        {
            //Vector between the two masses attached to the spring
            Vector2D s_vec = BodyB.Position - BodyA.Position;
            
            //Distance between the two masses, i.e. the length of the spring
            float length = s_vec.Length();

            //TODO: Compute the spring force based on Hooke's law
            //Apply the spring force to the two bodies joined by the spring
            //Note: The spring force has a direction which is given by the vector between BodyB and BodyA
            // The magnitude of the spring force is caculated using the Hooke's law

            //Obtain a value for the difference between the length and the rest length (extension)
            //Negative means compression. Positive means extension.
            float extension = length - RestLength;

            //Only apply calculations if the length is different to the rest length.
            // - if the extension is within 2 epsilon, don't apply calculations.
            if (!(Math.Abs( length - RestLength ) <= (2 * float.Epsilon)))
            {
                //Compute the spring force based on Hooke's law.
                // F = -kx
                float hookesForce = -(Stiffness * extension);

                //Create a vector of hookesForce.
                Vector2D hookesForceVec = new Vector2D(hookesForce, hookesForce);

                //normalise the vector between the two masses.
                s_vec.X = s_vec.X / s_vec.Length();
                s_vec.Y = s_vec.Y / s_vec.Length();

                //Create a vector for force proportional to the hookesForce to be applied
                // - And dampen it.
                hookesForceVec.X *= s_vec.X * Dampen;
                hookesForceVec.Y *= s_vec.Y * Dampen;

                //Take into account gravitational force where the Y is concerned.
                //hookesForceVec.Y += 9.81f;

                //Apply the force to body B. No force is required on body A as it is static.
                BodyB.Force = hookesForceVec;
            }
        }
    }
}
