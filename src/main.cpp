#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <ctime>

using namespace std;

const int NUM_SAMPLES = 15;
const int NUM_DIGITS = 10;

// Function to save the drawing
void saveDrawing(const vector<unsigned char>& imageData, ofstream& imageFile, int label, ofstream& labelFile) {
    // Save image data
    imageFile.write(reinterpret_cast<const char*>(imageData.data()), imageData.size());
    
    // Save label as a single byte
    unsigned char labelByte = static_cast<unsigned char>(label);
    labelFile.write(reinterpret_cast<const char*>(&labelByte), 1);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));  // Safely cast time_t to unsigned int

    int digit = 0;
    int count[NUM_DIGITS] = {0};  // Initialize counters for each digit
    vector<unsigned char> customImageData(28 * 28, 0);  // Initialize canvas as blank
    bool isDrawing = false;

    std::filesystem::create_directory("data"); // Create directory for data

    ofstream imageFile("data/images.bin", ios::binary);
    ofstream labelFile("data/labels.bin", ios::binary);

    if (!imageFile.is_open() || !labelFile.is_open()) {
        cerr << "Error: Could not open output files!" << endl;
        return 1;
    }

    while (true) {
        if (digit >= NUM_DIGITS) {
            cout << "Dataset creation completed!" << endl;
            break;
        }

        if (count[digit] >= NUM_SAMPLES) {
            digit++;
            continue;
        }

        cout << "Enter digit to draw (" << digit << ") or -1 to exit: ";
        int inputDigit;
        cin >> inputDigit;
        if (inputDigit == -1) break;
        if (inputDigit != digit) {
            cout << "Please enter the correct digit (" << digit << ") or -1 to exit." << endl;
            continue;
        }

        // Setup SFML window for drawing
        sf::RenderWindow window(sf::VideoMode(280, 280), "Draw a Digit");
        sf::RectangleShape pixel(sf::Vector2f(10, 10));

        // Drawing loop
        while (window.isOpen()) {
            window.setTitle("Draw the digit: " + std::to_string(digit) + " | Press 'S' to save and 'C' to clear");

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    isDrawing = true;
                }
                if (event.type == sf::Event::MouseButtonReleased) {
                    isDrawing = false;
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::C) {
                        fill(customImageData.begin(), customImageData.end(), 0);
                    } else if (event.key.code == sf::Keyboard::S) {
                        saveDrawing(customImageData, imageFile, digit, labelFile);
                        count[digit]++;
                        fill(customImageData.begin(), customImageData.end(), 0); // Clear after saving
                        if (count[digit] >= NUM_SAMPLES) {
                            window.close();
                        }
                    }
                }
            }

            if (isDrawing && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                int x = position.x / 10;  // Map mouse x to 28x28 grid
                int y = position.y / 10;  // Map mouse y to 28x28 grid
                if (x >= 0 && x < 28 && y >= 0 && y < 28) {
                    customImageData[y * 28 + x] = 255;  // Set pixel to white
                }
            }

            window.clear();
            for (int i = 0; i < 28; ++i) {
                for (int j = 0; j < 28; ++j) {
                    pixel.setPosition(j * 10.0f, i * 10.0f);  // Scale grid
                    if (customImageData[i * 28 + j] == 255) {
                        pixel.setFillColor(sf::Color::White);
                    } else {
                        pixel.setFillColor(sf::Color::Black);
                    }
                    window.draw(pixel);
                }
            }
            window.display();
        }
    }

    imageFile.close();
    labelFile.close();

    return 0;
}
