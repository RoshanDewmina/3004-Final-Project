#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <vector>
#include <string>

class DataProcessor {
public:
    DataProcessor();
    void processData(const std::vector<double>& rawData);
    std::string generateMetrics() const;
    std::string provideRecommendations() const;

    static std::vector<double> processedData;
    static double average;
    static double variance;
    static int highValueCount;
};

bool isHighValue(double val); // Function for count_if

#endif // DATAPROCESSOR_H

