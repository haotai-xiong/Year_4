﻿/*
 * Copyright (c) 2023 Kodeco Inc.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * Notwithstanding the foregoing, you may not use, copy, modify, merge, publish, 
 * distribute, sublicense, create a derivative work, and/or sell copies of the 
 * Software in any work that is designed, intended, or marketed for pedagogical or 
 * instructional purposes related to programming, coding, application development, 
 * or information technology.  Permission for such use, copying, modification,
 * merger, publication, distribution, sublicensing, creation of derivative works, 
 * or sale is expressly withheld.
 *    
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

using UnityEngine;
using UnityEngine.UI;
using static UnityEditor.PlayerSettings;

public class Game : MonoBehaviour
{
    public int score = 0;
    private int lives = 3;
    public bool isGameOver = false;

    [SerializeField] private GameObject shipModel;
    [SerializeField] private GameObject startGameButton;
    [SerializeField] private Text gameOverText;
    [SerializeField] private Text scoreText;
    [SerializeField] private Text livesText;
    [SerializeField] private GameObject titleText;
    [SerializeField] private Spawner spawner;
    //[SerializeField] private GameObject asteroidExplosion;

    float shipImmunityTimer = 3f;
    public bool immune = false;

    private static Game instance;

    public static Game GetInstance() { return instance; }

    public int Lives {  get { return lives; } set { lives = value; } }


    private void Start()
    {
        instance = this;
        titleText.SetActive(true);
        gameOverText.enabled = false;
        scoreText.enabled = false;
        livesText.enabled = false;
        startGameButton.SetActive(true);
    }

    private void Update()
    {
        if (immune)
        {
            shipImmunityTimer -= Time.deltaTime;
            if (shipImmunityTimer < 0)
            {
                immune = false;
                shipImmunityTimer = 3f;
            }
        }
    }

    public static void GameOver()
    {
        instance.titleText.SetActive(true);
        instance.startGameButton.SetActive(true);
        instance.isGameOver = true;
        instance.spawner.StopSpawning();
        instance.shipModel.GetComponent<Ship>().Explode();
        instance.gameOverText.enabled = true;
    }

    public void NewGame()
    {
        isGameOver = false;
        titleText.SetActive(false);
        startGameButton.SetActive(false);
        shipModel.transform.localPosition = new Vector3(0, 0, 0);
        score = 0;
        scoreText.text = $"Score: {score}";
        scoreText.enabled = true;
        spawner.BeginSpawning();
        shipModel.GetComponent<Ship>().RepairShip();
        spawner.ClearAsteroids();
        gameOverText.enabled = false;
        lives = 3;
        livesText.text = $"Lives: {lives}";
        livesText.enabled = true;
        shipImmunityTimer = 3f;
        immune = false;
    }

    public void AsteroidDestroyed()
    {
        score++;
        scoreText.text = $"Score: {instance.score}";
    }

    public void AsteroidExplode(Vector3 t_pos)
    {
        // Debug.Log("Asteroid Explode Function Triggered");
        GameObject t_explosion = instance.spawner.SpawnAsteroidExplosion(t_pos);
    }

    public Ship GetShip()
    {
        return shipModel.GetComponent<Ship>();
    }

    public Spawner GetSpawner()
    {
        return spawner.GetComponent<Spawner>();
    }

    public void DepleteLife()
    {
        lives -= 1;
        livesText.text = $"Lives: {lives}";
        if (lives <= 0)
        {
            GameOver();
        }
        else
        {
            immune = true;
        }
    }
}
