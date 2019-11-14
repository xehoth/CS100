/**
 * Copyright (c) 2019, HongtuXu
 * All rights reserved.
 *
 * @author HongtuXu
 * @date 2019-10-26
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

class ReportParser {
   public:
    ReportParser(int numStudents, int numInfos);
    ~ReportParser();
    void readReport();
    void writeStructuredReport(int sortOption);
    // Add your own functions and variables here
   private:
    std::vector<std::vector<std::string> > data;
    int numStudents, numInfos;
};

ReportParser::ReportParser(int numStudents, int numInfos)
    : data(numStudents, std::vector<std::string>(numInfos)),
      numStudents(numStudents),
      numInfos(numInfos) {}

ReportParser::~ReportParser() {}

void ReportParser::readReport() {
    for (auto &v : data)
        for (auto &i : v) std::cin >> i;
}

void ReportParser::writeStructuredReport(int sortOption) {
    if (sortOption >= numInfos) return;

    std::sort(data.begin(), data.end(),
              [&](const std::vector<std::string> &a, const std::vector<std::string> &b) {
                  return a[sortOption] < b[sortOption];
              });
    std::vector<size_t> width(numInfos);
    for (size_t i = 0; i < width.size(); i++)
        for (int j = 0; j < numStudents; j++) width[i] = std::max(width[i], data[j][i].size());

    //  first line
    std::cout << '/';
    const int firstLineSeperateLen =
        3 * numInfos - 1 + std::accumulate(width.begin(), width.end(), 0);
    for (int i = 0; i < firstLineSeperateLen; i++) std::cout << '-';
    std::cout << "\\\n";

    for (size_t p = 0; p < data.size(); p++) {
        const auto &stu = data[p];
        std::cout << '|';
        for (size_t i = 0; i < stu.size(); i++)
            std::cout << ' ' << std::left << std::setw(width[i]) << std::setfill(' ') << stu[i]
                      << " |";
        std::cout << '\n';

        if (p != data.size() - 1) {
            std::cout << '|';
            for (size_t i = 0; i < stu.size(); i++) {
                std::cout << '-';
                for (size_t j = 0; j < width[i]; j++) std::cout << '-';
                std::cout << "-|";
            }
            std::cout << '\n';
        }
    }

    // last line
    std::cout << '\\';
    for (int i = 0; i < firstLineSeperateLen; i++) std::cout << '-';
    std::cout << '/';
}

//////////////////////////////////////////////////////////////////////
///////////////// DO NOT SUBMIT THE FOLLOWING LINES //////////////////
//////////////////////////////////////////////////////////////////////
int main() {
    int m, n, sortOption;
    std::cin >> n >> m >> sortOption;
    getchar();
    ReportParser p(m, n);
    p.readReport();
    p.writeStructuredReport(sortOption);
    return 0;
}
