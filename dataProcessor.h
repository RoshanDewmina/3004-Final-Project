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
};

#endif
