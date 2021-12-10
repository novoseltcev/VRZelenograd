using System.Collections;
using NUnit.Framework;
using UnityEngine;
using Object = UnityEngine.Object;

namespace Assets.Tests;

public class MouseLookTest
{
    private GameObject go;
    private MouseLook _mouseLook;
    
    [SetUp]
    public void Setup()
    {
        go = new GameObject();
        _mouseLook = go.AddComponent<MouseLook>();
    }

    [TearDown]
    public void TearDown()
    {
        Object.Destroy(go);
    }
    
    [UnityTest]
    public IEnumerator CheckDownBoundary()
    {
        yield return new WaitForFixedUpdate();
        Assert.Greater(0, _mouseLook.GetMouseX());
        Assert.Greater(0, _mouseLook.GetMouseY());
        Assert.Less(1, _mouseLook.GetMouseX());
        Assert.Less(1, _mouseLook.GetMouseY());
    }
    
    [UnityTest]
    public IEnumerator CheckUpBoundary()
    {
        yield return new WaitForFixedUpdate();
        Assert.Less(1, _mouseLook.GetMouseX());
        Assert.Less(1, _mouseLook.GetMouseY());
    }
}