#include "ComplexPlane.h"
//  This contains the code for the header file
//  Pretty neat innit



//  Default constructor for the ComplexPlane class
ComplexPlane::ComplexPlane(float aspectRatio)
{
    //  Store the aspectRatio into m_aspectRatio
    m_aspectRatio = aspectRatio;

    //  setSize of the m_view variable to BASE_WIDTH, -BASE_HEIGHT*m_aspectRatio
    //  Negative size for the height will invert the vertical axis
    m_view.setSize(BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);

    //  setCenter of the m_view variable to 0.0, 0.0
    m_view.setCenter(0.0, 0.0);

    //  Set m_zoomCount to 0
    m_zoomCount = 0;
}

//  Zoom In Function
void ComplexPlane::zoomIn()
{
    //  Increment m_zoomCount
    m_zoomCount ++;

    //  Local Variable
    sf::Vector2f xySize;

    //  Set a local variable for the x size to BASE_WIDTH*(BASE_ZOOM to the m_ZoomCount power)
    xySize.x = BASE_WIDTH*(pow(BASE_ZOOM, m_zoomCount));

    //  Set a local variable for the y size to BASE_HEIGHT*m_aspectRatio*(BASE_ZOOM to the m_ZoomCount power)
    xySize.y = BASE_HEIGHT*m_aspectRatio*(pow(BASE_ZOOM, m_zoomCount));

    //  setSize in m_view to the new size
    m_view.setSize(xySize);
}

//  Zoom Out Function
void ComplexPlane::zoomOut()
{
    //  Decrement m_zoomCount
    m_zoomCount --;

    //  Local Variable
    sf::Vector2f xySize;

    //  Set a local variable for the x size to BASE_WIDTH*(BASE_ZOOM to the m_ZoomCount power)
    xySize.x = BASE_WIDTH*(pow(BASE_ZOOM, m_zoomCount));

    //  Set a local variable for the y size to BASE_HEIGHT*m_aspectRatio*(BASE_ZOOM to the m_ZoomCount power)
    xySize.y = BASE_HEIGHT*m_aspectRatio*(pow(BASE_ZOOM, m_zoomCount));

    //  setSize in m_view to the new size
    m_view.setSize(xySize);
}

//  Set Center Function
void ComplexPlane::setCenter(sf::Vector2f coord)
{
    //  setCenter for m_view to the given coordinate
    m_view.setCenter(coord);
}

//  Get View Function
sf::View ComplexPlane::getView()
{
    return m_view;
}

//  Head of Mouse location relations
void ComplexPlane::setMouseLocation(sf::Vector2f coord)
{
    m_mouseLocation = coord;
}

//  Text Loading Function
void ComplexPlane::loadText(sf::Text& text, sf::Vector2f coord)
{
    //  Creating a local stringstream variable
    std::stringstream ss;

    //  Pass the text input I want into the local variable
    ss << "Mandelbrot Set" << std::endl << "Center: (" << m_view.getCenter().x << "," << m_view.getCenter().y << ")" <<
    std::endl << "Cursor: (" << coord.x << "," << coord.y << ")" << std::endl <<
    "Left-click to Zoom in" << std::endl << "Right-click to Zoom out";

    //  setString the stringstream variable into the text object
    text.setString(ss.str());
}

//  Iteration Counting Function
size_t ComplexPlane::countIterations(sf::Vector2f coord)
{
    size_t iteration_count = 0;
    double real_number = coord.x;
    double imaginary_number = coord.y;
    std::complex <double> c (real_number, imaginary_number);
    std::complex <double> z (0.0,0.0);

    while (iteration_count < MAX_ITER && abs(z) < 2.0)
    {
        z = z*z + c;
        iteration_count ++;
    }
    return iteration_count;
}

/*
//  Iteration To RGB Color Function
void ComplexPlane::iterationsToRGB(size_t count, sf::Uint8& r, sf::Uint8& g, sf::Uint8& b)
{
    //  Default condition
    if (count == MAX_ITER)
    {
        //Sets the color to BLACK
        r = 0;
        g = 0;
        b = 0;
    }

    //  1st range of colors
    else if (count <= 63 && count >= 48)
    {
        r = 255*((count-48)/15);
        g = 255*((count-48)/15);
        b = 255*(1- (count-48)/15);
    }

    //  2nd range of colors
    else if (count <= 47 && count >= 32)
    {
        r = 255*((count-32)/15);
        g = 255*(1- (count-32)/15);
        b = 255*((count-32)/15);
    }
    
    //  3rd range of colors
    else if (count <= 31 && count >= 16)
    {
        r = 255*((count-16)/15);
        g = 255*(1- (count-16)/15);
        b = 255*(1- (count-16)/15);
    }

    //  4th range of colors
    else if (count <= 16 && count >= 1)
    {
        r = 255;
        g = 255*(1- (count-1)/15);
        b = 255;
    }
}
*/

//  Iteration To RGB Color Function
void ComplexPlane::iterationsToRGB(size_t count, sf::Uint8& r, sf::Uint8& g, sf::Uint8& b)
{
    double float_count = count;

    //  Default condition
    if (count == MAX_ITER)
    {
        //Sets the color to BLACK
        r = 0;
        g = 0;
        b = 0;
    }

    //  Green to white
    else if (count <= 259 && count >= 160)
    {
        r = 74 + 181*((float_count - 160)/99);
        g = 240 + 15*((float_count - 160)/99);
        b = 105 + 150*((float_count - 160)/99);
    }

    //  Purple to Green
    else if (count <= 159 && count >= 94)
    {
        r = 58 + 16*((float_count - 94)/65);
        g = 40 + 200*((float_count - 94)/65);
        b = 146 - 41*((float_count - 94)/65);
    }

    //  White to Purple
    else if (count <= 93 && count >= 63)
    {
        r = 255 - 197*((float_count - 63)/30);
        g = 255 - 215*((float_count - 63)/30);
        b = 255 - 109*((float_count - 63)/30);
    }

    //  Pink to White
    else if (count <= 62 && count >= 42)
    {
        r = 255 - 0*((float_count - 42)/20);
        g = 29 + 226*((float_count - 42)/20);
        b = 175 + 80*((float_count - 42)/20);
    }

    //  Turqoise to Pink
    else if (count <= 41 && count >= 31)
    {
        r = 0 + 255*((float_count - 31)/10);
        g = 155 - 126*((float_count - 31)/10);
        b = 142 + 33*((float_count - 31)/10);
    }

    //  Purple to Turqoise
    else if (count <= 30 && count >= 15)
    {
        r = 94 - 94*((float_count - 15)/15);
        g = 21 + 134*((float_count - 15)/15);
        b = 192 - 50*((float_count - 15)/15);
    }

    //  Red to Purple
    else if (count <= 14 && count >= 1)
    {
        r = 255 - 161*((float_count - 1)/13);
        g = 60 - 39*((float_count - 1)/13);
        b = 0 + 192*((float_count - 1)/13);
    }
}