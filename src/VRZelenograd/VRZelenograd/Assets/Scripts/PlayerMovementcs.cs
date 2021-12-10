namespace Assets.Scripts;

using UnityEngine;


public class PlayerMovement : MonoBehaviour
{
    public CharacterController controller;
    public readonly float speed = 12f;
    // void Start() {
    //     Assert.AreEqual(speed , 12f);
    // }

    void Update() {
        var x = Input.GetAxis("Horizontal");
        var z = Input.GetAxis("Vertical");

        var move = transform.right * x + transform.forward * z;

        controller.Move(move * speed * Time.deltaTime);
    }
}