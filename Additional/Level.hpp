#include "UI.hpp"

namespace Level {
    class Level{
    private:
        RenderWindow& window;
        Movement::Player& player;
        Sprite& background;
        BaseMap::Map& map;
        Movement::ViewSet& vv;
        Clock& GlobalClock;
        UI ui = UI(window,vv,player,GlobalClock,GlobalDisplayTime,map);
    public:
        bool forceEnd = false;
        Time GlobalDisplayTime;
    public:
        Level(RenderWindow& window,Movement::Player& player, Sprite& background,BaseMap::Map& map,Movement::ViewSet& vv, Clock& GlobalClock) : window(window),player(player),background(background),map(map),vv(vv),GlobalClock(GlobalClock){
        };
        ~Level(){};
        void GetTheKey();
        void DeathIsGood();
        void UpDownLeftRight();
        void InverseControl();
        void AutomaticDoor();
        void RightClick();
        void LightsOut();
        void TakeABreak();
        void MoreSpike();
        void PieInTheSky();
        void PressAnyKeyToContinue();
        void AdjustableDoor();
        void TextMode();
        void SelfProtected();
        void DeadlyFriendly();
        void AllClear();
    private:
        void parameter_reset(){
            this -> player.SpritePosition = Vector2f(100,900);
            this -> player.levelComplete = false;
            this -> player.keyDeathCount = 0;
            this -> player.SpriteTailReset();
            this -> map.keyFound = false;
            this -> map.SpecialItemReset();
            this -> map.doorOpen = false;
            this -> map.doorMask = IntRect(0,0,30,150);
            this -> map.keyRandom = false;
            this -> map.moreSpike(false);
            this -> map.disableDoorAnimation = false;
            this -> player.pause = false;
            this -> ui.reset();
        };
        void SpecialTimeSubtract(){
            if(map.timeSubtract > 0){
                ui.GreenTimeHighlighter.restart();
                GlobalDisplayTime -= seconds(map.timeSubtract);
                if(GlobalDisplayTime.asSeconds() < 0) GlobalDisplayTime = seconds(0);
                map.timeSubtract = 0;
            }
        }
    };
}

