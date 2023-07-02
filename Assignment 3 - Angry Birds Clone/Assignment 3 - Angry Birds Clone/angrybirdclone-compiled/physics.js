////////////////////////////////////////////////////////////////
function setupGround(){
  ground = Bodies.rectangle(500, 600, 1000, 40, {
    isStatic: true, angle: 0
  });
  World.add(engine.world, [ground]);
}

////////////////////////////////////////////////////////////////
function drawGround(){
  push();
  fill(128);
  drawVertices(ground.vertices);
  pop();
}
////////////////////////////////////////////////////////////////
function setupPropeller() {
  // Create a static rectangle body for the propeller at position (150, 480) with size (200, 15)
  propeller = Bodies.rectangle(150, 480, 200, 15, {
    isStatic: true,
    angle: angle
  });

  // Add the propeller to the physics world
  World.add(engine.world, [propeller]);
}

////////////////////////////////////////////////////////////////
//updates and draws the propeller
function drawPropeller() {
  push();
  // Set the angle of the propeller to the global variable angle
  Body.setAngle(propeller, angle);

  // Set the angular velocity of the propeller to the global variable angleSpeed
  Body.setAngularVelocity(propeller, angleSpeed);

  // Update the variable angle by angleSpeed
  angle += angleSpeed;

  // Draw the propeller using the drawVertices() helper function
  fill(255);
  drawVertices(propeller.vertices);
  pop();
}

////////////////////////////////////////////////////////////////
// function setupBird(){
//   var bird = Bodies.circle(mouseX, mouseY, 20, {friction: 0,
//       restitution: 0.95 });
//   Matter.Body.setMass(bird, bird.mass*10);
//   World.add(engine.world, [bird]);
//   birds.push(bird);
// }

function setupBird() {
  var bird = Bodies.circle(mouseX, mouseY, 20, {
    friction: 0,
    restitution: 0.95
  });
  Matter.Body.setMass(bird, bird.mass * 10);
  World.add(engine.world, [bird]);
  birds.push(bird);
}

////////////////////////////////////////////////////////////////
function drawBirds() {
  push();
  for (var i = birds.length - 1; i >= 0; i--) {
    var bird = birds[i];

    // Draw the bird using the drawVertices() helper function
    fill(255);
    drawVertices(bird.vertices);

    // Check if the bird is off-screen
    if (isOffScreen(bird)) {
      // Remove the bird from the physics world and from the array
      removeFromWorld(bird);
      birds.splice(i, 1);

      // Decrement the for-loop counter to avoid breaking the loop
      i--;
    }
  }
  pop();
}

////////////////////////////////////////////////////////////////
//creates a tower of boxes
function setupTower() {
  var boxWidth = 80;
  var boxHeight = 80;
  var towerRows = 6;
  var towerColumns = 3;

  for (var row = 0; row < towerRows; row++) {
    for (var col = 0; col < towerColumns; col++) {
      var x = 400 + col * boxWidth;
      var y = height - 100 - row * boxHeight;
      var box = Bodies.rectangle(x, y, boxWidth, boxHeight);
      boxes.push(box);
      World.add(engine.world, [box]);

      // Generate a random shade of green and push it onto the colors array
      var greenShade = color(random(0, 100), random(150, 255), random(0, 100));
      colors.push(greenShade);
    }
  }
}

////////////////////////////////////////////////////////////////
//draws tower of boxes
function drawTower() {
  push();
  for (var i = 0; i < boxes.length; i++) {
    var box = boxes[i];
    var boxColor = colors[i];

    // Set the fill color to the random shade of green from the colors array
    fill(boxColor);

    // Draw the box using the drawVertices() helper function
    drawVertices(box.vertices);
  }
  pop();
}

////////////////////////////////////////////////////////////////
function setupSlingshot() {
  slingshotBird = Bodies.circle(200, height - 200, 20, {
    friction: 0,
    restitution: 0.95
  });
  Matter.Body.setMass(slingshotBird, slingshotBird.mass * 10);
  World.add(engine.world, [slingshotBird]);

  var constraintOptions = {
    stiffness: 0.01,
    damping: 0.0001,
    bodyA: slingshotBird,
    pointB: { x: 200, y: height - 200 }
  };
  slingshotConstraint = Constraint.create(constraintOptions);
  World.add(engine.world, [slingshotConstraint]);
}

////////////////////////////////////////////////////////////////
//draws slingshot bird and its constraint
function drawSlingshot() {
  push();

  // Draw slingshot bird
  fill(255);
  drawVertices(slingshotBird.vertices);

  // Draw slingshot constraint
  drawConstraint(slingshotConstraint);

  pop();
}

/////////////////////////////////////////////////////////////////
function setupMouseInteraction(){
  var mouse = Mouse.create(canvas.elt);
  var mouseParams = {
    mouse: mouse,
    constraint: { stiffness: 0.05 }
  }
  mouseConstraint = MouseConstraint.create(engine, mouseParams);
  mouseConstraint.mouse.pixelRatio = pixelDensity();
  World.add(engine.world, mouseConstraint);
}
