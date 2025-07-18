# Uses Unreal Engine 5.6 or higher

Here is a RTS game prototype.
It includes: 
- Camera Controls
- Input managing in controller
- RTS selection units and buildings
- Dynamic UI
- Unit orders


# ProxyAssault's Camera
The camera can be tilted using the mouse scroll wheel.
The camera can also be panned by additionally pressing shift.
The camera can be moved using either ZQSD keys, WQSA keys, keyboard's arrows or by approaching the cursor from the screen's border.
To smoothen the movement, raycasts are traced to the ground and adjust the camera height.
Pressing control key and using the mouse wheel scroll at the same time enables to adjust the camera movement speed.
<p align="center">
  <video src="https://github.com/user-attachments/assets/87a5f5c1-e65d-44f0-a452-0283210cd869" width="500px"></video>
</p>

# RTS units & buildings selection
Units and buildings can be selected with the mouse's left button.
Selection square zones can be created using drag & drop on the screen.
Once, buildings are selected, different types of unit can produced.


# RTS units & buildings orders
After units are selected, the mouse's left button can be used to order them to move.
Different formations can be applied:
- Square
- Circle
- Column
- Line
- Diagonal
<p align="center">
  <video src="https://github.com/user-attachments/assets/a01049c1-713f-4f37-8876-607637cf79ec" width="500px"></video>
</p>

# Still to-do
The project is at an early stage. Features coming next will be:
- Attack orders
- Player unit impersonation
- Player attacks
- Interface refactoring (to separate the logic between selection/building/Units)
- Unit death
- Player resources
- UML Documentation

# Inspiration sources
RTS and combat games have interested me since my career as a player.
You might recognise some similarities with:
- Star Wars Empire At Wars (resources and building)
- Maelstrom: The Battle for Earth Begins (impersonate infantry characters)
- Homeworld (Unit orders)
- Titanfall Assault (orders accessibility)
