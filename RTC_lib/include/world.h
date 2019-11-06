/**
 * The <code>World</code> class renders 3D objects.
 *
 */

#ifndef RTC_WORLD_H
#define RTC_WORLD_H

#include "light.h"
#include "sphere.h"
#include "tuple.h"
#include "transform.h"
#include "intersection.h"

namespace raytracer {
class World {
    public:
        World();

        void defaultWorld();

        void intersectWorld(const Ray &ray, std::vector<Intersection> * xs) const;
        Color shadeHit(const IntersectionData &comps, int remaining = 5);
        Color colorAt(const Ray &ray, int remaining = 5);
        Color reflectedColor(const IntersectionData &comps, int remaining = 5);
        Color refractedColor(const IntersectionData &comps, int remaining = 5);
//        bool isShadowed(const Point &lightPosition, const Point& point) const;
        bool isShadowed(const Tuple &point) const;


        void addObject(const std::shared_ptr<Shape>& shape);

        Light light_;
        std::vector<std::shared_ptr<Shape> > shapes_;
        Transform transform_;
    };
} // namespace raytracer



#endif //RTC_WORLD_H
