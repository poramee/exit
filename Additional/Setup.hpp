#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

namespace Parameter{
    const float sprite_scale = 0.2;
    const int sprite_size = 500;
    const float view_zoom = 0.9;
    const sf::Vector2u view_size = Vector2u(1024*view_zoom,768*view_zoom);
}

namespace Setup{
    void initSprite(Sprite& sprite,const float posX, const float posY);
    void initTexture(Texture& texture,const string str);
}
