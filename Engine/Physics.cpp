#include <iostream>
#include <vector>
#include <algorithm>
#include "Shapes.cpp"
#include <SFML/Graphics.hpp>

using namespace std;

struct Body {
    float Mass;
    Vector Position;
    Vector Velocity;
    Vector Force;
    
    Body() : Mass(1.0f), Position(0, 0), Velocity(0, 0), Force(0, 0) {}
    
    // действие силы на тело
    void applyForce(const Vector& force) {
        Force += force;
    }
    
    // обновление позиции
    void update(float dt) {
        // v(t+dt) = a*dt + v(t), где a = F/m
        Vector speed = Force * (1.0f / Mass);
        Velocity += speed * dt;
        Position += Velocity * dt;
        Force = Vector(0, 0);
    }
};

void draw(sf::RenderWindow& window, float deltaTime, vector<Body>& projectiles, sf::Vector2i mousePos) {
    // корды мышки
    sf::Vector2f mousePosF(mousePos.x, mousePos.y);
    
    // линия направления
    sf::Vertex line[2];
    line[0].position = sf::Vector2f(400, 500);
    line[0].color = sf::Color::Blue;
    line[1].position = mousePosF;
    line[1].color = sf::Color::Red;
    window.draw(line, 4, sf::Lines);
    
    // пушка
    sf::CircleShape cannon(15);
    cannon.setFillColor(sf::Color::Blue);
    cannon.setOrigin(15, 15);
    cannon.setPosition(400, 500);
    window.draw(cannon);
    
    // снаряды
    sf::CircleShape ballShape(3);
    ballShape.setFillColor(sf::Color::Red);
    ballShape.setOrigin(3, 3);
    
    for (const auto& p : projectiles) {
        ballShape.setPosition(p.Position.x, p.Position.y);
        window.draw(ballShape);
    }
}

int main() {
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hmmm");
    window.setFramerateLimit(60);
    sf::Clock clock;
    
    vector<Body> projectiles; // вектор для хранения ядер
    const Vector gravity(0, 9.8f); // сила гравитации
    
    // флаг для стрельбы
    bool wasPressed = false;
    
    while (window.isOpen()) {
        // oбработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        float deltaTime = clock.restart().asSeconds();
        if (deltaTime > 0.03f) deltaTime = 0.03f; // ограничение dt
        
        // получаем позицию мыши
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        // стрельба по левой кнопке мыши
        bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        
        if (isPressed/* && !wasPressed*/) { // так прикольнее
            Body ball;
            ball.Mass = 1.0f;
            ball.Position = Vector(400, 500); // позиция пушки
            
            // направление от пушки к мыши
            sf::Vector2f direction = sf::Vector2f(mousePos.x, mousePos.y) - sf::Vector2f(400, 500);
            float len = sqrt(direction.x * direction.x + direction.y * direction.y);
            if (len > 0) {
                direction.x /= len;
                direction.y /= len;
            }
            
            float speed = 500.0f; // начальная скорость ядра
            ball.Velocity = Vector(direction.x * speed, direction.y * speed);
            projectiles.push_back(ball);
        }
        wasPressed = isPressed;
        
        // обновление физики для всех ядер
        for (auto& p : projectiles) {
            p.applyForce(gravity); // применяем гравитацию
            p.update(deltaTime);
        }
        
        // удаление ядер, которые вышли за пределы экрана
        projectiles.erase(
            remove_if(projectiles.begin(), projectiles.end(),
                [](const Body& b) {
                    return b.Position.y > 650 ||   // упали ниже экрана
                           b.Position.y < -50 ||   // улетели выше
                           b.Position.x < -50 ||   // ушли влево
                           b.Position.x > 850;     // ушли вправо
                }),
            projectiles.end()
        );
        
        // отрисовка
        window.clear(sf::Color::Black);
        draw(window, deltaTime, projectiles, mousePos);
        window.display();
    }
    
    return 0;
}