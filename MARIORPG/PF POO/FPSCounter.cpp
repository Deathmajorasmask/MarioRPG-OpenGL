#include "FPSCounter.h"

FPSCounter::FPSCounter() {};
FPSCounter::~FPSCounter() {};

// return FPS
double FPSCounter::FPS_WM_TIMER() {

    frame++;

    // Get the current time in milliseconds
    DWORD currentTime = GetTickCount();

    // Check if 1 second (1000 ms) has passed
    if (currentTime - lastTime >= 1000) {
        // Calculate FPS
        fps = frame * 1000.0 / (currentTime - lastTime);

        // Reset frame counter
        frame = 0;

        // Update last time
        lastTime = currentTime;

        // Optional: Show or use calculated FPS
        char buffer[50];
        sprintf(buffer, "FPS: %.2f\n", fps);
        OutputDebugString(buffer);
        return fps;
    }
}