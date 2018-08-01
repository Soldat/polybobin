#ifndef UTILS_HPP
#define UTILS_HPP

enum PMSPolygonType : unsigned char;
struct PMSColor;

namespace Utils
{
    PMSColor GetPolygonColorByType(PMSPolygonType polygonType);

    /**
     * \brief Checks if there is an intersection between segments AB and CD.
     * http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
     */
    bool SegmentsIntersect(float aX, float aY, float bX, float bY,
                           float cX, float cY, float dX, float dY);

    // https://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
    bool RectanglesIntersect(float aX, float aY, float bX, float bY,
                             float cX, float cY, float dX, float dY);

    // http://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
    float Sign(float aX, float aY, float bX, float bY, float cX, float cY);
}

#endif