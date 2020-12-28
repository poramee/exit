#include "Level.hpp"

void Level::Level::GetTheKey(){
    Event event;
    map.randomKeyPosition();
    parameter_reset();
    player.onLevel = "GetTheKey";
    map.drawLevel = true;
    map.randomTileColor();
    map.randomSpecialItem();
    ui.reset();
    while(window.isOpen()){
        if(forceEnd) return;
        if(map.keyFound) map.doorOpen = true;
        
        while(window.pollEvent(event)){
            ui.interruptCheck(event,forceEnd,1);
        }
        
        window.clear();
        vv.setView();
        if(map.drawLevel) window.draw(background);
        map.draw(window);
        window.draw(player.draw());
        ui.drawOverheadMenu(1, "JUST GET THE KEY");
        if(player.levelComplete){
            if(ui.levelCompleteFlashScreen()) return;
        }
        else if(player.pause) ui.pauseMenu();
        else if(!player.pause) ui.resetPause();
        SpecialTimeSubtract();
        window.display();
    }
}

void Level::Level::DeathIsGood(){
    Event event;
    map.randomKeyPosition();
    unsigned int prerun_death = player.death;
    bool deathMemory = false;
    parameter_reset();
    player.onLevel = "DeathIsGood";
    map.drawLevel = true;
    map.randomTileColor();
    map.randomSpecialItem();
    while(window.isOpen()){
        if(forceEnd) return;
        if(map.keyFound){
            if(!deathMemory){
                prerun_death = player.death;
                deathMemory = true;
            }
            if(player.death - prerun_death >= 3) map.doorOpen = true;
        }
        
        while(window.pollEvent(event)){
            ui.interruptCheck(event,forceEnd,3);
        }
        
        
        window.clear();
        vv.setView();
        if(map.drawLevel) window.draw(background);
        map.draw(window);
        window.draw(player.draw());
        ui.drawOverheadMenu(3, "DE3TH IS GOOD");
        if(player.levelComplete){
            if(ui.levelCompleteFlashScreen()) return;
        }
        else if(player.pause) ui.pauseMenu();
        else if(!player.pause) ui.resetPause();
        SpecialTimeSubtract();
        window.display();
    }
}


void Level::Level::UpDownLeftRight(){
    Event event;
    int pivot = 0;
    
    map.randomKeyPosition();
    map.randomTileColor();
    map.randomSpecialItem();
    ui.reset();
    parameter_reset();
    player.onLevel = "UpDownLeftRight";
    map.drawLevel = true;
    while(window.isOpen()){
        if(forceEnd) return;
        if(map.keyFound && pivot == 4){
            map.doorOpen = true;
        }
        
        while(window.pollEvent(event)){
            ui.interruptCheck(event,forceEnd,2);
            if(event.type == sf::Event::EventType::KeyPressed){
                if(event.key.code == sf::Keyboard::W){
                    if(pivot == 0) ++pivot;
                    else pivot = 0;
                }
                else if(event.key.code == sf::Keyboard::S){
                    if(pivot == 1) ++pivot;
                    else pivot = 0;
                }
                else if(event.key.code == sf::Keyboard::A){
                    if(pivot == 2) ++pivot;
                    else pivot = 0;
                }
                else if(event.key.code == sf::Keyboard::D){
                    if(pivot == 3) ++pivot;
                    else pivot = 0;
                }
            }
        }
        window.clear();
        vv.setView();
        if(map.drawLevel) window.draw(background);
        map.draw(window);
        window.draw(player.draw());
        ui.drawOverheadMenu(2, "UP DOWN LEFT RIGHT");
        if(player.levelComplete){
            if(ui.levelCompleteFlashScreen()) return;
        }
        else if(player.pause) ui.pauseMenu();
        else if(!player.pause) ui.resetPause();
        SpecialTimeSubtract();
        window.display();
    }
}


void Level::Level::InverseControl(){
    Event event;
    
    map.randomKeyPosition();
    map.randomTileColor();
    map.randomSpecialItem();
    ui.reset();
    parameter_reset();
    player.onLevel = "InverseControl";
    map.drawLevel = true;
    while(window.isOpen()){
        if(forceEnd) return;
        if(map.keyFound) map.doorOpen = true;
        while(window.pollEvent(event)){
            ui.interruptCheck(event,forceEnd,4);
        }
        
        window.clear();
        vv.setView();
        if(map.drawLevel) window.draw(background);
        map.draw(window);
        window.draw(player.draw());
        ui.drawOverheadMenu(4, "INVERSE CONTROL");
        if(player.levelComplete){
            if(ui.levelCompleteFlashScreen()) return;
        }
        else if(player.pause) ui.pauseMenu();
        else if(!player.pause) ui.resetPause();
        SpecialTimeSubtract();
        window.display();
    }
}

