using UnityEngine;

public class Character : MonoBehaviour
{
    [SerializeField] private float movementSpeed = 10;
    
    void Update()
    {
        Inputs.ReadFromArduino();
        
        transform.position +=
            (Inputs.forward * transform.forward + Inputs.right * transform.right)
            * Time.deltaTime * movementSpeed;
    }
}
