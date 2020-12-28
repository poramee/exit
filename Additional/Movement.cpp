#include "Movement.hpp"
#include "Setup.hpp"

using namespace Movement;

Sprite Movement::Player::draw(){
    int ret;
    if(!levelComplete && !pause){
        if(Keyboard::isKeyPressed(Keyboard::A) && onLevel != "TextMode"){
            if(onLevel == "InverseControl"){
                if(velocity.first < WalkSpeed) velocity.first += 1;
                Run.setScale(Parameter::sprite_scale, Parameter::sprite_scale);
            }
            else{
                if(velocity.first > -WalkSpeed) velocity.first -= 1;
                Run.setScale(-Parameter::sprite_scale,Parameter::sprite_scale);
            }
        }
        else if(Keyboard::isKeyPressed(Keyboard::D) && onLevel != "TextMode"){
            if(onLevel == "InverseControl"){
                if(velocity.first > -WalkSpeed) velocity.first -= 1;
                Run.setScale(-Parameter::sprite_scale,Parameter::sprite_scale);
            }
            else{
                if(velocity.first < WalkSpeed) velocity.first += 1;
                Run.setScale(Parameter::sprite_scale, Parameter::sprite_scale);
            }
        }
        else{
            if(velocity.first > 0){
                velocity.first -= flying? 0.5:0.6;
                if(velocity.first < 0) velocity.first = 0;
            }
            else if(velocity.first < 0){
                velocity.first += flying? 0.5:0.6;
                if(velocity.first > 0) velocity.first = 0;
            }
        }
        
        if(Keyboard::isKeyPressed(Keyboard::Space) && onLevel != "TextMode"){
            WalkSpeed = 20;
            BoostSFX.setVolume(80*((velocity.first < 0? -velocity.first:velocity.first)/float(WalkSpeed)));
            if(lastBoostState == false){
                BoostSFX.play();
                lastBoostState = true;
            }
        }
        else{
            WalkSpeed = 7;
            BoostSFX.stop();
            lastBoostState = false;
        }
        
        
        if(velocity.first > WalkSpeed) velocity.first -= flying? 0.5:0.6;
        
        if(onLevel != "TextMode" && ((onLevel == "InverseControl" && Keyboard::isKeyPressed(Keyboard::S) && !flying) ||(onLevel != "InverseControl" && Keyboard::isKeyPressed(Keyboard::W) && !flying))){
            velocity.second -= 17;
            flying = true;
            
            JumpSFX.play();
        }
    }
    else BoostSFX.stop();
    
    //Tail Generator
    int cnt = 0;
    for(auto a : lastSpritePosition){
        ++cnt;
        a.setColor(Color(255,255,255,210 - cnt * 7));
        window.draw(a);
    }
    
    if(velocity.first == 0){
        Clk.restart();
        Pos.left = 0;
    }
    if(Clk.getElapsedTime().asMilliseconds() >= delta*(1/(velocity.first < 0? -velocity.first : velocity.first))){
        delta -= Clk.restart().asMilliseconds() - defaultDelta;
        Pos.left += Run.getTextureRect().width;
        if(Pos.left >= 7000) Pos.left = 0;
        Run.setTextureRect(Pos);
    }
    if(pause) velocity = {0,0};
    else checkCollision();
    //Update All Sprite Position
    update();
    
    Sprite ReturnSprite;
    
    if(flying){
        if(velocity.first < 0) Jump.setScale(-Parameter::sprite_scale,Parameter::sprite_scale);
        else Jump.setScale(Parameter::sprite_scale,Parameter::sprite_scale);
        ReturnSprite = Jump;
        if(Keyboard::isKeyPressed(Keyboard::Space) && !levelComplete && onLevel != "TextMode"){
            ReturnSprite.setTexture(JumpGlow);
            if(spriteCount == 2){
                lastSpritePosition.push_front(ReturnSprite);
                spriteCount = 0;
            }
            else ++spriteCount;
        }
        else{
            Sprite emp;
            lastSpritePosition.push_front(emp);
        }
    }
    else if(velocity.first != 0){
        ReturnSprite = Run;
        if(Keyboard::isKeyPressed(Keyboard::Space) && !levelComplete && onLevel != "TextMode"){
            ReturnSprite.setTexture(RunGlow);
            if(spriteCount == 2){
                lastSpritePosition.push_front(ReturnSprite);
                spriteCount = 0;
            }
            else ++spriteCount;
        }
        else{
            Sprite emp;
            lastSpritePosition.push_front(emp);
        }
    }
    else{
        ReturnSprite = Still;
        if(Keyboard::isKeyPressed(Keyboard::Space) && !levelComplete && onLevel != "TextMode"){
            ReturnSprite.setTexture(StillGlow);
            if(spriteCount == 2){
                lastSpritePosition.push_front(ReturnSprite);
                spriteCount = 0;
            }
            else ++spriteCount;
        }
        else{
            Sprite emp;
            lastSpritePosition.push_front(emp);
        }
    }
    while(lastSpritePosition.size() > 30) lastSpritePosition.pop_back();
    
    return ReturnSprite;
}

