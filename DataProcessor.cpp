#include "DataProcessor.h"
#include <cmath>
#include <sstream>
#include <algorithm>
#include <numeric>

// Constructor
DataProcessor::DataProcessor() {}

// Normalize data
std::vector<double> normalize(const std::vector<double>& rawData) {
    std::vector<double> normalized(rawData);
    double minVal = *std::min_element(rawData.begin(), rawData.end());
    double maxVal = *std::max_element(rawData.begin(), rawData.end());

    for (std::size_t i = 0; i < normalized.size(); ++i) {
        normalized[i] = (normalized[i] - minVal) / (maxVal - minVal);
    }

    return normalized;
}

// High value detection function
bool isHighValue(double val) {
    return val > 0.8;
}

// Preprocess and calculate metrics
void DataProcessor::processData(const std::vector<double>& rawData) {
    // Normalize raw data
    processedData = normalize(rawData);

    // Calculate metrics
    double sum = std::accumulate(processedData.begin(), processedData.end(), 0.0);
    average = sum / processedData.size();

    double sq_sum = std::inner_product(processedData.begin(), processedData.end(), processedData.begin(), 0.0);
    variance = sq_sum / processedData.size() - average * average;

    highValueCount = std::count_if(processedData.begin(), processedData.end(), isHighValue);
}

// Generate health metrics
std::string DataProcessor::generateMetrics() const {
    std::ostringstream metrics;
    metrics << "Average Value: " << average << "\n";
    metrics << "Variance: " << variance << "\n";
    metrics << "High Value Count (> 0.8): " << highValueCount << "\n";
    return metrics.str();
}

// Provide recommendations
std::string DataProcessor::provideRecommendations() const {
    std::ostringstream recommendations;
    if (average < 0.4) {
        recommendations << "Average value is low. Consider improving your diet and hydration.\n";
    } else if (variance > 0.2) {
        recommendations << "High variance detected. Focus on maintaining a stable routine.\n";
    }
    if (highValueCount > 5) {
        recommendations << "Multiple high values detected. Monitor for potential health risks.\n";
    } else {
        recommendations << "Metrics are within normal ranges. Keep up the good work!\n";
    }
    return recommendations.str();
}

// Static member definitions
std::vector<double> DataProcessor::processedData;
double DataProcessor::average = 0.0;
double DataProcessor::variance = 0.0;
int DataProcessor::highValueCount = 0;

