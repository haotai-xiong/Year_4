using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static Unity.Burst.Intrinsics.X86.Avx;

public class BoundaryCheck : MonoBehaviour
{
    public static BoundaryCheck Instance { get; private set; }

    public GameObject boundaryGameObject;
    public BoxCollider2D boundaryBox;

    private float MinX;
    private float MaxX;
    private float MinY;
    private float MaxY;

    void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
            DontDestroyOnLoad(gameObject);
        }
        else
        {
            Destroy(gameObject);
        }
    }

    void Start()
    {
        boundaryBox = boundaryGameObject.GetComponent<BoxCollider2D>();

        MinX = boundaryBox.bounds.min.x;
        MaxX = boundaryBox.bounds.max.x;
        MinY = boundaryBox.bounds.min.y;
        MaxY = boundaryBox.bounds.max.y;
    }

    // wrap around boundary check
    public void BoundaryChecking(ref Vector3 goPos, ref Collider2D goCollider)
    {
        goPos.x = Repositioning(goPos.x, ref MinX, ref MaxX, goCollider.bounds.size.x);
        goPos.y = Repositioning(goPos.y, ref MinY, ref MaxY, goCollider.bounds.size.y);
    }

    private float Repositioning(float position, ref float minBoundary, ref float maxBoundary, float size)
    {
        if (position < minBoundary - size / 2.0f)
        {
            return maxBoundary + size / 2.0f;
        }
        if (position > maxBoundary + size / 2.0f)
        {
            return minBoundary - size / 2.0f;
        }
        return position;
    }
}
