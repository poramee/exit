#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <list>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

namespace BaseMap{
    class Map{
    public:
        char mapLoaded[100][100];
        Sprite blockSprite;
        IntRect blockSize;
        vector<pair<int,int>> mapRandom;
        pair<int,int> randomKey = {0,0};
        bool doorOpen = false;
        bool doorIsOpening = false;
        void doorAnimation(RenderWindow& );
        Sprite doorAnimationSprite;
        IntRect doorMask = IntRect(0,0,30,150);
        bool keyRandom = false;
        bool disableDoorAnimation = false;
        
        //For Level "Lights Out"
        bool drawLevel = true;
        Vector2f& SpritePosition;
        
        Texture Special5Tx;
        Sprite Special5;
        Vector2i Special5Position;
        bool Special5Found = false;
        
        Texture Special10Tx;
        Sprite Special10;
        Vector2i Special10Position;
        bool Special10Found = false;
        int timeSubtract = 0;
        
        Texture keyTexture;
        Sprite key;
        bool keyFound = false;
        
        //Self-Protected Key
        list<pair<Sprite,int>> BulletPosition;
        Clock BulletSpawnClock;
        Clock BulletBreak;
        Texture BulletTx;
        Sprite Bullet;
        
    private:
        ifstream mapFile;
        pair<int , int> mapBound = {0,0};
        Texture blockTexture;
        bool wantSpike = false;
        vector<pair<int,int>> mapGround;
        vector<pair<int,int>> mapSpike[5];
        vector<pair<int,int>> moreSpikeLocation,emptyVector;
        string fileLocation;
        Clock doorAnimationClock;
        Texture doorAnimationTexture;
        int tileColor = 0;
        SoundBuffer doorOpenSB;
        Sound doorOpenFx;
        const unsigned int drawLevelRadius = 100;
        
    public:
        Map(const string fileLocation, pair<int ,int>blockSize,Vector2f& SpritePosition);
        ~Map(){};
        void draw(RenderWindow& window);
        void moreSpike(bool want);
        void manualDoor(int step, RenderWindow& window){
            doorMask.left = 30 * step;
            doorMask.height = 150 - 15 * step;
            doorAnimationSprite.setTextureRect(doorMask);
            window.draw(doorAnimationSprite);
        };
        void randomKeyPosition(){
            keyRandom = true;
            const int i = rand() % mapRandom.size();
            randomKey.first = mapRandom[i].first;
            randomKey.second = mapRandom[i].second;
            key.setPosition(randomKey.first*blockSize.width,randomKey.second*blockSize.height);
        };
        void randomTileColor(){tileColor = rand() % 4;};
        void randomSpecialItem(){
            int a;
            do{
                a = rand() % mapRandom.size();
            }while(mapRandom[a] == randomKey);
            Special5.setPosition(mapRandom[a].first*blockSize.width,mapRandom[a].second*blockSize.height);
            do{
                a = rand() % mapRandom.size();
                Special10.setPosition(mapRandom[a].first*blockSize.width,mapRandom[a].second*blockSize.height);
            }while(mapRandom[a] == randomKey || Special5.getPosition() == Special10.getPosition());
        };
        void SpecialItemReset(){
            Special5Found = Special10Found = false;
        };
        void SelfProtectedKeyDraw(RenderWindow& window,bool pause);
    };
}
