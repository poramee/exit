#include "UI.hpp"

void loadingScreen::loadingScreenDraw(){
    window -> setActive(true);
    
    while(window -> isOpen() && !exitLoading){
        if(loadingText.getFillColor().a >= 255){
            loadingCircle.setColor(Color(255,255,255,255));
            loadingText.setFillColor(Color(255,255,255,255));
        }
        else{
            loadingCircle.setColor(Color(255,255,255,loadingCircle.getColor().a + 15));
            loadingText.setFillColor(Color(255,255,255,loadingText.getFillColor().a + 15));
        }
        window -> clear();
        loadingCircle.rotate(10);
        window -> draw(loadingCircle);
        window -> draw(loadingText);
        window -> display();
    }
    while (window -> isOpen()) {
        if (loadingText.getFillColor().a <= 0) break;
        else {
            loadingCircle.setColor(Color(255, 255, 255, loadingCircle.getColor().a - 15));
            loadingText.setFillColor(Color(255, 255, 255, loadingText.getFillColor().a - 15));
        }
        window -> clear();
        loadingCircle.rotate(10);
        window -> draw(loadingCircle);
        window -> draw(loadingText);
        window -> display();
    }
    
    window -> setActive(false);
}

FloatRect getMouseRect(Vector2i MousePosition, View view) {
    MousePosition -= Vector2i(640,480);
    return FloatRect((MousePosition.x * 0.9*(float(512)/float(640))) + view.getCenter().x,(MousePosition.y * 0.9*(float(384)/float(480))) + view.getCenter().y,10,10);
};

