# Fast ColorThief (C++ Only)

A high-performance C++ library for extracting the most dominant colors from images using the **Modified Median Cut Quantization** algorithm.  
Originally based on [`color-thief-py`](https://github.com/fengsp/color-thief-py), but rewritten for standalone C++ usage.

## 🚀 Features

- Extract dominant colors from any image using C++
- No third-party dependencies (except optional `stb_image.h`)
- Optionally supports CUDA for GPU acceleration
- Lightweight and fast (usable in real-time applications, games, or embedded tools)

---

## 🔧 Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/yourname/fast-colorthief-cpp
cd fast-colorthief-cpp
```

### 2. Integrate into your project
- Include the source files in your CMake or build system:

- If you need to load images, use [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h) or any other image loading library.

## 🖼 Example Usage

```cpp
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "FastColorThief.h"

int main() {
    int width, height, channels;
    uint8_t* data = stbi_load("example.jpg", &width, &height, &channels, 4); // force RGBA

    if (!data) {
        std::cerr << "Failed to load image.\n";
        return 1;
    }

    int color_count = 5;
    int quality = 10;

    auto colors = get_palette_cpp(data, width, height, color_count, quality);

    for (const auto& color : colors) {
        std::cout << "RGB: " << int(color[0]) << ", " << int(color[1]) << ", " << int(color[2]) << "\n";
    }

    stbi_image_free(data);
    return 0;
}
```

## ⚙️ API Reference

```cpp
std::vector<color_t> get_palette_cpp(
    uint8_t* data,
    int width,
    int height,
    int color_count,
    int quality
);
```

- `data`: pointer to RGBA image data

- `width`, `height`: image dimensions

- `color_count`: number of colors to extract (2–256)

- `quality`: sampling quality (1 = best, higher = faster but less accurate)
