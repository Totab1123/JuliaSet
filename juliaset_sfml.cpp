#include <SFML/Graphics.hpp>
#include <iostream>
#include <complex>

#define CHECK 300

int julia(double x, double y, double real, double ima){
    const std::complex<double> i(0.0, 1.0);
    std::complex<double> c(real, ima);
    std::complex<double> z;

    z = x + i * y;
    for(int i = 0; i < CHECK; i++){
        z = z*z + c;
         if(std::abs(z)>10){
            break;
        }
        if(i>CHECK-2){
            return 1;
        }
    }
    return 0;
}


int main(){
    int middle = 500;
    
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML juliaset", sf::Style::Default);
    sf::RectangleShape player(sf::Vector2f(1.0f, 1.0f));
    player.setFillColor(sf::Color(0,0,128,10));
    sf::RectangleShape background(sf::Vector2f(1000.0f, 1000.0f));
    background.setFillColor(sf::Color(255, 255, 255, 255));
    while(window.isOpen())
    {
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            switch(evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            
            case sf::Event::Resized:
                std::cout << "New window width: " << evnt.size.width << " New window height" << evnt.size.height << std::endl;
                break;
            }
        }
        window.draw(background);
        double n, m;

        double r, i;
        r = 0.27334;
        i = 0.00742;

        for(m = -2; m <= 2; m += 0.0005){
            for(n = -2; n <= 2; n += 0.0005){
                if(julia(n, m, r, i)==1){
                    player.setPosition(middle + n*300, middle + m*300);
                    window.draw(player);   
                }
            }
        }
        
        window.display();
    }

    return 0;
}