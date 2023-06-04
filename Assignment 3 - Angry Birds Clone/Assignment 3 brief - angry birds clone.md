 # Summary of the game:
 
 Componets of the game:
  Propeller System:
    - The propeller is a static rectangular body located at (150, 480) with a size of (200, 15).
    - You can control the propeller's angle by pressing the left and right arrow keys, which will change its angular velocity.
    - The propeller is drawn on the screen using the drawPropeller() function.

  Bird Creation:
    - Pressing the 'b' key will create a bird at the current mouse position using the setupBird() function.
    - The birds are stored in an array and their movement is simulated in the physics world.
    - The drawBirds() function loops over the birds array and draws them on the screen using the drawVertices() function.
    - Birds that go off-screen are removed from the physics world and the array.

  Tower of Boxes:
    - The setupTower() function creates a tower of boxes with dimensions 80x80 pixels.
    - The tower is six boxes high and three boxes wide, forming a structure.
    - Each box has a random shade of green assigned to it from the colors array.
    - The drawTower() function loops over the boxes array and draws each box on the screen using the drawVertices() function.

  Slingshot:
    - The slingshot consists of a circular body called slingshotBird and a constraint called slingshotConstraint.
    - The setupSlingshot() function initializes these elements, positioning them accordingly.
    - You can control the slingshot by dragging it with the mouse to extend its position and release the mouse to launch the bird.
    - The drawSlingshot() function draws the slingshot bird and constraint using the drawVertices() and drawConstraint() functions.

  Additional Interactions:
    - The game includes a ground that is automatically created and drawn.
    - Pressing the 'r' key resets the slingshot, removing the current bird and constraint, and setting up a new slingshot.





# Step 1:
_____________
the setupPropeller() function needs to create a rectangular body to represent the propeller in the game. This body will be static, meaning it won't move on its own. The body should be positioned at coordinates (150, 480) and have a size of (200, 15). The initial angle of the propeller should be set to the value of the global variable angle. Finally, the propeller should be added to the world.

To implement this step, you can modify the setupPropeller() function in the physics.js file as follows:

```js
function setupPropeller() {
  propeller = Bodies.rectangle(150, 480, 200, 15, { isStatic: true, angle: angle });
  World.add(engine.world, [propeller]);
}
```

In this code, Bodies.rectangle() creates a rectangular body with the specified dimensions and position. 
- The isStatic: true option ensures that the propeller remains fixed in its position. 
- The angle: angle sets the initial angle of the propeller to the value of the global variable angle. Finally, the propeller body is added to the world using World.add().
- By adding this code, the setupPropeller() function will create and add the propeller to the world when it is called.

# Step 2
__________________________

Step 2 involves updating the propeller's angle and angular velocity in the drawPropeller() function, as well as adjusting the angle speed based on arrow key presses in the keyPressed() function.

In the drawPropeller() function:
- Set the angle of the propeller to the global variable angle.
- Set the angular velocity of the propeller to the global variable angleSpeed.
- Update the angle variable by adding the angleSpeed value to it.
- Draw the propeller on the canvas using the drawVertices() helper function.

Here's the updated code for drawPropeller() in the physics.js file:

```js
function drawPropeller() {
  push(); // This function is used to push the current drawing settings onto a stack. 
  // It allows us to temporarily change the drawing state without affecting other elements drawn afterwards.
  Body.setAngle(propeller, angle);
  Body.setAngularVelocity(propeller, angleSpeed);
  angle += angleSpeed;

  fill(0, 255, 0); // Set fill color to green (R: 0, G: 255, B: 0)
  drawVertices(propeller.vertices);
  pop();
  // This function is used to restore the drawing settings previously saved with push(). 
  // It ensures that any changes made within the push() and pop() blocks do not affect other elements drawn outside of them.
}
```

In the keyPressed() function:
- When the left arrow key is pressed, increment the angleSpeed variable by 0.01.
- When the right arrow key is pressed, decrement the angleSpeed variable by 0.01.

```js
function keyPressed() {
  if (keyCode === LEFT_ARROW) {
    angleSpeed += 0.01;
  } else if (keyCode === RIGHT_ARROW) {
    angleSpeed -= 0.01;
  }
}
```
- These changes ensure that the drawPropeller() function updates the propeller's angle and velocity, and the keyPressed() function adjusts the angleSpeed variable based on arrow key presses.
- With these updates, when you run the sketch, you should be able to control the propeller on the screen using the left and right arrow keys.

# Step 3
_________________________________

Step 3 involves creating birds when the 'b' key is pressed, updating the drawBirds() function to draw the birds, checking if the birds have left the screen using the isOffScreen() function, and removing the birds from the physics world and the array if they have left the screen. When the 'b' key is pressed, a bird is created at the current mouse position by calling the setupBird() function.

