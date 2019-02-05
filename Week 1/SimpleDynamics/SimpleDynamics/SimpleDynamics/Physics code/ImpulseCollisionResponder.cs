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

            //Impulse.

            //Calculate the radii
            Vector2D radius1 = data.ContactPoint - data.BodyA.Position;
            Vector2D radius2 = data.ContactPoint - data.BodyB.Position;

            //calculate the two velocities.
            Vector2D velocity1 = data.BodyA.LinearVelocity;
            Vector2D velocity2 = data.BodyB.LinearVelocity;

            //calculate the normal length sqr
            float normalLengthSqr = data.ContactNormal.Dot(data.ContactNormal);

            //Calculate dV
            Vector2D dVelocity = velocity1 - velocity2;

            //If there can be no collision
            if (dVelocity * data.ContactNormal < 0.0f)
            {
                return;
            }

            //Need to resolve both normal and tangential impulses.
            //
            //1. Normal impulse.
            float r1XNormal = radius1.Cross(data.ContactNormal);
            float r2XNormal = radius2.Cross(data.ContactNormal);

            float normalDiv = normalLengthSqr * (data.BodyA.InvMass + data.BodyB.InvMass) +
                data.ContactNormal.Dot(
                    (data.BodyA.Inertia * r1XNormal))

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
