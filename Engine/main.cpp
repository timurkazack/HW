#include <iostream>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Phys/Physics.h"
#include "Geom/Geometry.h"

using namespace std;

// Функция отрисовки
void draw(sf::RenderWindow& window, vector<Physics::RigidBody>& projectiles, sf::Vector2i mousePos) {
    // Координаты мышки
    sf::Vector2f mousePosF(mousePos.x, mousePos.y);
    
    // Линия направления
    sf::Vertex line[2];
    line[0].position = sf::Vector2f(400, 500);
    line[0].color = sf::Color::Blue;
    line[1].position = mousePosF;
    line[1].color = sf::Color::Red;
    window.draw(line, 2, sf::Lines);
    
    // Пушка
    sf::CircleShape cannon(15);
    cannon.setFillColor(sf::Color::Blue);
    cannon.setOrigin(15, 15);
    cannon.setPosition(400, 500);
    window.draw(cannon);
    
    // Снаряды
    for (const auto& p : projectiles) {
        if (!p.isStatic && p.shape && p.shape->type() == Geometry::Shape::Circle) {
            auto* circle = static_cast<Geometry::Circle*>(p.shape);
            sf::CircleShape ballShape(circle->radius);
            ballShape.setFillColor(sf::Color::Red);
            ballShape.setOrigin(circle->radius, circle->radius);
            ballShape.setPosition(p.position.x, p.position.y);
            window.draw(ballShape);
        }
    }
    
    // Рисуем границы
    sf::RectangleShape leftWall(sf::Vector2f(5, 600));
    leftWall.setFillColor(sf::Color::Green);
    leftWall.setPosition(10, 0);
    window.draw(leftWall);
    
    sf::RectangleShape rightWall(sf::Vector2f(5, 600));
    rightWall.setFillColor(sf::Color::Green);
    rightWall.setPosition(785, 0);
    window.draw(rightWall);
    
    sf::RectangleShape topWall(sf::Vector2f(800, 5));
    topWall.setFillColor(sf::Color::Green);
    topWall.setPosition(0, 10);
    window.draw(topWall);
    
    sf::RectangleShape bottomWall(sf::Vector2f(800, 5));
    bottomWall.setFillColor(sf::Color::Green);
    bottomWall.setPosition(0, 585);
    window.draw(bottomWall);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Physics Engine");
    window.setFramerateLimit(60);
    sf::Clock clock;
    
    // Вектор для хранения тел
    vector<Physics::RigidBody> bodies;
    
    // Гравитация
    const Geometry::Vector gravity(0, 500.0f);
    
    // Флаг для стрельбы
    bool wasPressed = false;
    
    
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        float deltaTime = clock.restart().asSeconds();
        if (deltaTime > 0.033f) deltaTime = 0.033f;
        
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        // Стрельба
        bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        
        if (isPressed && !wasPressed) {
            // Создаем снаряд
            Geometry::Circle* ballShape = new Geometry::Circle(Geometry::Vector(400, 500), 8.0f);
            Physics::RigidBody ball(ballShape, Geometry::Vector(400, 500), Geometry::Vector(0,0), false, 1.0f);

            // Направление
            sf::Vector2f direction(mousePos.x - 400, mousePos.y - 500);
            float len = sqrt(direction.x * direction.x + direction.y * direction.y);
            if (len > 0) {
                direction.x /= len;
                direction.y /= len;
            }

            float speed = 400.0f;
            ball.velocity = Geometry::Vector(direction.x * speed, direction.y * speed);

            bodies.push_back(std::move(ball));
        }
        wasPressed = isPressed;
        
        // Обновление физики
        const int iterations = 4;
        for (int iter = 0; iter < iterations; ++iter) {
            float subDt = deltaTime / iterations;
            
            // Применяем гравитацию
            for (auto& body : bodies) {
                if (!body.isStatic) {
                    body.velocity = body.velocity + gravity * subDt;
                }
            }
            
            // Обновляем позиции
            for (auto& body : bodies) {
                if (!body.isStatic) {
                    body.update(subDt);
                }
            }
            
            // Проверка границ
            const float leftBound = 15.0f;   // левая стена x = 15
            const float rightBound = 785.0f; // правая стена x = 785
            const float topBound = 15.0f;    // верхняя стена y = 15
            const float bottomBound = 585.0f;// нижняя стена y = 585
            const float restitution = 0.2f;  // упругость

            for (auto& body : bodies) {
                if (body.isStatic) continue;
                if (body.shape && body.shape->type() == Geometry::Shape::Circle) {
                    auto* circle = static_cast<Geometry::Circle*>(body.shape);
                    float r = circle->radius;
                
                    if (body.position.x - r < leftBound) {
                        body.position.x = leftBound + r;
                        body.velocity.x = -body.velocity.x * restitution;
                    }
                    if (body.position.x + r > rightBound) {
                        body.position.x = rightBound - r;
                        body.velocity.x = -body.velocity.x * restitution;
                    }
                    if (body.position.y - r < topBound) {
                        body.position.y = topBound + r;
                        body.velocity.y = -body.velocity.y * restitution;
                    }
                    if (body.position.y + r > bottomBound) {
                        body.position.y = bottomBound - r;
                        body.velocity.y = -body.velocity.y * restitution;
                    }
                }
            }
            
            // Проверка столкновений между снарядами
            for (size_t i = 0; i < bodies.size(); ++i) {
                if (bodies[i].isStatic) continue;
                if (!bodies[i].shape || bodies[i].shape->type() != Geometry::Shape::Circle) continue;
                auto* circleA = static_cast<Geometry::Circle*>(bodies[i].shape);

                for (size_t j = i + 1; j < bodies.size(); ++j) {
                    if (bodies[j].isStatic) continue;
                    if (!bodies[j].shape || bodies[j].shape->type() != Geometry::Shape::Circle) continue;
                    auto* circleB = static_cast<Geometry::Circle*>(bodies[j].shape);
                
                    float dx = bodies[j].position.x - bodies[i].position.x;
                    float dy = bodies[j].position.y - bodies[i].position.y;
                    float dist = sqrt(dx*dx + dy*dy);
                    float minDist = circleA->radius + circleB->radius;
                
                    if (dist < minDist) {
                        if (dist == 0.0f) dist = 0.001f;
                        float overlap = minDist - dist;
                        float nx = dx / dist;
                        float ny = dy / dist;
                    
                        // Выталкивание (массы одинаковы → пополам)
                        float correction = overlap * 0.5f;
                        bodies[i].position.x -= nx * correction;
                        bodies[i].position.y -= ny * correction;
                        bodies[j].position.x += nx * correction;
                        bodies[j].position.y += ny * correction;
                    
                        // Изменение скоростей (упругое столкновение)
                        float vrelx = bodies[j].velocity.x - bodies[i].velocity.x;
                        float vrely = bodies[j].velocity.y - bodies[i].velocity.y;
                        float dot = vrelx * nx + vrely * ny;
                        if (dot < 0) {
                            float e = 0.8f;
                            float m1 = bodies[i].mass, m2 = bodies[j].mass;
                            float imp = (1 + e) * dot / ((1/m1) + (1/m2));
                            bodies[i].velocity.x += imp / m1 * nx;
                            bodies[i].velocity.y += imp / m1 * ny;
                            bodies[j].velocity.x -= imp / m2 * nx;
                            bodies[j].velocity.y -= imp / m2 * ny;
                        }
                    }
                }
            }
        }
        
        // Удаляем снаряды за пределами
        bodies.erase(
            remove_if(bodies.begin(), bodies.end(),
                [](const Physics::RigidBody& b) {
                    return !b.isStatic && (
                        b.position.y > 650 ||
                        b.position.y < -50 ||
                        b.position.x < -50 ||
                        b.position.x > 850
                    );
                }),
            bodies.end()
        );
        
        // Отрисовка
        window.clear(sf::Color::Black);
        draw(window, bodies, mousePos);
        
        
        
        window.display();
    }
    
    return 0;
}