- Amend the drawBirds() function to loop over the birds array and draw each bird using the drawVertices() helper function. Additionally, check if each bird has left the screen using the isOffScreen() function. If a bird is off-screen, remove it from the physics world using the removeFromWorld() helper function and remove it from the birds array. Make sure to decrement the for-loop counter to avoid any issues with the loop.

- Here's the updated code for drawBirds() in the physics.js file:
```js
function drawBirds() {
  push(); // Save the current drawing style settings

  // Loop through the birds array in reverse order
  for (var i = birds.length - 1; i >= 0; i--) {
    var bird = birds[i]; // Get the current bird

    fill(225, 0, 0); // Set fill color to red (R: 0, G: 255, B: 0)
    drawVertices(bird.vertices); // Draw the bird using its vertices

    // Check if the bird is off-screen
    if (isOffScreen(bird)) {
      removeFromWorld(bird); // Remove the bird from the physics world
      birds.splice(i, 1); // Remove the bird from the birds array
    }
  }
  pop(); // Restore the previous drawing style settings
}
```
- Implement the removeFromWorld() function. This function removes a body from the physics world:

```js
function removeFromWorld(body) {
  World.remove(engine.world, body);
}
```

- With these changes, when you press the 'b' key, a bird will be created at the mouse position. The drawBirds() function will draw the birds on the canvas, and if a bird goes off-screen, it will be removed from the physics world and the birds array.

- Now, when you press 'b', a new bird will be created at the mouse position, and it will fly away upon impact with the moving propeller.


# Step 4
_________________________________________________________________

Step 4, which involves creating a tower of boxes, follow these steps:

  - Amend the setupTower() function in the physics.js file.
  - Create a nested for loop to iterate over the desired number of rows and columns for the tower.
  - Inside the loop, create a rectangle body using Bodies.rectangle() with a width and height of 80 pixels.
  - Calculate the position of each box based on the row and column index, and add an offset if necessary.
  - Push each box body to the boxes array.
  - Generate a random shade of green for each box and push it to the colors array.
  - Add the boxes to the physics world using World.add().

Here's the updated code for the setupTower() function:
```js
function setupTower() {
  var boxSize = 80; // Size of each box
  var towerHeight = 6; // Number of rows in the tower
  var towerWidth = 3; // Number of columns in the tower
  var towerOffsetX = 200; // X-coordinate offset for the tower
  var towerOffsetY = height - towerHeight * boxSize - 20; // Y-coordinate offset for the tower
  // Calculates the Y-coordinate offset for the tower based on the canvas height, number of rows, box size, and additional spacing.
  

  // Loop through each row of the tower
  for (var row = 0; row < towerHeight; row++) {
    // Loop through each column of the tower
    for (var col = 0; col < towerWidth; col++) {
      var x = towerOffsetX + col * boxSize; // Calculate the x-coordinate of the current box
      var y = towerOffsetY + row * boxSize; // Calculate the y-coordinate of the current box

      var box = Bodies.rectangle(x, y, boxSize, boxSize); // Create a box body at the specified position and size
      boxes.push(box); // Add the box body to the boxes array

      // Generate a random shade of green for the box color
      var shadeOfGreen = color(random(50, 150), random(150, 255), random(50, 150));
      colors.push(shadeOfGreen); // Add the color to the colors array
    }
  }

  World.add(engine.world, boxes); // Add all the box bodies to the physics world
}

```

Make sure to add the necessary variables and arrays to the beginning of the file:
```js
var boxes = []; // Array to store box bodies
var colors = []; // Array to store colors of the boxes
```

- With these changes, the setupTower() function will create a tower of boxes with the specified dimensions and colors. The boxes will be added to the boxes array and the colors will be added to the colors array. Finally, the boxes will be added to the physics world using World.add().

- Now, when you run the program, you should see a tower of boxes on the screen.

# Step 5
________________________________
Step 5, which involves drawing the tower of boxes in different shades of green, follow these steps:

    - Amend the drawTower() function in the physics.js file.
    - Use a for loop to iterate over the boxes array.
    - Inside the loop, retrieve the box body and its corresponding color from the boxes and colors arrays, respectively.
    - Set the fill color to the retrieved color using fill().
    - Draw the box using the drawVertices() helper function, passing in the box's vertices.
    - Close the loop.

Here's the updated code for the drawTower() function:
```js
function drawTower() {
  push();
  for (var i = 0; i < boxes.length; i++) {
    var box = boxes[i];
    var color = colors[i];
    fill(color);
    drawVertices(box.vertices);
  }
  pop();
}
```
- With these changes, the drawTower() function will loop over the boxes array and draw each box using the drawVertices() helper function. The fill color for each box will be retrieved from the colors array, resulting in a tower of boxes in different shades of green.

- Now, when you run the program, you should see a tower of boxes in various shades of green on the screen.

