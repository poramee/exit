#include "Movement.hpp"
#include <SFML/Audio.hpp>
#include <fstream>
#include <list>

using namespace Movement;

struct TIME{
    int min;
    int sec;
    int mili;
};

bool isScoreFileExist();
bool createScoreFile();
void temporarySave(const Time& playerTime,const int Death,const int LevelNumber);
int loadTemporarySave(Time& time,unsigned int& death);
FloatRect getMouseRect(Vector2i MousePosition, View view);

class loadingScreen{
public:
    RenderWindow* window;
    bool& exitLoading;
    Texture loadingCircleTx;
    Sprite loadingCircle;
    Text loadingText;
    Font heavy;
public:
    loadingScreen(RenderWindow* window,bool& exitLoading):window(window), exitLoading(exitLoading){
        heavy.loadFromFile("Resources/Fonts/Raleway-Bold.ttf");
        loadingText.setFont(heavy);
        loadingText.setString("LOADING");
        loadingText.setCharacterSize(24);
        loadingText.setPosition(130,60);
        loadingText.setFillColor(Color(255,255,255,0));
        
        loadingCircleTx.loadFromFile("Resources/UI/loading_circle.png");
        loadingCircleTx.setSmooth(true);
        loadingCircle.setTexture(loadingCircleTx);
        loadingCircle.setOrigin(150,150);
        loadingCircle.setScale(0.2,0.2);
        loadingCircle.setPosition(90,80);
        loadingCircle.setColor(Color(255,255,255,0));
    };
    ~loadingScreen(){};
    void loadingScreenDraw();
};

class menuUI{
public:
    int menuPivot = 0;
private:
    
    RenderWindow& window;
    View view;
    
    Texture MainTx;
    Sprite Main;
    Texture BGTx;
    Sprite BG;
    Texture RunningTx;
    IntRect RunningMask = IntRect(0,0,500,500);
    Sprite Running;
    Clock RunningAnimation;
    Texture PlayIdleTx;
    Sprite PlayIdle;
    Texture PlayTx;
    Sprite Play;
    Texture ScoreIdleTx;
    Sprite ScoreIdle;
    Texture ScoreTx;
    Sprite Score;
    Texture TutorialIdleTx;
    Sprite TutorialIdle;
    Texture TutorialTx;
    Sprite Tutorial;
    vector<pair<TIME,string>> scoreInfo,empty;
    Texture EscToMenuTx;
    Sprite EscToMenu;
    Sprite EscToMenu2;
    Texture TutorialScreenTx;
    Sprite TutorialScreen;
    Text ContinueAtLevel;
    Text NoScore;
    Texture ScoreBoardTitleTx;
    Sprite ScoreBoardTitle;
    Text Creator;
    
