#include "Character.h"

//CONSTRUCTOR
//sprite sheet is the filename for txt with sprites
//screen width,height is width,height of the box where everything is rendered.
//map is the Playable map object
//posX,posY is the starting coordinate of the Character
//obj_type is the type of Gameobject the character is -> should be set to character.
Character::Character(std::string sprite_sheet, int screen_width, int screen_height, PlayableMap& map, int posX, int posY, int obj_type)
:GameObject(sprite_sheet, posX, posY, obj_type), screen_height(screen_height), screen_width(screen_width), map(map)
{
    //checks if the starting coordinates are valid
    if(!map.IsMoveable(posX-1,posY-1, object_type))
    {
        std::cout << "Invalid haracter starting coordinates" << std::endl;
        exit(-1);
    }
    //sets the animation state to default -> circle
    setState(DEFAULT);
}

//DECONSTRUCTOR
Character::~Character()
{
}

//EXTERNAL MEMBER FUNCTIONS
void Character::handleCharacterMove(std::vector<GameObject*> & handle , int & character_index, bool & freightened, int & freightened_timer)
{
    if (selectGetch()) //CHECK IF THERE IS A VALID KEY IN QUEUE
    {
        int input = getch(); //retreive the valid key in the queue
        //check if the input is one of the control buttons ie WASD or up right down left
        bool isvalid = ((char)input ==  'w'|| input == KEY_UP)||((char)input == 's' || input == KEY_DOWN)||((char)input == 'd'|| input == KEY_RIGHT)||((char)input == 'a'|| input == KEY_LEFT);
        
        if (input != last_input && isvalid) //CHECK IF THE DIRECTION OF CHARACTER HAS CHANGED
        {
            //if direction has changed, reset the move_count and set last input to current direction
            last_input = input;
            move_count=0;
        }
    }
    //moves the character and handles any processes associated with moving.
    moveCharacter(handle,character_index, freightened, freightened_timer);

    //increments movecount then limits it to a MOVE SPEED value. 
    //The Gameobject will only move when movecount is 0, so it controls speed.
    move_count++;
    move_count%=MOVE_SPEED;
}

void Character :: updateAnimationState()
{
    if (anim_counter < ANIMATION_DURATION) //if the timing is not correct, keep to default state
    {
        setState(DEFAULT); //default state
    }
    else //otherwise, if the counter passes the timing, switch to the animation state of its direction
    {
        setState(current_direction);
    }
    //increments counter and limits to twice the duration, because there are 2 states switching back and forth.
    anim_counter++;
    anim_counter%=(ANIMATION_DURATION*2);

}

//INTERNAL MEMBER FUNCTIONS

//will ignore non inputs ie pressing nothing and only accept inputs that are pressed in keyboard
bool Character :: selectGetch()
{
    int input = getch(); //gets the current input detected

    if (input != ERR) //checks something has been pressed
    {
        ungetch(input); //PLACES THE INPUT BACK INTO THE buffer
        return true;
    }
    else //otherwise if nothing has been pressed, return false.
    {
        return false;
    }
//returns true when a character has been typed
//returns false when non keyboard characters are passing through getch.
}

//will check the inputs pressed, update the position, and check for any encountered pills
//handle is the vector containing all active gameobjects in the game.
//character index is the int that represents where the Character pointer is stored in the vector
//freightened is the bool that determines whether or not the ghosts will enter a freightened state.
//freightened timer is the time ghosts have left until the return to normal state.
void Character::moveCharacter(std::vector<GameObject*> & handle, int & character_index, bool & freightened,int & freightened_timer) //actually moves the character 
{
    //calculate which direction the player is moving towards
    int moveY = ((char)last_input == 'w' || last_input == KEY_UP) ? -1 : ((char)last_input == 's' || last_input == KEY_DOWN) ? 1 : 0;
    int moveX = ((char)last_input == 'd' || last_input == KEY_RIGHT) ? 1 : ((char)last_input == 'a'|| last_input == KEY_LEFT) ? -1 : 0;

    //store the new player position in the calculated direction
    int new_pos_X = moveX + x; 
    int new_pos_Y = moveY + y; 

    //update the direction variable to the calculated direction
    current_direction = (moveX==1) ? RIGHT : (moveX==-1) ? LEFT : (moveY==-1) ? UP : (moveY==1) ? DOWN : current_direction;

    //if new player position is moveable ie not a wall, then move
    if (map.IsMoveable(new_pos_X-1,new_pos_Y-1, object_type))
    {
        //if the player is timed to move, ie when move count is 0, then move to the new position
        if (move_count == 0)
        {
            moveToNewPos(new_pos_X,new_pos_Y);
        }

        //BINARY SEARCH FOR PILL WITH SAME COORDINATE AS PLAYER
        int length = handle.size()-1,pivot=0,start=0;

        while (true)
        {
            //pivot is the middle left position in the handle vector
            pivot = ((length-start)+1/2);

            for (int i = start; i < pivot;i++) //for loop to search if the pill with same x,y exists in the left side of pivot
            {
                //if a player and pill have collided, ie same coordinate
                if (handle.at(i)->object_type == 3 && handle.at(i)->getX() == x  && handle.at(i)->getY() == y)
                {
                    //SET PLAYER POINTS TO CURRENT VALUE + PILL VALUE
                    setPoints(getPoints() + handle.at(i)->getPoints());

                    //IF THE PILL WAS A SUPER PILL, SET GHOST STATE TO FREIGHTENED
                    if (handle.at(i)->getPoints() == 100)
                    {
                        //add 6 seconds to the freightened timer so that ghosts are freightened state for 6 more seconds
                        freightened_timer += 6*60*4;
                        freightened = true;
                    }

                    //DEALLOCATE THE PILL OBJECT MEMORY
                    delete handle.at(i);
                    //REMOVE POINTER
                    handle.erase(handle.begin()+i);
                    character_index-=1;
                    break;
                }
            }
            length -= pivot;
            start = pivot;
            //if a pill isnt found, break and return.
            if (length <=0)
            {
                break;
            }
        }
    }
}

//returns the points aqquired by the player
int Character:: getPoints()
{
    return points;
}
//sets the points of the player to the value new_points
void Character :: setPoints(int new_points)
{
    this->points = new_points;
}


