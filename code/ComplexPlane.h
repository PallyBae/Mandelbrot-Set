#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <complex>
//THIS IS A HEADER FILE
//CHECK IT OUT!!!



//Global Variables
const unsigned int MAX_ITER = 260;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;


class ComplexPlane
    {
        public:
        ComplexPlane(float aspectRatio);
        void zoomIn();
        void zoomOut();
        void setCenter(sf::Vector2f coord);
        sf::View getView();
        void setMouseLocation(sf::Vector2f coord);
        void loadText(sf::Text& text, sf::Vector2f coord);
        static size_t countIterations(sf::Vector2f coord);
        static void iterationsToRGB(size_t count, sf::Uint8& r, sf::Uint8& g, sf::Uint8& b);

        private:
        sf::Vector2f m_mouseLocation;
        sf::View m_view;
        int m_zoomCount;
        float m_aspectRatio;
    };