void Level::Level::AutomaticDoor(){
    Event event;
    
    ui.reset();
    parameter_reset();
    
    player.onLevel = "AutomaticDoor";
    map.keyFound = true; // prevent function to place the key onto the map.
    map.drawLevel = true;
    map.randomTileColor();
    map.randomSpecialItem();
    Clock AutoDoor;
    while(window.isOpen()){
        if(forceEnd) return;
        while(window.pollEvent(event)){
            ui.interruptCheck(event,forceEnd,6);
        }
        
        if(!(map.doorAnimationSprite.getGlobalBounds().intersects(player.Still.getGlobalBounds()))) AutoDoor.restart();
        if(AutoDoor.getElapsedTime().asSeconds() > 1) map.doorOpen = true;
        window.clear();
        vv.setView();
        window.draw(background);
        map.draw(window);
        window.draw(player.draw());
        ui.drawOverheadMenu(6, "AUTOMATIC DOOR");
        if(player.levelComplete){
            if(ui.levelCompleteFlashScreen()) return;
        }
        else if(player.pause) ui.pauseMenu();
        else if(!player.pause) ui.resetPause();
        SpecialTimeSubtract();
        window.display();
    }
}

void Level::Level::RightClick(){
    Event event;
    
    ui.reset();
    parameter_reset();
    map.randomKeyPosition();
    map.randomTileColor();
    map.randomSpecialItem();
    player.onLevel = "RightClick";
    
    map.drawLevel = true;
    bool drawCircle = false;
    Vector2f mousePosition = Vector2f(0,0);
    
    while(window.isOpen()){
        if(forceEnd) return;
        while(window.pollEvent(event)){
            ui.interruptCheck(event,forceEnd,5);
            if(event.type == sf::Event::EventType::MouseButtonPressed && map.keyFound){
                if(event.mouseButton.button == sf::Mouse::Right){
                    mousePosition = Vector2f(event.mouseButton.x,event.mouseButton.y);
                    map.doorOpen = true;
                    drawCircle = true;
                    ui.rightClickPrepare();
                }
            }
        }
        
        window.clear();
        vv.setView();
        window.draw(background);
        map.draw(window);
        window.draw(player.draw());
        ui.drawOverheadMenu(5, "MAKE A RIGHT CLICK");
        if(player.levelComplete){
            if(ui.levelCompleteFlashScreen()) return;
        }
        else if(player.pause) ui.pauseMenu();
        else if(!player.pause) ui.resetPause();
        if(drawCircle) drawCircle = ui.rightClick(mousePosition);
        SpecialTimeSubtract();
        window.display();
    }
}


void Level::Level::LightsOut(){
    Event event;
    
    ui.reset();
    parameter_reset();
    map.randomKeyPosition();
    map.randomTileColor();
    map.randomSpecialItem();
    player.onLevel = "LightsOut";
    
    map.drawLevel = false;
    
    while(window.isOpen()){
        if(forceEnd) return;
        while(window.pollEvent(event)){
            ui.interruptCheck(event,forceEnd,7);
        }
        if(map.keyFound) map.doorOpen = true;
        window.clear();
        vv.setView();
        map.draw(window);
        window.draw(player.draw());
        ui.drawOverheadMenu(7, "BLACKOUT");
        if(player.levelComplete){
            if(ui.levelCompleteFlashScreen()) return;
        }
        else if(player.pause) ui.pauseMenu();
        else if(!player.pause) ui.resetPause();
        SpecialTimeSubtract();
        window.display();
    }
}


void Level::Level::TakeABreak(){
    Event event;
    map.randomKeyPosition();
    ui.reset();
    parameter_reset();
    map.randomTileColor();
    player.onLevel = "TakeABreak";
    map.drawLevel = true;
    
    while(window.isOpen()){
        if(forceEnd) return;
        if(map.keyFound && player.pause) map.doorOpen = true;
        
        while(window.pollEvent(event)){
            ui.interruptCheck(event,forceEnd,9);
        }
        
        window.clear();
        vv.setView();
        if(map.drawLevel) window.draw(background);
        map.draw(window);
        window.draw(player.draw());
        ui.drawOverheadMenu(9, "TAKE A BREAK");
        if(player.levelComplete){
            if(ui.levelCompleteFlashScreen()) return;
        }
        else if(player.pause) ui.pauseMenu();
        else if(!player.pause) ui.resetPause();
        SpecialTimeSubtract();
        window.display();
    }
}

