#ifndef MENSAJES_H_INCLUDED
#define MENSAJES_H_INCLUDED

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Mensaje:public sf::Drawable
{
public:
    Mensaje()
    {
        font.loadFromFile("arial.ttf");
    }
    void inicializa(unsigned ancho,unsigned alto,unsigned ancho_panel);
    void set_string_turno(const std::string& texto);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::Font font;
	sf::Text texto_turno;
	sf::Text texto_puntuacion;
	sf::Text currentTurnText;
	sf::Text scoreText;
	sf::Text gameVersusText;
	sf::Text buttonText1;
	sf::Text buttonText2;

};

#endif // MENSAJES_H_INCLUDED
