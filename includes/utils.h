#pragma once

#include <SFML/Graphics.hpp>
#include <thread>

const size_t hardware_threads = std::thread::hardware_concurrency();

/*
 * @brief Get the color from the number of iterations
 * @param iterations The number of iterations
 */
sf::Color getColorFromIterations(int iterations, int maxIterations);

/*
 * @brief Custom implementation of the for_each/execution::par algorithm
 * @param first The first element of the range
 * @param last The last element of the range
 * @param func The function to apply to each element
 */
template<typename Iterator, typename Function>
void parallelForEach(Iterator first, Iterator last, Function func) {
    const auto length = std::distance(first, last);
    if (!length) return;

    constexpr size_t min_per_thread = 25;
    const size_t max_threads = (length + min_per_thread - 1) / min_per_thread;
    const size_t num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
    const size_t block_size = length / num_threads;
    std::vector<std::thread> threads(num_threads - 1);
    Iterator block_start = first;

    for (size_t i = 0; i < (num_threads - 1); ++i) {
        Iterator block_end = block_start;
        size_t chunk_start_index = std::distance(first, block_start);

        std::advance(block_end, block_size);
        threads[i] = std::thread([=, &func] {
            size_t index = chunk_start_index;
            for (Iterator it = block_start; it != block_end; ++it, ++index) {
                func(*it, index);
            }
        });
        block_start = block_end;
    }
    size_t chunk_start_index = std::distance(first, block_start);
    size_t index = chunk_start_index;

    for (Iterator it = block_start; it != last; ++it, ++index) {
        func(*it, index);
    }
    std::for_each(threads.begin(), threads.end(), [](std::thread &x) { x.join(); });
}
