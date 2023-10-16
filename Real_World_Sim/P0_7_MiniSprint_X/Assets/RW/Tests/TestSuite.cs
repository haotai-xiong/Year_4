using UnityEngine;
using UnityEngine.TestTools;
using NUnit.Framework;
using System.Collections;

public class LaserTest
{

    private Game game;
    private Ship ship;

    [SetUp]
    public void Setup()
    {
        GameObject gameGameObject =
          MonoBehaviour.Instantiate(
            Resources.Load<GameObject>("Prefabs/Game"));
        game = gameGameObject.GetComponent<Game>();
        ship = game.GetShip();
    }

    [TearDown]
    public void Teardown()
    {
        Object.Destroy(game.gameObject);
    }

    [UnityTest]
    public IEnumerator TestShipCoolDown()
    {
        for (int i = 0; i < 10; i++)
        {
            ship.ShootLaser();
        }
        yield return new WaitForSeconds(2.5f); // Wait for 2 seconds + some buffer time
        Assert.IsFalse(ship.IsReloading());
    }
}