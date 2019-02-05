using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleDynamics
{
    class ImpulseCollisionResponder
    {
        private List<CollisionPairData> mCollisionPairs;

        public ImpulseCollisionResponder()
        {
            mCollisionPairs = new List<CollisionPairData>();
        }

        public void AddCollisionPair(CollisionPairData pair)
        {
            RigidBody A = pair.BodyA;
            RigidBody B = pair.BodyB;

            //Check if the pair already exists
            foreach (var p in mCollisionPairs)
            {
                if (
                    (Object.ReferenceEquals(A,p.BodyA) && Object.ReferenceEquals(B,p.BodyB))|| 
                    (Object.ReferenceEquals(A,p.BodyB) && Object.ReferenceEquals(B,p.BodyA))
                   )
                {
                    return;
                }
            }

            mCollisionPairs.Add(pair);       
        }

        public void Resolve(CollisionPairData data)
        {
            //TODO: Resolve the collision using the impulse based method
            //Since the rigid bodies except for the pendulum do not "spin", you can for now 
            //ignore the rotational part of the motion, i.e. angular velocity.
            //This also means that you only need to know the contact location

            //TODO: Further improvement if two objects have already overlapped,
            //It is often useful to first separate them along the contact normal 
            //using the projection method before resolving the collision using impulse.
        }

        public void ResolveAllPairs()
        {
            foreach(var p in mCollisionPairs)
            {
                Resolve(p);
            }

            mCollisionPairs.Clear();
        }
    }
}
