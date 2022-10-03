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

const int TEXTBOX_BKG_W_ALIGN = 2;
const int TEXTBOX_BKG_H_ALIGN = 7;

int main()
{
    //!!! Created a windowScale value to test how the program will behave with different scales
    //!!! also give the benefit of using winsdowScale in other parts of code such as Text size
    float windowScale = 0.8f;

    //!!! Same here! Can call the following 2 variables in other parts to avoid having to use any object member accessors
    int currentWindowWidth  = sf::VideoMode::getDesktopMode().width  * windowScale; 
    int currentWindowHeight = sf::VideoMode::getDesktopMode().height * windowScale;

    //  Get the desktop resolution using:
    sf::VideoMode desktop(currentWindowWidth, currentWindowHeight); //!!! Changed to reflect the above changes
    //  Calculate the aspect ratio of the moniter
    float aspect_ratio = currentWindowHeight / static_cast<float>(currentWindowWidth); //!!! Changed to reflect the above changes
    //  Construct your window
    sf::RenderWindow window(desktop, "Mandelbrot Set!!", sf::Style::Default);
    //  Construct an object of type ComplexPlane
    ComplexPlane c_plane(aspect_ratio);

    //  Construct Font and Text Objects
    sf::Font font;
    font.loadFromFile("fonts/SebastianSerifNbp-7weB.ttf");
    sf::Text instruction_text;
    instruction_text.setFont(font);
    instruction_text.setPosition( {currentWindowWidth * 0.02f, currentWindowHeight * 0.02f} );

    //Create a rectangle for the text to be drawn on top of.
    const int textBoxBgBorder = 5;
    sf::RectangleShape textBoxBg;
    textBoxBg.setFillColor(sf::Color(0,0,0,127));
    textBoxBg.setPosition( {instruction_text.getPosition().x - TEXTBOX_BKG_W_ALIGN - textBoxBgBorder, instruction_text.getPosition().y + TEXTBOX_BKG_H_ALIGN - textBoxBgBorder});

    //  Construct a VertexArray
    sf::VertexArray vertex_array(sf::Points, currentWindowWidth*currentWindowHeight);

    vertex_array.resize(currentWindowWidth*currentWindowHeight); //!!! using the 2 window vars made this line a bit cleaner imo

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
    size_t iterations_storage = 0;

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
            {
                window.close();
                break;
            }

            case sf::Event::KeyPressed:
            {
                // Check if Keyboard:isKeyPRessed(Keyboard:Escape) to close the window
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
                break;
            }

            case sf::Event::MouseButtonPressed:
            {
                //  Use mapPixelToCoords to find the Vector2f coordinate in the Complex Plane View
                //  that corresponds to the screen mouse click
                mouse = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }, c_plane.getView());

                if (event.mouseButton.button == sf::Mouse::Right)
                    c_plane.zoomOut();

                if (event.mouseButton.button == sf::Mouse::Left)
                    c_plane.zoomIn();

                //After we zoom in or out, make sure to set center of the Complex Plane.
                c_plane.setCenter(mouse);

                //  Set the state to CALCULATING to generate
                //  the new complex plane view in the update segment
                state_variable = CALCULATING;
                break;
            }
            
            case sf::Event::MouseMoved:
            {
                //  Use mapPixelToCoords to find the Vector2f coordinate
                //  in the ComplexPlane View that corresponds to the screen mouse location
                mouse = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y }, c_plane.getView());

                //  setMouseLocation on the ComplexPLane object to store this coordinate
                //  This will be used later to display the mouse coordinates as it moves
                c_plane.setMouseLocation(mouse);
                break;
            }
                
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
            int percentUpdate = 0;
            int prevPercent = 0;
            //point_counter = 0;
            for (int j = 0; j < currentWindowWidth; j++) //!!! using the new currentWindowHeight var
            {
                percentUpdate = (j / static_cast<float>(currentWindowWidth)) * 100.0;
                if (percentUpdate != prevPercent && percentUpdate % 5 == 0)
                {
                    std::cout << "Percent: " << percentUpdate << std::endl;
                }

                for(int i = 0; i < currentWindowHeight; i++) //!!! using the new currentWindowWidth var
                {
                    //  Set the position variable in the element of VertexArray
                    //  that corresponds to the screen coordinate j,i
                    //  This is difficult, so study the line of code below:
                    vertex_array[j+i*currentWindowWidth].position = {(float)j,(float)i};

                    //  Use mapPixelToCoords to find the Vector2f coordinate in the ComplexPlane View
                    //  that corresponds to the screen pixel location at j,i
                    pixel_location = window.mapPixelToCoords(sf::Vector2i(j, i),c_plane.getView());

                    //  Call ComplexPlane::countIterations for the Vector2f coordinate in the ComplexPlane and store the number of iterations
                    iterations_storage = ComplexPlane::countIterations(pixel_location);//!!! Infinite loop is here!!!

                    //  Declare three local Uint8 variables r,g,b to store the RGB values for the curent pixel
                    //  Uint8 is an alias for unsigned char
                    sf::Uint8 r = 0;
                    sf::Uint8 g = 0;
                    sf::Uint8 b = 0;
                    
                    //  Pass the number of iterations and RGB variables into ComplexPlane::iterationsToRGB
                    //  This will assign the RGB values by reference
                    ComplexPlane::iterationsToRGB(iterations_storage, r, g, b);

                    //  Set the color variable in the element of VertexArray that corresponds to the screen coordinate j,i
                    vertex_array[j+i*static_cast<int>(currentWindowWidth)].color = {r,g,b};
                }
                prevPercent = percentUpdate;

            }
            std::cout << "Percent: 100" << std::endl;

            std::cout << aspect_ratio << std::endl;
            //  Set the state to DISPLAYING
            state_variable = DISPLAYING;

            //  Call loadText from the ComplexPlane object
            c_plane.loadText(instruction_text, mouse);
            textBoxBg.setSize({ instruction_text.getLocalBounds().width + textBoxBgBorder*2 , instruction_text.getLocalBounds().height + textBoxBgBorder*2} );
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

        //Draw the instruction_text and textBoxbg
        //  Call loadText from the ComplexPlane object
        c_plane.loadText(instruction_text, mouse);

        instruction_text.setPosition( { currentWindowWidth * 0.02f, currentWindowHeight * 0.02f } );

        textBoxBg.setPosition( {instruction_text.getPosition().x - TEXTBOX_BKG_W_ALIGN - textBoxBgBorder, instruction_text.getPosition().y + TEXTBOX_BKG_H_ALIGN - textBoxBgBorder});
        textBoxBg.setSize({ instruction_text.getLocalBounds().width + textBoxBgBorder*2 , instruction_text.getLocalBounds().height + textBoxBgBorder*2} );
        window.draw(textBoxBg);
        window.draw(instruction_text);

        //  Display
        window.display();

        //  Dont worry about setting any Views, I tried to do it but the small fraction coordinates caused screen tearing
    }


    return 0;
}