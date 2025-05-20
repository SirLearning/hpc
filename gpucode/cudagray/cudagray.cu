/*https://blog.imfing.com/2020/05/cuda-image-processing/
 * Convert RGB image to grayscale
 *
 * Load image with lodepng (https://github.com/lvandeve/lodepng)
 *
 * Sample image: lena.png
 *
 * Y = 0.2126*R + 0.7152*G + 0.0722*B
 *
 * */

#include <iostream>
#include <string>

#include "cuda_runtime.h"
#include "lodepng.h"

#define CHANNELS 4          // RGBA in PNG
#define BLOCK_SIZE 16       // Thread block size
__global__ void RGB2GrayKernel(uint8_t* input_image,
    uint8_t* output_image,
    int width, int height) {

    // input_image size: width*height*Channels
    // output_image size: width*height

    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if ((row < height) && (col < width)) {
        // Offset in Grayscale image
        int offset = row * width + col;

        // Get RGB values
        uint8_t r = input_image[offset * CHANNELS + 0];
        uint8_t g = input_image[offset * CHANNELS + 1];
        uint8_t b = input_image[offset * CHANNELS + 2];

        // Convert to grayscale
        output_image[offset] = 0.2126f * r + 0.7152f * g + 0.0722f * b;
    }
}


/* Main */
int main(int argc, char* argv[]) {
    const char* input_file = argc > 1 ? argv[1] : "lena.png";

    // Variables
    std::vector<uint8_t> image;
    unsigned int width, height;

    // Load image
    unsigned error = lodepng::decode(image, width, height, input_file);

    std::cout << width << " x " << height << std::endl;

    // Allocate memory for CUDA device
    size_t mem_size = width * height * sizeof(uint8_t);
    uint8_t* dev_input, * dev_output;

    cudaMalloc(&dev_input, mem_size * CHANNELS);
    cudaMemcpy(dev_input, image.data(), mem_size * CHANNELS, cudaMemcpyHostToDevice);

    cudaMalloc(&dev_output, mem_size);

    // Invoke CUDA kernel
    dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
    dim3 dimGrid((width + BLOCK_SIZE - 1) / dimBlock.x, (height + BLOCK_SIZE - 1) / dimBlock.y);

    RGB2GrayKernel <<<dimGrid, dimBlock >>> (dev_input, dev_output, width, height);

    // Copy output from device
    uint8_t* image_y = new uint8_t[width * height];
    cudaMemcpy(image_y, dev_output, mem_size, cudaMemcpyDeviceToHost);

    cudaFree(dev_input);
    cudaFree(dev_output);

    // Prepare for output
    std::vector<uint8_t> out_image(image.size(), 255);
    for (size_t i = 0; i < width * height; i++) {
        size_t offset = i * CHANNELS;
        out_image[offset + 0] = out_image[offset + 1] = out_image[offset + 2] = image_y[i];
    }

    // Save processed image
    std::string output_file(input_file);
    output_file += ".gray.png";

    error = lodepng::encode(output_file, out_image, width, height);

    delete[] image_y;
    return 0;
}


