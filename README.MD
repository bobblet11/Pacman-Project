README

GROUP MEMBERS:
Benjamin Jun-jie Glover 3035962764
Wong Shom
Ahmed Shaan Nabid

GROUP NUMBER:
group 106

PROJECT DESCRIPTION:
  Pacman type game that utilises ncurses, unicode and termios. 
  1. Main menu
    view your previous highscores -> tied to the name you input
    quit the game
    play the game

  2. Loading sequence
    Enter a name for you scores to be recorded under
    Loading animation

  3. Game
    use the WASD to control the PACMAN character
    eat all the pills to win
    avoid all ghosts
    eat super pills to put ghosts in freightened state -> ghosts are now edible and provide extra points
    try to beat your highscore by eating more ghosts and completing the level quickly.

  4. How to play
      1) start the game with ./pacman after compiling and linking using "make compile"

      2) use arrow keys to navigate the main menu, press enter to click selected button
          2.1) Press enter on "Play Game" to start game
          2.2) Press enter on "HighScores" to see all highscores of your attempts
          2.3) Press enter on Quit to close the game and clear screen

      3) Once you press "Play Game", enter in a name to save your highscore under. If you use a name you already used before, the highscore will be overridden under that name -> given that you beat the previous score under that name.
         Press enter once you typed your name to begin playing

      4) Playing the Game:
           - Use arrow keys or WASD to move the playable character. The character will move in the direction you set it forever until you change direction.
           - Eat all of the white pills on the map to win the game
           - Ghosts will chase you and try to touch you
           - If you touch a ghost, you lose the game
           - Ghosts AI will increase in difficulty as your points increase.
           - Eating white pills causes Ghosts to enter freightened state for 10 seconds -> ghosts turn white -> you can eat the ghosts and gain extra points.
           - The faster you finish the game, the larger the score bonus you receive at the end.
           - You can enter the tunnel located at the left and right sides of the map to quickly cross over to the other side.

      5) Winning/losing:
          - when you win or lose, your score is saved.
          - winning happens when you eat all pills
              - enter a winning page
          - losing happens when a ghost touches you
              - enter a losing page
          - conclude winning/losing page
          - Once you conclude the losing/winning page, you will be redirected to the main menu to view your highscores, play again, or quit.


IMPLEMENTATION NOTES:

list of features:
  coloured rendering
  randomised ghost movement
  used probability to change the playstyles of each ghost
  realtime input output
  save score under player inputted name
  used dynamic memory extensively
  utilised multiple STL containers
  txt input output
  interactive main menu
  pointers to keep track of all dynamic objects
  inheritance and OOP employed -> overloading, overriding

Generation of random game sets or events:
    All ghost AI is randomised using probabilities. Each coloured ghosts has different playstyles and probability parameters,
    Red Ghost will always chase player with high accuracy, purple will also chase with lower probalities, 
    Cyan and Pink will chase but move very ineffectively -> scatters more often and makes random movement decisions.
    
    Scores are also somewhat different every playthrough. Player performance and randomised Ghost behaviour largely dictates the highscore a player can achieve.
    different players have different playstyles and video game skills, so their scores will vary largely between each player.

Data structures for storing game status:
    Use many different types of data structurres including vectors, dyanmically allocated arrays, strings, unicode strings, ints
    Pointers are used extensively aswell, for example we use a vector of pointers to keep track and access all dynamically allocated class instances.

Dynamic memory management
    Use a vector of pointers pointing to our dynamically Allocated GameObject class instances.
    Use dynamic arrays to store all sprite data and animation states.
    Use pointers to pass objects to eachother.
  
File input/output (e.g., for loading/saving game status)
    Used multiple txt files for loading GameObject sprites, loading the playable map, and accessing/saving highscores.
  
Program codes in multiple files
    have used multiple files for each class, declared all functions and data structures in header files, defined them in source files.
    used Make file to combine all of these files and link ncurses.
  
Proper indentation and naming styles
     all variables follow the same naming style, all lowercase and _ between every word
     all Classes and Functions follow same naming style, Capitalised first letter of each word, no spaces between words
     all code blocks are indented
   
In-code documentation
    all code contains comments describing what the paramters are, what the output are and what the function does.


QUICKSTART:
  download the github repo
  enter the directory of the repo
  open terminal in repo
  build the project by typing "make compile" or just "make"
  please enter fullscreen BEFORE running the game.
  run the game by typing "./pacman"
  to quit midgame, press ctrl + C and clear terminal with "clear"
  Otherwise, the player must finish the game -> WIN or LOSE -> then quit at the main menu.

DEPENDENCIES
  require ncurses to render the game
  ncurses is used to draw all charcters at (y,x) coordinates only.
  ncurses on server is used.



DOCUMENTATION:
files:

- Screen.cpp + Screen.h                                                     //handles the rendering of the screen when playing the game
- PlayableMap.cpp PlayableMap.h PlayableMap.txt                             //handles the loading and collision of the playable map, ie the walls of the map. Will read off the PlayableMap.txt to load the map into the terminal
- Pill.cpp Pillh Pills.txt                                                  //Child of GameObject, contains all specialised classes for Pill objects that player eats. Will read off the Pills.txt to load in all sprites for Pills.
- NameBox.txt functions.cpp functions.h middle.cpp middle.h menu.cpp menu.h //contains all functions, defintions and classes required for the main menu
- main.cpp                                                                  //central process that controls the game state, loads object into dynamic memory, deallocates dynamic memory, and is the overaching game loop.
- Highscores.cpp Highscores.h highscores.txt                                //handles all fileIO neccesary for loading and writing HIGHSCORES
- Ghosts.cpp Ghosts.h GhostSprites.txt                                      //Child of GameObject, conatins all specialisd classes, functions, and defintions for Ghosts objects. Will read off the GhostSprites.txt to load in all sprites for Ghosts
- GameObject.cpp Gameobject.h                                               //overaching template for all Ghosts, Pills, and Character(the player). Contains basic functions required for interactive gamebjects
- Character.cpp Character.h CharacterSprites.txt                            //Child of GameObject, contains all specialised functions for the playable character. Will read off the CharacterSprites.txt to load in all sprites for the PACMAN character.



class hierarchy: upper = parent, lower = child

                    <CLASSES>
                    
Screen    Menu    Item    PlayableMap      GameObject
                                               |
                                         :-----:----------:
                                         v     v          v    
                                     Ghost    Pill    Character
 
 
 all function notes and documentation can be found in the file comments.
