using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleDynamics
{
    class Box : Shape
    {
        public Vector2D[] Vertices;

        public Box()
        {
            Vertices = new Vector2D[4];

            Vertices[0] = new Vector2D(-10, -10);
            Vertices[1] = new Vector2D(10, -10);
            Vertices[2] = new Vector2D(10, 10);
            Vertices[3] = new Vector2D(-10, 10);
        }

        public Box(Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4)
        {
            Vertices = new Vector2D[4];

            Vertices[0] = v1;
            Vertices[1] = v2;
            Vertices[2] = v3;
            Vertices[3] = v4;
        }

        public override AABB ComputeAABB()
        {
            //TODO: Compute the AABB of an oriented Box


            return this.aabb;
        }
    }
}
