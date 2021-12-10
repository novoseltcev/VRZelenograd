namespace Assets.Tests;

using UnityEngine;

public class MouseLook : MonoBehaviour {
    public float mouseSensitivity = 100f;
    public Transform playerBody;
    private float _mouseX;
    private float _mouseY;
    private float _xRotation = 0f;

    public float GetMouseX()
    {
        return _mouseX;
    }
    
    public float GetMouseY()
    {
        return _mouseY;
    }
    
    public float GetRotation()
    {
        return _xRotation;
    }
    
    public void Start() {
        Cursor.lockState = CursorLockMode.Locked;
    }
    
    public void Update() {

        _mouseX = Input.GetAxis("Mouse X") * mouseSensitivity * Time.deltaTime;
        _mouseY = Input.GetAxis("Mouse Y") * mouseSensitivity * Time.deltaTime;

        _xRotation -= _mouseY;
        _xRotation = Mathf.Clamp(_xRotation, -90f, 90f);

        transform.localRotation = Quaternion.Euler(_xRotation, 0f, 0f);
        playerBody.Rotate(Vector3.up * _mouseX);
    }
}