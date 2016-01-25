#pragma once

// Since freeglut is a C library, we can't easily use it in full C++, mostly because of callbacks

void StartGlut(); // Set callbacks and start main loop

// Callbacks below delegate the job to the WindowManager
void MouseClick(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void RenderWindow();
