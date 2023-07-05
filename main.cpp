#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

int ground = 370;

class Player {
public:
    float dx, dy;
    FloatRect rect;
    bool onGround;
    Sprite sprite;
    float curFrame;
    int a;

    Player(Texture & image) {
        sprite.setTexture(image);
        sprite.setTextureRect(IntRect(0, 0, 90, 95));

        dx = dy = 0;
        curFrame = 0;
        a = 0;
    }

    void update(float time) {
        rect.left += dx * time;

        if (!onGround) {
            dy = dy + 0.0005 * time;
        }

        rect.top += dy * time;

        if (rect.left == 0) {
            rect.left = 100;
        }
        if (rect.top == 0) {
            rect.top = 370;
        }

        onGround = false;

        if (rect.top > ground) {
            rect.top = ground;
            dy = 0;

            onGround = true;
        }

        if (dy == 0) {
            if (a == 0) {
                curFrame += 0.0005;
                if (curFrame > 1 && curFrame < 1.95) {
                    curFrame = 1.95;
                }
                if (curFrame > 2) {
                    curFrame -= 2;
                }
            } else if (a == 1) {
                if (curFrame < 2) {
                    curFrame = 2;
                }

                curFrame += 0.007;
                if (curFrame > 4) {
                    curFrame -= 2;
                }
            } else if (a == 2) {
                curFrame = 4;
            }

            sprite.setTextureRect(IntRect(90*int(curFrame), 0, 90, 95));
        }

        sprite.setPosition(rect.left, rect.top);

        dx = 0;
    }
};