void UI::drawOverheadMenu(int level,string str){
    if(overHead.Level != to_string(level)){
        overHead.LevelText.setString("LEVEL " + to_string(level));
        overHead.Level = to_string(level);
    }
    overHead.LevelText.setPosition(view.view.getCenter().x - 450, view.view.getCenter().y - 320 + overHead.UIOffset);
    window.draw(overHead.LevelText);
    
    if(overHead.Description != str){
        overHead.Description = str;
        overHead.LevelDes.setString(str);
    }
    overHead.LevelDes.setPosition(view.view.getCenter().x - 450, view.view.getCenter().y - 265 + overHead.UIOffset);
    window.draw(overHead.LevelDes);
    
    overHead.DeathSpr.setPosition(view.view.getCenter().x + 380,view.view.getCenter().y - 320 + overHead.UIOffset);
    window.draw(overHead.DeathSpr);
    
    const string playerDeathString = to_string(player.death);
    overHead.DeathCount.setFont(heavy);
    overHead.DeathCount.setCharacterSize(32);
    if(overHead.DeathString != playerDeathString){
        overHead.DeathCount.setString(playerDeathString);
        overHead.DeathString = playerDeathString;
        overHead.DeathCountRedColorClock.restart();
    }
    if(overHead.DeathCountRedColorClock.getElapsedTime().asSeconds() < 0.5 && !overHead.firstTime) {
        overHead.DeathCount.setFillColor(Color(171, 0, 33));
    }
    else overHead.DeathCount.setFillColor(Color::White);
    
    overHead.DeathCount.setOrigin(0, 0);
    overHead.DeathCount.setPosition(view.view.getCenter().x + 340  - ((playerDeathString.length() - 1)*16), view.view.getCenter().y - 312 + overHead.UIOffset);
    window.draw(overHead.DeathCount);
    
    overHead.TimeSpr.setPosition(view.view.getCenter().x + 380,view.view.getCenter().y - 250 + overHead.UIOffset);
    window.draw(overHead.TimeSpr);
    
    
    Text Time;
    Time.setFont(heavy);
    Time.setCharacterSize(32);
    string TimeString = "";
    
    if(!player.pause) GlobalDisplayTime += GlobalClock.restart();
    else GlobalClock.restart();
    
    if(GlobalDisplayTime.asSeconds() / 60 < 10) TimeString += "0";
    TimeString += to_string(int(GlobalDisplayTime.asSeconds() / 60)) + ":";
    
    if(int(GlobalDisplayTime.asSeconds()) % 60 < 10) TimeString += "0";
    TimeString += to_string(int(GlobalDisplayTime.asSeconds()) % 60) + ".";
    
    if(int(GlobalDisplayTime.asMilliseconds() / 10) % 100 < 10) TimeString += "0";
    TimeString += to_string(int(GlobalDisplayTime.asMilliseconds() / 10) % 100);
    Time.setString(TimeString);
    Time.setOrigin(0, 0);
    Time.setPosition(view.view.getCenter().x + 230,view.view.getCenter().y - 245 + overHead.UIOffset);
    
    if(GreenTimeHighlighter.getElapsedTime().asSeconds() <= 1 && GreenTimeHighlighter.getElapsedTime().asSeconds() > 0) Time.setFillColor(Color::Green);
    else Time.setFillColor(Color::White);
    
    window.draw(Time);
    
    //Draw the Key UI
    if(!(player.onLevel == "AutomaticDoor")){
        if(!map.keyFound){
            overHead.KeyNotFound.setScale(0.17,0.17);
            overHead.KeyNotFound.setPosition(view.view.getCenter().x + 380,view.view.getCenter().y - 190 + overHead.UIOffset);
            window.draw(overHead.KeyNotFound);
            overHead.KeyFoundFlash.restart();
        }
        else{
            if(overHead.KeyFoundFlash.getElapsedTime().asSeconds() > 0.1 && overHead.FlashCount < 5){
                overHead.Flash = !overHead.Flash;
                ++overHead.FlashCount;
                overHead.KeyFoundFlash.restart();
            }
            if(overHead.FlashCount >= 5 || overHead.Flash){
                overHead.KeyFound.setScale(0.17,0.17);
                overHead.KeyFound.setPosition(view.view.getCenter().x + 380,view.view.getCenter().y - 190 + overHead.UIOffset);
                window.draw(overHead.KeyFound);
            }
            else{
                overHead.KeyNotFound.setScale(0.17,0.17);
                overHead.KeyNotFound.setPosition(view.view.getCenter().x + 380,view.view.getCenter().y - 190 + overHead.UIOffset);
                window.draw(overHead.KeyNotFound);
            }
        }
    }
    
    
    
    if(overHead.DeathCountRedColorClock.getElapsedTime().asSeconds() < 0.5 && !overHead.firstTime){
        RectangleShape WhiteRect;
        WhiteRect.setSize(Vector2f(1920,1080));
        WhiteRect.setFillColor(Color(255, 255, 255,255 - overHead.DeathCountRedColorClock.getElapsedTime().asSeconds()*510));
        window.draw(WhiteRect);
    }
    
    //Allow Death Flash Screen
    if(overHead.DeathCountRedColorClock.getElapsedTime().asSeconds() >= 0.5 && overHead.firstTime) overHead.firstTime = false;
    
    //User Resize Check
    if(window.getSize() != Vector2u(1280,960)) window.setSize(Vector2u(1280,960));
}

bool UI::levelCompleteFlashScreen(){
    player.velocity.first = 4;
    if(levelComplete.clock.getElapsedTime().asMilliseconds() >= 1.0 && levelComplete.alpha < 256){
        if(levelComplete.alpha < 50) overHead.UIOffset += 3;
        else overHead.UIOffset -= levelComplete.alpha * 0.2;
        levelComplete.alpha += 5;
        levelComplete.WhiteRectangle.setFillColor(Color(255,255,255,levelComplete.alpha > 255? 255 : levelComplete.alpha));
        levelComplete.clock.restart();
    }
    else if(levelComplete.alpha >= 256) return true;
    window.draw(levelComplete.WhiteRectangle);
    return false;
}

