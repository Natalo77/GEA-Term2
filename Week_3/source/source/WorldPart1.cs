using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleDynamics
{
    partial class World
    {
        private void SimpleDetectCollision()
        {
            //Testing collision against the top edge of the GROUND rectangle
            foreach (var prop in mDynamicPropList)
            {
                if (prop.Position.Y > 560.0)
                {
                    CollisionPairData pair = new CollisionPairData();
                    pair.BodyA = prop;
                    pair.BodyB = Ground;
                    pair.ContactNormal = new Vector2D(0, -1);

                    mCollisionResponder.Resolve(pair);
                    Ground.LinearVelocity.X = 0.0f;
                    Ground.LinearVelocity.Y = 0.0f;
                }
            }

            //Brute force N^2 pairwise circle-circle intersection test
            for (int i = mDynamicPropList.Count - 1; i >=0; i--)
            {
                RigidBody a = mDynamicPropList[i];

                for (int j = mDynamicPropList.Count - 1; j >= 0; j--)
                {
                    if ( i != j )
                    {
                        RigidBody b = mDynamicPropList[j];

                        float d = (a.Position - b.Position).Length();

                        if (d < 30 ) //N.B. since all circles have a radius of 15
                        {
                            Vector2D normal = (a.Position - b.Position);
                            CollisionPairData pair = new CollisionPairData();
                            pair.BodyA = a;
                            pair.BodyB = b;
                            pair.ContactNormal = normal;

                            mCollisionResponder.AddCollisionPair(pair);
                        }
                    }
                }

                mCollisionResponder.ResolveAllPairs();
            }
        }

    }
}
