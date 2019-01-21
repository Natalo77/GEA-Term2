using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleDynamics
{
    class Circle : Shape
    {
        public Vector2D Centre { get; set; }
        public float Radius { get; set; }

        public Circle()
        {
            this.Centre = new Vector2D();
            this.Radius = 15.0f;
        }

        public override AABB ComputeAABB()
        {
            if (this.aabb != null) return this.aabb;
            
            this.aabb = new AABB();

            aabb.MIN = new Vector2D(Centre.X - Radius, Centre.Y - Radius);
            aabb.MAX = new Vector2D(Centre.X + Radius, Centre.Y + Radius);

            return new AABB();
        }
    }
}
