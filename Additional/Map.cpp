#include "Map.hpp"
#include "Setup.hpp"

using namespace BaseMap;

void BaseMap::Map::SelfProtectedKeyDraw(RenderWindow& window,bool pause){
    list<list<pair<Sprite,int>>::iterator> BulletToErase;
    
    //Spawn New Bullet
    if(BulletBreak.getElapsedTime().asSeconds() > 3.25) BulletBreak.restart();
    else if(BulletBreak.getElapsedTime().asSeconds() > 1.25 && BulletSpawnClock.getElapsedTime().asSeconds() > 0.1 && !keyFound){
        BulletSpawnClock.restart();
        int position = rand() % 4;
        Bullet.setPosition(key.getPosition());
        BulletPosition.push_back({Bullet,position});
    }
    
    //Move Bullet
    for(auto a = BulletPosition.begin();a != BulletPosition.end();++a){
        window.draw(a -> first);
        if(pause) continue;
        if(!(a -> first.getGlobalBounds().intersects(FloatRect(0,0,1920,1080)))){
            BulletToErase.push_back(a);
            continue;
        }
        if(a -> second == 0) a -> first.move(Vector2f(0,-5));
        else if(a -> second == 1) a -> first.move(Vector2f(5,0));
        else if(a -> second == 2) a -> first.move(Vector2f(0,5));
        else if(a -> second == 3) a -> first.move(Vector2f(-5,0));
    }
    
    //Delete Bullet that's out of screen
    for(auto a : BulletToErase) BulletPosition.erase(a);
    
}

BaseMap::Map::Map(const string fileLocation, pair<int,int>blockSize,Vector2f& SpritePosition):SpritePosition(SpritePosition){
    doorOpenSB.loadFromFile("Resources/Sounds/Door_Open.wav");
    doorOpenFx.setBuffer(doorOpenSB);
    doorOpenFx.setRelativeToListener(false);
    doorOpenFx.setVolume(100);
    doorOpenFx.setPosition(54 * blockSize.first,0, 28*blockSize.second);
    doorOpenFx.setMinDistance(1);
    doorOpenFx.setAttenuation(0.0025);
    
    doorOpenFx.setLoop(false);
    
    keyTexture.setSmooth(true);
    keyTexture.loadFromFile(fileLocation + "/Key.png");
    key.setTexture(keyTexture);
    key.setScale(0.2,0.2);
    
    Special5Tx.loadFromFile("Resources/Map/SI_5.png");
    Special5Tx.setSmooth(true);
    Special5.setTexture(Special5Tx);
    Special5.setScale(0.5,0.5);
    
    Special10Tx.loadFromFile("Resources/Map/SI_10.png");
    Special10Tx.setSmooth(true);
    Special10.setTexture(Special10Tx);
    Special10.setScale(0.5,0.5);
    
    BulletTx.loadFromFile("Resources/Map/Bullet.png");
    BulletTx.setSmooth(true);
    Bullet.setTexture(BulletTx);
    Bullet.setScale(0.25,0.25);
    
    
    mapFile.open(fileLocation + "/LevelMap.exitmap");
    int x,y;
    x = y = 0;
    while(!mapFile.eof()){
        string str;
        mapFile >> str;
        for(auto receive : str){
            if(receive == '0') mapGround.push_back({x,y});
            else if(receive >= '1' && receive <= '4') mapSpike[receive - '0'].push_back({x,y});
            else if(receive == 'r'){
                mapRandom.push_back({x,y});
            }
            mapLoaded[y][x] = receive;
            ++x;
        }
        ++y;
        x = 0;
    }
    mapFile.close();
    mapBound = {x,y};
    this -> fileLocation = fileLocation;
    blockSprite.setTexture(blockTexture);
    
    this -> blockSize = IntRect(0,0,blockSize.first,blockSize.second);
    
    doorAnimationTexture.loadFromFile(fileLocation + "/DoorAnimation.png");
    doorAnimationTexture.setSmooth(true);
    doorAnimationSprite.setTexture(doorAnimationTexture);
    doorAnimationSprite.setPosition(54 * blockSize.first, 28*blockSize.second);
    doorAnimationSprite.setTextureRect(doorMask);
    
    blockSprite.setTextureRect(IntRect(0,0,100,100));
    blockSprite.setScale(0.3,0.3);
}

