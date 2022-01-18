#  CS 126 Final Project README File
This project is a basketball shooting simulator. The user has 1 
minute to shoot as many shots as they can. The user can move from a 
three pointer to a two pointer and back to a three pointer. The 
user can also change the angle of the shot, as well as the power. 
After the one minute is over, the user has the option to restart 
the game. Some elements of the GUI of the game include a timer box, the user's score, a rectangle which changes height for the power of the ball's release, a basketball, and a hoop. Here are the controls for the game: 
	
* 's' - Start the game
* 'f' - Move from a three pointer to a two pointer
* 'b' - Move from a two pointer to a three pointer
* Number Keys - Increases the angle as the number increases; '1' represents 10 degrees, while '9' represents 90 degrees
* Space Bar - Shooting the ball; the power is determined by how long the space bar is held for
* 'r' - Restart the game

## How to Build and Run
To make the game function, you have to download cmake and cinder. Once you have downloaded these, you must create a Cinder directory which stores Cinder, along with a my_projects directory. In this my_projects directory, you will store this project. You will also need to make CMAKELISTS.txt file for the project, which allows the code to compile. Once you have finished these steps, you can successfully run the game.