void UI::interruptCheck(Event& event,bool& forceEnd,const int LevelNumber){
    if(event.type == Event::Closed){
        temporarySave(GlobalDisplayTime, player.death, LevelNumber);
        window.close();
    }
    if(event.type == Event::LostFocus) player.pause = true;
    if(event.type == sf::Event::EventType::KeyPressed){
        if(event.key.code == sf::Keyboard::R && player.onLevel != "TextMode"){
            player.SpritePosition = Vector2f(100,900);
            player.flying = false;
            player.velocity = {0,0};
            ++player.death;
            DeathSFX.play();
        }
        if(event.key.code == Keyboard::Escape){
            player.pause = !player.pause;
            if(!player.pause) GlobalClock.restart();
        }
        else if(player.pause && event.key.code == Keyboard::BackSpace){
            temporarySave(GlobalDisplayTime, player.death, LevelNumber);
            forceEnd = true;
        }
    }
}

void UI::pauseMenu(){
    if(pause.animationClock.getElapsedTime().asMilliseconds() >= 1 && pause.menuOffset + pause.menuOffset * 0.03 > -300){
        pause.menuOffset -= 25;
        pause.animationClock.restart();
    }
    else if (pause.menuOffset < -300){
        pause.menuOffset = -300;
    }
    
    PauseTitle.setPosition(view.view.getCenter().x - 450.2, view.view.getCenter().y - 600 - pause.menuOffset);
    Back.setPosition(view.view.getCenter().x - 450.2, view.view.getCenter().y - 300 - pause.menuOffset);
    Continue.setPosition(view.view.getCenter().x - 450.2, view.view.getCenter().y - 400 - pause.menuOffset);
    
    
    window.draw(WhiteRect);
    window.draw(PauseTitle);
    window.draw(Back);
    window.draw(Continue);
}

bool UI::PIText(){
    Text pi;
    const string piNumber = "31415926535";
    int piDigit = piNumber[pivot] - '0';
    Keyboard::Key piKeyPress = Keyboard::Key(26 + piDigit);
    if((Keyboard::isKeyPressed(Keyboard::Key(26 + piDigit)) || Keyboard::isKeyPressed(Keyboard::Key(75 + piDigit))) && pivot < 11) ++pivot;
    string displayPI = "";
    int cnt = 0;
    for(int i = 0;i < pivot;++i){
        displayPI += piNumber[i];
        if(i == 0) displayPI += ".";
    }
    pi.setFont(heavy);
    pi.setCharacterSize(72);
    pi.setString(displayPI);
    pi.setFillColor(pivot == 11? Color::Green : Color(128, 166, 201));
    pi.setPosition(view.view.getCenter().x - 250, view.view.getCenter().y - 150 + overHead.UIOffset);
    window.draw(pi);
    if(pivot == 11) return true;
    else return false;
}

bool UI::rightClick(Vector2f center){
    Text doorOpen;
    doorOpen.setFont(heavy);
    doorOpen.setCharacterSize(28);
    doorOpen.setString("DOOR OPENED");
    doorOpen.setOutlineThickness(5);
    center = center - Vector2f(640,480);
    center = Vector2f(center.x*0.9*(float(512)/float(640)),center.y*0.9*(float(384)/float(480))) + view.view.getCenter();
    doorOpen.setPosition(center);
    
    if(255 - rightClickCircle.getElapsedTime().asMilliseconds() / 5 > 0){
        doorOpen.setFillColor(Color(255,255,255,255 - rightClickCircle.getElapsedTime().asMilliseconds() / 5));
        doorOpen.setOutlineColor(Color(255, 153, 153,255 - rightClickCircle.getElapsedTime().asMilliseconds() / 5));
        window.draw(doorOpen);
        return true;
    }
    else  return false;
}

bool cmpTime(const pair<TIME,string>& a,const pair<TIME,string>& b){
    if(a.first.min == b.first.min){
        if(a.first.sec == b.first.sec) return a.first.mili < b.first.mili;
        else return a.first.sec < b.first.sec;
    }
    else return a.first.min < b.first.min;
}