void Level::Level::MoreSpike(){
    Event event;
    map.randomKeyPosition();
    ui.reset();
    parameter_reset();
    map.randomTileColor();
    map.randomSpecialItem();
    map.moreSpike(true);
    player.onLevel = "MoreSpike";
    map.drawLevel = true;
    
    while(window.isOpen()){
        if(forceEnd) return;
        if(map.keyFound) map.doorOpen = true;
        
        while(window.pollEvent(event)){
            ui.interruptCheck(event,forceEnd,8);
        }
        
        window.clear();
        vv.setView();
        if(map.drawLevel) window.draw(background);
        map.draw(window);
        window.draw(player.draw());
        ui.drawOverheadMenu(8, "A SPIKY LEVEL");
        if(player.levelComplete){
            if(ui.levelCompleteFlashScreen()) return;
        }
        else if(player.pause) ui.pauseMenu();
        else if(!player.pause) ui.resetPause();
        SpecialTimeSubtract();
        window.display();
    }
}

void Level::Level::PieInTheSky(){
    Event event;
    map.randomKeyPosition();
    map.randomTileColor();
    map.randomSpecialItem();
    ui.reset();
    parameter_reset();
    player.onLevel = "PieInTheSky";
    map.drawLevel = true;
    bool piComplete = false;
    
    
    while(window.isOpen()){
        if(forceEnd) return;
        if(map.keyFound && piComplete) map.doorOpen = true;
        
        while(window.pollEvent(event)){
            ui.interruptCheck(event,forceEnd,10);
        }
        
        window.clear();
        vv.setView();
        if(map.drawLevel) window.draw(background);
        map.draw(window);
        window.draw(player.draw());
        ui.drawOverheadMenu(10, "PI IN THE SKY");
        if(map.keyFound) piComplete = ui.PIText();
        if(player.levelComplete){
            if(ui.levelCompleteFlashScreen()) return;
        }
        else if(player.pause) ui.pauseMenu();
        else if(!player.pause) ui.resetPause();
        SpecialTimeSubtract();
        window.display();
    }
}

void Level::Level::PressAnyKeyToContinue(){
    Event event;
    map.randomKeyPosition();
    map.randomTileColor();
    map.randomSpecialItem();
    ui.reset();
    parameter_reset();
    player.onLevel = "PressAnyKey";
    map.drawLevel = true;
    bool pressTheKey = false;
    while(window.isOpen()){
        if(forceEnd) return;
        if(map.keyFound && pressTheKey) map.doorOpen = true;
        
        while(window.pollEvent(event)){
            ui.interruptCheck(event,forceEnd,11);
            if(event.type == Event::MouseButtonPressed){
                FloatRect mouse = getMouseRect(Vector2i(event.mouseButton.x,event.mouseButton.y), vv.view);
                if(map.keyFound && ui.getKeyGlobalBound().intersects(mouse)){
                    ui.keyFlash();
                    pressTheKey = true;
                }
            }
        }
        
        window.clear();
        vv.setView();
        if(map.drawLevel) window.draw(background);
        map.draw(window);
        window.draw(player.draw());
        ui.drawOverheadMenu(11, "PRESS THE KEY TO CONTINUE");
        if(player.levelComplete){
            if(ui.levelCompleteFlashScreen()) return;
        }
        else if(player.pause) ui.pauseMenu();
        else if(!player.pause) ui.resetPause();
        SpecialTimeSubtract();
        window.display();
    }
}

void Level::Level::AdjustableDoor(){
    Event event;
    map.randomKeyPosition();
    map.randomTileColor();
    map.randomSpecialItem();
    ui.reset();
    parameter_reset();
    map.disableDoorAnimation = true;
    player.onLevel = "Adjust";
    map.drawLevel = true;
    int doorStep = 0;
    
    
    while(window.isOpen()){
        if(forceEnd) return;
        while(window.pollEvent(event)){
            ui.interruptCheck(event,forceEnd,12);
            if(event.type == Event::KeyPressed && map.keyFound){
                if(event.key.code == Keyboard::Up && doorStep < 9) ++doorStep;
                if(event.key.code == Keyboard::Down && doorStep > 0) --doorStep;
            }
        }
        
        window.clear();
        vv.setView();
        if(map.drawLevel) window.draw(background);
        map.draw(window);
        map.manualDoor(doorStep, window);
        window.draw(player.draw());
        ui.drawOverheadMenu(12, "ADJUSTABLE DOOR");
        if(player.levelComplete){
            if(ui.levelCompleteFlashScreen()) return;
        }
        else if(player.pause) ui.pauseMenu();
        else if(!player.pause) ui.resetPause();
        SpecialTimeSubtract();
        window.display();
    }
}

