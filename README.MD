README



![Model](https://raw.githubusercontent.com/bobblet11/Pacman-Project/master/pacmangit5.png)

![Model](https://raw.githubusercontent.com/bobblet11/Pacman-Project/master/pacmangit6.png)




PROJECT DESCRIPTION:
  A pacman game that utilises ncurses, Unicode and termios. 
  1. Main menu

![Model](https://raw.githubusercontent.com/bobblet11/Pacman-Project/master/pacmangit2.png)

      - use arrow keys to navigate the main menu.
      - view your previous high scores -> tied to the name you input
      - quit the game
      - play the game

  2. Loading sequence

![Model](https://raw.githubusercontent.com/bobblet11/Pacman-Project/master/pacmangit3.png)

      - Enter a name for your scores to be recorded under
      - Loading animation

  3. Game
       - use the WASD or arrow keys to control the PACMAN character
       - eat all the pills to win
       - avoid all ghosts
       - eat super pills to put ghosts in a frightened state -> Ghosts are now edible and provide extra points
       - try to beat your high score by eating more ghosts and completing the level quickly.

![Model](https://raw.githubusercontent.com/bobblet11/Pacman-Project/master/pacmangit4.png)


  4. How to play
      0) SINGLE PLAYER GAME
         ASSUME PLAYER WILL NOT TYPE CONTROL C MIDGAME -> This will exit the game as it is a command to exit runtime
         MUST SET THE TERMINAL TO FULL SCREEN FIRST!
      1) start the game with ./pacman after compiling and linking using "make compile"

      2) use arrow keys to navigate the main menu, and press enter to click the selected button
            - Press enter on "Play Game" to start the game
            - Press enter on "HighScores" to see all high scores of your attempts
            - Press enter on Quit to close the game and clear the screen

      3) Once you press "Play Game", enter a name to save your high score. If you use a name you already used before, 
         the high score will be overridden under    that name -> given that you beat the previous score under that name.
         Press enter once you typed your name to begin playing

      4) Playing the Game:
         - Use arrow keys or WASD to move the playable character. The character will move in the direction you set it forever until you change direction.
         - Eat all of the white pills on the map to win the game
         - Ghosts will chase you and try to touch you
         - If you touch a ghost, you lose the game
         - Ghosts AI will increase in difficulty as your points increase.
         - Eating white pills causes Ghosts to enter a frightened state for 10 seconds -> ghosts turn white -> you can eat the ghosts and gain extra points.
         - The faster you finish the game, the larger the score bonus you receive at the end.
         - You can enter the tunnel located at the left and right sides of the map to quickly cross over to the other side.

      5) Winning/losing:
          - when you win or lose, your score is saved.
          - winning happens when you eat all the pills
           - enter a winning page
          - losing happens when a ghost touches you
           - enter a losing page
          - conclude winning/losing page
          - Once you conclude the losing/winning page, you will be redirected to the main menu to view your high scores, play again, or quit.


IMPLEMENTATION NOTES:

Generation of random game sets or events:
    All ghost AI is randomised using probabilities. Each coloured ghost has different playstyles and probability parameters,
    Red Ghost will always chase players with high accuracy, purple will also chase with lower probabilities, 
    Cyan and Pink will chase but move very ineffectively -> scatter more often and make random movement decisions.
    
    Scores are also somewhat different every playthrough. Player performance and randomised Ghost behaviour largely dictate the high score a player can achieve.
    different players have different playstyles and video game skills, so their scores will vary largely between each player.


Data structures for storing game status:
    Use many different types of data structures including vectors, dynamically allocated arrays, strings, Unicode strings, ints
    Pointers are used extensively as well, for example, we use a vector of pointers to keep track of and access all dynamically allocated class instances.


Dynamic memory management

    Use a vector of pointers pointing to our dynamically Allocated GameObject class instances.
    Use dynamic arrays to store all sprite data and animation states.
    Use pointers to pass objects to each other.


File input/output (e.g., for loading/saving game status)
    Used multiple txt files for loading GameObject sprites, loading the playable map, and accessing/saving high scores.


Program codes in multiple files
    have used multiple files for each class, declared all functions and data structures in header files, and defined them in source files.
    used Make file to combine all of these files and link ncurses.


Proper indentation and naming styles
     all variables follow the same naming style, all lowercase and _ between every word
     All classes and Functions follow the same naming style, Capitalised first letter of each word, and no spaces between words
     all code blocks are indented


In-code documentation
    all code contains comments describing what the parameters are, what the output is and what the function does.


QUICKSTART:

![Model](https://raw.githubusercontent.com/bobblet11/Pacman-Project/master/pacmangit1.png)

  download the GitHub repo
  enter the directory of the repo
  open terminal in repo
  build the project by typing "make compile" or "make"
  please enter fullscreen BEFORE running the game.
  run the game by typing "./pacman"
  to quit midgame, press ctrl + C and clear the terminal with "clear"
  Otherwise, the player must finish the game -> WIN or LOSE -> then quit at the main menu.


DEPENDENCIES
  require ncurses to render the game
  ncurses is used to draw all characters at (y,x) coordinates only.


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



 all function notes and documentation can be found in the file comments.
