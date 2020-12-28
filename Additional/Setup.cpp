#include "Setup.hpp"

using namespace std;
using namespace sf;


//Setup Value
const IntRect Pos = IntRect(0,0,Parameter::sprite_size,Parameter::sprite_size);

void Setup::initSprite(Sprite& sprite,const float posX, const float posY){
    sprite.setTextureRect(Pos);
    sprite.setScale(Parameter::sprite_scale,Parameter::sprite_scale);
    sprite.setOrigin(Parameter::sprite_size / 2,Parameter::sprite_size / 2);
    sprite.setPosition(posX,posY);
}

void Setup::initTexture(Texture& texture,const string str){
    texture.loadFromFile(str);
}
