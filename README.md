# 🚀 Interactive Spaceship Controller (OpenGL)

An interactive, real-time 2D spaceship simulation built with **C++** and **OpenGL (GLUT)**. This project demonstrates core computer graphics concepts including 2D transformations, interactive UI rendering, and basic physics/animation.

---

## ✨ Key Features

* **Advanced 2D Transformations:** Smooth implementation of Translation, Rotation, Scaling (Zoom), and Shearing (Skew) using matrix operations.
* **Sci-Fi Responsive UI:** Custom-built overlay panels featuring rounded corners, alpha blending, and real-time telemetry updates (Position, Angle, Scale, Shear).
* **Dynamic Environment:** A continuous, auto-generating starfield background and a glowing celestial body (Moon) using `GL_BLEND`.
* **Weapon System:** Directional laser firing mechanics mathematically aligned with the spaceship's current transformation matrix (Rotation & Shearing).
* **Responsive Design:** The viewport and UI elements dynamically scale and reposition upon window resizing.

---

## 🎥 Gameplay Demo
<video src="https://github.com/user-attachments/assets/7c02ad07-4497-4ff1-a557-5c378c78f011" controls="controls" style="max-width: 100%;">
</video>

## 🎮 Keyboard Controls

| Key | Action |
| :--- | :--- |
| **Up / Down Arrows** | Translate Rocket (Y-Axis) |
| **Left / Right Arrows** | Translate Rocket (X-Axis) |
| **A / D** | Rotate Rocket (Counter-Clockwise / Clockwise) |
| **W / S** | Scale / Zoom (In / Out) |
| **Q / E** | Shear / Skew (Left / Right) |
| **SPACE** | Fire Laser |
| **R** | Reset all transformations to default |
| **ESC** | Exit Program |

---

## 🛠️ Tech Stack & Requirements

* **Language:** C++
* **Graphics Library:** OpenGL
* **Utility Toolkit:** GLUT (OpenGL Utility Toolkit)

---

## 🚀 How to Build and Run

### On Linux (Ubuntu/Debian)
1. Install the required OpenGL libraries:
   ```bash
   sudo apt-get install freeglut3-dev
   ```
2. Compile the project using `g++`:
   ```bash
   g++ main.cpp -o spaceship -lGL -lGLU -lglut
   ```
3. Run the executable:
   ```bash
   ./spaceship
   ```

### On Windows
* It is recommended to use an IDE like **Code::Blocks** or **Visual Studio** with the GLUT libraries pre-configured.
* Simply add `main.cpp` to your project, link the OpenGL libraries (`opengl32.lib`, `glu32.lib`, `glut32.lib`), build, and run.

---

## 🧠 Core Architecture Highlights
* **Main Game Loop:** Driven by `glutTimerFunc` executing at ~30 FPS for smooth animations.
* **Trigonometry & Physics:** Lasers calculate their trajectory using `sin()` and `cos()` of the current rotation angle, adjusted for the shear factor.
* **UI Rendering:** Orthographic projection (`gluOrtho2D`) ensures UI elements remain perfectly aligned with the screen boundaries regardless of window size.

---

## 👥 Contributors
*   **[Yusuf Husayn](https://github.com/yusuf-husayn)** - **[Yusuf Sayed](https://github.com/youssef-sayed8)** - **[Yusuf Ramadan](https://github.com/youseeframadan255)** - **[Yusuf Emad](https://github.com/yossifemadmhmd)**
*   **[Omar Khaled](https://github.com/Omdfhfgh)** - **[Yusuf Shaker](https://github.com/youssefmohamed63)** - **[Ahmad Yasser](https://github.com/ahmedyasser0-ay)** - **[Yehia Khalaf](https://github.com/yehia209)**

*Prepared for FCAI Beni-Suef University.*
