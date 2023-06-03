# Step 1:
_____________
the setupPropeller() function needs to create a rectangular body to represent the propeller in the game. This body will be static, meaning it won't move on its own. The body should be positioned at coordinates (150, 480) and have a size of (200, 15). The initial angle of the propeller should be set to the value of the global variable angle. Finally, the propeller should be added to the world.

To implement this step, you can modify the setupPropeller() function in the physics.js file as follows:

```python
function setupPropeller() {
  propeller = Bodies.rectangle(150, 480, 200, 15, { isStatic: true, angle: angle });
  World.add(engine.world, [propeller]);
}
```

In this code, Bodies.rectangle() creates a rectangular body with the specified dimensions and position. 
- The isStatic: true option ensures that the propeller remains fixed in its position. 
- The angle: angle sets the initial angle of the propeller to the value of the global variable angle. Finally, the propeller body is added to the world using World.add().
- By adding this code, the setupPropeller() function will create and add the propeller to the world when it is called.
