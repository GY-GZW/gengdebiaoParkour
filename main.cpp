//����ͷ�ļ�
#include <SFML/Graphics.hpp> //SFMLͼ�ο�
#include <SFML/Audio.hpp> //SFML��Ƶ��
#include <bits/stdc++.h> //C++��׼��

//ʹ�������ռ�
using namespace std; 


enum class CollisionDirection {
    None, Top, Bottom, Left, Right
};

//����Ԥ����
void killing(sf::RenderWindow &gygamewindow,sf::Sprite &player,sf::Sprite &map,float &x,float &y,double &xSpeed,double &ySpeed);
bool canrungame();
bool isHit(const sf::Sprite& sprite1, const sf::Sprite& sprite2, const sf::Color& targetColor);
set<CollisionDirection> checkCollisionDirection(const sf::Sprite& sprite1, const sf::Sprite& sprite2, const sf::Color& targetColor);

int main()
{
    sf::Music gamemusic;
    int level=0; 
    float x=0,y=0; 
    double xSpeed = 0,ySpeed = 0;
    bool end=false,canjump=true;
    system("color 2");
    cout<<"________________________________________________________________________________________________________________________\n��Ϸ���ƣ�������ܿ�\t��Ϸ���棺SFML\t����汾��2.5.1\t��Ϸ�汾��0.5(beta)\n���ߣ��Ϲ���Ъ����bilibili:�Ϲ���Ъ��-��԰������,Github:GY-GZW��\t���������ң���԰�����ң�������https://gy-gzw.github.io/��\n��ã���ң���ӭ���汾��Ϸ��������һ����������BUG�޸����ܽ����������½⣬�������κ�BUG���ύ��GitHub\n�����ע�⣺����ϷΪMIT��ԴЭ�飬���ϸ�����Э�飬ף���������\n________________________________________________________________________________________________________________________\n���ڼ����Ϸ��Դ�����ԣ����Ժ�:\n";
    if(!canrungame()){
        cout<<"��Ϸ��Դȱʧ�����������ᵽ��ȱʧ�ļ�\n";
        cout<<"��������˳���Ϸ...";
        system("pause>nul");
        return -3;
    }else{
        cout<<"��Ϸ��Դ����,��������\n________________________________________________________________________________________________________________________\n�Ƿ������Ϸ(y/n):";
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
    y=200;
    while (gygamewindow.isOpen()) {

        sf::Event event;
        while (gygamewindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gygamewindow.close();
            }
        }

        std::set<CollisionDirection> directions = checkCollisionDirection(player, map, sf::Color(255, 0, 0));
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
        //cout<<"isHit:"<<isHit(player, map,sf::Color(0,0,0))<<"top:"<<top<<"bottom:"<<bottom<<"left:"<<left<<"right:"<<right<<endl;//���Դ���
        if(!bottom){
            ySpeed+=5;
        }
        if (isHit(player, map,sf::Color(255,0,0))) {
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
            y=200;
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
        cout<<"��ϲ����ͨ�ر���Ϸ��δ�����ܻ�������������ڴ�\n";
    }
    cout<<"��������˳���Ϸ...";
    system("pause>nul");
    gamemusic.stop();
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
        cout<<"icon/SFML.png��Դȱʧ\n";
        canrun=false;
    }else{
        cout<<"icon/SFML.png��Դ����\n";
    }
    if (!mapicon.loadFromFile("icon/player_left.png")) {
        cout<<"icon/player_left.png��Դȱʧ\n";
        canrun=false;
    }else{
        cout<<"icon/player_left.png��Դ����\n";
    }
    if (!mapicon.loadFromFile("icon/player_right.png")) {
        cout<<"icon/player_right.png��Դȱʧ\n";
    }else{
        cout<<"icon/player_right.png��Դ����\n";
    }
    if (!mapicon.loadFromFile("icon/gy.png")) {
        cout<<"icon/gy.png��Դȱʧ\n";
        canrun=false;
    }else{
        cout<<"icon/gy.png��Դ����\n";
    }
    if (!mapicon.loadFromFile("icon/level_0.png")) {
        cout<<"icon/level_0.png��Դȱʧ\n";
        canrun=false;
    }else{
        cout<<"icon/level_0.png��Դ����\n";
    }
    if (!mapicon.loadFromFile("icon/level_1.png")) { 
        cout<<"icon/level_1.png��Դȱʧ\n";
        canrun=false;
    }else{
        cout<<"icon/level_1.png��Դ����\n";
    }
    if (!mapicon.loadFromFile("icon/level_2.png")) { 
        cout<<"icon/level_2.png��Դȱʧ\n";
        canrun=false;
    }else{
        cout<<"icon/level_2.png��Դ����\n";
    }
    if (!mapicon.loadFromFile("icon/level_3.png")) { 
        cout<<"icon/level_3.png��Դȱʧ\n";
        canrun=false;
    }else{
        cout<<"icon/level_3.png��Դ����\n";
    }
    if (!mapicon.loadFromFile("icon/level_4.png")) { 
        cout<<"icon/level_4.png��Դȱʧ\n";
        canrun=false;
    }else{
        cout<<"icon/level_4.png��Դ����\n";
    }
    if (!mapicon.loadFromFile("icon/level_5.png")) { 
        cout<<"icon/level_5.png��Դȱʧ\n";
        canrun=false;
    }else{
        cout<<"icon/level_5.png��Դ����\n";
    }
    if (!mapicon.loadFromFile("icon/level_6.png")) { 
        cout<<"icon/level_6.png��Դȱʧ\n";
        canrun=false;
    }else{
        cout<<"icon/level_6.png��Դ����\n";
    }
    if (!mapicon.loadFromFile("icon/level_7.png")) { 
        cout<<"icon/level_7.png��Դȱʧ\n";
        canrun=false;
    }else{
        cout<<"icon/level_7.png��Դ����\n";
    }
    if (!mapicon.loadFromFile("icon/level_8.png")) { 
        cout<<"icon/level_8.png��Դȱʧ\n";
        canrun=false;
    }else{
        cout<<"icon/level_8.png��Դ����\n";
    }
    if (!mapicon.loadFromFile("icon/level_9.png")) { 
        cout<<"icon/level_9.png��Դȱʧ\n";
        canrun=false;
    }else{
        cout<<"icon/level_9.png��Դ����\n";
    }
    if (!mapicon.loadFromFile("icon/level_10.png")) { 
        cout<<"icon/level_10.png��Դȱʧ\n";
        canrun=false;
    }else{
        cout<<"icon/level_10.png��Դ����\n";
    }
    if (!mapicon.loadFromFile("icon/level_11.png")) { 
        cout<<"icon/level_11.png��Դȱʧ\n";
        canrun=false;
    }else{
        cout<<"icon/level_11.png��Դ����\n";
    }
    if (!music.openFromFile("wav/start.wav")) {
        cout<<"wav/start.wav��Դȱʧ\n";
        canrun=false;
    }else{
        cout<<"wav/start.wav��Դ����\n";
    }
    if (!music.openFromFile("wav/game.wav")) {
        cout<<"wav/game.wav��Դȱʧ\n";
        canrun=false;
    }
    else{
        cout<<"wav/game.wav��Դ����\n";
    }
    return canrun;
}

