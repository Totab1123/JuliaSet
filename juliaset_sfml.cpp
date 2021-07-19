#include <SFML/Graphics.hpp>
#include <complex>
#include <iostream>

float julia(double x, double y, double real, double ima, uint maxItr)
{
    const std::complex<double> i(0.0, 1.0);
    std::complex<double> c(real, ima);
    std::complex<double> z = x + i * y;

    for (int i = 0; i < maxItr; i++)
    {
        z = z * z + c;
        if (std::abs(z) > 2) { return static_cast<float>(i) / maxItr; }
    }
    return 1;
}

int zeroOneToIndex(const float inValue, const uint step)
{
    const float normalizedStep = 1.f / (step - 1);
    return inValue / normalizedStep;
}

sf::Color colorTable[] = {
    { 0, 0, 0 }, { 0, 0, 255 },   { 0, 255, 0 },   { 0, 255, 255 }, { 255, 0, 0 },
    { 255, 0, 255 }, { 255, 255, 0 }
};

template<typename T, uint L>
constexpr uint getArrayLength(const T (&)[L])
{
    return L;
}

template<typename To, typename From>
sf::Vector2<To> convertVector(const sf::Vector2<From> inValue)
{
    return sf::Vector2<To>(static_cast<To>(inValue.x),
                           static_cast<To>(inValue.y));
}

int main()
{
    const sf::Vector2u DEFAULT_WINDOW_SIZE = { 1000, 1000 };
    auto middle = DEFAULT_WINDOW_SIZE / 2u;
    sf::Color DEFAULT_BACKGROUND_COLOR = {255, 255, 255};

    sf::RenderWindow window(
      sf::VideoMode(DEFAULT_WINDOW_SIZE.x, DEFAULT_WINDOW_SIZE.y),
      "SFML juliaset",
      sf::Style::Default);
    sf::RectangleShape player(sf::Vector2f(1.0f, 1.0f));
    player.setFillColor(sf::Color(0, 0, 128, 128));

    bool completed = false;
    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
                case sf::Event::Closed: {
                    window.close();
                    break;
                }

                case sf::Event::Resized: {
                    std::cout << "New window width: " << evnt.size.width
                              << " New window height" << evnt.size.height
                              << std::endl;

                    sf::Vector2u afterSize(evnt.size.width, evnt.size.height);
                    sf::View view = window.getDefaultView();
                    view.setSize(afterSize.x, afterSize.y);
                    window.setView(view);
                    completed = false;
                    break;
                }
                default: {
                }
            }
        }

        if (!completed)
        {
            window.clear(DEFAULT_BACKGROUND_COLOR);
            const double r = 0.27334;
            const double i = 0.00742;
            for (double m = -2; m <= 2; m += 0.005)
            {
                for (double n = -2; n <= 2; n += 0.005)
                {
                    if (float v = julia(n, m, r, i, 300); v != 0)
                    {
                        player.setPosition(middle.x + n * 300,
                                           middle.y + m * 300);
                        const auto tableLen = getArrayLength(colorTable);
                        const auto fillColor =
                          colorTable[zeroOneToIndex(v, tableLen)];
                        player.setFillColor(fillColor);
                        window.draw(player);
                    }
                }
            }
            completed = true;
            std::cout << "drew julia" << std::endl;
            window.display();
        }
    }

    return 0;
}
