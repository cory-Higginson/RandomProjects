#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

std::array<sf::Color,7> Color_List = {sf::Color::Green,
                                   sf::Color::Blue,
                                   sf::Color::Red,
                                   sf::Color::Cyan,
                                   sf::Color::Magenta,
                                   sf::Color::Yellow,
                                   sf::Color::White};

void add(std::vector<sf::RectangleShape>& recs, sf::Color color)
{
    int collums = 0;
    int rows    = 0;
    if (!recs.empty())
    {
        collums =   (int)recs.back().getPosition().x / 12;
        rows    =   (int)recs.back().getPosition().y / 12;
    }
    while (true)
    {


        if ((12 * collums) + 10 >= 1080)
        {
            collums = 0;
            rows++;
        }
        if ((12 * rows) + 10 >= 720)
        {
            return ;
        }
        recs.emplace_back(sf::Vector2f{10, 10});
        recs.back().setFillColor(color);
        recs.back().setPosition(12.f * (float )collums,
                                12.f * (float )rows);
        collums++;
    }
}

void change(std::vector<sf::RectangleShape>& recs,sf::Color color)
{
    if (recs.empty())
        return ;
    for (auto &item: recs)
    {
        item.setFillColor(color);
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
    }
}


int main()
{
    /// create a window and set up
    sf::RenderWindow window(sf::VideoMode
                            (1080, 720),
                            "Factory",
                            sf::Style::Close);

    window.setFramerateLimit(120);
    ///initialise an instance of the game class

    std::vector<sf::RectangleShape> winrecs;
    ///run the init function of the game class and check it all initialises ok

    /// A Clock starts counting as soon as it's created
    sf::Clock clock;
    sf::Color color = {sf::Color::Black};
    int color_time = 0;

    add(winrecs, color);
    /// Game loop: run the program as long as the window is open
    while (window.isOpen())
    {
        /// check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        ///calculate delta time
        sf::Time time = clock.restart();
        float dt = time.asSeconds();

        ///'process inputs' element of the game loop
        while (window.pollEvent(event))
        {
            /// "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                color_time >= 7 ? color_time = 0 : color_time++;
                color = Color_List[color_time];
                std::thread t([&] { change(winrecs, {color}); });
                t.detach();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::V)
            {

            }

            ///game.eventHandler(event);
        }

        ///'update' element of the game loop


        window.clear(sf::Color::Black);
        ///'render' elements of the game loop
        for (const auto &item: winrecs)
            window.draw(item);

        window.display();
    }

    return 0;
}