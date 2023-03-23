#include "GameObject.h"

GameObject::GameObject(std::string sprite_sheet, int posX,  int posY)
:x(posX), y(posY)
{
    readSpriteSheet(sprite_sheet);
    current_state_index = 0;
}


GameObject::~GameObject()
{
    delete[] animation_sprites;
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
    return animation_sprites[current_state_index];
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
    file>>num_of_sprite_states;
    file>>height;
    file>>width;
    
    animation_sprites = new std::string[num_of_sprite_states];

    int count = 0;

    while(getline(file,line))
    {
        if(line[0] == '!')
        {
            //end of a sprite state
            count++;
        }
        else
        {
            animation_sprites[count]=line;
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
    this->x = x;
}
void GameObject::setY(const int y)
{
    this->y = y;
}

void GameObject :: printCharacterAtPosition()
{

}
