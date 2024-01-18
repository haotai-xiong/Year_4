using UnityEngine;

public class EnemyController : MonoBehaviour
{
    public float changeTime = 1.0f;
    private float timer;
    public float moveSpeed = 10.0f;

    private Vector2 randomDirection;
    private Vector3 currentPos;
    private new Collider2D collider;

    void Start()
    {
        timer = changeTime;
        currentPos = transform.position;
        collider = GetComponent<Collider2D>();
        GetRandomDirection();
    }

    void Update()
    {
        if (!GameManager.Instance.gameFinished)
        {
            timer -= Time.deltaTime;

            if (timer <= 0)
            {
                GetRandomDirection();
                timer = changeTime;
            }
            Move();
        }
    }

    private void GetRandomDirection()
    {
        randomDirection = new Vector2(Random.Range(-1.0f, 1.0f), Random.Range(-1.0f, 1.0f)).normalized;
    }

    private void Move()
    {
        currentPos += (Vector3)(moveSpeed * Time.deltaTime * randomDirection);
        BoundaryCheck.Instance.BoundaryChecking(ref currentPos, ref collider);
        transform.position = currentPos;
    }
}
