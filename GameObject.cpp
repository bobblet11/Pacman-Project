#include "GameObject.h"
#include "functions.h"


//CONSTRUCTORS
// sprite_sheet is a file name for the txt where all the sprites are stored
// posX, posY are the starting coordinates
// obj type is the object that this GameObject represents
GameObject::GameObject(std::string sprite_sheet, int posX,  int posY, int obj_type) //sprite_sheet is a file name for the txt where all the sprites are stored
:x(posX), y(posY)
{   
    object_type = obj_type;
    readSpriteSheet(sprite_sheet);
    current_state_index = 0;
    colour = obj_type;
}


//COPY CONSTRUCTORS
GameObject :: GameObject(const GameObject &t)
:x(t.x), y(t.y)
{
    animation_sprites =  t.animation_sprites;
    current_state_index = 0;
}


//DECONSTRUCTORS
GameObject::~GameObject()
{
}


//GETTERS
std::vector<std::string> GameObject :: getAnimationSprites()
{
    return animation_sprites; //returns the vector containing all animation sprites.
}
int GameObject :: getX()
{
    return x; //returns x coordinate of GameObject
}
int GameObject :: getY()
{
    return y; //returns y coordinate of GameObject
}
std::string& GameObject :: getCurrentSprite()
{
    return animation_sprites.at(current_state_index); //returns the current sprite displayed
}
int GameObject :: getCurrentStateIndex()
{
    return current_state_index; //returns the current index in the vector of animation states.
}

//SETTERS
void GameObject::setState(const int state)
{
    current_state_index = state;
}
void GameObject::setX(const int x)
{
    this->x = x;
}
void GameObject::setY(const int y)
{
    this->y = y;
}

//INTERNAL FUNCTIONS
// sprite sheet is the filename for the txt where all the sprites states are stored
void GameObject :: readSpriteSheet(std::string sprite_sheet)
{
    //opens the txt where sprites are stored and loads them into a vector
    std::string line;
    std::fstream file;
    file.open(sprite_sheet);
    if (!file)
    {
        std::cout << "[ERROR] Failed to open sprite sheet." << std::endl;
        exit(1);
    }
    while(getline(file,line)) //since each sprite is only 1 character large, ie one line, each line in a txt is pushed into the vector
    {
        animation_sprites.push_back(line);
    }
    file.close();
}

// x and y are the positions that the GameObject is trying to move to
void GameObject :: moveToNewPos(int x,int y)
{
    if (x == 29 && y == 15 ) //checks if the GameObject is moving into the rightside tunnel
    {
        //teleports GameObject to other end of then tunnel
        this-> x = 1;
        this -> y = 15;
    }
    else if (x == 0 && y == 15) //checks if the GameObject is moving into the leftside tunnel
    {
        //teleports GameObject to other end of then tunnel
        this-> x = 28;
        this -> y = 15;
    }
    else
    {
        this->x = x;
        this->y = y;
    }
}

//EXTERNAL FUNCTIONS
void GameObject :: printCharacterAtPosition()
{
	attron(COLOR_PAIR(colour)); //changes the prinitng colour to the colour of the GameObject
    //prints at the current position + the x and y offset of positioning the game in middle of screen
    mvprintw(y+(getmax_x()/2-16)+1, x*2+(getmax_y()/2-30), "%s", getCurrentSprite().c_str());
    attroff(COLOR_PAIR(colour)); //changes the prinitng colour back to default
}


//VIRTUALS (FOR CHILD CLASSES)
void GameObject :: updateAnimationState()
{
}
void GameObject :: handleCharacterMove(std::vector<GameObject*> & handle,int & character_index,bool & freightened, int & freightened_timer)
{
}
void GameObject ::  handleState(GameObject* charac_obj_ptr, int & gameState, bool&freightened, int & freightened_timer)
{
}
void GameObject :: setPoints(int x)
{

}
int GameObject :: getPoints()
{
    return  0; //returns 0 if the Gameobject is not one that uses points systems.
}