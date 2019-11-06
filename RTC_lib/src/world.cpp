#include "include/world.h"

#include <memory>
#include <cmath>

namespace raytracer {
World::World()
    : light_(Light()), shapes_(std::vector<std::shared_ptr<Shape> >())
{
}

void World::intersectWorld(const raytracer::Ray &ray, std::vector<Intersection> * xs) const {
    for (const auto& shape : shapes_) {
        shape->intersect(ray, * xs);
    }
    std::sort(xs->begin(), xs->end());
}

Color World::shadeHit(const IntersectionData &comps, int remaining) {
    bool shadowed = this->isShadowed(comps.overPoint);
//    float shadowed = this->light_.intensityAt(comps.overPoint, * this); // area light_ related

    auto surface = comps.object->material.setPhongLighting(comps.object, this->light_, comps.overPoint, comps.eye, comps.normal, shadowed);
    auto reflected = this->reflectedColor(comps, remaining);
    auto refracted = this->refractedColor(comps, remaining);

    auto material = comps.object->material;
    if (material.reflection > 0 && material.transparency > 0) {
        auto reflectance = comps.schlick();
        return surface + reflected * reflectance + refracted * (1 - reflectance);
    } else {
        return surface + reflected + refracted;
    }
}

Color World::colorAt(const Ray &ray, int remaining) {
    auto * xs = new std::vector<Intersection>();
    this->intersectWorld(ray, xs);
    auto intersection = hit(* xs);

    if (intersection.getObject() == nullptr && intersection.getDistance() == 0.f) {
        return Color(0, 0, 0);
    }
    Color output = this->shadeHit(intersection.prepareComputations(ray, * xs), remaining);

    delete xs;

    return output;
}

void World::addObject(const std::shared_ptr<Shape> &shape) {
    shapes_.emplace_back(shape);
}

void World::defaultWorld() {
    this->light_ = Light(createPoint(-10.0, 10.0, -10.0), Color(1, 1, 1));

    this->shapes_ = std::vector<std::shared_ptr<Shape> >{2};
    shapes_[0] = std::make_shared<Sphere>();
    shapes_[1] = std::make_shared<Sphere>();

    shapes_[0]->material.color = Color(0.8, 1.0, 0.6);
    shapes_[0]->material.diffuse = 0.7;
    shapes_[0]->material.specular = 0.2;

    shapes_[1]->setTransform(transform_.scale(0.5, 0.5, 0.5));
}

//bool World::isShadowed(const Point &lightPosition, const Point &point) const {
////    auto vector = this->light.position - point;
//    auto vector = lightPosition - point;
//    double distance = magnitude(vector);
//    auto direction = normalize(vector);
//
//    auto ray = Ray(point, direction);
//    auto * xs = new std::vector<Intersection>();
//    intersectWorld(ray, xs);
//    auto * h = new Intersection();
//    * h = hit(* xs);
//    return h->getObject() != nullptr && h->getDistance() < distance;
//}

bool World::isShadowed(const Tuple &point) const {
    auto vector = this->light_.position_ - point;
    auto distance = magnitude(vector);
    auto direction = normalize(vector);

    auto ray = Ray(point, direction);
    auto * xs = new std::vector<Intersection>();
    intersectWorld(ray, xs);
    std::unique_ptr<Intersection> h(new Intersection());

    * h = hit(* xs);

    delete xs;

    return h->getObject() != nullptr && h->getDistance() < distance;
}

Color World::reflectedColor(const IntersectionData &comps, int remaining) {
    if (comps.object->material.reflection == 0.0 || remaining <= 0) {
        return Color(0.0, 0.0, 0.0);
    }
    auto reflectRay = Ray(comps.overPoint, comps.reflect);
    auto color = this->colorAt(reflectRay, remaining - 1);

    return color * comps.object->material.reflection;
}

Color World::refractedColor(const IntersectionData &comps, int remaining) {
    if (comps.object->material.transparency == 0.0 || remaining <= 0) {
        return Color(0.0, 0.0, 0.0);
    }
    double nRatio = comps.n1 / comps.n2;
    double cosI = dot(comps.eye, comps.normal);
    double sin2T = pow(nRatio, 2) * (1 - pow(cosI, 2));
    double cosT = sqrt(1.0 - sin2T);
    auto direction = comps.normal * (nRatio * cosI - cosT) - comps.eye * nRatio;
    auto refractRay = Ray(comps.underPoint, direction);
    auto color = this->colorAt(refractRay, remaining - 1);

    return color * comps.object->material.transparency;
}
}
