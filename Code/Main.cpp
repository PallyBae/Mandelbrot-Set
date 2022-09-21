#include <SFML/Graphics.hpp>
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <sstream>
#include "ComplexPlane.h"
//!!! using #include "ComplexPlane.cpp" caused "multiple definition" errors 
//!!! got rid of using namespace sf and std due to personal preference,
//!!! it can be difficult to discern where a class comes from if they are from differnt namepaces.
//!!! Vector vs vector, one is from sf and the other from std. It's personal preferennce and helped me debug


/*-------------------------------------------------*\
*****************************************************
|___|****                                   ****|___|
!!!!!***                                     ***!!!!!
|___|**     Check out this Mandelbrot Set     **|___|
!!!!!***                                     ***!!!!!
|___|****                                   ****|___|
*****************************************************
\*-------------------------------------------------*/
int main()
{
    //!!! Created a windowScale value to test how the program will behave with different scales
    //!!! also give the benefit of using winsdowScale in other parts of code such as Text size
    float windowScale = 0.75f;

    //!!! Same here! Can call the following 2 variables in other parts to avoid having to use any object member accessors
    float currentWindowWidth  = sf::VideoMode::getDesktopMode().width  * windowScale; 
    float currentWindowHeight = sf::VideoMode::getDesktopMode().height * windowScale;

    //  Get the desktop resolution using:
    sf::VideoMode desktop(currentWindowWidth, currentWindowHeight); //!!! Changed to reflect the above changes
    //  Calculate the aspect ratioof the moniter
    float aspect_ratio = currentWindowWidth / currentWindowHeight; //!!! Changed to reflect the above changes
    //  Construct your window
    sf::RenderWindow window(desktop, "Mandelbrot Set!!", sf::Style::Default);
    //  Construct an object of type ComplexPlane
    ComplexPlane c_plane(aspect_ratio);

    //  Construct Font and Text Objects
    sf::Font font;
    sf::Text instruction_text;

    //  Construct a VertexArray
    sf::VertexArray vertex_array(sf::Points, 0);
    //vertex_array.setPrimitiveType(sf::Points);
    vertex_array.resize(currentWindowWidth*currentWindowHeight*1); //!!! using the 2 window vars made this line a bit cleaner imo

    //  Create an enum class state variable with states CALCULATING and DISPLAYING
    enum state 
    {
        CALCULATING, DISPLAYING
    };

    //  Initialize it to CALCULATING
    state state_variable = CALCULATING;
    //  When the program starts or when the user clicks the mouse, 
            //  we will calculate a new view for the complex plane
            //  This is very CPU intense, so we will set the state variable
            //  back to DISPLAYING after it is done so we only have to do it
            //  once per click

    //  SOME USEFUL VARIABLES
    sf::Vector2i clicked;
    sf::Vector2f mouse;
    sf::Vector2f pixel_location;
    int point_counter = 0;
    int pixelWidth = 1;
    size_t iterations_storage;

    /*----------------------------------*\
    **************************************
    |___|****                    ****|___|
    !!!!!***                      ***!!!!!
    |___|**     Main Game Loop     **|___|
    !!!!!***                      ***!!!!!
    |___|****                    ****|___|
    **************************************
    \*----------------------------------*/
    while (window.isOpen())
    {
        //  Handle Input segment
        sf::Event event;
        
        //  Poll Windows queue events
        while (window.pollEvent(event))
        {
            switch (event.type) //!!! This is kind of unnecessary but allows easy handling of other events
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                // Check if Keyboard:isKeyPRessed(Keyboard:Escape) to close the window
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    window.close();
                }
                break;

            case sf::Event::MouseButtonPressed:
                //Handle Right Mouse button press, which zooms out and centers the view
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    //  Use mapPixelToCoords to find the Vector2f coordinate in the Complex Plane View
                    //  that corresponds to the screen mouse click
                    mouse = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    //  Right click will zoomOut and setCenter of the ComplexPlane object
                    c_plane.setCenter(mouse);
                    c_plane.zoomOut();
                        
                    //  Set the state to CALCULATING to generate
                    //  the new complex plane view in the update segment
                    state_variable = CALCULATING;
                }
                //  Left click will zoomIn and setCenter of the ComplexPlane object
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    mouse = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), c_plane.getView());

                    //Left click will zoomIn and setCenter of the ComplexPlane object
                    c_plane.setCenter(mouse);
                    c_plane.zoomIn();

                    //  Set the state to CALCULATING to generate
                    //  the new complex plane view in the update segment
                    state_variable = CALCULATING;
                }
                break;
            
            case sf::Event::MouseMoved:
                //  Use mapPixelToCoords to find the Vector2f coordinate
                //  in the ComplexPlane View that corresponds to the screen mouse location
                mouse = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                //  setMouseLocation on the ComplexPLane object to store this coordinate
                //  This will be used later to display the mouse coordinates as it moves
                c_plane.setMouseLocation(mouse);
                break;
                
            default: //!!! Added this to handle misc events
                break;
            }
        }

        /*----------------------------------------*\
        ********************************************
        |___|****                          ****|___|
        !!!!!***                            ***!!!!!
        |___|**     Update Scene Segment     **|___|
        !!!!!***                            ***!!!!!
        |___|****                          ****|___|
        ********************************************
        \*----------------------------------------*/

        if(state_variable == CALCULATING)
        {
            //  Double for loop to loop through all pixels in the screen height and width
            //  Use j for x and i for y
            for(int i = 0; i < currentWindowHeight; i++) //!!! using the new currentWindowHeight var
            {
                for(int j = 0; j < currentWindowWidth; j++) //!!! using the new currentWindowWidth var
                {
                    vertex_array[point_counter].position = sf::Vector2f(j,i);
                    point_counter ++;

                    //  Set the position variable in the element of VertexArray
                    //  that corresponds to the screen coordinate j,i
                    //  This is difficult, so study the line of code below:
                    vertex_array[j+i*pixelWidth].position = {(float)j,(float)i};

                    //  Use mapPixelToCoords to find the Vector2f coordinate in the ComplexPlane View
                    //  that corresponds to the screen pixel location at j,i
                    pixel_location = window.mapPixelToCoords(sf::Vector2i(j, i));

                    //  Call ComplexPlane::countIterations for the Vector2f coordinate in the ComplexPlane and store the number of iterations
                    iterations_storage = ComplexPlane::countIterations(pixel_location);//!!! Infinite loop is here!!!

                    //  Declare three local Uint8 variables r,g,b to store the RGB values for the curent pixel
                    //  Uint8 is an alias for unsigned char
                    sf::Uint8 r;
                    sf::Uint8 g;
                    sf::Uint8 b;
                    
                    //  Pass the number of iterations and RGB variables into ComplexPlane::iterationsToRGB
                    //  This will assign the RGB values by reference
                    ComplexPlane::iterationsToRGB(iterations_storage, r, g, b);

                    //  Set the color variable in the element of VertexArray that corresponds to the screen coordinate j,i
                    vertex_array[j+i*pixelWidth].color = {r,g,b};

                }

            }

            //  Set the state to DISPLAYING
            state_variable = DISPLAYING;

            //  Call loadText from the ComplexPlane object
            c_plane.loadText(instruction_text);
        }

        /*--------------------------------------*\
        ******************************************
        |___|****                        ****|___|
        !!!!!***                          ***!!!!!
        |___|**     Draw Scene Segment     **|___|
        !!!!!***                          ***!!!!!
        |___|****                        ****|___|
        ******************************************
        \*--------------------------------------*/

        //  Clear the window
        window.clear(sf::Color(50, 50, 50, 255));

        //  Draw the VertexArray
        window.draw(vertex_array);

        //  Draw the Text
        window.draw(instruction_text);

        //  Display
        window.display();

        //  Dont worry about setting any Views, I tried to do it but the small fraction coordinates caused screen tearing
    }


    return 0;
}