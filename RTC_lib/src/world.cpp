#include "include/world.h"

#include <memory>

namespace raytracer {
World::World()
    : light(Light()), shapes(std::vector<std::shared_ptr<Shape> >())
{
}

void World::intersectWorld(const raytracer::Ray &ray, std::vector<Intersection> * xs) const {
    for (const auto& shape : shapes) {
        shape->intersect(ray, * xs);
    }
    std::sort(xs->begin(), xs->end());
}

Color World::shadeHit(const IntersectionData &intersectionData) {
//    bool shadowed = this->isShadowed(intersectionData.overPoint, this->light.position);
    float shadowed = this->light.intensityAt(intersectionData.overPoint, * this);

    return intersectionData.object->material.setPhongLighting(intersectionData.object,
                                                              this->light,
                                                              intersectionData.overPoint,
                                                              intersectionData.eye,
                                                              intersectionData.normal,
                                                              shadowed);
}

Color World::colorAt(const Ray &ray) {
    auto * xs = new std::vector<Intersection>();
    this->intersectWorld(ray, xs);
    auto intersection = hit(* xs);

    if (intersection.getObject() == nullptr && intersection.getDistance() == 0.f) {
        return Color(0, 0, 0);
    }

    auto * intersectionData = new IntersectionData();
    * intersectionData = intersection.prepareComputations(ray);
    return this->shadeHit(* intersectionData);
}

void World::addObject(const std::shared_ptr<Shape>& shape) {
    shapes.push_back(shape);
}

void World::defaultWorld() {
    this->light = Light(Point(-10.0, 10.0, -10.0), Color(1, 1, 1));

    this->shapes = std::vector<std::shared_ptr<Shape> >{2};
    shapes[0] = std::make_shared<Sphere>();
    shapes[1] = std::make_shared<Sphere>();

    shapes[0]->material.color = Color(0.8, 1.0, 0.6);
    shapes[0]->material.diffuse = 0.7;
    shapes[0]->material.specular = 0.2;

    shapes[1]->setTransform(transform.scale(0.5, 0.5, 0.5));
}

bool World::isShadowed(const Point &lightPosition, const Point &point) const {
//    auto vector = this->light.position - point;
    auto vector = lightPosition - point;
    double distance = magnitude(vector);
    auto direction = normalize(vector);

    auto ray = Ray(point, direction);
    auto * xs = new std::vector<Intersection>();
    intersectWorld(ray, xs);
    auto * h = new Intersection();
    * h = hit(* xs);
    return h->getObject() != nullptr && h->getDistance() < distance;
}

Color World::reflectedColor(const IntersectionData &xs) {
    if (xs.object->material.reflection == 0.0) {
        return Color(0.0, 0.0, 0.0);
    } else {
        auto reflectRay = Ray(xs.overPoint, xs.reflect);
        auto color = this->colorAt(reflectRay);
        return color * xs.object->material.reflection;
    }

}
}
