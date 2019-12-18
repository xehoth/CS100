#include "ThreadedFilteredImage.hpp"
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
#include <iostream>
#include <future>

/**
 * Implementation of `ThreadedFilteredImage::ThreadedFilteredImage( Image & img, int numberThreads
 * )` This is a constructor of class ThreadedFilteredImage, which is defined in
 * `ThreadedFilteredImage.h` You should set the member variable `_img` as given parameter `img` You
 * should set the member variable `_numberThreads` as given parameter `numberThreads`
 * @param img: The image that will be filtered
 * @param numberThreads: The number of threads to use
 */
ThreadedFilteredImage::ThreadedFilteredImage(Image &img, int numberThreads) : FilteredImage(img) {
    _numberThreads = numberThreads;
}

/**
 * Implementation of `void ThreadedFilteredImage::applyKernel( Image & input, Image & output, Kernel
 * & K )` It's the similar as `applyKernel` in `class FilteredImage` But you need to do that job
 * using parallelism (using `# of threads = _numberThreads`) You will found these functions /
 * classes are useful: `std::vector<T>`, `std::thread`, `std::bind()`, `std::thread::join()`,
 * `std::thread::joinable()`
 */
void ThreadedFilteredImage::applyKernel(Image &input, Image &output, Kernel &K) {
    const int R = input.rows();
    const int C = input.cols();
    const int h = (K.rows() - 1) / 2;
    const int w = (K.cols() - 1) / 2;
    output.resize(R, C);
    output.fill(0);
    const int BLOCK = input.cols() / _numberThreads;
    int start = 0;

    std::vector<std::thread> threads;
    for (int i = 0; i < _numberThreads - 1; ++i) {
        threads.emplace_back(&ThreadedFilteredImage::applyKernelThread, this, start,
                             std::ref(input), std::ref(output), std::ref(K));
        start += BLOCK;
    }
    for (int r = h; r + h < R; ++r)
        for (int c = std::max(w, start); c + w < C; ++c)
            output(r, c) = (K * input.block(r - h, c - w, 2 * h + 1, 2 * w + 1)).sum();
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

/**
 * For parallelism, you will need to divide the image into `k` different parts
 * Which `k` is the number of threads.
 * This function is each thread's job
 * A simple idea is, divide the image by column.
 * It should start from `startingCol`, ends at `startingCol + (totalCol / numThreads)`
 * It's similar as `applyKernelThread` in `class FilteredImage`
 * But now, you should not convolute the whole image, just a part of that.
 */
void ThreadedFilteredImage::applyKernelThread(int startingCol, Image &input, Image &output,
                                              Kernel &K) {
    const int endCol = startingCol + input.cols() / _numberThreads;
    const int h = (K.rows() - 1) / 2;
    const int w = (K.cols() - 1) / 2;
    const int R = input.rows();
    const int C = input.cols();
    for (int r = h; r + h < R; ++r)
        for (int c = std::max(w, startingCol); c < endCol && c + w < C; ++c)
            output(r, c) = (K * input.block(r - h, c - w, 2 * h + 1, 2 * w + 1)).sum();
}