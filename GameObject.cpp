#include "GameObject.h"

GameObject::GameObject(std::string sprite_sheet, int posX,  int posY, int obj_type)
:x(posX), y(posY)
{   
    object_type = obj_type;
    readSpriteSheet(sprite_sheet);
    current_state_index = 0;
}

GameObject :: GameObject(const GameObject &t)
:x(t.x), y(t.y)
{
    animation_sprites =  t.animation_sprites;
    current_state_index = 0;
}


GameObject::~GameObject()
{
}

std::vector<std::string> GameObject :: getAnimationSprites()
{
    return animation_sprites;
}

int GameObject :: getX()
{
    return x;
}
int GameObject :: getY()
{
    return y;
}
int GameObject :: getWidth()
{
    return width;
}
int GameObject :: getHeight()
{
    return height;
}
std::string& GameObject :: getCurrentSprite()
{
    return animation_sprites.at(current_state_index);
}

int GameObject :: getCurrentStateIndex()
{
    return current_state_index;
}

void GameObject :: readSpriteSheet(std::string sprite_sheet)
{//will read and replace the sprite list of gameobject
    std::string line;
    std::fstream file;
    file.open(sprite_sheet);
    if (!file)
    {
        std::cout << "[ERROR] Failed to open sprite sheet." << std::endl;
        exit(1);
    }
    //first line is num_of_states height width
    while(getline(file,line))
    {
        std::cout << "line: " << line << std::endl;
        animation_sprites.push_back(line);
        std::cout << "Current vector :" << std::endl;
        for (int i=0; i < animation_sprites.size(); i++)
        {
                std::cout << animation_sprites.at(i) << std::endl;
        }
    }
    file.close();
}

//add x,y checks in screen or main
void GameObject::setState(const int state)
{
    current_state_index = state;
}
void GameObject::setX(const int x)
{
    // std::cout << "setting X from " << this->x <<" to " << x << std::endl;
    this->x = x;
}
void GameObject::setY(const int y)
{
    // std::cout << "setting Y from " << this->y <<" to " << y << std::endl;
    this->y = y;
}

void GameObject :: printCharacterAtPosition()
{
	attron(COLOR_PAIR(object_type));
    mvprintw(y,x*2, "%s", getCurrentSprite().c_str());
    attroff(COLOR_PAIR(object_type));
}
void GameObject :: updateAnimationState()
{
    // std::cout<<"GO UPDATE ANIM" << std::endl;
}
void GameObject :: handleCharacterMove(std::vector<GameObject*> & handle,int& character_index)
{
    //  std::cout<<"GO  HANDLE CHARACTER MOVE" << std::endl;
}

void GameObject ::  handleState(GameObject* charac_obj_ptr)
{
    
}

void GameObject :: moveToNewPos(int x,int y)
{
    if (x == 29 && y == 15 )
    {
        this-> x = 1;
        this -> y = 15;
    }
    else if (x == 0 && y == 15)
    {
        this-> x = 28;
        this -> y = 15;
    }
    else
    {
        this->x = x;
        this->y = y;
    }
}