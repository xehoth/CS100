/**
 * Copyright (c) 2019, HongtuXu
 * All rights reserved.
 *
 * @author HongtuXu
 * @date 2019-10-26
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

const int ERRORCODE = -1;
const int INVALID_INPUT = 0;

class DataAnalyser {
   public:
    DataAnalyser(){};
    virtual ~DataAnalyser(){};
    /**
     * virtual function "calculate"
     * @param data: the data array need to be calculated
     * @param size: the length of the data
     * @return: the calculated result
     */
    virtual float calculate(float *data, size_t size) {
        std::cout << "ERROR: Try to access virtual function which is in base class" << std::endl;
        return ERRORCODE;
    };
};

// MaximumAnalyser
class MaximumAnalyser : public DataAnalyser {
    float calculate(float *data, size_t size) override {
        return size ? *std::max_element(data, data + size) : INVALID_INPUT;
    }
};

// MinimumAnalyser
class MinimumAnalyser : public DataAnalyser {
    float calculate(float *data, size_t size) override {
        return size ? *std::min_element(data, data + size) : INVALID_INPUT;
    }
};

// AverageAnalyser
class AverageAnalyser : public DataAnalyser {
    float calculate(float *data, size_t size) override {
        return size ? std::accumulate(data, data + size, 0.0f) / size : INVALID_INPUT;
    }
};

// MedianAnalyser
class MedianAnalyser : public DataAnalyser {
    float calculate(float *data, size_t size) override {
        if (!size) return INVALID_INPUT;
        if (size & 1) {
            std::nth_element(data, data + size / 2, data + size);
            return data[size / 2];
        }
        std::sort(data, data + size);
        return (data[size / 2 - 1] + data[size / 2]) / 2;
    }
};

// StdDevAnalyser
class StdDevAnalyser : public DataAnalyser {
    float calculate(float *data, size_t size) override {
        if (!size) return INVALID_INPUT;
        float avg = std::accumulate(data, data + size, 0.0f) / size;
        float ret = 0;
        for (size_t i = 0; i < size; i++) ret += (data[i] - avg) * (data[i] - avg);
        return sqrtf(ret / size);
    }
};

//////////////////////////////////////////////////////////////////////
///////////////// DO NOT SUBMIT THE FOLLOWING LINES //////////////////
//////////////////////////////////////////////////////////////////////
int main() {
    float arr[] = {0.3, -100, 1, 2, 5, 6, 9, 12, 2};
    DataAnalyser *foo = new StdDevAnalyser();                       /* it can be any of the
                         required 5 child classes */
    std::cout << std::fixed << foo->calculate(arr, 9) << std::endl; /* should be -100 in
  this case */
    delete foo;
    return 0;
}