void menuUI::scoreboardDraw(){
    int cnt = 0;
    window.draw(ScoreBoardTitle);
    for(auto a : scoreInfo){
        ++cnt;
        Text Name;
        Name.setFont(heavy);
        Name.setString(a.second);
        Name.setFillColor(cnt == 1? Color::Yellow: Color::White);
        Name.setCharacterSize(56);
        Name.setScale(0.5,0.5);
        Name.setPosition(1250, 120 + (cnt*50));
        
        Text Position;
        Position.setFont(heavy);
        Position.setString(to_string(cnt));
        Position.setFillColor(cnt == 1? Color::Yellow: Color::White);
        Position.setCharacterSize(56);
        Position.setScale(0.5,0.5);
        Position.setPosition(1150, 120 + (cnt*50));
        
        Text Time;
        Time.setFont(heavy);
        string timeString = "";
        if(a.first.min < 10) timeString += "0";
        timeString += to_string(a.first.min) + ":";
        if(a.first.sec < 10) timeString += "0";
        timeString += to_string(a.first.sec) + ".";
        if(a.first.mili < 10) timeString += "0";
        timeString += to_string(a.first.mili);
        Time.setString(timeString);
        Time.setFillColor(cnt == 1? Color::Yellow: Color::White);
        Time.setCharacterSize(56);
        Time.setScale(0.5,0.5);
        Time.setPosition(1730, 120 + (cnt*50));
        
        window.draw(Name);
        window.draw(Position);
        window.draw(Time);
        if(cnt == 10) break;
    }
    if(cnt == 0) window.draw(NoScore);
    window.draw(EscToMenu);
}

