using UnityEngine;

public class AutoDestroyParticleSystem : MonoBehaviour
{
    private new ParticleSystem particleSystem;

    void Start()
    {
        particleSystem = GetComponent<ParticleSystem>();
    }

    void Update()
    {
        if (particleSystem.isPlaying == false)
        {
            Destroy(gameObject);
        }
    }
}