int main() {
    RenderWindow window(VideoMode(1000, 500), "Dinosaur!");

    Texture F;
    F.loadFromFile("/home/andrey/Desktop/dinosaur/Paint/pol.png");
    Sprite Floor(F);
    Floor.scale(0.42, 1);
    Floor.setPosition(0, 450);

    Texture D;
    D.loadFromFile("/home/andrey/Desktop/dinosaur/Paint/Din.png");
    Player p(D);

    Texture arr[6];
    Sprite cactArr[6];
    arr[0].loadFromFile("/home/andrey/Desktop/dinosaur/Paint/Cact/1.png");
    arr[1].loadFromFile("/home/andrey/Desktop/dinosaur/Paint/Cact/2.png");
    arr[2].loadFromFile("/home/andrey/Desktop/dinosaur/Paint/Cact/3.png");
    arr[3].loadFromFile("/home/andrey/Desktop/dinosaur/Paint/Cact/4.png");
    arr[4].loadFromFile("/home/andrey/Desktop/dinosaur/Paint/Cact/5.png");
    arr[5].loadFromFile("/home/andrey/Desktop/dinosaur/Paint/Cact/6.png");

    for (int i = 0; i < 6; i++) {
        cactArr[i].setTexture(arr[i]);

        if (i < 3) {
            cactArr[i].setPosition(1000, 395);
        }
        if (i > 2) {
            cactArr[i].setPosition(1000, 370);
        }
    }

    srand(time(NULL));
    int cit = rand() % 6 + 1;

    int b = 0;
    int pt = rand() % 2 + 1;

    Texture Pt;
    Pt.loadFromFile("/home/andrey/Desktop/dinosaur/Paint/Ptic.png");
    Sprite Ptic(Pt);
    Ptic.setTextureRect(IntRect(0, 0, 93, 80));
    Ptic.setPosition(1000, 380 - 100 * (pt - 1));

    float Fp = 0;

    bool play = false;
    bool go = false;

    Clock clock;

    Texture O;
    O.loadFromFile("/home/andrey/Desktop/dinosaur/Paint/GameOver.png");
    Sprite Over(O);
    Over.setPosition(1000, 0);

    Texture N;
    N.loadFromFile("/home/andrey/Desktop/dinosaur/Paint/Naz.png");
    Sprite Naz(N);
    Naz.setPosition(1000, 0);

    Texture Cf;
    Cf.loadFromFile("/home/andrey/Desktop/dinosaur/Paint/Cifr.png");

    Sprite Score[5];
    float cr[5] = {0};
    for (int i = 0; i < 5; i++) {
        Score[i].setTexture(Cf);
        Score[i].setTextureRect(IntRect(0, 0, 20, 24));
        Score[i].setPosition(950 - 25*i, 2);
    }

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            if (p.onGround) {
                if (p.a < 2) {

                    p.dy = -0.4;
                    p.onGround = false;

                    p.sprite.setTextureRect(IntRect(180, 0, 90, 95));
                    p.a = 1;
                } else if (p.a == 2) {
                    p.a = 1;
                    for (int i = 0; i < 6; i++) {
                        if (i < 3) {
                            cactArr[i].setPosition(1000, 395);
                        }
                        if (i > 2) {
                            cactArr[i].setPosition(1000, 370);
                        }
                    }

                    cit = rand() % 6 + 1;

                    pt = rand() % 2 + 1;
                    Ptic.setPosition(1000, 380 - 100 * (pt - 1));

                    b = 0;

                    Over.setPosition(1000,0);
                    Naz.setPosition(1000, 0);

                    go = false;

                    for (int i = 0; i < 5; i++) {
                        cr[i] = 0;

                        Score[i].setTextureRect(IntRect(0, 0, 20, 24));
                    }
                }
            }
        }

        if (p.a == 1 && p.onGround == true) {
            play = true;
        }
        for (int i = 0; i < 6; i++) {
            if (p.sprite.getGlobalBounds().intersects(cactArr[i].getGlobalBounds())) {
                go = true;
            }
        }

        if (p.sprite.getGlobalBounds().intersects(Ptic.getGlobalBounds())) {
            go = true;
        }

        if (play) {
            if (b < 10) {
                cactArr[cit - 1].move(-0.35 * time, 0);

                Vector2f ct[6];
                for (int i = 0; i < 6; i++) {
                    ct[i] = cactArr[i].getPosition();

                    if (ct[i].x < -200) {
                        if (i < 3) {
                            cactArr[i].setPosition(1000, 395);
                        }
                        if (i > 2) {
                            cactArr[i].setPosition(1000, 370);
                        }

                        cit = rand() % 6 + 1;

                        b++;
                    }
                }
            } else if (b == 10) {
                Ptic.move(-0.3*time, 0);

                Vector2f pit = Ptic.getPosition();
                if (pit.x < -200) {
                    pt = rand() % 2 + 1;

                    Ptic.setPosition(1000, 380 - 100 * (pt - 1));

                    b = 0;
                }
            }
            cr[0] += 0.005;
            if (cr[0] > 10) {
                cr[0] -= 10;
                cr[1]++;
                if (cr[1] > 9) {
                    cr[1] -= 10;
                    cr[2]++;
                    if (cr[2] > 9) {
                        cr[2] -= 10;
                        cr[3]++;
                        if (cr[3] > 9) {
                            cr[3] -= 10;
                            cr[4]++;
                            if (cr[4] > 9) {
                                cr[4] -= 10;
                            }
                            Score[4].setTextureRect(IntRect(20*int(cr[4]),0,20,24));
                        }
                        Score[3].setTextureRect(IntRect(20*int(cr[3]),0,20,24));
                    }
                    Score[2].setTextureRect(IntRect(20*int(cr[2]),0,20,24));
                }
                Score[1].setTextureRect(IntRect(20*int(cr[1]),0,20,24));
                }
            Score[0].setTextureRect(IntRect(20*int(cr[0]),0,20,24));
        }
        
        if (go) {
            p.a = 2;

            play = false;

            Over.setPosition(300,200);
            Naz.setPosition(450, 250);
        }

        Fp += 0.0025;
        if (Fp > 2) {
            Fp -= 2;
        }
        Ptic.setTextureRect(IntRect(93 * int(Fp), 0, 93, 80));

        p.update(time);
        window.clear(Color::White);
        window.draw(Floor);
        window.draw(p.sprite);
        for (int i = 0; i < 6; i++) {
            window.draw(cactArr[i]);
        }
        window.draw(Ptic);
        window.draw(Over);
        window.draw(Naz);
        for (int i = 0; i < 5; i++) {
            window.draw(Score[i]);
        }
        window.display();
    }


    return 0;
}