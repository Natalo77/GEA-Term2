using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleDynamics
{
    class CollisionPairData
    {
        public RigidBody BodyA
        {
            get;
            set;
        }
        public RigidBody BodyB
        {
            get;
            set;
        }

        public Vector2D ContactPoint
        {
            get;
            set;
        }

        public Vector2D ContactNormal
        {
            get;
            set;
        }


        public CollisionPairData()
        {
            BodyA = null;
            BodyB = null;
        }
    }
}
