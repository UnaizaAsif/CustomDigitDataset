CustomDigitDataset

This is a C++ tool that allows users (especially kids) to draw digits using a graphical interface and save them in binary format (`images.bin`, `labels.bin`).  
The generated dataset is then used for training/testing digit classifiers such as the [KNNProject]((https://github.com/UnaizaAsif/KNN-Digit-Recognizer)).

---

Project Purpose

This project was built to:
- Help generate custom handwritten digit datasets (in MNIST-style format)
- Allow drawing digits through a mouse-based SFML interface
- Store data in binary format for further use in machine learning models

---

Folder Structure
CustomDigitDataset/
├── data/ ← Stores generated binary files (images.bin, labels.bin)
├── src/ ← Source code files (main, verify)
├── External/ ← External dependencies like SFML
├── CMakeLists.txt ← CMake build configuration

---

Dependencies

SFML (Simple and Fast Multimedia Library)
- Used for the drawing interface (graphics and window handling)
- Download from: [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php)

> Place SFML headers/binaries inside `External/SFML/` or configure your build to link SFML from your system path.

---

How to Use

1. **Build the project** using CMake or your preferred compiler (with SFML linked).
2. **Run the program** — a window will appear asking you to draw a digit (0–9).
3. Use your **mouse** to draw. Press:
   - `Enter` to submit
   - `C` to clear the screen
4. The image and label will be saved in:
   - `data/images.bin`
   - `data/labels.bin`

You can later use these files in projects like a KNN digit classifier.

---

Related Project

[KNNProject]((https://github.com/UnaizaAsif/KNN-Digit-Recognizer)) — A digit classification project that uses this dataset as training/testing input.

---

Notes

- The `/build/` folder is ignored and should not be uploaded.
- Binary files (`images.bin`, `labels.bin`) are created **after** running the program.
- The `verify.cpp` file (in `/src/`) can be used to inspect or test saved data.



