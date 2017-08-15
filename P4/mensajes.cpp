#include "mensajes.h"

void Mensaje::inicializa(unsigned ancho,unsigned alto,unsigned ancho_panel)
{
	texto_turno.setFont(font);
    texto_turno.setString("BLACK");
    texto_turno.setCharacterSize(30);
    texto_turno.setPosition(ancho-ancho_panel+10, 100);
    texto_turno.setFillColor(sf::Color::White);
    texto_turno.setStyle(sf::Text::Regular);


    texto_puntuacion.setFont(font);
    texto_puntuacion.setString("-");
    texto_puntuacion.setCharacterSize(30);
    texto_puntuacion.setPosition(ancho-ancho_panel+10, 200);

    currentTurnText.setFont(font);
    currentTurnText.setString("Current turn:");
    currentTurnText.setCharacterSize(14);
    currentTurnText.setPosition(ancho-ancho_panel+10, 75);



    scoreText.setFont(font);
    scoreText.setString("Score: \nBlack-White");
    scoreText.setPosition(ancho-ancho_panel+10, 150);
    scoreText.setCharacterSize(16);


    gameVersusText.setFont(font);
    gameVersusText.setString("Nuevo juego:");
    gameVersusText.setCharacterSize(16);
    gameVersusText.setPosition(ancho-ancho_panel+20, 450);

    buttonText1.setFont(font);
    buttonText1.setString("AI");
    buttonText1.setPosition(ancho-ancho_panel+10, 515);
    buttonText1.setFillColor(sf::Color::Black);

    buttonText2.setFont(font);
    buttonText2.setString("Player");
    buttonText2.setPosition(ancho-ancho_panel+10, 635);
    buttonText2.setFillColor(sf::Color::Black);
}


void Mensaje::set_string_turno(const std::string& texto)
{
    texto_turno.setString(texto);
}
void Mensaje::draw(sf::RenderTarget& target, sf::RenderStates ) const
{
    target.draw(texto_turno);
    target.draw(texto_puntuacion);
    target.draw(gameVersusText);
    target.draw(currentTurnText);
    target.draw(scoreText);
    target.draw(buttonText1);
    target.draw(buttonText2);
}
