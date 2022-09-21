#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
using namespace std;

/*
*****************************************************
|___|****                                  ****|___|
!!!!!***                                    ***!!!!!
|___|**     Check out this Mandelbrot Set    **|___|
!!!!!***                                    ***!!!!!
|___|****                                  ****|___|
*****************************************************
*/
int main()
{
    //Get the desktop resolution using:
    VideoMode desktop(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
    //Calculate the aspect ratioof the moniter
    float aspect_ratio = desktop.height / desktop.width;
    //Construct your window
    RenderWindow window(desktop, "Mandelbrot Set!!", Style::Default);
    //Construct an object of type ComplexPlane
    
            //NEEDS WORK!!! (1)
            //NEEDS WORK!!! (1)
            //NEEDS WORK!!! (1)
            //NEEDS WORK!!! (1)
            //NEEDS WORK!!! (1)

    //Construct Font and Text Objects
    Font font;
    Text instruction_text;
    //Construct a VertexArray
    VertexArray vertex_array;
    vertex_array.setPrimitiveType(Points);
    vertex_array.resize(desktop.width*desktop.height*1);
    /*    
        //Filling the array
    int point_counter = 0;
    for(int i = 0; i < desktop.width; i++)
    {
        for(int j = 0; j < desktop.height; j++)
        {
            vertex_array[point_counter].position = Vector2f(i,j);
            point_counter ++;
        }
    }
    */
    //Create an enum class state variable with states CALCULATING and DISPLAYING
    enum state 
    {
        CALCULATING, DISPLAYING
    };
    //Initialize it to CALCULATING
    state state_variable = CALCULATING;
            //  When the program starts or when the user clicks the mouse, 
            //  we will calculate a new view for the complex plane
            //  This is very CPU intense, so we will set the state variable
            //  back to DISPLAYING after it is done so we only have to do it
            //  once per click
    //SOME USEFUL VARIABLES
    Vector2i clicked;

    //Begin the main loop
    //MAIN GAME LOOP
    while (window.isOpen())
    {
        //Handle Input segment
        Event event;
        
            //Poll Windows queue events
        while (window.pollEvent(event))
        {
            //Handle Event::Closed event to close the window
            if(event.type == Event::Closed)
            {
                window.close();
            }

            //Handle Event::MouseButtonPressed
            if (event.type == Event::MouseButtonPressed)
            {
                //NEEDS WORK!!! (2: 1)
                //NEEDS WORK!!! (2: 1)
                //NEEDS WORK!!! (2: 1)
                //NEEDS WORK!!! (2: 1)
                //NEEDS WORK!!! (2: 1)
                //Something like this
                    //Vector2f mouse = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));

                //Right click will zoomOut and setCenter of the ComplexPlane object
                if (event.mouseButton.button == Mouse::Right)
                {
                    //NEEDS WORK!!! (3: 1 and 2)
                    //NEEDS WORK!!! (3: 1 and 2)
                    //NEEDS WORK!!! (3: 1 and 2)
                    //NEEDS WORK!!! (3: 1 and 2)
                    //NEEDS WORK!!! (3: 1 and 2)
                    
                    //  Set the state to CALCULATING to generate
                    //  the new complex plane view in the update segment
                    //      LIKE THIS
                    //      state_variable = CALCULATING;
                }

                //Left click will zoomIn and setCenter of the ComplexPlane object
                if (event.mouseButton.button == Mouse::Left)
                {
                    //NEEDS WORK!!! (4: 1 and 2)
                    //NEEDS WORK!!! (4: 1 and 2)
                    //NEEDS WORK!!! (4: 1 and 2)
                    //NEEDS WORK!!! (4: 1 and 2)
                    //NEEDS WORK!!! (4: 1 and 2)

                    //  Set the state to CALCULATING to generate
                    //  the new complex plane view in the update segment
                    //      LIKE THIS
                    //      state_variable = CALCULATING;
                }
            }
            
            //Handle Event::MouseMoved
            if (event.type == Event::MouseMoved)
            {
                //NEEDS WORK!!! (5: 1)
                //NEEDS WORK!!! (5: 1)
                //NEEDS WORK!!! (5: 1)
                //NEEDS WORK!!! (5: 1)
                //NEEDS WORK!!! (5: 1)

                //  Use mapPixelToCoords to find the Vector2f coordinate
                //  in the ComplexPlane View that corresponds to the screen mouse location
                //      SOMETHING LIKE THIS
                //      Vector2f mouse = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
                

            }
        }
    }


    return 0;
}