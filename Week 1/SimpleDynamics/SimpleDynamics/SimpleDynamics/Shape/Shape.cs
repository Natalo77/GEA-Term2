using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleDynamics
{
    abstract class Shape
    {
        protected AABB aabb = null;

        public abstract AABB ComputeAABB();
    }
}