void menuUI::draw(int levelJump){
    if(!isScoreFileExist()) createScoreFile();
    Event event;
    Music menuMusic;
    menuMusic.openFromFile("Resources/Sounds/Deuces.flac");
    menuMusic.setLoop(true);
    menuMusic.play();
    if(levelJump == -1) ContinueAtLevel.setString("Enter Your Name");
    else if(levelJump == 0) ContinueAtLevel.setString("Start a New Game");
    else ContinueAtLevel.setString("Continue at Level " + to_string(levelJump));
    while(window.isOpen()){
        bool exit = false;
        bool keyboard = false;
        while(window.isOpen() && !exit){
            while(window.pollEvent(event)){
                if(event.type == Event::Closed){
                    window.close();
                }
                else if(event.type == Event::KeyPressed){
                    if(event.key.code == Keyboard::Up && menuPivot > 0) --menuPivot;
                    else if(event.key.code == Keyboard::Down && menuPivot < 2) ++menuPivot;
                    else if(event.key.code == Keyboard::Enter) exit = true;
                    keyboard = true;
                }
                else if(event.type == Event::MouseMoved){
                    Vector2i MousePosition = Mouse::getPosition(window);
                    FloatRect mousePos = getMouseRect(MousePosition,view);
                    if(Play.getGlobalBounds().intersects(mousePos)){
                        menuPivot = 0;
                        keyboard = false;
                    }
                    else if(Score.getGlobalBounds().intersects(mousePos)){
                        menuPivot = 1;
                        keyboard = false;
                    }
                    else if(Tutorial.getGlobalBounds().intersects(mousePos)){
                        menuPivot = 2;
                        keyboard = false;
                    }
                    else if(!keyboard) menuPivot = -1;
                }
            }
            
            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                Vector2i MousePosition = Mouse::getPosition(window);
                FloatRect mousePos = getMouseRect(MousePosition,view);
                if(Play.getGlobalBounds().intersects(mousePos) ||
                       Score.getGlobalBounds().intersects(mousePos) ||
                       Tutorial.getGlobalBounds().intersects(mousePos)) exit = true;
            }
            
            if(RunningAnimation.getElapsedTime().asMilliseconds() >= 20){
                if(RunningMask.left >= 6500) RunningMask.left = 0;
                else RunningMask.left += 500;
                Running.setTextureRect(RunningMask);
                RunningAnimation.restart();
            }
            
            if(view.getCenter().x > 512){
                view.move(-64,0);
                BG.move(-30,0);
            }
            if(view.getCenter().y > 384){
                view.move(0,-64);
                BG.move(0,-30);
            }
            
            window.clear();
            window.setView(view);
            window.draw(BG);
            window.draw(Main);
            window.draw(Running);
            window.draw(menuPivot == 0? Play : PlayIdle);
            if(menuPivot == 0) window.draw(ContinueAtLevel);
            window.draw(menuPivot == 1? Score : ScoreIdle);
            window.draw(menuPivot == 2? Tutorial : TutorialIdle);
            scoreboardDraw();
            window.draw(TutorialScreen);
            window.draw(EscToMenu2);
            window.draw(Creator);
            window.display();
        }
        
        int alpha = 0;
        RectangleShape WhiteFlash;
        WhiteFlash.setSize(Vector2f(4096,3072));
        WhiteFlash.setPosition(0,0);
        WhiteFlash.setFillColor(Color::White);

        while(window.isOpen() && menuPivot == 0){
            while(window.pollEvent(event)){
                if(event.type == Event::Closed){
                    window.close();
                }
            }
            window.clear();
            alpha += 5;
            WhiteFlash.setFillColor(Color(255,255,255,alpha));
            menuMusic.setVolume(100*(float(255 - alpha)/255));
            if(alpha >= 255) return;
            BG.scale(1.03, 1.03);
            window.setView(view);
            window.draw(BG);
            window.draw(Main);
            window.draw(Running);
            window.draw(menuPivot == 0? Play : PlayIdle);
            window.draw(menuPivot == 1? Score : ScoreIdle);
            window.draw(menuPivot == 2? Tutorial : TutorialIdle);
            scoreboardDraw();
            window.draw(TutorialScreen);
            window.draw(EscToMenu2);
            window.draw(Creator);
            window.draw(WhiteFlash);
            window.display();
        }


        bool exitPivot1 = false;
        //PreRun Sorting
        if(menuPivot == 1){
            loadScoreFile();
            sort(scoreInfo.begin(),scoreInfo.end(),cmpTime);
        }

        while(window.isOpen() && menuPivot == 1 && !exitPivot1){
            while(window.pollEvent(event)){
                if(event.type == Event::Closed){
                    window.close();
                }
                if(event.type == Event::KeyPressed){
                    if(event.key.code == Keyboard::Escape) exitPivot1 = true;
                }
            }
            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                Vector2i MousePosition = Mouse::getPosition(window);
                FloatRect mouseRect = getMouseRect(MousePosition,view);
                if(EscToMenu.getGlobalBounds().intersects(mouseRect)) exitPivot1 = true;
            }
            
            
            if(view.getCenter().x < 1536){
                view.move(64,0);
                BG.move(30,0);
            }

            window.clear();
            window.setView(view);
            window.draw(BG);
            window.draw(Main);
            window.draw(Running);
            window.draw(menuPivot == 0? Play : PlayIdle);
            window.draw(menuPivot == 1? Score : ScoreIdle);
            window.draw(menuPivot == 2? Tutorial : TutorialIdle);
            scoreboardDraw();
            window.draw(TutorialScreen);
            window.draw(EscToMenu2);
            window.draw(Creator);
            window.display();
        }

        bool exitPivot2 = false;

        while(window.isOpen() && menuPivot == 2 && !exitPivot2){
            while(window.pollEvent(event)){
                if(event.type == Event::Closed){
                    window.close();
                }
                if(event.type == Event::KeyPressed){
                    if(event.key.code == Keyboard::Escape) exitPivot2 = true;
                }
            }
            
            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                Vector2i MousePosition = Mouse::getPosition(window);
                FloatRect mouseRect = getMouseRect(MousePosition,view);
                if(EscToMenu2.getGlobalBounds().intersects(mouseRect)) exitPivot2 = true;
            }
            
            if(view.getCenter().y < 1152){
                view.move(0,64);
                BG.move(0,30);
            }

            window.clear();
            window.setView(view);
            window.draw(BG);
            window.draw(Main);
            window.draw(Running);
            window.draw(menuPivot == 0? Play : PlayIdle);
            window.draw(menuPivot == 1? Score : ScoreIdle);
            window.draw(menuPivot == 2? Tutorial : TutorialIdle);
            scoreboardDraw();
            window.draw(TutorialScreen);
            window.draw(EscToMenu2);
            window.draw(Creator);
            window.display();
        }
   }
}

