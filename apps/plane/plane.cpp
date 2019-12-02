#include "include/transform.h"
#include "include/material.h"
#include "include/camera.h"
#include "include/canvas.h"
#include "include/plane.h"

#include <chrono>

int main() {

    auto right = std::make_shared<raytracer::Sphere>();
    auto left = std::make_shared<raytracer::Sphere>();
    
    auto light = raytracer::Light();
    auto * camera = new raytracer::Camera();
    

    auto * canvas = new raytracer::Canvas();

    //auto * transform = new raytracer::Transform();
    auto * translation = new raytracer::Transform();
    auto * rotationY = new raytracer::Transform();
    auto * rotationX = new raytracer::Transform();
    auto * scaling = new raytracer::Transform();
    
    // floor
    auto const floor = [] {
        auto floor = std::make_shared<raytracer::Plane>();
        floor->material.pattern = std::make_shared<raytracer::StripePattern>(raytracer::Color(1, 1, 1),
                                                                             raytracer::Color(0, 0, 0));
        floor->material.color = raytracer::Color(1, 1, 1);
        floor->material.reflection = 0.5;
        return floor;
    }();




    auto * world = new raytracer::World();
    world->addObject(floor);

    // middle sphere
    auto middle = std::make_shared<raytracer::Sphere>();
        //translation->translate(-0.5, 1, 0.5);
        //middle->setTransform(* translation);
        middle->setTransform(Transform().translation(-0.5,1.0, 0.5));
        middle->material.color = raytracer::Color(0.1, 1, 0.5);
        middle->material.diffuse = 0.1;
        middle->material.specular = 0.3;
        middle->material.transparency = 0.9;
        middle->material.reflection = 0.9;
        middle->material.refractiveIndex = 1.52;
    world->addObject(middle);

    // right sphere
    translation->translate(1.5, 0.5, -0.5);
    scaling->scale(0.5, 0.5, 0.5);
    * transform = * translation * * scaling;
    right->setTransform(* transform);
    right->material.color = raytracer::Color(0.5, 1, 0.1);
    right->material.diffuse = 0.7;
    right->material.specular = 0.3;
//    right->material.pattern = std::make_shared<raytracer::StripePattern>(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    world->addObject(right);

    // left sphere
    translation->translate(-1.5, 0.33, -0.75);
    scaling->scale(0.33, 0.33, 0.33);
    * transform = * translation * * scaling;
    left->setTransform(* transform);
    left->material.color = raytracer::Color(1, 0.8, 0.1);
    left->material.diffuse = 0.7;
    left->material.specular = 0.3;
//    left->material.pattern = std::make_shared<raytracer::StripePattern>(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    world->addObject(left);

    light->setAreaLight(raytracer::createPoint(-2, 10, 0), raytracer::createVector(2, 0, 0), 2, raytracer::createVector(0, 2, 0), 2, raytracer::Color(1, 1, 1));
//    light->setPointLight(raytracer::createPoint(-2, 10, -10), raytracer::Color(1, 1, 1));
    world->light_ = * light;

    auto start = std::chrono::high_resolution_clock::now();

    // camera
    * camera = raytracer::Camera(500, 250, PI/3);
    * transform = viewTransform(raytracer::createPoint(1.f, 1.5, -5.f), raytracer::createPoint(0.f, 1.f, 0.f), raytracer::createVector(0.f, 1.f, 0.f));
    camera->transform_ = * transform;
    * canvas = camera->render(world);
    canvas->saveToFile();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

    std::cout << "Time of render: " << duration.count() << "s" << '\n';

    delete light;
    delete camera;
    delete world;
    delete transform;
    delete translation;
    delete rotationX;
    delete rotationY;
    delete scaling;
    delete canvas;

    std::cout << "Image rendered successfully.";

    return 0;
}