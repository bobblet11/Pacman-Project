Pacman clone

A Pacman clone written in C++ that plays inside the terminal using ncurses and termios libraries.

Table of Contents:
1) how to install and run the project
   - dependencies
2) showcasing
3) implementation notes
4) documentation

--------------------------------------------

QUICKSTART:

![Model](https://raw.githubusercontent.com/bobblet11/Pacman-Project/master/pacmangit1.png)

- Download the GitHub repo.
- Open the terminal in the downloaded folder.
- Build the project by typing "make compile" or "make" into the terminal.
- Enter fullscreen before running.
- Run the game by typing "./pacman".

DEPENDENCIES:
- require ncurses to render the game.

--------------------------------------------

SHOWCASE:

![Model](https://raw.githubusercontent.com/bobblet11/Pacman-Project/master/pacmangit2.png)

- Use arrow keys to navigate the main menu.
- View your previous high scores attached to the username you input.
- Quit the game.
- Play the game.

![Model](https://raw.githubusercontent.com/bobblet11/Pacman-Project/master/pacmangit3.png)

- view high scores through the main menu and at the end of playthroughs.

![Model](https://raw.githubusercontent.com/bobblet11/Pacman-Project/master/pacmangit4.png)

- Enter a username which will be used to store your high score, previous scores under the same name will be overwritten if beaten.

![Model](https://raw.githubusercontent.com/bobblet11/Pacman-Project/master/pacmangit6.png)

- Game starts, avoid ghosts while eating all pills on the map. Super pills will force ghosts into a frightened state and can be eaten by the player for 500 pts.
- The player wins if they eat all the pills on the map.
- The player loses if they collide with a ghost.

---------------------------------------------------------------------------------------------------------------------------------------------------------------

IMPLEMENTATION NOTES:

Generation of random game sets or events:
- All ghost AI is randomised using probabilities. Each coloured ghost has different playstyles and probability parameters.
- Red Ghost will always chase players with high accuracy, and purple will also chase with lower probabilities.
- Cyan and Pink will chase but move very ineffectively. Will scatter more often and make random movement decisions.  

Dynamic memory management
- Use a vector of pointers pointing to our dynamically Allocated GameObject class instances.
- Use dynamic arrays to store all sprite data and animation states.
- Use pointers to pass objects to each other.

File input/output (e.g., for loading/saving game status)
- Used multiple txt files for loading GameObject sprites, loading the playable map, and accessing/saving high scores.

---------------------------------------------------------------------------------------------------------------------------------------------------------------

DOCUMENTATION:
- Screen.cpp + Screen.h                                                     
//handles the rendering of the screen when playing the game

- PlayableMap.cpp PlayableMap.h PlayableMap.txt                             
//handles the loading and collision of the playable map, ie the walls of the map. Will read off the PlayableMap.txt to load the map into the terminal

- Pill.cpp Pillh Pills.txt                                                  
//Child of GameObject contains all specialised classes for Pill objects that the player eats. Will read off the Pills.txt to load in all sprites for Pills.

- NameBox.txt functions.cpp functions.h middle.cpp middle.h menu.cpp menu.h item.cpp item.h
//contains all functions, definitions and classes required for the main menu

- main.cpp                                                                  
//central process that controls the game state, loads object into dynamic memory, deallocates dynamic memory, and is the overarching game loop.

- Highscores.cpp Highscores.h highscores.txt                                
//handles all fileIO necessary for loading and writing HIGHSCORES

- Ghosts.cpp Ghosts.h GhostSprites.txt                                      
//Child of GameObject contains all specialised classes, functions, and definitions for Ghosts objects. Will read off the GhostSprites.txt to load in all sprites for Ghosts

- GameObject.cpp Gameobject.h                                               
//overarching template for all Ghosts, Pills, and Characters (the player). Contains basic functions required for interactive game objects

- Character.cpp Character.h CharacterSprites.txt                            
//Child of GameObject contains all specialised functions for the playable character. Will read off the CharacterSprites.txt to load in all sprites for the PACMAN character.



                          <CLASSES>
                       
        Screen    Menu    Item    PlayableMap      GameObject
                                                       |
                                                 :-----:----------:
                                                 v     v          v    
                                             Ghost    Pill    Character


