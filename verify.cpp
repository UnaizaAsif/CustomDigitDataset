#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;

const int IMAGE_SIZE = 28 * 28;

// Function to read images from the binary file
vector<vector<unsigned char>> readImages(const string& fileName, int& numImages) {
    ifstream file(fileName, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return {};
    }

    // Read the entire file content into a vector
    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);

    numImages = static_cast<int>(fileSize / IMAGE_SIZE);
    vector<vector<unsigned char>> images(numImages, vector<unsigned char>(IMAGE_SIZE));

    for (int i = 0; i < numImages; ++i) {
        file.read(reinterpret_cast<char*>(images[i].data()), IMAGE_SIZE);
    }

    return images;
}

// Function to read labels from the binary file
vector<int> readLabels(const string& fileName, int& numLabels) {
    ifstream file(fileName, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return {};
    }

    // Read the entire file content into a vector
    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);

    numLabels = static_cast<int>(fileSize);
    vector<int> labels(numLabels);

    for (int i = 0; i < numLabels; ++i) {
        unsigned char label;
        file.read(reinterpret_cast<char*>(&label), 1);
        labels[i] = static_cast<int>(label);  // Convert to int
    }

    return labels;
}

int main() {
    string imageFile = "data/images.bin";
    string labelFile = "data/labels.bin";
    int numImages = 0;
    int numLabels = 0;

    // Load images and labels
    vector<vector<unsigned char>> images = readImages(imageFile, numImages);
    vector<int> labels = readLabels(labelFile, numLabels);

    // Debug prints
    cout << "Number of images loaded: " << numImages << endl;
    cout << "Number of labels loaded: " << numLabels << endl;

    if (numImages != numLabels) {
        cerr << "Error: The number of images and labels do not match!" << endl;
        return 1;
    }

    // Print out the first few images and labels for verification
    for (int i = 0; i < min(10, numImages); ++i) {
        cout << "Label: " << labels[i] << endl;
        cout << "Image: " << endl;
        for (int y = 0; y < 28; ++y) {
            for (int x = 0; x < 28; ++x) {
                cout << (images[i][y * 28 + x] ? '#' : '.');
            }
            cout << endl;
        }
        cout << endl;
    }

    cout << "Dataset verification completed successfully!" << endl;
    return 0;
}