bool isHit(const sf::Sprite& sprite1, const sf::Sprite& sprite2, const sf::Color& targetColor) {
    //return false;//����
    sf::FloatRect bounds1 = sprite1.getGlobalBounds();
    sf::FloatRect bounds2 = sprite2.getGlobalBounds();

    if (!bounds1.intersects(bounds2)) {
        return false;
    }

    const sf::Texture* texture2 = sprite2.getTexture();
    if (!texture2) {
        return false;
    }

    sf::FloatRect intersectRect = bounds1;
    intersectRect.intersects(bounds2, intersectRect);

    for (float x = intersectRect.left; x < intersectRect.left + intersectRect.width; x += 1) {
        for (float y = intersectRect.top; y < intersectRect.top + intersectRect.height; y += 1) {
            sf::Vector2f globalPos(x, y);
            sf::Vector2i localPos2 = static_cast<sf::Vector2i>(sprite2.getInverseTransform().transformPoint(globalPos));

            if (localPos2.x >= 0 && localPos2.y >= 0 && 
                localPos2.x < texture2->getSize().x && localPos2.y < texture2->getSize().y) {
                sf::Color pixelColor2 = texture2->copyToImage().getPixel(localPos2.x, localPos2.y);

                if (pixelColor2 == targetColor) {
                    return true;
                }
            }
        }
    }
    return false;
}


std::set<CollisionDirection> checkCollisionDirection(const sf::Sprite& sprite1, const sf::Sprite& sprite2, const sf::Color& targetColor) {
    std::set<CollisionDirection> directions;
    sf::FloatRect bounds1 = sprite1.getGlobalBounds();
    sf::FloatRect bounds2 = sprite2.getGlobalBounds();

    if (!bounds1.intersects(bounds2)) {
        return directions;
    }

    const sf::Texture* texture2 = sprite2.getTexture();
    if (!texture2) {
        return directions;
    }

    sf::IntRect textureRect = sprite2.getTextureRect();

    sf::FloatRect intersectRect = bounds1;
    intersectRect.intersects(bounds2, intersectRect);

    for (float x = intersectRect.left; x < intersectRect.left + intersectRect.width; x += 1) {
        for (float y = intersectRect.top; y < intersectRect.top + intersectRect.height; y += 1) {
            sf::Vector2f globalPos(x, y);
            sf::Vector2i localPos2 = static_cast<sf::Vector2i>(sprite2.getInverseTransform().transformPoint(globalPos));

            if (localPos2.x >= textureRect.left && localPos2.y >= textureRect.top &&
                localPos2.x < textureRect.left + textureRect.width && localPos2.y < textureRect.top + textureRect.height) {
                sf::Color pixelColor2 = texture2->copyToImage().getPixel(localPos2.x - textureRect.left, localPos2.y - textureRect.top);

                if (pixelColor2 == targetColor) {
                    if (y < bounds1.top + bounds1.height / 2) {
                        directions.insert(CollisionDirection::Top);
                    } else {
                        directions.insert(CollisionDirection::Bottom);
                    }

                    if (x < bounds1.left + bounds1.width / 2) {
                        directions.insert(CollisionDirection::Left);
                    } else {
                        directions.insert(CollisionDirection::Right);
                    }

                    return directions;
                }
            }
        }
    }

    return directions;
}