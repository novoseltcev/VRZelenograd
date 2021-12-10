using UnityEngine;
using NUnit.Framework;

namespace Assets.Tests;

using Assets.Scripts;

public class MouseLookTest
{
    private GameObject _player;
    private MouseLook _mouseLook;
    
    [SetUp]
    public void Setup()
    {
        _player = MonoBehaviour.Instantiate(Resources.Load<GameObject>("Prefabs/Player"));
        _mouseLook = _player.AddComponent<MouseLook>();
        _mouseLook.Start();
        _mouseLook.Update();

    }

    [TearDown]
    public void TearDown()
    {
        MouseLook.Destroy(_mouseLook);
        GameObject.Destroy(_player);
    }
    
    [Test]
    public void CheckBoundary()
    {
        Assert.Greater(0, _mouseLook.GetMouseX());
        Assert.Greater(0, _mouseLook.GetMouseY());
        Assert.Less(1, _mouseLook.GetMouseX());
        Assert.Less(1, _mouseLook.GetMouseY());
    }
    
    // [NUnit.Framework.Test]
    // public void CheckRotation()
    // {
    //     
    // }
}