void Map::draw(RenderWindow& window){
    if(drawLevel){
        blockTexture.loadFromFile(fileLocation + "/Tile_0_"+to_string(tileColor)+".png");
        blockTexture.setSmooth(true);
        blockSprite.setOrigin(0,0);
        for(auto i : mapGround){
            blockSprite.setPosition(i.first * blockSize.width,i.second * blockSize.height);
            window.draw(blockSprite);
        }
        for(int a = 1; a <= 4;++a){
            blockTexture.loadFromFile(fileLocation + "/Tile_"+to_string(a)+".png");
            for(auto i : mapSpike[a]){
                blockSprite.setPosition(i.first * blockSize.width,i.second * blockSize.height);
                window.draw(blockSprite);
            }
            if(a == 1){
                for(auto i : moreSpikeLocation){
                    blockSprite.setPosition(i.first * blockSize.width,i.second * blockSize.height);
                    window.draw(blockSprite);
                }
            }
        }
        
        doorAnimationSprite.setTextureRect(doorMask);
        if(!disableDoorAnimation){
            if(!doorOpen) window.draw(doorAnimationSprite);
            else doorAnimation(window);
        }
    }
    else {
        blockTexture.loadFromFile(fileLocation + "/Tile_0_"+to_string(tileColor)+".png");
        blockTexture.setSmooth(true);
        blockSprite.setOrigin(0,0);
        for(auto i : mapGround){
            blockSprite.setPosition(i.first * blockSize.width,i.second * blockSize.height);
            if(blockSprite.getPosition().x >= SpritePosition.x - drawLevelRadius && blockSprite.getPosition().x <= SpritePosition.x + drawLevelRadius && blockSprite.getPosition().y >= SpritePosition.y - drawLevelRadius && blockSprite.getPosition().y <= SpritePosition.y + drawLevelRadius) window.draw(blockSprite);
        }
        for(int a = 1; a <= 4;++a){
            blockTexture.loadFromFile(fileLocation + "/Tile_"+to_string(a)+".png");
            for(auto i : mapSpike[a]){
                blockSprite.setPosition(i.first * blockSize.width,i.second * blockSize.height);
                if(blockSprite.getPosition().x >= SpritePosition.x - drawLevelRadius && blockSprite.getPosition().x <= SpritePosition.x + drawLevelRadius && blockSprite.getPosition().y >= SpritePosition.y - drawLevelRadius && blockSprite.getPosition().y <= SpritePosition.y + drawLevelRadius) window.draw(blockSprite);
            }
            if(a == 1){
                for(auto i : moreSpikeLocation){
                    blockSprite.setPosition(i.first * blockSize.width,i.second * blockSize.height);
                    window.draw(blockSprite);
                }
            }
        }
        
        doorAnimationSprite.setTextureRect(doorMask);
        if(doorOpen) doorAnimation(window);
        if(doorAnimationSprite.getPosition().x >= SpritePosition.x - drawLevelRadius && doorAnimationSprite.getPosition().x <= SpritePosition.x + drawLevelRadius && doorAnimationSprite.getPosition().y >= SpritePosition.y - drawLevelRadius && blockSprite.getPosition().y <= SpritePosition.y + drawLevelRadius){
            if(!doorOpen) window.draw(doorAnimationSprite);
        }
    }
    
    if(!keyFound) window.draw(key);
    if(!Special5Found) window.draw(Special5);
    if(!Special10Found) window.draw(Special10);
}

void BaseMap::Map::doorAnimation(RenderWindow& window){
    if(doorAnimationClock.getElapsedTime().asMilliseconds() >= 50){
        if(doorMask.left == 0) doorOpenFx.play();
        if(doorMask.left < 270){
            doorMask.left += 30;
            doorMask.height -= 15;
        }
        doorAnimationClock.restart();
    }
    doorAnimationSprite.setTextureRect(doorMask);
    if(!drawLevel){
        if(doorAnimationSprite.getPosition().x >= SpritePosition.x - drawLevelRadius && doorAnimationSprite.getPosition().x <= SpritePosition.x + drawLevelRadius && doorAnimationSprite.getPosition().y >= SpritePosition.y - drawLevelRadius && blockSprite.getPosition().y <= SpritePosition.y + drawLevelRadius){
            window.draw(doorAnimationSprite);
        }
    }
    else window.draw(doorAnimationSprite);
}

void BaseMap::Map::moreSpike(bool want){
    
    for(auto a : moreSpikeLocation){
        mapLoaded[a.second][a.first] = 'x';
    }
    moreSpikeLocation = emptyVector;
    
    if(want){
        wantSpike = true;
        int spikeCnt = 0;
        
        while(spikeCnt < 15){
            int i = rand() % mapRandom.size();
            int cnt = 0;
            for(auto a : mapRandom){
                if(cnt++ == i){
                    if((a.first >= randomKey.first - 10 && a.first <= randomKey.first + 10) &&
                       (a.second >= randomKey.second - 10 && a.second <= randomKey.second + 10)) break;
                    else{
                        moreSpikeLocation.push_back({a.first,a.second});
                        mapLoaded[a.second][a.first] = '1';
                        ++spikeCnt;
                        break;
                    }
                }
            }
        }
    }
    else{
        wantSpike = false;
    }
}
