#include <iostream>
#include <vector>
#include <ctime> // For random number generation

using namespace std;

// Define a structure to represent a size fraction
struct SizeFraction {
    double size; // Particle size in mm
    double massPercentage; // Mass percentage
};

// Function to simulate crushing process
void simulateCrushing(vector<SizeFraction>& psd, double minSize, double maxSize) {
    // Randomly assign a new size to each particle within the specified range
    srand(time(nullptr)); // Seed the random number generator
    for (SizeFraction& fraction : psd) {
        fraction.size = minSize + (maxSize - minSize) * (rand() / static_cast<double>(RAND_MAX));
    }
}

// Function to calculate average particle size
double calculateAverageSize(const vector<SizeFraction>& psd) {
    double totalMass = 0.0;
    double weightedSum = 0.0;
    for (const SizeFraction& fraction : psd) {
        totalMass += fraction.massPercentage;
        weightedSum += fraction.size * fraction.massPercentage;
    }
    return weightedSum / totalMass;
}

int main() {
    // Read input parameters
    double feedRate; // Mass flow rate (ton/hour or kg/s)
    // Initialize the initial PSD (you can modify this based on your data)
    vector<SizeFraction> initialPSD = {
        {0.5, 20.0}, // Example: 0.5 mm size fraction with 20% mass
        {1.0, 30.0},
        // Add more size fractions as needed
    };
    double minCrusherSize = 0.1; // Minimum crusher size (mm)
    double maxCrusherSize = 10.0; // Maximum crusher size (mm)

    // Simulate crushing process
    simulateCrushing(initialPSD, minCrusherSize, maxCrusherSize);

    // Calculate average particle size of the crushed material
    double averageCrushedSize = calculateAverageSize(initialPSD);

    // Display final PSD and reduction ratio
    cout << "Final Particle Size Distribution (Crushed Material):\n";
    for (const SizeFraction& fraction : initialPSD) {
        cout << "Size: " << fraction.size << " mm, Mass Percentage: " << fraction.massPercentage << "%\n";
    }
    cout << "Overall Reduction Ratio: " << averageCrushedSize << " (feed size) / " << calculateAverageSize(initialPSD) << " (crushed size)\n";

    return 0;
}