# Step 6
_____________________________
To implement Step 6, which involves creating a slingshot with a bird and a constraint, follow these steps:

  - Amend the setupSlingshot() function in the physics.js file.
  - Create the slingshotBird as a circular body using Bodies.circle(). Set its position to the desired coordinates, and provide the necessary options: zero friction and a restitution of 0.95.
  - Adjust the mass of the slingshotBird by using Matter.Body.setMass() and multiplying its mass by 10.
  - Create the slingshotConstraint as a constraint using Constraint.create(). Provide the necessary options: stiffness of 0.01 and damping of 0.0001. Set the bodyA property to null for now.
  - Add the slingshotBird and the slingshotConstraint to the physics world using World.add().

Here's the updated code for the setupSlingshot() function:
```js
function setupSlingshot() {
  var birdX = 200; // X-coordinate of the slingshot bird
  var birdY = height - 100; // Y-coordinate of the slingshot bird
  var birdRadius = 20; // Radius of the slingshot bird

  // Create the slingshot bird as a circular body
  slingshotBird = Bodies.circle(birdX, birdY, birdRadius, {
    friction: 0,
    restitution: 0.95,
  });

  // Increase the mass of the slingshot bird
  Matter.Body.setMass(slingshotBird, slingshotBird.mass * 10);

  // Add the slingshot bird to the physics world
  World.add(engine.world, slingshotBird);

  // Set up the slingshot constraint options
  var constraintOptions = {
    bodyA: null,
    pointB: { x: birdX, y: birdY },
    stiffness: 0.01,
    damping: 0.0001,
  };

  // Create the slingshot constraint
  slingshotConstraint = Constraint.create(constraintOptions);

  // Add the slingshot constraint to the physics world
  World.add(engine.world, slingshotConstraint);
}
```
- With these changes, the setupSlingshot() function will create the slingshotBird as a circular body and the slingshotConstraint as a constraint. Both the bird and the constraint will be added to the physics world.
- In the provided code, the variable birdY is set to height - 100 to position the slingshot bird near the bottom of the canvas.

# Step 7
________________________
Step 7, which involves drawing the slingshot bird and constraint and enabling mouse control, follow these steps:

- Amend the drawSlingshot() function in the physics.js file.
- Inside the function, use the drawVertices() helper function to draw the slingshot bird. Pass in the vertices of the slingshotBird body.
- Use the drawConstraint() helper function to draw the slingshot constraint. Pass in the slingshotConstraint object.
- Close the function.

Here's the updated code for the drawSlingshot() function:

```js
function drawSlingshot() {
  push();
  
  // Draw the slingshot bird
  drawVertices(slingshotBird.vertices);

  // Draw the slingshot constraint
  drawConstraint(slingshotConstraint);

  pop();
}

```

- With these changes, the drawSlingshot() function will draw the slingshot bird and constraint on the screen using the drawVertices() and drawConstraint() helper functions, respectively.

- Now, when you run the program, you should be able to control the slingshot with the mouse. You can drag the slingshot to extend it and release the mouse button to launch the bird. Pressing 'r' will reset the slingshot, allowing you to create a new bird and use it again.

- Please note that the behavior of the slingshot may also depend on other parts of the code, such as mouse interactions and physics calculations, which are not mentioned in this specific step.

# Step 8
 Step 8 and add further development to the game, you can choose one of the ideas mentioned or come up with your own. Let's go through each idea and see how you can implement it:

 - Turn it into a game with a countdown: To add a countdown timer to the game, you can create a variable to store the remaining time and decrement it in the draw() function on each frame. You can display the countdown on the screen using the text() function from p5.js. Here's an example of how you can implement it:
```js
var countdown = 60; // Initial countdown time in seconds

function draw() {
  // ... (existing code)

  // Decrement the countdown
  countdown -= 1 / frameRate();

  // Display the countdown on the screen
  textSize(32);
  fill(255);
  text("Time: " + Math.ceil(countdown), 10, 50);

  // Check if the countdown reaches zero
  if (countdown <= 0) {
    // Stop the game or perform any necessary actions
    noLoop();
    textSize(64);
    fill(255, 0, 0);
    text("GAME OVER", width / 2 - 150, height / 2);
  }
}
```

- In this example, the countdown starts at 60 seconds (countdown = 60), and on each frame, it decreases by the elapsed time (1 divided by frameRate(), which gives the frame time in seconds). The countdown is displayed using the text() function, and when it reaches zero, the game is over, and the "GAME OVER" message is displayed on the screen.

- Change colors and style: To make the game your own by changing the colors and style, you can modify the colors used for the ground, propeller, birds, boxes, and other elements. You can use the fill() function with different color values to change the appearance. Additionally, you can experiment with different shapes, textures, and visual effects to customize the game's style.

- Add another physics object: To add another physics object that adds to the gameplay, you can create a new body using the Bodies module from Matter.js. For example, you could add a dynamic circle that moves around the screen and interacts with other objects. You can create the object in the setup() function, update its position in the draw() function, and add any necessary constraints or interactions.

Remember to implement these changes in the appropriate functions and sections of the code, based on the chosen idea. Feel free to mix and match ideas or come up with your own creative additions to make the game more interesting and engaging.