    Font heavy;
    Font regular;
private:
    bool loadScoreFile();
    void scoreboardDraw();
    
public:
    menuUI(RenderWindow& window):window(window){
        heavy.loadFromFile("Resources/Fonts/Raleway-Bold.ttf");
        regular.loadFromFile("Resources/Fonts/Raleway-Regular.ttf");
        
        
        view.setSize(1024, 768);
        view.setCenter(512, 384);
        MainTx.loadFromFile("Resources/UI/Main_Title.png");
        MainTx.setSmooth(true);
        Main.setTexture(MainTx);
        Main.setPosition(50, 50);
        Main.setScale(0.6,0.6);
        
        BGTx.loadFromFile("Resources/UI/Main_BG.png");
        BGTx.setSmooth(true);
        BG.setTexture(BGTx);
        BG.setPosition(0,0);
        
        RunningTx.loadFromFile("Resources/sprite_run.png");
        RunningTx.setSmooth(true);
        Running.setTexture(RunningTx);
        Running.setTextureRect(RunningMask);
        Running.setPosition(600,40);
        Running.setScale(0.5,0.5);
        RunningAnimation.restart();
        
        PlayIdleTx.loadFromFile("Resources/UI/Main_PlayIdle.png");
        PlayIdleTx.setSmooth(true);
        PlayIdle.setTexture(PlayIdleTx);
        PlayIdle.setScale(0.5,0.5);
        PlayIdle.setPosition(80,300);
        
        PlayTx.loadFromFile("Resources/UI/Main_Play.png");
        PlayTx.setSmooth(true);
        Play.setTexture(PlayTx);
        Play.setScale(0.5,0.5);
        Play.setPosition(80,300);
        
        ScoreIdleTx.loadFromFile("Resources/UI/Main_ScoreIdle.png");
        ScoreIdleTx.setSmooth(true);
        ScoreIdle.setTexture(ScoreIdleTx);
        ScoreIdle.setScale(0.5,0.5);
        ScoreIdle.setPosition(80,370);
        
        ScoreTx.loadFromFile("Resources/UI/Main_Score.png");
        ScoreTx.setSmooth(true);
        Score.setTexture(ScoreTx);
        Score.setScale(0.5,0.5);
        Score.setPosition(80,370);
        
        TutorialIdleTx.loadFromFile("Resources/UI/Main_TutorialIdle.png");
        TutorialIdleTx.setSmooth(true);
        TutorialIdle.setTexture(TutorialIdleTx);
        TutorialIdle.setScale(0.5,0.5);
        TutorialIdle.setPosition(80,440);
        
        TutorialTx.loadFromFile("Resources/UI/Main_Tutorial.png");
        TutorialTx.setSmooth(true);
        Tutorial.setTexture(TutorialTx);
        Tutorial.setScale(0.5,0.5);
        Tutorial.setPosition(80,440);
        
        EscToMenuTx.loadFromFile("Resources/UI/Main_ESC_to_menu.png");
        EscToMenuTx.setSmooth(true);
        EscToMenu.setTexture(EscToMenuTx);
        EscToMenu.setScale(0.17,0.17);
        EscToMenu.setPosition(1055,700);
        
        EscToMenu2 = EscToMenu;
        EscToMenu2.setPosition(30,1468);
        
        TutorialScreenTx.loadFromFile("Resources/UI/Tutorial_Screen.png");
        TutorialScreenTx.setSmooth(true);
        TutorialScreen.setTexture(TutorialScreenTx);
        TutorialScreen.setScale(0.5,0.5);
        TutorialScreen.setPosition(0, 769);
        
        ContinueAtLevel.setFont(regular);
        ContinueAtLevel.setFillColor(Color::White);
        ContinueAtLevel.setPosition(400,340);
        ContinueAtLevel.setString("");
        ContinueAtLevel.setCharacterSize(32);
        
        NoScore.setFont(heavy);
        NoScore.setFillColor(Color::White);
        NoScore.setOrigin(0,0);
        NoScore.setPosition(1360,340);
        NoScore.setString("No Score Record");
        NoScore.setCharacterSize(44);
        
        ScoreBoardTitleTx.loadFromFile("Resources/UI/ScoreboardTitle.png");
        ScoreBoardTitleTx.setSmooth(true);
        ScoreBoardTitle.setTexture(ScoreBoardTitleTx);
        ScoreBoardTitle.setOrigin(0,0);
        ScoreBoardTitle.setScale(0.5,0.5);
        ScoreBoardTitle.setPosition(1025,35);
        
        Creator.setFont(heavy);
        Creator.setString("Created By 61010627 Poramee Chansuksett");
        Creator.setPosition(80,700);
        Creator.setCharacterSize(32);
    };
    ~menuUI(){};
    void draw(int levelJump);
    
};

class UI{
private:
    SoundBuffer DeathSB;
    Sound DeathSFX;
    RenderWindow& window;
    Player& player;
    ViewSet& view;
    Clock& GlobalClock;
    Time& GlobalDisplayTime;
    Font regular,heavy,commandFont;
    BaseMap::Map& map;
    struct overHeadComponent{
        float UIOffset;
        bool firstTime;
        string Level = "";
        string Description = "";
        string DeathString = "";
        Text DeathCount;
        Text LevelText,LevelDes;
        Clock DeathCountRedColorClock;
        Texture KeyNotFoundTx;
        Sprite KeyNotFound;
        Clock KeyFoundFlash;
        int FlashCount;
        Image KeyFoundImg;
        Texture KeyFoundTx;
        Sprite KeyFound;
        bool Flash;
        
        Texture DeathTexture;
        Sprite DeathSpr;
        Texture TimeTexture;
        Sprite TimeSpr;
    }overHead;
    
    struct levelComplete{
        Clock clock;
        RectangleShape WhiteRectangle;
        int alpha = 0;
    }levelComplete;
    
    struct pauseMenu{
        Clock animationClock;
        float menuOffset = 100;
    }pause;
    
    //Pause Menu
    Texture PauseTitleTx;
    Sprite PauseTitle;
    Texture BackTx;
    Sprite Back;
    Texture ContinueTx;
    Sprite Continue;
    RectangleShape WhiteRect;
    
    //for Right Click
    Clock rightClickCircle;
    
    int pivot = 0; //PIText
    