void Level::Level::TextMode(){
    Event event;
    View moveViewUp;
    map.randomKeyPosition();
    parameter_reset();
    player.onLevel = "TextMode";
    map.drawLevel = true;
    map.randomTileColor();
    map.randomSpecialItem();
    ui.reset();
    string cmd = "";
    bool isEnter = false;
    while(window.isOpen()){
        if(forceEnd) return;
        if(map.keyFound) map.doorOpen = true;
        
        while(window.pollEvent(event)){
            ui.interruptCheck(event,forceEnd,13);
            if(event.type == Event::TextEntered){
                //32 - 127
                if(event.text.unicode >= 32 && event.text.unicode <= 127){
                    cmd += event.text.unicode;
                }
            }
            if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Enter) isEnter = true;
                if(event.key.code == Keyboard::BackSpace && cmd.size() > 0) cmd.erase(cmd.end() - 1);
            }
        }
        
        window.clear();
        vv.setView();
        moveViewUp = window.getView();
        moveViewUp.setCenter(moveViewUp.getCenter() + Vector2f(0,200));
        if(player.SpritePosition.y <= vv.view.getSize().y / 2) {
            float move = vv.view.getSize().y / 2 - player.SpritePosition.y;
            if(move > 200) move = 200;
            moveViewUp.move(Vector2f(0,-move));
        }
        vv.view = moveViewUp;
        window.setView(moveViewUp);
        if(map.drawLevel) window.draw(background);
        map.draw(window);
        window.draw(player.draw());
        ui.drawOverheadMenu(13, "TEXT MODE");
        
        int returnValue = ui.textModeDraw(cmd, isEnter);
        
        if(returnValue == 0) player.SpritePosition = map.key.getPosition() + Vector2f(0,-40);
        else if(returnValue == 1) player.SpritePosition = map.doorAnimationSprite.getPosition();
        else if(returnValue == 2) player.SpritePosition = Vector2f(1770,930);
        
        if(player.levelComplete){
            if(ui.levelCompleteFlashScreen()) return;
        }
        else if(player.pause) ui.pauseMenu();
        else if(!player.pause) ui.resetPause();
        SpecialTimeSubtract();
        window.display();
    }
}

void Level::Level::SelfProtected(){
    Event event;
    map.randomKeyPosition();
    parameter_reset();
    player.onLevel = "SelfProtected";
    map.drawLevel = true;
    map.randomTileColor();
    map.randomSpecialItem();
    ui.reset();
    while(window.isOpen()){
        if(forceEnd) return;
        if(map.keyFound) map.doorOpen = true;
        
        while(window.pollEvent(event)){
            ui.interruptCheck(event,forceEnd,14);
        }
        
        window.clear();
        vv.setView();
        if(map.drawLevel) window.draw(background);
        map.draw(window);
        map.SelfProtectedKeyDraw(window,player.pause);
        window.draw(player.draw());
        ui.drawOverheadMenu(14, "SELF-PROTECTED KEY");
        if(player.levelComplete){
            if(ui.levelCompleteFlashScreen()) return;
        }
        else if(player.pause) ui.pauseMenu();
        else if(!player.pause) ui.resetPause();
        SpecialTimeSubtract();
        window.display();
    }
}


void Level::Level::DeadlyFriendly(){
    Event event;
    map.randomKeyPosition();
    parameter_reset();
    player.onLevel = "DeadlyFriendly";
    map.drawLevel = true;
    map.randomTileColor();
    map.randomSpecialItem();
    ui.reset();
    
    while(window.isOpen()){
        if(forceEnd) return;
        if(map.keyFound) map.doorOpen = true;
        
        while(window.pollEvent(event)){
            ui.interruptCheck(event,forceEnd,15);
        }
        
        window.clear();
        vv.setView();
        if(map.drawLevel) window.draw(background);
        map.draw(window);
        window.draw(player.draw());
        ui.drawOverheadMenu(15, "DEADLY DEADLY FRIENDLY KEY");
        if(player.levelComplete){
            if(ui.levelCompleteFlashScreen()) return;
        }
        else if(player.pause) ui.pauseMenu();
        else if(!player.pause) ui.resetPause();
        SpecialTimeSubtract();
        window.display();
    }
}

