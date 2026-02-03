/**
 * @file Utils.hpp
 * @brief Utility helpers for math and SFML vector operations.
 */
#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

/**
 * @brief Calculates Euclidean distance between two 2D points
 *
 * This template function computes the straight-line distance between
 * two points in 2D space using the Pythagorean theorem.
 *
 * @tparam T Numeric type for vector coordinates (int, float, double, etc.)
 * @param a First point
 * @param b Second point
 * @return Distance between the two points as a float
 */
template<typename T>
float calculDistanta(const sf::Vector2<T> &a, const sf::Vector2<T> &b) {
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

#endif
