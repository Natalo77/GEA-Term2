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
            float epsilon = float.Epsilon;

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
            if (Math.Abs(dVelocity * data.ContactNormal) < 0.0f)
            {
                return;
            }

            //Need to resolve both normal and tangential impulses.
            //
            //1. Normal impulse.
            
            //Calculate components of J
            float r1XNormal = radius1.Cross(data.ContactNormal);
            float r2XNormal = radius2.Cross(data.ContactNormal);

            float ir1xN = r1XNormal * data.BodyA.InvMass;
            float ir2xN = r2XNormal * data.BodyB.InvMass;

            Vector2D scaleR1 = radius1 * ir1xN;
            Vector2D scaleR2 = radius2 * ir2xN;
            Vector2D scaleR1AR2 = scaleR1 + scaleR2;

            float Ja = scaleR1AR2.Dot(data.ContactNormal);

            float normalDiv = data.ContactNormal.LengthSqr() * (data.BodyA.InvMass + data.BodyB.InvMass) + Ja;
            //End region

            //Calculate Impulse
            float normalImpulse = -(1.0f + epsilon) * (dVelocity.Dot(data.ContactNormal)) / normalDiv;

            //Calculate resultant velocities.
            data.BodyA.LinearVelocity += data.ContactNormal * normalImpulse * data.BodyA.InvMass;
            data.BodyB.LinearVelocity -= data.ContactNormal * normalImpulse * data.BodyB.InvMass;

            //Calculate resultant angular velocities.
            data.BodyA.AngularVelocity += data.BodyA.InvMass * (radius1.Cross(data.ContactNormal * normalImpulse));
            data.BodyB.AngularVelocity -= data.BodyB.InvMass * (radius2.Cross(data.ContactNormal * normalImpulse));

            /*
            //2. Tangential impulse.
            Vector2D impulseVector1 = (radius1 - (data.ContactNormal * (radius1.Dot(data.ContactNormal))) * 2) * -1;
            Vector2D impulseVector2 = (radius2 - (data.ContactNormal * (radius2.Dot(data.ContactNormal))) * 2) * -1;

            //Calculate components of J
            r1XNormal = radius1.Cross(data.ContactNormal);
            r2XNormal = radius2.Cross(data.ContactNormal);

            ir1xN = r1XNormal * data.BodyA.InvMass;
            ir2xN = r2XNormal * data.BodyB.InvMass;

            scaleR1 = radius1 * ir1xN;
            scaleR2 = radius2 * ir2xN;
            scaleR1AR2 = scaleR1 + scaleR2;

            Ja = scaleR1AR2.Dot(data.ContactNormal);

            normalDiv = data.ContactNormal.LengthSqr() * (data.BodyA.InvMass + data.BodyB.InvMass) + Ja;
            //End region

            //Calculate Impulse
            normalImpulse = -(1.0f + epsilon) * (dVelocity.Dot(data.ContactNormal)) / normalDiv;

            //Calculate resultant velocities.
            data.BodyA.LinearVelocity += data.ContactNormal * normalImpulse * data.BodyA.InvMass;
            data.BodyB.LinearVelocity -= data.ContactNormal * normalImpulse * data.BodyB.InvMass;

            //Calculate resultant angular velocities.
            data.BodyA.AngularVelocity += data.BodyA.InvMass * (radius1.Cross(data.ContactNormal * normalImpulse));
            data.BodyB.AngularVelocity -= data.BodyB.InvMass * (radius2.Cross(data.ContactNormal * normalImpulse));
            */

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
