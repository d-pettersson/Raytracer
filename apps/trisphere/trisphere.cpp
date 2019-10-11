#include "include/transform.h"
#include "include/material.h"
#include "include/camera.h"
#include "include/canvas.h"

#include <chrono>

int main() {
    auto floor = std::make_shared<raytracer::Sphere>();
    auto leftWall = std::make_shared<raytracer::Sphere>();
    auto rightWall = std::make_shared<raytracer::Sphere>();
    auto middle = std::make_shared<raytracer::Sphere>();
    auto right = std::make_shared<raytracer::Sphere>();
    auto left = std::make_shared<raytracer::Sphere>();

    auto * light = new raytracer::Light();
    auto * camera = new raytracer::Camera();

    auto * world = new raytracer::World();
    auto * canvas = new raytracer::Canvas(500, 250);

    auto * transform = new raytracer::Transform();
    auto * translation = new raytracer::Transform();
    auto * rotationY = new raytracer::Transform();
    auto * rotationX = new raytracer::Transform();
    auto * scaling = new raytracer::Transform();

    // floor
    scaling->scale(10, 0.01, 10);
    floor->setTransform(* scaling);
    floor->material.color = raytracer::Color(1, 0.9, 0.9);
    floor->material.specular = 0;
    world->addObject(floor);

    // left wall
    translation->translate(0, 0, 5);
    rotationY->rotateY(-PI/4);
    rotationX->rotateX(PI/2);
    scaling->scale(10, 0.01, 10);
    * transform = * translation * * rotationY * * rotationX * * scaling;
    leftWall->setTransform(* transform);
    leftWall->material = floor->material;
    world->addObject(leftWall);

    // right wall
    rotationY->rotateY(PI/4);
    * transform = * translation * * rotationY * * rotationX * * scaling;
    rightWall->setTransform(* transform);
    rightWall->material = floor->material;
    world->addObject(rightWall);

    // middle sphere
    translation->translate(-0.5, 1, 0.5);
    middle->setTransform(* translation);
    middle->material.color = raytracer::Color(0.1, 1, 0.5);
    middle->material.diffuse = 0.7;
    middle->material.specular = 0.3;
    world->addObject(middle);

    // right sphere
    translation->translate(1.5, 0.5, -0.5);
    scaling->scale(0.5, 0.5, 0.5);
    * transform = * translation * * scaling;
    right->setTransform(* transform);
    right->material.color = raytracer::Color(0.5, 1, 0.1);
    right->material.diffuse = 0.7;
    right->material.specular = 0.3;
    world->addObject(right);

    // left sphere
    translation->translate(-1.5, 0.33, -0.75);
    scaling->scale(0.33, 0.33, 0.33);
    * transform = * translation * * scaling;
    left->setTransform(* transform);
    left->material.color = raytracer::Color(1, 0.8, 0.1);
    left->material.diffuse = 0.7;
    left->material.specular = 0.3;
    world->addObject(left);

    // light source
//    light->setPointLight(raytracer::Point(-10, 10, -10), raytracer::Color(1, 1, 1));
    light->setAreaLight(raytracer::Point(-2, 10, -10), raytracer::Vector(2, 0, 0), 1, raytracer::Vector(0, 2, 0), 1, raytracer::Color(1, 1, 1));
    world->light = * light;

    auto start = std::chrono::high_resolution_clock::now();

    // camera
    * camera = raytracer::Camera(500, 250, PI/3);
    * transform = viewTransform(raytracer::Point(1.f, 1.5, -5.f), raytracer::Point(0.f, 1.f, 0.f), raytracer::Vector(0.f, 1.f, 0.f));
    camera->transform = * transform;
    * canvas = camera->render(* world);
    canvas->saveToFile();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time of render: " << duration.count() << " ms" << '\n';

    delete light;
    delete camera;
    delete world;
    delete canvas;
    delete transform;
    delete translation;
    delete rotationX;
    delete rotationY;
    delete scaling;

    std::cout << "Image rendered successfully.";

    return 0;
}