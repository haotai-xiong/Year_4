using System.Collections;
using System.Collections.Generic;
using NUnit.Framework;
using UnityEngine;
using UnityEngine.TestTools;

namespace Tests
{
    public class CombinedFilterTest
    {
        [Test]
        public void CombinedFilterSimple()
        {
            int[] input = { 1, 4, 10, 2000, 999,  };
            int[] output = CombinedFilter.combinedFilter(input);
            int[] expected = { 1, 0, 0, 1, 2 };

            CollectionAssert.AreEqual(expected, output);
        }
    }
}
