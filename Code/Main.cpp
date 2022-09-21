#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include "ComplexPlane.h"
#include "ComplexPlane.cpp"
using namespace std;

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
    //  Get the desktop resolution using:
    VideoMode desktop(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
    //  Calculate the aspect ratioof the moniter
    float aspect_ratio = desktop.height / desktop.width;
    //  Construct your window
    RenderWindow window(desktop, "Mandelbrot Set!!", Style::Default);
    //  Construct an object of type ComplexPlane
    ComplexPlane c_plane(aspect_ratio);

    //  Construct Font and Text Objects
    Font font;
    Text instruction_text;

    //  Construct a VertexArray
    VertexArray vertex_array;
    vertex_array.setPrimitiveType(Points);
    vertex_array.resize(desktop.width*desktop.height*1);

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
    Vector2i clicked;
    Vector2f mouse;
    Vector2f pixel_location;
    int point_counter = 0;
    int pixelWidth = 1;
    size_t iterations_storage;
    Text instruction_text;

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
        Event event;
        
            //  Poll Windows queue events
        while (window.pollEvent(event))
        {
            //  Handle Event::Closed event to close the window
            if(event.type == Event::Closed)
            {
                window.close();
            }

            //  Handle Event::MouseButtonPressed
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Right)
                {
                    //  Use mapPixelToCoords to find the Vector2f coordinate in the Complex Plane View
                    //  that corresponds to the screen mouse click
                    mouse = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));

                    //  Right click will zoomOut and setCenter of the ComplexPlane object
                    c_plane.setCenter(mouse);
                    c_plane.zoomOut();
                    
                    //  Set the state to CALCULATING to generate
                    //  the new complex plane view in the update segment
                    state_variable = CALCULATING;
                }

                //  Left click will zoomIn and setCenter of the ComplexPlane object
                if (event.mouseButton.button == Mouse::Left)
                {
                    mouse = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));

                    //Left click will zoomIn and setCenter of the ComplexPlane object
                    c_plane.setCenter(mouse);
                    c_plane.zoomIn();

                    //  Set the state to CALCULATING to generate
                    //  the new complex plane view in the update segment
                    state_variable = CALCULATING;
                }
            }
            
            //  Handle Event::MouseMoved
            if (event.type == Event::MouseMoved)
            {
                //  Use mapPixelToCoords to find the Vector2f coordinate
                //  in the ComplexPlane View that corresponds to the screen mouse location
                mouse = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));

                //  setMouseLocation on the ComplexPLane object to store this coordinate
                //  This will be used later to display the mouse coordinates as it moves
                c_plane.setMouseLocation(mouse);


            }

            // Check if Keyboard:isKeyPRessed(Keyboard:Escape) to close the window
            if (Keyboard::isKeyPressed(Keyboard::Escape))
		    {
			    window.close();
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
            for(int i = 0; i < desktop.height; i++)
            {
                for(int j = 0; j < desktop.width; j++)
                {
                    vertex_array[point_counter].position = Vector2f(j,i);
                    point_counter ++;

                    //  Set the position variable in the element of VertexArray
                    //  that corresponds to the screen coordinate j,i
                    //  This is difficult, so study the line of code below:
                    vertex_array[j+i*pixelWidth].position = {(float)j,(float)i};

                    //  Use mapPixelToCoords to find the Vector2f coordinate in the ComplexPlane View
                    //  that corresponds to the screen pixel location at j,i
                    pixel_location = window.mapPixelToCoords(Vector2i(j, i));

                    //  Call ComplexPlane::countIterations for the Vector2f coordinate in the ComplexPlane and store the number of iterations
                    iterations_storage = ComplexPlane::countIterations(pixel_location);
                    
                    //  Declare three local Uint8 variables r,g,b to store the RGB values for the curent pixel
                    //  Uint8 is an alias for unsigned char
                    Uint8 r;
                    Uint8 g;
                    Uint8 b;
                    
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
        window.clear();

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