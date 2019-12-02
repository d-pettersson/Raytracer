/**
 * The <code>Light</code> class allows the creation of light to illuminate our scene, and the objects present inside the scene
 *
 * @param[in] Tuple position
 * @param[in] Color intensity
 */

#ifndef RTC_LIGHT_H
#define RTC_LIGHT_H

#include "tuple.h"
#include "utils.h"

#include <vector>

namespace raytracer{

class World;

class Light {
public:
    Light();
    Light(Tuple position, Color intensity);

    /**
     * Create a Point Light which is a single source of light
     *
     * @param[in] const Tuple& position
     * @param[in] const Color& intensity
     */
    void setPointLight(const Tuple &position, const Color &intensity);

    /**
     * Create an Area Light which is composed of multiple light sources
     * in a rectangular shape
     *
     * @param[in] const Tuple& corner
     * @param[in] const Tuple& fullUvec
     * @param[in] const int& uSteps
     * @param[in] const Tuple& fullVVec
     * @param[in] const int& vSteps
     * @param[in] const Color& intensity
     */
    void setAreaLight(const Tuple &corner, const Tuple &fullUVec, const int &uSteps, const Tuple &fullVVec, const int &vSteps, const Color &intensity);

    Tuple pointOnLight(const double &u, const double &v) const;
    float intensityAt(const Tuple &point, const World &world);

    Color intensity_;
    Tuple position_;

    Tuple corner_;
    Tuple uVec_;
    int uSteps_;
    Tuple vVec_;
    int vSteps_;
    int samples_;

    bool operator==(const Light &rhs) const;
    bool operator!=(const Light &rhs) const;
};
}



#endif //RTC_LIGHT_H
