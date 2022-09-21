

//  This contains the code for the header file
//  Pretty neat innit


//  Default constructor for the ComplexPlane class
ComplexPlane::ComplexPlane(float aspectRatio)
{
    //  Store the aspectRatio into m_aspectRatio
    m_aspectRatio = aspectRatio;

    //  setSize of the m_view variable to BASE_WIDTH, -BASE_HEIGHT*m_aspectRatio
    //  Negative size for the height will invert the vertical axis
    m_view.setSize(BASE_WIDTH, -BASE_HEIGHT*m_aspectRatio);

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
    Vector2f xySize;

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
    Vector2f xySize;

    //  Set a local variable for the x size to BASE_WIDTH*(BASE_ZOOM to the m_ZoomCount power)
    xySize.x = BASE_WIDTH*(pow(BASE_ZOOM, m_zoomCount));

    //  Set a local variable for the y size to BASE_HEIGHT*m_aspectRatio*(BASE_ZOOM to the m_ZoomCount power)
    xySize.y = BASE_HEIGHT*m_aspectRatio*(pow(BASE_ZOOM, m_zoomCount));

    //  setSize in m_view to the new size
    m_view.setSize(xySize);
}

// Set Center Function
void ComplexPlane::setCenter(Vector2f coord)
{
    
}