#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>    
#include <chrono>
using namespace std; 


enum class CollisionDirection {
    None, Top, Bottom, Left, Right
};


void killing(sf::RenderWindow &gygamewindow,sf::Sprite &player,sf::Sprite &map,float &x,float &y,double &xSpeed,double &ySpeed);
bool canrungame();
bool isHit(const sf::Sprite& sprite1, const sf::Sprite& sprite2, const sf::Color& targetColor, int numThreads);
set<CollisionDirection> checkCollisionDirection(const sf::Sprite& sprite1, const sf::Sprite& sprite2, const sf::Color& targetColor, int numThreads);

int main()
{
    sf::Music gamemusic;
    int level=0; 
    float x=0,y=0; 
    double xSpeed = 0,ySpeed = 0;
    bool end=false,canjump=true;
    system("color 2");
    cout<<"________________________________________________________________________________________________________________________\n游戏名称：耿德飙跑酷\t游戏引擎：SFML\t引擎版本：2.5.1\t游戏版本：0.0(beta)\n作者：上古米歇尔（bilibili:上古米歇尔-果园工作室,Github:GY-GZW）\t所属工作室：果园工作室（官网：https://gy-gzw.github.io/）\n你好，玩家，欢迎游玩本游戏，作者是一个初中生，BUG修复可能较慢，请您谅解，如遇到任何BUG请提交到GitHub\n最后，请注意：本游戏为MIT开源协议，请严格遵守协议，祝您游玩愉快\n________________________________________________________________________________________________________________________\n正在检查游戏资源完整性，请稍后:\n";
    if(!canrungame()){
        cout<<"游戏资源缺失，请检查以上提到的缺失文件\n";
        cout<<"按任意键退出游戏...";
        system("pause>nul");
        return -3;
    }else{
        cout<<"游戏资源完整,可以启动\n________________________________________________________________________________________________________________________\n锟角凤拷锟斤拷锟斤拷锟较?(y/n):";
    }
    gamemusic.openFromFile("wav/start.wav");
    gamemusic.setLoop(true);
    gamemusic.play();
    string* a = new string;
    cin>>*a;
    if(!(*a=="y"||*a=="Y"||*a=="yes"||*a=="Yes"||*a=="YES")){
        return 0;
    }
    delete a;
    sf::VideoMode videoMode(800, 600);
    sf::RenderWindow gygamewindow(videoMode, "gygame");
    gygamewindow.setFramerateLimit(60);
    sf::Texture mapicon, playericon;
    playericon.loadFromFile("icon/player_right.png");
    mapicon.loadFromFile("icon/SFML.png");
    sf::Sprite map(mapicon),player(playericon);
    map.setPosition(0.0f, 0.0f); 
    player.setPosition(x, y); 
    gygamewindow.clear(sf::Color::Black);
    gygamewindow.draw(map);
    gygamewindow.display();
    this_thread::sleep_for(chrono::seconds(5));
    mapicon.loadFromFile("icon/gy.png");
    gygamewindow.clear(sf::Color::Black);
    gygamewindow.draw(map);
    gygamewindow.display();
    this_thread::sleep_for(chrono::seconds(5));
    mapicon.loadFromFile("icon/level_"+to_string(level)+".png");
    gamemusic.stop();
    gamemusic.openFromFile("wav/game.wav");
    gamemusic.play();
    while (gygamewindow.isOpen()) {

        sf::Event event;
        while (gygamewindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gygamewindow.close();
            }
        }

        std::set<CollisionDirection> directions = checkCollisionDirection(player, map, sf::Color(255, 0, 0), 30);
        bool top = false, bottom = false, left = false, right = false;
        if (!directions.empty()) {
            for (const auto& direction : directions) {
                switch (direction) {
                    case CollisionDirection::Top:
                        top = true;
                        break;
                    case CollisionDirection::Bottom:
                        bottom = true;
                        break;
                    case CollisionDirection::Left:
                        left = true;
                        break;
                    case CollisionDirection::Right:
                        right = true;
                        break;
                };
            }
        }

        if(!bottom){
            ySpeed+=1;
        }
        if (isHit(player, map,sf::Color(255,0,0),10)) {
            killing(gygamewindow, player, map,x, y, xSpeed, ySpeed);
        }else {
            if (top&left&right) {
                y += 1;
                ySpeed = 0;
            }else { 
                if (bottom&left&right) {
                    y -= 1;
                    ySpeed = 0;
                }else {
                    if (top&left) {
                        xSpeed = 3;
                        ySpeed = 3;
                    }else {
                        if (top&right) {
                            xSpeed = -3;
                            ySpeed = 3;
                        }else {
                            if (bottom&(left||right)) {
                                xSpeed = 0;
                                ySpeed = 0;
                            }else { 
                                if (right) {
                                    xSpeed = -3;
                                    ySpeed = -3;
                                }else {
                                    if (left) {
                                        xSpeed = 3;
                                        ySpeed = -3;
                                    }else {
                                        if (bottom) {
                                            ySpeed = 0;
                                            canjump=true;
                                        }
                                        ySpeed*=0.9;
                                        xSpeed*=0.9;
                                        if ((event.key.code == sf::Keyboard::W||event.key.code == sf::Keyboard::Up||event.key.code == sf::Keyboard::Space)&&canjump) {
                                            ySpeed = -5;
                                            canjump=false;
                                        }
                                        if ((event.key.code == sf::Keyboard::A||event.key.code == sf::Keyboard::Left)&&xSpeed>0&&!left) {
                                            xSpeed = -10;
                                            playericon.loadFromFile("icon/player_left.png");
                                        }
                                        if ((event.key.code == sf::Keyboard::D||event.key.code == sf::Keyboard::Right)&&xSpeed<800&&!right) {
                                            xSpeed = 10;
                                            playericon.loadFromFile("icon/player_right.png");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if(x>760&&level<11) {
            level++;
            mapicon.loadFromFile("icon/level_"+to_string(level)+".png");
            x=0;
            y=0;
        }
        if(x>790&&level==11){
            end=true;
            break;
        }
        if(x<0){
            x=0;
            xSpeed=0;
        }else{
            if(y>600){
                killing(gygamewindow, player, map,x, y, xSpeed, ySpeed);
            }else{
                x+=xSpeed;
                y+=ySpeed;
            }
        }
        player.setPosition(x, y);
        gygamewindow.clear(sf::Color(128, 128, 128));
        gygamewindow.draw(map);
        gygamewindow.draw(player);
        gygamewindow.display();
    }
    if(end) {
        gygamewindow.close();
        cout<<"恭喜你已通关本游戏，未来可能会出续作，敬请期待\n";
    }
    cout<<"按任意键退出游戏...";
    system("pause>nul");
    return 0;
}

void killing(sf::RenderWindow &gygamewindow,sf::Sprite &player,sf::Sprite &map,float &x,float &y,double &xSpeed,double &ySpeed){
    xSpeed=0;
    ySpeed=0;
    for(int i=0;i<10000;i++){
        gygamewindow.clear(sf::Color(128, 128, 128));
        x+=0.001;
        y+=0.001;
        player.setPosition(x, y);
        gygamewindow.draw(map);
        gygamewindow.draw(player);
        gygamewindow.display();
    }
    x=0,y=0;
}

bool canrungame(){
    sf::Texture mapicon;
    sf::Music music;
    bool canrun=true;
    if (!mapicon.loadFromFile("icon/SFML.png")) {
        cout<<"icon/SFML.png资源缺失\n";
        canrun=false;
    }else{
        cout<<"icon/SFML.png资源完整\n";
    }
    if (!mapicon.loadFromFile("icon/player_left.png")) {
        cout<<"icon/player_left.png资源缺失\n";
        canrun=false;
    }else{
        cout<<"icon/player_left.png资源完整\n";
    }
    if (!mapicon.loadFromFile("icon/player_right.png")) {
        cout<<"icon/player_right.png资源缺失\n";
    }else{
        cout<<"icon/player_right.png资源完整\n";
    }
    if (!mapicon.loadFromFile("icon/gy.png")) {
        cout<<"icon/gy.png资源缺失\n";
        canrun=false;
    }else{
        cout<<"icon/gy.png资源完整\n";
    }
    if (!mapicon.loadFromFile("icon/level_0.png")) {
        cout<<"icon/level_0.png资源缺失\n";
        canrun=false;
    }else{
        cout<<"icon/level_0.png资源完整\n";
    }
    if (!mapicon.loadFromFile("icon/level_1.png")) { 
        cout<<"icon/level_1.png资源缺失\n";
        canrun=false;
    }else{
        cout<<"icon/level_1.png资源完整\n";
    }
    if (!mapicon.loadFromFile("icon/level_2.png")) { 
        cout<<"icon/level_2.png资源缺失\n";
        canrun=false;
    }else{
        cout<<"icon/level_2.png资源完整\n";
    }
    if (!mapicon.loadFromFile("icon/level_3.png")) { 
        cout<<"icon/level_3.png资源缺失\n";
        canrun=false;
    }else{
        cout<<"icon/level_3.png资源完整\n";
    }
    if (!mapicon.loadFromFile("icon/level_4.png")) { 
        cout<<"icon/level_4.png资源缺失\n";
        canrun=false;
    }else{
        cout<<"icon/level_4.png资源完整\n";
    }
    if (!mapicon.loadFromFile("icon/level_5.png")) { 
        cout<<"icon/level_5.png资源缺失\n";
        canrun=false;
    }else{
        cout<<"icon/level_5.png资源完整\n";
    }
    if (!mapicon.loadFromFile("icon/level_6.png")) { 
        cout<<"icon/level_6.png资源缺失\n";
        canrun=false;
    }else{
        cout<<"icon/level_6.png资源完整\n";
    }
    if (!mapicon.loadFromFile("icon/level_7.png")) { 
        cout<<"icon/level_7.png资源缺失\n";
        canrun=false;
    }else{
        cout<<"icon/level_7.png资源完整\n";
    }
    if (!mapicon.loadFromFile("icon/level_8.png")) { 
        cout<<"icon/level_8.png资源缺失\n";
        canrun=false;
    }else{
        cout<<"icon/level_8.png资源完整\n";
    }
    if (!mapicon.loadFromFile("icon/level_9.png")) { 
        cout<<"icon/level_9.png资源缺失\n";
        canrun=false;
    }else{
        cout<<"icon/level_9.png资源完整\n";
    }
    if (!mapicon.loadFromFile("icon/level_10.png")) { 
        cout<<"icon/level_10.png资源缺失\n";
        canrun=false;
    }else{
        cout<<"icon/level_10.png资源完整\n";
    }
    if (!mapicon.loadFromFile("icon/level_11.png")) { 
        cout<<"icon/level_11.png资源缺失\n";
        canrun=false;
    }else{
        cout<<"icon/level_11.png资源完整\n";
    }
    if (!music.openFromFile("wav/start.wav")) {
        cout<<"wav/start.wav资源缺失\n";
        canrun=false;
    }else{
        cout<<"wav/start.wav资源完整\n";
    }
    if (!music.openFromFile("wav/game.wav")) {
        cout<<"wav/game.wav资源缺失\n";
        canrun=false;
    }
    else{
        cout<<"wav/game.wav资源完整\n";
    }
    return canrun;
}

bool isHit(const sf::Sprite& sprite1, const sf::Sprite& sprite2, const sf::Color& targetColor, int numThreads) {
    sf::FloatRect bounds1 = sprite1.getGlobalBounds();
    sf::FloatRect bounds2 = sprite2.getGlobalBounds();

    if (!bounds1.intersects(bounds2)) {
        return false;
    }

    const sf::Texture* texture1 = sprite1.getTexture();
    const sf::Texture* texture2 = sprite2.getTexture();
    if (!texture1 || !texture2) {
        return false;
    }

    float left = bounds1.left;
    float top = bounds1.top;
    float right = bounds1.left + bounds1.width;
    float bottom = bounds1.top + bounds1.height;

    int totalRows = static_cast<int>(bottom - top);
    int rowsPerThread = totalRows / numThreads;

    std::vector<std::thread> threads;
    std::mutex mutex;
    bool found = false;

    auto task = [&](int startRow, int endRow) {
        for (int y = startRow; y < endRow; ++y) {
            if (found) {
                return;
            }

            for (float x = left; x < right; x += 1) {
                sf::Vector2f globalPos(x, y + top);
                sf::Vector2i localPos1 = sf::Vector2i(sprite1.getInverseTransform().transformPoint(globalPos));
                sf::Vector2i localPos2 = sf::Vector2i(sprite2.getInverseTransform().transformPoint(globalPos));

                if (localPos1.x >= 0 && localPos1.y >= 0 && localPos1.x < texture1->getSize().x && localPos1.y < texture1->getSize().y &&
                    localPos2.x >= 0 && localPos2.y >= 0 && localPos2.x < texture2->getSize().x && localPos2.y < texture2->getSize().y) {
                    sf::Color pixelColor1 = texture1->copyToImage().getPixel(localPos1.x, localPos1.y);
                    sf::Color pixelColor2 = texture2->copyToImage().getPixel(localPos2.x, localPos2.y);

                    if (pixelColor1 == targetColor || pixelColor2 == targetColor) {
                        std::lock_guard<std::mutex> lock(mutex);
                        found = true;
                        return;
                    }
                }
            }
        }
    };

    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? totalRows : (i + 1) * rowsPerThread;
        threads.emplace_back(task, startRow, endRow);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return found;
}

std::set<CollisionDirection> checkCollisionDirection(const sf::Sprite& sprite1, const sf::Sprite& sprite2, const sf::Color& targetColor, int numThreads) {
    std::set<CollisionDirection> directions;
    sf::FloatRect bounds1 = sprite1.getGlobalBounds();
    sf::FloatRect bounds2 = sprite2.getGlobalBounds();

    if (!bounds1.intersects(bounds2)) {
        return directions;
    }

    const sf::Texture* texture1 = sprite1.getTexture();
    const sf::Texture* texture2 = sprite2.getTexture();
    if (!texture1 || !texture2) {
        return directions;
    }

    float left = bounds1.left;
    float top = bounds1.top;
    float right = bounds1.left + bounds1.width;
    float bottom = bounds1.top + bounds1.height;

    int totalRows = static_cast<int>(bottom - top);
    int rowsPerThread = totalRows / numThreads;

    std::vector<std::thread> threads;
    std::mutex mutex;
    bool found = false;

    auto task = [&](int startRow, int endRow) {
        for (int y = startRow; y < endRow; ++y) {
            if (found) {
                return;
            }

            for (float x = left; x < right; x += 1) {
                sf::Vector2f globalPos(x, y + top);
                sf::Vector2i localPos1 = sf::Vector2i(sprite1.getInverseTransform().transformPoint(globalPos));
                sf::Vector2i localPos2 = sf::Vector2i(sprite2.getInverseTransform().transformPoint(globalPos));

                if (localPos1.x >= 0 && localPos1.y >= 0 && localPos1.x < texture1->getSize().x && localPos1.y < texture1->getSize().y &&
                    localPos2.x >= 0 && localPos2.y >= 0 && localPos2.x < texture2->getSize().x && localPos2.y < texture2->getSize().y) {
                    sf::Color pixelColor1 = texture1->copyToImage().getPixel(localPos1.x, localPos1.y);
                    sf::Color pixelColor2 = texture2->copyToImage().getPixel(localPos2.x, localPos2.y);

                    if (pixelColor1 == targetColor || pixelColor2 == targetColor) {
                        std::lock_guard<std::mutex> lock(mutex);
                        if (!found) {
                            if (y + top < bounds1.top + bounds1.height / 2) {
                                directions.insert(CollisionDirection::Top);
                            } else {
                                directions.insert(CollisionDirection::Bottom);
                            }

                            if (x < bounds1.left + bounds1.width / 2) {
                                directions.insert(CollisionDirection::Left);
                            } else {
                                directions.insert(CollisionDirection::Right);
                            }

                            found = true;
                        }
                        return;
                    }
                }
            }
        }
    };

    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? totalRows : (i + 1) * rowsPerThread;
        threads.emplace_back(task, startRow, endRow);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return directions;
}