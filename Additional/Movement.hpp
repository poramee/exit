#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Map.hpp"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

namespace Movement{
    class Player{
    public:
        Player(Sprite& Run,
               Sprite& Still,
               Sprite& Jump,
               Sprite& Background,
               Vector2f& SpritePosition,
               Clock& Clk,
               const float& defaultDelta,
               float& WalkSpeed,
               IntRect& Pos,
               float& delta,
               BaseMap::Map& map,
               RenderWindow& window
               ) : Run(Run), Still(Still),Jump(Jump),Background(Background),SpritePosition(SpritePosition),Clk(Clk),defaultDelta(defaultDelta),WalkSpeed(WalkSpeed),Pos(Pos),delta(delta),map(map),velocity({0,0}),window(window){
            BoostSB.loadFromFile("Resources/Sounds/Boost.wav");
            BoostSFX.setBuffer(BoostSB);
            BoostSFX.setLoop(true);
            BoostSFX.setVolume(80);
            
            DeathSB.loadFromFile("Resources/Sounds/Death.wav");
            DeathSFX.setBuffer(DeathSB);
            DeathSFX.setVolume(50);
            
            JumpSB.loadFromFile("Resources/Sounds/Jump.wav");
            JumpSFX.setBuffer(JumpSB);
            JumpSFX.setVolume(10);
            JumpSFX.setRelativeToListener(true);
            JumpSFX.setPosition(0,0,0);
            
            KeySB.loadFromFile("Resources/Sounds/Key.wav");
            KeySFX.setBuffer(KeySB);
            KeySFX.setVolume(50);
            KeySFX.setRelativeToListener(true);
            KeySFX.setPosition(0,0,0);
            
            RunGlow.loadFromFile("Resources/sprite_run_glow.png");
            RunGlow.setSmooth(true);
            
            StillGlow.loadFromFile("Resources/sprite_still_glow.png");
            StillGlow.setSmooth(true);
            
            JumpGlow.loadFromFile("Resources/sprite_jump_glow.png");
            JumpGlow.setSmooth(true);
            
            SpecialSB.loadFromFile("Resources/Sounds/Special.wav");
            SpecialSFX.setBuffer(SpecialSB);
            SpecialSFX.setVolume(40);
            
        };
        ~Player(){};
        Sprite draw();
        void SpriteTailReset(){
            lastSpritePosition = empty;
        }
    private:
        void update();
        void checkCollision();
    public:
        Clock WalkClk;
        Clock deadAnimationClk;
        bool dead = false;
        bool levelComplete = false;
        unsigned int death = 0;
        bool flying = false;
        pair<float, float> velocity;
        string onLevel = "NA";
        Sprite& Still;
        Vector2f& SpritePosition;
        bool pause = false;
        list<Sprite> lastSpritePosition,empty;
        int spriteCount = 0;
        //Level DeadlyFriendly
        int keyDeathCount = 0;
    private:
        Texture RunGlow;
        Texture StillGlow;
        Texture JumpGlow;
        Sprite& Run;
        Sprite& Jump;
        Sprite& Background;
        Clock& Clk;
        Clock flyClk;
        const float& defaultDelta;
        float& WalkSpeed;
        IntRect& Pos;
        float& delta;
        BaseMap::Map& map;
        RenderWindow& window;
        SoundBuffer BoostSB;
        Sound BoostSFX;
        SoundBuffer DeathSB;
        Sound DeathSFX;
        SoundBuffer JumpSB;
        Sound JumpSFX;
        SoundBuffer KeySB;
        Sound KeySFX;
        SoundBuffer SpecialSB;
        Sound SpecialSFX;
        bool lastBoostState = false;
    };
    
    class ViewSet{
    private:
        Sprite& bgnd;
        Vector2f& SpritePosition;
        RenderWindow& window;
        pair<float,float>& playerSpeed;
    public:
        View& view;
    public:
        ViewSet(
                Sprite& bgnd,
                Vector2f& SpritePosition,
                pair<float,float>& playerSpeed,
                RenderWindow& window,
                sf::View& view
                ):bgnd(bgnd),SpritePosition(SpritePosition),window(window),view(view),playerSpeed(playerSpeed){};
        ~ViewSet(){};
        Vector2f viewPosition();
        void setView();
    };
}