int loadTemporarySave(Time& time,unsigned int& death){
    ifstream file;
    file.open("Saves/temporary.saves");
    if(!file.is_open()) return 0;
    else{
        float tt;
        int level;
        file >> tt >> death >> level;
        time = seconds(tt);
        file.close();
        return level;
    }
}

bool isScoreFileExist(){
    ifstream checkFile;
    checkFile.open("Saves/Scores.saves");
    if(checkFile.is_open()){
        checkFile.close();
        return true;
    }
    else return false;
}

bool createScoreFile(){
    ofstream createFile;
    createFile.open("Saves/Scores.saves");
    if(createFile.is_open()){
        createFile.close();
        return true;
    }
    else return true;
}

bool menuUI::loadScoreFile(){
    ifstream load;
    load.open("Saves/Scores.saves");
    scoreInfo = empty;
    while(!load.eof()){
        string name = "";
        TIME tt;
        getline(load,name);
        if(name == "") continue;
        load >> tt.min >> tt.sec >> tt.mili;
        scoreInfo.push_back({tt,name});
    }
    load.close();
    return true;
}

void temporarySave(const Time& playerTime,const int Death,const int Level){
    ofstream tempFile;
    tempFile.open("Saves/temporary.saves");
    tempFile << playerTime.asSeconds() << " " << Death << " " << Level;
    tempFile.close();
    return;
}

int UI::textModeDraw(string& cmd,bool& enter){
    command.setString(cmd);
    CommandWindow.setPosition(view.view.getCenter().x - 512, view.view.getCenter().y + 84);
    int cnt = 0;
    int returnValue = -1;
    window.draw(CommandWindow);
    for(auto it = commandView.rbegin(); it != commandView.rend();++it){
        if(cnt >= 6) break;
        command.setString(*it);
        command.setPosition(view.view.getCenter().x - 440,view.view.getCenter().y + 250 - (30*cnt++));
        window.draw(command);
    }
    command.setString(">> " + cmd + "_");
    command.setPosition(view.view.getCenter().x - 440,view.view.getCenter().y + 300);
    window.draw(command);
    
    if(enter){
        commandView.push_back(">> " + cmd);
        returnValue = textModeCommandProcess(cmd);
        cmd = "";
        enter = false;
    }
    return returnValue;
}

int UI::textModeCommandProcess(string cmd){
    auto it = cmd.begin();
    string cmdA = "";
    int returnValue = -1;
    for(;it != cmd.end();++it){
        if(*it == ' ') break;
        cmdA += *it;
    }
    if(cmdA == "help"){
        commandView.push_back("USAGE: ");
        commandView.push_back("goto [Place]\tMove player to the place specified.");
        commandView.push_back("\t\t\t\tList of Places: 'key', 'door', 'exit'");
        commandView.push_back("reset\t\t   Reset player.");
    }
    else if(cmdA == "goto"){
        string cmdB = "";
        for(;it != cmd.end();++it){
            if(*it == ' ') continue;
            cmdB += *it;
        }
        if(cmdB == "key") returnValue = 0;
        else if(cmdB == "door") returnValue = 1;
        else if(cmdB == "exit"){
            if(!map.keyFound) commandView.push_back(cmdB + ": Place not permitted");
            else returnValue = 2;
        }
        else commandView.push_back("Unable to find place: " + cmdB);
    }
    else if(cmdA == "reset"){
        player.SpritePosition = Vector2f(100,900);
        player.flying = false;
        player.velocity = {0,0};
        ++player.death;
    }
    else commandView.push_back(cmdA + ": Command not found");
    
    return returnValue;
}