void Level::Level::AllClear(){
    if(forceEnd || !window.isOpen()) return;
    Font regular,heavy;
    heavy.loadFromFile("Resources/Fonts/Raleway-Bold.ttf");
    regular.loadFromFile("Resources/Fonts/Raleway-Regular.ttf");
    
    View view;
    view.setSize(1024, 768);
    view.setCenter(512, 384);
    
    Text nameText;
    nameText.setFont(regular);
    nameText.setPosition(50,400);
    nameText.setFillColor(Color::Black);
    nameText.setCharacterSize(64);
    
    Text Title;
    Title.setFont(heavy);
    Title.setPosition(50,150);
    Title.setFillColor(Color::Black);
    Title.setCharacterSize(70);
    Title.setString("Game Completed\nEnter Your Name");
    
    string name = "";
    string TimeString = "";
    TimeString += to_string(int(GlobalDisplayTime.asSeconds() / 60)) + " ";
    TimeString += to_string(int(GlobalDisplayTime.asSeconds()) % 60) + " ";
    TimeString += to_string(int(GlobalDisplayTime.asMilliseconds() / 10) % 100);
    
    Texture TimeTx;
    TimeTx.loadFromFile("Resources/UI/Time Elapse Icon.png");
    TimeTx.setSmooth(true);
    Sprite TimeSpr(TimeTx);
    TimeSpr.setOrigin(0,0);
    TimeSpr.setScale(0.2,0.2);
    TimeSpr.setColor(Color(0,0,0));
    TimeSpr.setPosition(50,600);
    
    Text TimeText;
    TimeText.setFont(heavy);
    string TimeStringDisplay;
    if(GlobalDisplayTime.asSeconds() / 60 < 10) TimeStringDisplay += "0";
    TimeStringDisplay += to_string(int(GlobalDisplayTime.asSeconds() / 60)) + ":";
    
    if(int(GlobalDisplayTime.asSeconds()) % 60 < 10) TimeStringDisplay += "0";
    TimeStringDisplay += to_string(int(GlobalDisplayTime.asSeconds()) % 60) + ".";
    
    if(int(GlobalDisplayTime.asMilliseconds() / 10) % 100 < 10) TimeStringDisplay += "0";
    TimeStringDisplay += to_string(int(GlobalDisplayTime.asMilliseconds() / 10) % 100);
    
    
    TimeText.setString(TimeStringDisplay);
    TimeText.setPosition(150,607);
    TimeText.setCharacterSize(32);
    TimeText.setFillColor(Color::Black);
    
    Texture DeathTx;
    DeathTx.loadFromFile("Resources/UI/Death Icon.png");
    DeathTx.setSmooth(true);
    Sprite DeathSpr(DeathTx);
    DeathSpr.setOrigin(0,0);
    DeathSpr.setScale(0.2,0.2);
    DeathSpr.setColor(Color(0,0,0));
    DeathSpr.setPosition(400,600);
    
    
    Text DeathText;
    DeathText.setFont(heavy);
    DeathText.setString(to_string(player.death));
    DeathText.setPosition(500,607);
    DeathText.setFillColor(Color::Black);
    DeathText.setCharacterSize(32);
    
    
    Texture ConfettiTx;
    ConfettiTx.loadFromFile("Resources/UI/Confetti/Confetti_0.png");
    ConfettiTx.setSmooth(true);
    
    Sprite Confetti(ConfettiTx);
    Confetti.setScale(0.64,0.64);
    Confetti.setPosition(0,0);
    float ConfettiIndex = 0;
    Clock ConfettiClock;
    Clock TestClock;
    
    bool exit = false;
    Event event;
    while(window.isOpen() && !exit){
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
                temporarySave(GlobalDisplayTime, player.death, -1);
            }
            if(event.type == Event::TextEntered && name.size() < 20){
                //32 - 127
                if(event.text.unicode >= 32 && event.text.unicode <= 127){
                    name += event.text.unicode;
                }
            }
            if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Backspace && name.size() > 0) name.erase(name.end() - 1);
                if(event.key.code == Keyboard::Enter && name.size() > 0){
                    exit = true;
                    break;
                }
            }
        }
        nameText.setString(name + "_");
        window.clear(Color(243, 255, 236));
        window.setView(view);
        window.draw(nameText);
        window.draw(Title);
        window.draw(TimeSpr);
        window.draw(TimeText);
        window.draw(DeathSpr);
        window.draw(DeathText);
        ConfettiIndex += (ConfettiClock.restart().asMilliseconds() / 16.667);
        if(ConfettiIndex <= 126){
            ConfettiTx.loadFromFile("Resources/UI/Confetti/Confetti_" + to_string(int(ConfettiIndex)) + ".png");
            window.draw(Confetti);
        }
        window.display();
    }
    
    if(!window.isOpen()) return;
    remove("Saves/temporary.saves");
    ofstream write;
    write.open("Saves/Scores.saves",ios::app);
    write << endl << name << endl << TimeString;
    write.close();
}
