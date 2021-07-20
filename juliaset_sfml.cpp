#include <SFML/Graphics.hpp>
#include <complex>
#include <iostream>

const sf::Vector2u DEFAULT_WINDOW_SIZE = { 1000, 1000 };
const sf::Color DEFAULT_BACKGROUND_COLOR = { 255, 255, 255 };

float julia(const double x,
            const double y,
            const double real,
            const double ima,
            const uint maxItr)
{
    const std::complex<double> i(0.0, 1.0);
    const std::complex<double> c(real, ima);
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

const sf::Color colorTable[] = { { 0, 0, 0, 0 }, { 0, 0, 255 },
                                 { 0, 255, 0 },  { 0, 255, 255 },
                                 { 255, 0, 0 },  { 255, 0, 255 },
                                 { 255, 255, 0 } };

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

void drawJulia(sf::RenderWindow& window,
               const sf::Vector2i drawPos,
               const float stepSize = 0.005,
               const uint maxItr = 300,
               const float drawScale = 300)
{
    const double r = 0.27334;
    const double i = 0.00742;
    const int startAreaPos = -2;
    const int endAreaPos = 2;
    const uint totalStep = (endAreaPos - startAreaPos) / stepSize;
    const auto tableLen = getArrayLength(colorTable);

    sf::RectangleShape player(sf::Vector2f(1.0f, 1.0f));
    for (int y = 0; y < totalStep; y++)
    {
        for (int x = 0; x < totalStep; x++)
        {
            const float n = startAreaPos + stepSize * y;
            const float m = startAreaPos + stepSize * x;
            if (const float v = julia(m, n, r, i, maxItr); v != 0)
            {
                const auto p =
                  drawPos + (sf::Vector2i(m * drawScale, n * drawScale));
                player.setPosition(p.x, p.y);
                const auto fillColor = colorTable[zeroOneToIndex(v, tableLen)];
                player.setFillColor(fillColor);
                window.draw(player);
            }
        }
        window.display();
    }
}

int main()
{

    sf::RenderWindow window(
      sf::VideoMode(DEFAULT_WINDOW_SIZE.x, DEFAULT_WINDOW_SIZE.y),
      "SFML juliaset",
      sf::Style::Default);

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
                    // std::cout << "New window width: " << evnt.size.width
                    //           << ", New window height: " << evnt.size.height
                    //           << std::endl;

                    const sf::Vector2u afterSize(evnt.size.width,
                                                 evnt.size.height);
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
            drawJulia(window, convertVector<int>(DEFAULT_WINDOW_SIZE / 2u), 0.005, 300, 400);
            completed = true;
            std::cout << "drew julia" << std::endl;
        }
    }

    return 0;
}
