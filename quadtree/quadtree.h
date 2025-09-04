#pragma once

#include "../body.h"
#include "box.h"
#include "vector2.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace quadtree {

template <typename T> class Node {
  public:
    Box<T> boundary;
    bool isLeaf;
    PVector<T> body_position;
    Body *body;
    std::array<std::unique_ptr<Node>, 4> children;

    void addBody(const PVector<T> &position, Body newBody) {
        if (isLeaf) {
            if (body_position == nullptr) {
                isLeaf = true;
                body_position = position;
                body = &newBody;
            } else {
                isLeaf = false;
                body_position = nullptr;
                body = nullptr;
                std::array<Box<T>, 4> quadrants = boundary.subdivide();
                for (int i = 0; i < 4; i++) {
                    children[i] = std::make_unique<Node>();
                    children[i]->boundary = quadrants[i];
                }
                addToInBoundsChild(body_position, newBody);
            }
        }
    };

    void addToInBoundsChild(const PVector<T> &position, Body newBody) {
        if (children[0]->boundary.contains(position)) {
            children[0]->addBody(position, newBody);
        } else if (children[1]->boundary.contains(position)) {
            children[1]->addBody(position, newBody);
        } else if (children[2]->boundary.contains(position)) {
            children[2]->addBody(position, newBody);
        } else if (children[3]->boundary.contains(position)) {
            children[3]->addBody(position, newBody);
        } else {
            throw std::invalid_argument("Position out of bounds");
        }
    }

    Body average_mass_body() {
        if (isLeaf) {
            return *body;
        } else {
            double total_mass = 0;
            int count = 0;
            PVector<double> c(0, 0);
            for (const auto &child : children) {
                if (child) {
                    Body childAvgBody = child->average_mass_body();
                    total_mass += childAvgBody.center_of_mass;
                    c += childAvgBody.position * childAvgBody.center_of_mass;
                    count++;
                }
            }
            return Body(c.x, c.y, 1, total_mass / count);
        }
    }
};

template <typename T, typename V> class Quadtree {
    Node<T> *root;
};

} // namespace quadtree
