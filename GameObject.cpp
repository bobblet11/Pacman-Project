#include "GameObject.h"

GameObject::GameObject(std::string sprite_sheet, int posX,  int posY,int colour_f, int colour_b)
:x(posX), y(posY)
{
    std::cout << "GO constructor invoked" << std::endl;
    readSpriteSheet(sprite_sheet);
    current_state_index = 0;
    CHARACTER_BACK_COLOUR = colour_b;
    CHARACTER_FORE_COLOUR = colour_f;
    
    init_pair(1, CHARACTER_FORE_COLOUR, CHARACTER_BACK_COLOUR);
    std::cout << "Current state index :"<< current_state_index << std::endl;
    std::cout << animation_sprites.at(current_state_index) << std::endl;
}

GameObject :: GameObject(const GameObject &t)
:x(t.x), y(t.y)
{
    std::cout << "GO COPY constructor invoked" << std::endl;
    animation_sprites =  t.animation_sprites;
    current_state_index = 0;
    CHARACTER_BACK_COLOUR = t.CHARACTER_BACK_COLOUR;
    CHARACTER_FORE_COLOUR = t.CHARACTER_FORE_COLOUR;
    init_pair(1, CHARACTER_FORE_COLOUR, CHARACTER_BACK_COLOUR);
    std::cout << "Current state index :"<< current_state_index << std::endl;
    std::cout << animation_sprites.at(current_state_index) << std::endl;
}


GameObject::~GameObject()
{
    std::cout << "GO deconstructor invoked" << std::endl;
    std::cout << "Current state index :"<< current_state_index << std::endl;
    std::cout << animation_sprites.at(current_state_index) << std::endl;
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
    mvprintw(y,x*2, "%s", animation_sprites.at(current_state_index).c_str());
}
void GameObject :: updateAnimationState()
{
    // std::cout<<"GO UPDATE ANIM" << std::endl;
}
void GameObject :: handleCharacterMove()
{
    //  std::cout<<"GO  HANDLE CHARACTER MOVE" << std::endl;
}