    //textModeDraw
    list<string>commandView;
    RectangleShape CommandWindow;
    Text command;

public:
    Clock GreenTimeHighlighter;
public:
    UI(RenderWindow& window,ViewSet& view, Player& player, Clock& GlobalClock, Time& GlobalDisplayTime, BaseMap::Map& map):view(view),player(player),GlobalClock(GlobalClock),window(window),GlobalDisplayTime(GlobalDisplayTime),map(map){
        heavy.loadFromFile("Resources/Fonts/Raleway-Bold.ttf");
        regular.loadFromFile("Resources/Fonts/Raleway-Regular.ttf");
        commandFont.loadFromFile("Resources/Fonts/Anonymous_Pro.ttf");
        overHead.LevelText.setFont(heavy);
        overHead.LevelText.setCharacterSize(40);
        overHead.LevelText.setFillColor(Color::White);
        overHead.LevelText.setOrigin(0, 0);
        overHead.LevelDes.setFont(regular);
        overHead.LevelDes.setCharacterSize(32);
        overHead.LevelDes.setFillColor(Color::White);
        overHead.LevelDes.setOrigin(0,0);
        this -> overHead.DeathString = to_string(player.death);
        this -> overHead.DeathCount.setString(overHead.DeathString);
        this -> overHead.firstTime = true;
        levelComplete.WhiteRectangle.setSize(Vector2f(3840 ,2160));
        overHead.KeyNotFoundTx.loadFromFile("Resources/UI/Key_UI_Not_Found.png");
        overHead.KeyNotFoundTx.setSmooth(true);
        overHead.KeyNotFound.setTexture(overHead.KeyNotFoundTx);
        overHead.KeyFoundImg.loadFromFile("Resources/UI/Key_UI_Found.png");
        overHead.KeyFoundTx.loadFromImage(overHead.KeyFoundImg);
        overHead.KeyFoundTx.setSmooth(true);
        overHead.KeyFound.setTexture(overHead.KeyFoundTx);
        overHead.FlashCount = 0;
        overHead.Flash = false;
        overHead.UIOffset = 0;
        overHead.DeathTexture.loadFromFile("Resources/UI/Death Icon.png");
        overHead.DeathTexture.setSmooth(true);
        overHead.DeathSpr.setTexture(overHead.DeathTexture);
        overHead.DeathSpr.setOrigin(0, 0);
        overHead.DeathSpr.setScale(0.17,0.17);
        overHead.TimeTexture.loadFromFile("Resources/UI/Time Elapse Icon.png");
        overHead.TimeTexture.setSmooth(true);
        overHead.TimeSpr.setTexture(overHead.TimeTexture);
        overHead.TimeSpr.setOrigin(0, 0);
        overHead.TimeSpr.setScale(0.17,0.17);
        
        PauseTitleTx.loadFromFile("Resources/UI/Pause_Title_UI.png");
        PauseTitleTx.setSmooth(true);
        PauseTitle.setTexture(PauseTitleTx);
        PauseTitle.setOrigin(0,0);
        PauseTitle.scale(0.45,0.45);
        
        BackTx.loadFromFile("Resources/UI/Pause_Back.png");
        BackTx.setSmooth(true);
        Back.setTexture(BackTx);
        Back.setOrigin(0,0);
        Back.scale(0.45,0.45);
        
        ContinueTx.loadFromFile("Resources/UI/Pause_Continue.png");
        ContinueTx.setSmooth(true);
        Continue.setTexture(ContinueTx);
        Continue.setOrigin(0,0);
        Continue.scale(0.45,0.45);
        
        WhiteRect.setFillColor(Color(255,255,255,200));
        WhiteRect.setSize(Vector2f(3840,2160));
        
        CommandWindow.setFillColor(Color(0,0,0,255));
        CommandWindow.setOutlineColor(Color(125,125,125,125));
        CommandWindow.setOutlineThickness(2);
        CommandWindow.setSize(Vector2f(1024,300));
        
        command.setFont(commandFont);
        command.setCharacterSize(26);
        command.setFillColor(Color::White);
        
        commandView.push_back("TEXT MODE Type \"help\" for more information.");
        
        DeathSB.loadFromFile("Resources/Sounds/Death.wav");
        DeathSFX.setBuffer(DeathSB);
        DeathSFX.setVolume(50);
    };
    ~UI(){};
    void reset(){
        overHead.FlashCount = 0;
        overHead.Flash = false;
        overHead.UIOffset = 0;
        this -> overHead.firstTime = true;
        overHead.Level = "";
        overHead.Description = "";
        overHead.DeathString = "";
        levelComplete.alpha = 0;
    };
    void drawOverheadMenu(int LevelNumber,const string LevelDescription);
    bool levelCompleteFlashScreen();
    void interruptCheck(Event& event, bool& forceEnd, const int LevelNumber);
    void pauseMenu();
    bool PIText(); // For Level "Pie in the Sky."
    FloatRect getOverHeadKeyPosition(){
        return overHead.KeyFound.getGlobalBounds();
    };
    void keyFlash(){overHead.FlashCount = -1;};
    void resetPause(){
        pause.animationClock.restart();
        pause.menuOffset = 100;
        
    };
    bool rightClick(Vector2f center);
    void rightClickPrepare(){ rightClickCircle.restart(); };
    int textModeDraw(string& cmd,bool& enter);
    int textModeCommandProcess(string cmd);
    FloatRect getKeyGlobalBound(){return overHead.KeyFound.getGlobalBounds();};
};
