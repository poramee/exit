#include "Additional/All.hpp"

int main(){
    //SETUP
    RenderWindow window(VideoMode(1280,960), "Exit!",sf::Style::Titlebar | sf::Style::Close);
    Event event;
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    Image icon;
    icon.loadFromFile("Resources/sprite_jump.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setActive(false);
    bool exitLoadingScreen = false;
    
    while(window.isOpen()){
        
        //View Setup
        View view(Vector2f(0,0),Vector2f(1024,768));
        view.setCenter(512,384);
        view.zoom(Parameter::view_zoom);
        window.setView(view);
        
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed) window.close();
        }
        
        exitLoadingScreen = false;
        loadingScreen loadingScr(&window,exitLoadingScreen);
        Thread loading(&loadingScreen::loadingScreenDraw,&loadingScr);
        window.setActive(false);
        loading.launch();
        
        //Set View Zoom
        
        Vector2f SpritePosition;
        Clock Clk;
        float delta = 30;
        const float defaultDelta = delta;
        float WalkSpeed = 7;
        IntRect Pos = IntRect(0,0,500,500);
        Clock cl;
        
        int window_x = -1;
        int window_y = -1;
        
        //Background Setup
        Texture bg;
        Setup::initTexture(bg,"Resources/background.png");
        bg.setSmooth(true);
        Sprite background(bg);
        background.setOrigin(1920, 1080);
        background.setScale(0.5,0.5);
        
        //Running Sprite Setup
        Texture runningMan;
        Setup::initTexture(runningMan, "Resources/sprite_run.png");
        runningMan.setSmooth(true);
        Sprite sprite(runningMan);
        Setup::initSprite(sprite, 100,900);
        
        //Still Sprite Setup
        Texture stillTx;
        Setup::initTexture(stillTx, "Resources/sprite_still.png");
        stillTx.setSmooth(true);
        Sprite still;
        still.setTexture(stillTx);
        Setup::initSprite(still,sprite.getPosition().x,sprite.getPosition().y);
        
        //Jump Sprite Setup
        Texture jumpTx;
        Setup::initTexture(jumpTx, "Resources/sprite_jump.png");
        jumpTx.setSmooth(true);
        Sprite jump(jumpTx);
        Setup::initSprite(jump,sprite.getPosition().x,sprite.getPosition().y);
        
        //Set Initial Sprite Position
        SpritePosition = sprite.getPosition();
        
        
        Clock Fast,MainClock;
        bool fast = false;
        MainClock.restart();
        
        srand(time(NULL));
        
        BaseMap::Map map("Resources/Map",{30,30},SpritePosition);
        Movement::Player character(sprite,still,jump,background,SpritePosition,Clk,defaultDelta,WalkSpeed,Pos,delta,map,window);
        
        //Assign Object
        Movement::ViewSet vv(background,SpritePosition,character.velocity,window,view);
        view.setCenter(SpritePosition);
        Level::Level level(window,character,background,map,vv,MainClock);
        
        menuUI menu(window);
        
        int LevelJumper = loadTemporarySave(level.GlobalDisplayTime,character.death);
        
        exitLoadingScreen = true;
        loading.wait();
        
        window.setActive(true);
        
        menu.draw(LevelJumper);
        if(!window.isOpen()) level.forceEnd = true;
        MainClock.restart();
        
        Music levelMusic;
        levelMusic.openFromFile("Resources/Sounds/Apero Hour.flac");
        levelMusic.setLoop(true);
        levelMusic.setVolume(70);
        levelMusic.play();
        
        if(LevelJumper == 0) LevelJumper = 1;
        switch(LevelJumper){
            case(1): level.GetTheKey();
            case(2): level.UpDownLeftRight();
            case(3): level.DeathIsGood();
            case(4): level.InverseControl();
            case(5): level.RightClick();
            case(6): level.AutomaticDoor();
            case(7): level.LightsOut();
            case(8): level.MoreSpike();
            case(9): level.TakeABreak();
            case(10): level.PieInTheSky();
            case(11): level.PressAnyKeyToContinue();
            case(12): level.AdjustableDoor();
            case(13): level.TextMode();
            case(14): level.SelfProtected();
            case(15): level.DeadlyFriendly();
            default: break;
        }
        level.AllClear();
    }
}
