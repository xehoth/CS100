#include "FilteredImage.hpp"
#include <iostream>
#include <cmath>

/**
 * Implementation of `FilteredImage::FilteredImage( Image & img )`
 * This is a constructor of class FilteredImage, which is defined in `FilteredImage.hpp`
 * You should set the member variable `_img` as given parameter `img`
 * @param img: The image that will be filtered
 */
FilteredImage::FilteredImage(Image &img) : _img(img) {}

/**
 * Implementation of `Image & FilteredImage::get( int type )`
 * This is a member function of class FilteredImage, which is defined in `FilteredImage.hpp`
 * You should refer to the documentation, finish 4 types of applications
 * Hint: The following 4 cases should be very similar.
 * @param type: The type of Kernel
 */
Image &FilteredImage::get(int type) {
    auto p = _filteredImages.find(type);
    if (p != _filteredImages.end()) return *p->second;
    _filteredImages[type] = std::make_shared<Image>();
    auto &o = *_filteredImages[type];
    switch (type) {
        case BLUR: {
            Kernel K_blur(5, 5);
            K_blur << (2.0f / 159.0f), (4.0f / 159.0f), (5.0f / 159.0f), (4.0f / 159.0f),
                (2.0f / 159.0f), (4.0f / 159.0f), (9.0f / 159.0f), (12.0f / 159.0f),
                (9.0f / 159.0f), (4.0f / 159.0f), (5.0f / 159.0f), (12.0f / 159.0f),
                (15.0f / 159.0f), (12.0f / 159.0f), (5.0f / 159.0f), (4.0f / 159.0f),
                (9.0f / 159.0f), (12.0f / 159.0f), (9.0f / 159.0f), (4.0f / 159.0f),
                (2.0f / 159.0f), (4.0f / 159.0f), (5.0f / 159.0f), (4.0f / 159.0f), (2.0f / 159.0f);
            applyKernel(_img, o, K_blur);
            return o;
        }
        case DER_X: {
            Kernel K_der_x(3, 3);
            K_der_x << -1.0f, 0.0f, 1.0f, -2.0f, 0.0f, 2.0f, -1.0f, 0.0f, 1.0f;
            applyKernel(_img, o, K_der_x);
            return o;
        }
        case DER_Y: {
            Kernel K_der_y(3, 3);
            K_der_y << -1.0f, -2.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f;
            applyKernel(_img, o, K_der_y);
            return o;
        }
        case DER_MAG: {
            Kernel K_der_x(3, 3);
            K_der_x << -1.0f, 0.0f, 1.0f, -2.0f, 0.0f, 2.0f, -1.0f, 0.0f, 1.0f;
            Image dxRes;
            applyKernel(_img, dxRes, K_der_x);

            Kernel K_der_y(3, 3);
            K_der_y << -1.0f, -2.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f;
            Image dyRes;
            applyKernel(_img, dyRes, K_der_y);

            o.resize(_img.rows(), _img.cols());
            for (int i = 0; i < o.rows(); ++i)
                for (int j = 0; j < o.cols(); ++j)
                    o(i, j) = sqrt(dxRes(i, j) * dxRes(i, j) + dyRes(i, j) * dyRes(i, j));
            return o;
        }
        default: { std::cout << "Error: unrecognized kernel option\n"; }
    }
    return _img;
}

/**
 * Implementation of `void FilteredImage::applyKernel( Image & input, Image & output, Kernel & K )`
 * This is a member function of class FilteredImage, which is defined in `FilteredImage.hpp`
 * You should do convolution operation for the input image
 * That is, OUTPUT = INPUT * KERNEL, where `*` is the convolution operator
 * @param input: The input image
 * @param output: The output image
 * @param kernel: The convolution kernel
 */
void FilteredImage::applyKernel(Image &input, Image &output, Kernel &K) {
    const int h = (K.rows() - 1) / 2;
    const int w = (K.cols() - 1) / 2;
    const int R = input.rows();
    const int C = input.cols();
    output.resize(R, C);
    output.fill(0);
    for (int r = h; r + h < R; ++r)
        for (int c = w; c + w < C; ++c)
            output(r, c) = (K * input.block(r - h, c - w, 2 * h + 1, 2 * w + 1)).sum();
}