# Prism

A GPU-rendered music visualizer built in C, inspired by [cava](https://github.com/karlstav/cava).

![demo_screenshot](assets/screenshot.png)

---

Prism performs real-time FFT analysis on system audio and renders a smooth, logarithmically scaled frequency spectrum with user configurable decays, colors and gradients.

The project uses [miniaudio] to capture background audio, [KissFFT] as a library for the fast fourier transform and [raylib] as the GUI library to display the visualiser.

