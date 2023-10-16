using System.Collections;
using NUnit.Framework;
using UnityEngine;
using UnityEngine.TestTools;

public class TestSuite
{
    // 1
    private Game game;

    [SetUp]
    public void Setup()
    {
        GameObject gameGameObject =
            Object.Instantiate(Resources.Load<GameObject>("Prefabs/Game"));
        game = gameGameObject.GetComponent<Game>();
    }

    [TearDown]
    public void Teardown()
    {
        Object.Destroy(game.gameObject);
    }

    // unity test
    [UnityTest]
    public IEnumerator AsteroidsMoveDown()
    {
        // 3
        GameObject asteroid = game.GetSpawner().SpawnAsteroid();
        // 4
        float initialYPos = asteroid.transform.position.y;
        // 5
        yield return new WaitForSeconds(0.1f);
        // 6
        Assert.Less(asteroid.transform.position.y, initialYPos);
    }

    [UnityTest]
    public IEnumerator GameOverOccursOnAsteroidCollision()
    {
        GameObject asteroid = game.GetSpawner().SpawnAsteroid();
        //1
        game.Lives = 1;
        asteroid.transform.position = game.GetShip().transform.position;
        //2
        yield return new WaitForSeconds(0.1f);

        //3
        Assert.True(game.isGameOver);
    }

    [Test]
    public void NewGameRestartsGame()
    {
        // 2
        game.isGameOver = true;
        game.NewGame();
        // 3
        Assert.False(game.isGameOver);
    }

    [UnityTest]
    public IEnumerator LaserMovesUp()
    {
        // 1
        GameObject laser = game.GetShip().SpawnLaser();
        // 2
        float initialYPos = laser.transform.position.y;
        yield return new WaitForSeconds(0.1f);
        // 3
        Assert.Greater(laser.transform.position.y, initialYPos);
    }

    [UnityTest]
    public IEnumerator LaserDestroysAsteroid()
    {
        // 1
        GameObject asteroid = game.GetSpawner().SpawnAsteroid();
        asteroid.transform.position = Vector3.zero;
        GameObject laser = game.GetShip().SpawnLaser();
        laser.transform.position = Vector3.zero;
        yield return new WaitForSeconds(0.1f);
        // 2
        // NUnit framework assertion Assert.IsNull() will not work for Unity null checks
        // When checking for nulls in Unity, you must explicitly use the 'UnityEngine.Assertions.Assert'
        // Not the NUnit 'Assert'
        UnityEngine.Assertions.Assert.IsNull(asteroid);
    }

    [UnityTest]
    public IEnumerator DestroyedAsteroidRaisesScore()
    {
        // 1
        GameObject asteroid = game.GetSpawner().SpawnAsteroid();
        asteroid.transform.position = Vector3.zero;
        GameObject laser = game.GetShip().SpawnLaser();
        laser.transform.position = Vector3.zero;
        yield return new WaitForSeconds(0.1f);
        // 2
        Assert.AreEqual(game.score, 1);
    }


    [UnityTest]
    public IEnumerator ShipStaysWithinLimits()
    {
        game.GetShip().MoveLeft();
        Vector3 t_Pos = game.GetShip().transform.localPosition;
        yield return new WaitForSeconds(0.1f);

        Assert.Greater(t_Pos.x, game.GetShip().MaxRight);
        Assert.Less(t_Pos.x, game.GetShip().MaxLeft);
    }

    [UnityTest]
    public IEnumerator ShipMoveLeft()
    {
        // 1
        Vector3 initPos = game.GetShip().transform.position;
        game.GetShip().MoveLeft();
        yield return new WaitForSeconds(0.1f);

        // 2
        Assert.Less(game.GetShip().transform.position.x, initPos.x);
    }

    [UnityTest]
    public IEnumerator ShipMoveRight()
    {
        // 1
        Vector3 initPos = game.GetShip().transform.position;
        game.GetShip().MoveRight();
        yield return new WaitForSeconds(0.1f);

        // 2
        Assert.Greater(game.GetShip().transform.position.x, initPos.x);
    }

    [UnityTest]
    public IEnumerator AsteroidDestoryedAfterMovingOut()
    {
        // 1
        GameObject asteroid = game.GetSpawner().SpawnAsteroid();
        asteroid.transform.position = new Vector3(asteroid.gameObject.transform.position.x, asteroid.GetComponent<Asteroid>().MaxY, asteroid.gameObject.transform.position.z);
        yield return new WaitForSeconds(0.1f);
        // 2
        UnityEngine.Assertions.Assert.IsNull(asteroid);
    }

    [UnityTest]
    public IEnumerator TestParticleSystemStarts()
    {
        // 1
        // GameObject parSys = Resources.Load<GameObject>("Prefabs/AsteroidExplosion");

        GameObject temp_ParSys = game.GetSpawner().SpawnAsteroidExplosion(game.GetShip().transform.position);
        GameObject particleSystemGameObject = Object.Instantiate(temp_ParSys);
        ParticleSystem particleSystem = particleSystemGameObject.GetComponent<ParticleSystem>();

        // 2
        particleSystem.Play();
        yield return null;

        // 3
        Assert.IsTrue(particleSystem.isPlaying);
    }

    [UnityTest]
    public IEnumerator TestParticleSystemStops()
    {
        // 1
        // GameObject parSys = Resources.Load<GameObject>("Prefabs/AsteroidExplosion");

        GameObject temp_ParSys = game.GetSpawner().SpawnAsteroidExplosion(game.GetShip().transform.position);
        GameObject particleSystemGameObject = Object.Instantiate(temp_ParSys);
        ParticleSystem particleSystem = particleSystemGameObject.GetComponent<ParticleSystem>();
        particleSystem.GetComponent<AutoDestroyParticleSystem>().enabled = false;

        // 2
        particleSystem.Play();
        particleSystem.Stop();
        yield return null;

        // 3
        Assert.IsFalse(particleSystem.isPlaying);
    }

    [UnityTest]
    public IEnumerator ShipMoveUp()
    {
        // 1
        Vector3 initPos = game.GetShip().transform.localPosition;
        game.GetShip().MoveUp();
        yield return new WaitForSeconds(0.1f);

        // 2
        Assert.Less(game.GetShip().transform.localPosition.z, initPos.z);
    }

    [UnityTest]
    public IEnumerator ShipMoveDown()
    {
        // 1
        Vector3 initPos = game.GetShip().transform.localPosition;
        game.GetShip().MoveDown();
        yield return new WaitForSeconds(0.1f);

        // 2
        Assert.Greater(game.GetShip().transform.localPosition.z, initPos.z);
    }
}