void Movement::Player::update(){
    SpritePosition.x += velocity.first;
    SpritePosition.y += velocity.second;
    Run.setPosition(SpritePosition);
    Still.setPosition(SpritePosition);
    Jump.setPosition(SpritePosition);
    Listener::setPosition(window.getView().getCenter().x,0,window.getView().getCenter().y);
}

void Movement::Player::checkCollision(){
    
    bool up, down, left, right;
    up = down = left = right = false;
    int spriteSizeCollision = 300;
    
    //Down Check
    int boundA = (SpritePosition.x - (spriteSizeCollision * Parameter::sprite_scale * 0.5))/(float)map.blockSize.width;
    int boundB = (SpritePosition.x - map.blockSize.width + (spriteSizeCollision * Parameter::sprite_scale * 0.5))/(float)map.blockSize.width;
    int constant = (SpritePosition.y + (Parameter::sprite_size * Parameter::sprite_scale * 0.5))/(float)map.blockSize.width;
    
    for(int x = boundA + 1;x <= boundB;++x){
        if(map.mapLoaded[constant][x] == '0') down = true;
        else if(map.mapLoaded[constant][x] >= '1' && map.mapLoaded[constant][x] <= '4') dead = true;
        
        if(map.mapLoaded[constant][x] == 'c') levelComplete = true;
    }
    if((down && velocity.second >= 0)){
        flying = false;
        velocity.second = 0;
        SpritePosition.y = ((constant)*map.blockSize.width) - (Parameter::sprite_size * Parameter::sprite_scale * 0.5);
    }
    else if (!down){
        velocity.second += 0.5;
        flying = true;
    }
    
    //Up Check
    boundA = (SpritePosition.x - (spriteSizeCollision * Parameter::sprite_scale * 0.5))/(float)map.blockSize.width;
    boundB = (SpritePosition.x + (spriteSizeCollision * Parameter::sprite_scale * 0.5))/(float)map.blockSize.width;
    constant = (SpritePosition.y - (Parameter::sprite_size * Parameter::sprite_scale * 0.5))/(float)map.blockSize.height;
    for(int x = boundA + 1;x <= boundB - 1;++x){
        if(map.mapLoaded[constant][x] == '0') up = true;
        else if(map.mapLoaded[constant][x] >= '1' && map.mapLoaded[constant][x] <= '4') dead = true;
        
        if(map.mapLoaded[constant][x] == 'c') levelComplete = true;
    }
    
    if(up && velocity.second < 0){
        velocity.second = 0;
        SpritePosition.y = ((constant+4) * map.blockSize.height - (Parameter::sprite_size * Parameter::sprite_scale * 0.5));
    }
    
    //Left Check
    boundA = (SpritePosition.y - (Parameter::sprite_size * Parameter::sprite_scale * 0.5))/(float)map.blockSize.width;
    boundB = (SpritePosition.y + (Parameter::sprite_size * Parameter::sprite_scale * 0.5))/(float)map.blockSize.width;
    constant = (SpritePosition.x - (spriteSizeCollision * Parameter::sprite_scale * 0.5))/(float)map.blockSize.width;
    for(int y = boundA + 1;y <= boundB - 1;++y){
        if(map.mapLoaded[y][constant] == '0') left = true;
        else if(map.mapLoaded[y][constant] >= '1' && map.mapLoaded[y][constant] <= '4') dead = true;
        
        if(map.mapLoaded[y][constant] == 'c') levelComplete = true;
    }
    
    //Right Check
    boundA = (SpritePosition.y - (Parameter::sprite_size * Parameter::sprite_scale * 0.5))/(float)map.blockSize.width;
    boundB = (SpritePosition.y + (Parameter::sprite_size * Parameter::sprite_scale * 0.5))/(float)map.blockSize.width;
    constant = (SpritePosition.x + (spriteSizeCollision * Parameter::sprite_scale * 0.5))/(float)map.blockSize.width;
    for(int y = boundA + 1;y <= boundB - 1;++y){
        if(map.mapLoaded[y][constant] == '0') right = true;
        else if(map.mapLoaded[y][constant] >= '1' && map.mapLoaded[y][constant] <= '4') dead = true;
        
        if(map.mapLoaded[y][constant] == 'c') levelComplete = true;
    }
    
    //Door Check
    if(map.doorAnimationSprite.getGlobalBounds().intersects(Still.getGlobalBounds()) && velocity.first > 0) velocity.first = 0;
    
    if((left && velocity.first < 0) || (right && velocity.first > 0)) velocity.first = 0;
    
    if(map.key.getGlobalBounds().intersects(Still.getGlobalBounds()) && !map.keyFound){
        if(onLevel == "DeadlyFriendly" && keyDeathCount < 2){
            dead = true;
            ++keyDeathCount;
        }
        else{
            map.keyFound = true;
            KeySFX.play();
        }
    }
    
    if(map.Special5.getGlobalBounds().intersects(Still.getGlobalBounds()) && !map.Special5Found){
        map.Special5Found = true;
        map.timeSubtract = 5;
        SpecialSFX.play();
    }
    
    if(map.Special10.getGlobalBounds().intersects(Still.getGlobalBounds()) && !map.Special10Found){
        map.Special10Found = true;
        map.timeSubtract = 10;
        SpecialSFX.play();
    }
    
    if(onLevel == "SelfProtected"){
        for(auto i = map.BulletPosition.begin();i != map.BulletPosition.end();++i){
            if(i -> first.getGlobalBounds().intersects(Still.getGlobalBounds())){
                map.BulletPosition.erase(i);
                dead = true;
                break;
            }
        }
    }
    
    if(dead){
        DeathSFX.play();
        if(onLevel == "MoreSpike") map.moreSpike(true);
        SpritePosition = Vector2f(100,900);
        Clk.restart();
        flying = false;
        velocity = {0,0};
        ++death;
        dead = false;
    }
}
Vector2f Movement::ViewSet::viewPosition(){
    Vector2f viewPosition;
    const float cameraDelay = 1.35;
    if(SpritePosition.y - cameraDelay*(playerSpeed.second) >= bgnd.getGlobalBounds().height - ((view.getSize().y) / 2)){
        viewPosition = Vector2f(0,bgnd.getGlobalBounds().height - ((view.getSize().y/ 2)));
    }
    else if(SpritePosition.y - cameraDelay*(playerSpeed.second) <= view.getSize().y/ 2){
        viewPosition = Vector2f(0,view.getSize().y/ 2);
    }
    else{
        viewPosition = Vector2f(0,SpritePosition.y - cameraDelay*(playerSpeed.second));
    }
    
    if(SpritePosition.x - cameraDelay*(playerSpeed.first) <= view.getSize().x/2){
        viewPosition += Vector2f(view.getSize().x/2,0);
    }
    else if(SpritePosition.x - cameraDelay*(playerSpeed.first) >= bgnd.getGlobalBounds().width - (view.getSize().x/ 2)){
        viewPosition += Vector2f(bgnd.getGlobalBounds().width - (view.getSize().x/ 2),0);
    }
    else{
        viewPosition += Vector2f(SpritePosition.x - cameraDelay*(playerSpeed.first),0);
    }
    
    return viewPosition;
}

void Movement::ViewSet::setView(){
    view.setCenter(viewPosition());
    bgnd.setOrigin(Vector2f(1920,1080) + Vector2f(500*(view.getCenter().x / 3840),500*(view.getCenter().y / 2160)));
    bgnd.setPosition(view.getCenter());
    window.setView(view);
}
