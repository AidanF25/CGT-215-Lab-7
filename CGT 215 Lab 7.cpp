#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h> 

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
    RenderWindow window(VideoMode(800, 600), "Bouncy Ball");
    World world(Vector2f(0, 1));

    PhysicsCircle ball;
    ball.setCenter(Vector2f(400, 30));
    ball.setRadius(20);
    world.AddPhysicsBody(ball);
    ball.applyImpulse(Vector2f(0.1, 0.1));

    PhysicsRectangle floor;
    floor.setSize(Vector2f(960, 50));
    floor.setCenter(Vector2f(500, 580));
    floor.setStatic(true);
    world.AddPhysicsBody(floor);

    PhysicsRectangle ceiling;
    ceiling.setSize(Vector2f(800, 20));
    ceiling.setCenter(Vector2f(400, 10));
    ceiling.setStatic(true);
    world.AddPhysicsBody(ceiling);

    PhysicsRectangle LeftSide;
    LeftSide.setSize(Vector2f(20, 600));
    LeftSide.setCenter(Vector2f(10, 300));
    LeftSide.setStatic(true);
    world.AddPhysicsBody(LeftSide);

    PhysicsRectangle RightSide;
    RightSide.setSize(Vector2f(20, 600));
    RightSide.setCenter(Vector2f(790, 300));
    RightSide.setStatic(true);
    world.AddPhysicsBody(RightSide);

    PhysicsRectangle center;
    center.setSize(Vector2f(100, 100));
    center.setCenter(Vector2f(400, 300));
    center.setStatic(true);
    world.AddPhysicsBody(center);

    int thudCount(0);
    floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
        };

    int bangCount(1);
    center.onCollision = [&bangCount](PhysicsBodyCollisionResult result)
        {
            cout << "bang " << bangCount << endl;
            bangCount++;
            if (bangCount == 3)
            {
                exit(0);
            }
        };

    Clock clock;
    Time lastTime(clock.getElapsedTime());
    while (true)
    {
        Time currentTime(clock.getElapsedTime());
        Time deltaTime(currentTime - lastTime);
        int deltaTimeMS(deltaTime.asMilliseconds());
        if (deltaTimeMS > 0)
        {
            world.UpdatePhysics(deltaTimeMS);
            lastTime = currentTime;
        }

        window.clear(Color(150, 50, 50));
        window.draw(ball);
        window.draw(floor);
        window.draw(ceiling);
        window.draw(LeftSide);
        window.draw(RightSide);
        window.draw(center);
        window.display();
    }

    return 0; 
}
