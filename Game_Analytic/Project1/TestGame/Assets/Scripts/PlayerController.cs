using System.Xml.Serialization;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    [SerializeField]
    private float moveSpeed = 3.0f;
    private Vector2 direction;
    private Vector3 currentPos;
    private new Collider2D collider;

    private float timer;
    GameState playerData;

    private void Start()
    {
        currentPos = transform.position;
        collider = GetComponent<Collider2D>();
        playerData = new() { collision_happended_time = "", player_clicks = 0, collision_count = 0 };
    }

    void Update()
    {
        if (!GameManager.Instance.gameFinished)
        {
            if (Input.GetMouseButtonDown(0)) // left click
            {
                Vector2 targetPosition = Camera.main.ScreenToWorldPoint(Input.mousePosition);
                direction = (targetPosition - (Vector2)transform.position).normalized;
                playerData.player_clicks += 1;
            }
            Move();

            timer += Time.deltaTime;
        }
    }

    [System.Obsolete]
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.CompareTag("Enemy"))
        {
            GameManager.Instance.gameFinished = true;
            playerData.collision_count += 1;
            playerData.collision_happended_time = timer.ToString("0.00") + " seconds";
            string jsonData = JsonUtility.ToJson(playerData);
            StartCoroutine(AnalyticsManager.PostMethod(jsonData));
        }
    }

    private void Move()
    {
        currentPos += (Vector3)(moveSpeed * Time.deltaTime * direction);
        BoundaryCheck.Instance.BoundaryChecking(ref currentPos, ref collider);
        transform.position = currentPos;
    }
}
