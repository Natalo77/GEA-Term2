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
        }
    }
}
