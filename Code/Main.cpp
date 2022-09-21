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
    class ComplexPlane
    {
        private:

        public:
    };
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
    

    //Declaring Variables
    double real_number;
    double imaginary_number;
    complex<double> c (real_number, imaginary_number);
    complex<double> z (0.0,0.0);
    float view_center_real = 0.0f;
    float view_center_imaginary = 0.0f;
    float view_window_real_length = 2.0f;
    float view_window_imaginary_length = 2.0f;
    Vector2f center_point(view_center_real, view_center_imaginary);
    Vector2f window_dim(view_window_real_length, view_window_imaginary_length);
    View view1(center_point, window_dim);

    //Running Calculations


    return 0;
}