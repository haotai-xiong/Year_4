using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CombinedFilter
{
    public static int[] combinedFilter(int[] xs)
    {
        return Modulo3Filter.Modulo3(DiffFilter.Diff(xs));
    }
}



