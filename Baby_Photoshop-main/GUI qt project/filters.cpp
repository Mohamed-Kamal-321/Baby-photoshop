#include<iostream>
using namespace std;

#include "filters.h"

#include<string>
#include <random>
#include <algorithm>
#include <cmath>
#include <QImage>
filters::filters() {
    flag=1;
}
void filters::greyscale(QImage& img) {

    for (int i = 0; i < img.width(); ++i) {
        for (int j = 0; j < img.height(); ++j) {
            // Get the RGB values of the current pixel
            QRgb pixel = img.pixel(i, j);
            int r = qRed(pixel);
            int g = qGreen(pixel);
            int b = qBlue(pixel);

            // Calculate the average of the RGB values for the current pixel
            int avg = (r + g + b) / 3;

            // Set each color channel (R, G, B) to the average value to achieve greyscale
            img.setPixel(i, j, qRgb(avg, avg, avg));
        }
    }
}
void filters::Black_and_White(QImage& image) {
    // Iterate over each pixel in the image
    for (int i = 0; i < image.width(); ++i) {
        for (int j = 0; j < image.height(); ++j) {
            // Get the RGB color of the current pixel
            QRgb pixel = image.pixel(i, j);

            // Extract the individual RGB components
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            // Calculate the average of the RGB values for the current pixel
            int avg = (red + green + blue) / 3;

            // Set each color channel (R, G, B) to either 0 (black) or 255 (white) based on the average value
            if (avg < 128)
                image.setPixel(i, j, qRgb(0, 0, 0)); // Set the pixel to black
            else
                image.setPixel(i, j, qRgb(255, 255, 255)); // Set the pixel to white
        }
    }
}
void filters::invert(QImage& image) {
    // Iterate over each pixel in the image
    for (int i = 0; i < image.width(); ++i) {
        for (int j = 0; j < image.height(); ++j) {
            // Get the RGB color of the current pixel
            QRgb pixel = image.pixel(i, j);

            // Extract the individual RGB components
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            // Invert each color channel by subtracting its value from 255
            red = 255 - red;
            green = 255 - green;
            blue = 255 - blue;

            // Set the inverted RGB values back to the pixel
            image.setPixel(i, j, qRgb(red, green, blue));
        }
    }
}
void filters::lighten(QImage& image) {

    // Lighten the image by 50%
    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            // Get the RGB color of the current pixel
            QRgb pixel = image.pixel(i, j);

            // Extract the individual RGB components
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            // Lighten each color channel by multiplying by 1.5 (50%)
            red = qMin(int(red * 1.5), 255);
            green = qMin(int(green * 1.5), 255);
            blue = qMin(int(blue * 1.5), 255);


            // Set the new RGB values back to the pixel
            image.setPixel(i, j, qRgb(red, green, blue));
        }
    }


}
void filters::darken(QImage&image){
    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            // Get the RGB color of the current pixel
            QRgb pixel = image.pixel(i, j);

            // Extract the individual RGB components
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);


            red = max(int(red * 0.5), 0);
            green = max(int(green * 0.5), 0);
            blue = max(int(blue * 0.5), 0);

            // Set the new RGB values back to the pixel
            image.setPixel(i, j, qRgb(red, green, blue));
        }
    }
}
void filters:: Detect_Image_Edges(QImage& image) {
    // Convert the image to grayscale
    for (int i = 0; i < image.width(); ++i) {
        for (int j = 0; j < image.height(); ++j) {
            // Get the RGB color of the current pixel
            QRgb pixel = image.pixel(i, j);

            // Extract the individual RGB components
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            // Calculate the average of the RGB values for the current pixel
            int avg = (red + green + blue) / 3;

            // Set each color channel (R, G, B) to the average value to achieve grayscale
            image.setPixel(i, j, qRgb(avg, avg, avg));
        }
    }

    // Apply edge detection
    QImage newImage(image.width(), image.height(), QImage::Format_RGB888);

    int threshold = 50; // Adjust threshold as needed

    for (int i = 1; i < image.width() - 1; i++) {
        for (int j = 1; j < image.height() - 1; j++) {
            int current = qRed(image.pixel(i, j)); // Grayscale value of the current pixel

            // Calculate differences with neighboring pixels
            int top = qRed(image.pixel(i + 1, j)) - current;
            int bottom = qRed(image.pixel(i - 1, j)) - current;
            int right = qRed(image.pixel(i, j + 1)) - current;
            int left = qRed(image.pixel(i, j - 1)) - current;
            int top_right = qRed(image.pixel(i + 1, j + 1)) - current;
            int bottom_left = qRed(image.pixel(i - 1, j - 1)) - current;
            int top_left = qRed(image.pixel(i + 1, j - 1)) - current;
            int bottom_right = qRed(image.pixel(i - 1, j + 1)) - current;

            // Check if any difference is above threshold
            if (top > threshold || bottom > threshold || right > threshold || left > threshold ||
                top_right > threshold || bottom_left > threshold || top_left > threshold || bottom_right > threshold) {
                newImage.setPixel(i, j, qRgb(0, 0, 0)); // Set pixel to black (edge)
            } else {
                newImage.setPixel(i, j, qRgb(255, 255, 255)); // Set pixel to white (background)
            }
        }
    }

    image = newImage; // Update the input image with the edge-detected image
}
void filters::blur(QImage& s) {
    QImage tmp_image = s;
    int sum_r,sum_g,sum_b, pixels_num;
    for (int i = 0; i < s.width(); i++) {
        for (int j = 0; j < s.height(); j++) {

                sum_r=0,sum_g=0,sum_b=0, pixels_num = 1;

                // Top left (4 units away)
                if (i > 3 && j > 3) {
                    QRgb pixel = tmp_image.pixel(i - 4, j - 4);
                    sum_r += qRed(pixel);
                    sum_g += qGreen(pixel);
                    sum_b += qBlue(pixel);
                    pixels_num++;
                }

                // Top (4 units away)
                if (i > 3) {
                    QRgb pixel = tmp_image.pixel(i - 4, j);
                    sum_r += qRed(pixel);
                    sum_g += qGreen(pixel);
                    sum_b += qBlue(pixel);
                    pixels_num++;
                }

                // Top right (4 units away)
                if (i > 3 && j < s.height() - 4) {
                    QRgb pixel = tmp_image.pixel(i - 4, j + 4);
                    sum_r += qRed(pixel);
                    sum_g += qGreen(pixel);
                    sum_b += qBlue(pixel);
                    pixels_num++;
                }

                // Left (4 units away)
                if (j > 3) {
                    QRgb pixel = tmp_image.pixel(i, j - 4);
                    sum_r += qRed(pixel);
                    sum_g += qGreen(pixel);
                    sum_b += qBlue(pixel);
                    pixels_num++;
                }

                // Right (4 units away)
                if (j < s.height() - 4) {
                    QRgb pixel = tmp_image.pixel(i, j + 4);
                    sum_r += qRed(pixel);
                    sum_g += qGreen(pixel);
                    sum_b += qBlue(pixel);
                    pixels_num++;
                }

                // Bottom left (4 units away)
                if (i < s.width() - 4 &&( j > 3)) {
                    QRgb pixel = tmp_image.pixel(i + 4, j - 4);
                    sum_r += qRed(pixel);
                    sum_g += qGreen(pixel);
                    sum_b += qBlue(pixel);
                    pixels_num++;
                }

                // Bottom (4 units away)
                if (i < s.width() - 4) {
                    QRgb pixel = tmp_image.pixel(i + 4, j);
                    sum_r += qRed(pixel);
                    sum_g += qGreen(pixel);
                    sum_b += qBlue(pixel);
                    pixels_num++;
                }

                // Bottom right (4 units away)
                if (i < s.width() - 4 && j < s.height() - 4) {
                    QRgb pixel = tmp_image.pixel(i + 4, j + 4);
                    sum_r += qRed(pixel);
                    sum_g += qGreen(pixel);
                    sum_b += qBlue(pixel);
                    pixels_num++;
                }

                // Calculate average and assign to the pixel in the original image
                s.setPixel(i, j, qRgb(sum_r / pixels_num, sum_g / pixels_num, sum_b / pixels_num));

        }
    }
}
void filters::wano(QImage& s) {
    // Iterate over each pixel in the image
    for (int i = 0; i < s.width(); ++i) {
        for (int j = 0; j < s.height(); ++j) {
            QRgb pixel = s.pixel(i, j);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            // Apply the land of Wano filter transformation to each color channel
            red = static_cast<int>(red * 0.825 + 0.175 * 255.0 * (0 == 0 || 0 == 1));
            green = static_cast<int>(green * 0.825 + 0.175 * 255.0 * (1 == 0 || 1 == 1));
            blue = static_cast<int>(blue * 0.825 + 0.175 * 255.0 * (2 == 0 || 2 == 1));

            // Clamp values to [0, 255]
            red = (red < 0) ? 0 : ((red > 255) ? 255 : red);
            green = (green < 0) ? 0 : ((green > 255) ? 255 : green);
            blue = (blue < 0) ? 0 : ((blue > 255) ? 255 : blue);

            // Set the transformed pixel values back to the image
            s.setPixel(i, j, qRgb(red, green, blue));
        }
    }

}
void filters::old_tv(QImage& image) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-25, 25);

    // Apply noise to each pixel
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QRgb pixel = image.pixel(x, y);
            int r = qRed(pixel);
            int g = qGreen(pixel);
            int b = qBlue(pixel);

            int noise = dis(gen);
            r = clamp(r + noise, 0, 255);
            g = clamp(g + noise, 0, 255);
            b = clamp(b + noise, 0, 255);

            image.setPixel(x, y, qRgb(r, g, b));
        }
    }



}
void filters ::purple(QImage& s) {
    // Iterate over each pixel in the image
    for (int i = 0; i < s.width(); ++i) {
        for (int j = 0; j < s.height(); ++j) {
            QRgb pixel = s.pixel(i, j);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            // Decrease the green channel intensity by 25%
            green = static_cast<int>(green * 0.75);

            // Increase the intensity of each channel by 20%, clamping to 255
            red = static_cast<int>(min(red * 1.2, 255.0));
            green = static_cast<int>(min(green * 1.2, 255.0));
            blue = static_cast<int>(min(blue * 1.2, 255.0));

            // Set the transformed pixel values back to the image
            s.setPixel(i, j, qRgb(red, green, blue));
        }
    }
}
void filters ::infrared(QImage& s) {
    // Iterate over each pixel in the image
    for (int i = 0; i < s.width(); ++i) {
        for (int j = 0; j < s.height(); ++j) {
            QRgb pixel = s.pixel(i, j);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            // Reduce the intensity of the red channel by 90%
            red = static_cast<int>(red * 0.1);

            // Invert each color channel by subtracting its value from 255
            red = static_cast<int>(255 - red);
            green = static_cast<int>(255 - green);
            blue = static_cast<int>(255 - blue);

            // Set the transformed pixel values back to the image
            s.setPixel(i, j, qRgb(red, green, blue));
        }
    }
}
void filters::oil_paint(QImage& img) {
    int width = img.width();
    int height = img.height();
    int radius = 3;
    float intensityLevels = 5.0;

    for (int y = radius; y < height - radius; y++) {
        for (int x = radius; x < width - radius; x++) {
            int IntensityCount[256] = {0};
            int nSumR[256] = {0};
            int nSumG[256] = {0};
            int nSumB[256] = {0};

            for (int dy = -radius; dy <= radius; dy++) {
                for (int dx = -radius; dx <= radius; dx++) {
                    int xx = x + dx;
                    int yy = y + dy;

                    if (xx >= 0 && xx < width && yy >= 0 && yy < height) {
                        QRgb pixel = img.pixel(xx, yy);
                        int r = qRed(pixel);
                        int g = qGreen(pixel);
                        int b = qBlue(pixel);

                        int Intensity = int((((r + g + b) / 3.0) * intensityLevels) / 255.0);
                        if (Intensity > 255) {
                            Intensity = 255;
                        }

                        int i = Intensity;
                        IntensityCount[i]++;
                        nSumR[i] += r;
                        nSumG[i] += g;
                        nSumB[i] += b;
                    }
                }
            }

            int Max = 0;
            int maxIndex = 0;
            for (int i = 0; i < 256; i++) {
                if (IntensityCount[i] > Max) {
                    Max = IntensityCount[i];
                    maxIndex = i;
                }
            }

            img.setPixel(x, y, qRgb(nSumR[maxIndex] / Max, nSumG[maxIndex] / Max, nSumB[maxIndex] / Max));
        }
    }
}
void filters::flip_horizontal(QImage& img) {
    // Create a copy of the original image
    QImage flippedImg = img.copy();

    for (int i = 0; i < img.width(); ++i) {
        for (int j = 0; j < img.height(); ++j) {
            QRgb pixel = img.pixel(i, j);
            flippedImg.setPixel(img.width() - 1 - i, j, pixel);
        }
    }
    // Replace the original image with the flipped image
    img = flippedImg;
}
void filters::flip_vertical(QImage& img) {
    // Create a copy of the original image
    QImage flippedImg = img.copy();

    // Perform vertical flip

    for (int i = 0; i < img.width(); ++i) {
        for (int j = 0; j < img.height(); ++j) {
            QRgb pixel = img.pixel(i, j);
            flippedImg.setPixel(i, img.height() - 1 - j, pixel);
        }
    }

    // Replace the original image with the flipped image
    img = flippedImg;
}
void filters::rotate(QImage& img) {

    QImage rotated(img.height(), img.width(), img.format());
    for (int i = 0; i < img.width(); ++i) {
        for (int j = 0; j < img.height(); ++j) {
            QRgb pixel = img.pixel(i, j);
            rotated.setPixel( img.height() - 1 - j,i, pixel);
        }
    }
    img = rotated;

}
void filters::blur_edges(QImage& s) {
    QImage tmp_image = s;
    int sum_r,sum_g,sum_b, pixels_num;
    for (int i = 0; i < s.width(); i++) {
        for (int j = 0; j < s.height(); j++) {

            sum_r=0,sum_g=0,sum_b=0, pixels_num = 1;
            float x = s.width() * .05;
            float y = s.height() * .05;
            // Check if the pixel is near the edges
            bool nearEdge = (i < x || i >= s.width() - x || j < y || j >= s.height() - y);
            if(nearEdge){
                // Top left (4 units away)
                if (i > 3 && j > 3) {
                    QRgb pixel = tmp_image.pixel(i - 4, j - 4);
                    sum_r += qRed(pixel);
                    sum_g += qGreen(pixel);
                    sum_b += qBlue(pixel);
                    pixels_num++;
                }

                // Top (4 units away)
                if (i > 3) {
                    QRgb pixel = tmp_image.pixel(i - 4, j);
                    sum_r += qRed(pixel);
                    sum_g += qGreen(pixel);
                    sum_b += qBlue(pixel);
                    pixels_num++;
                }

                // Top right (4 units away)
                if (i > 3 && j < s.height() - 4) {
                    QRgb pixel = tmp_image.pixel(i - 4, j + 4);
                    sum_r += qRed(pixel);
                    sum_g += qGreen(pixel);
                    sum_b += qBlue(pixel);
                    pixels_num++;
                }

                // Left (4 units away)
                if (j > 3) {
                    QRgb pixel = tmp_image.pixel(i, j - 4);
                    sum_r += qRed(pixel);
                    sum_g += qGreen(pixel);
                    sum_b += qBlue(pixel);
                    pixels_num++;
                }

                // Right (4 units away)
                if (j < s.height() - 4) {
                    QRgb pixel = tmp_image.pixel(i, j + 4);
                    sum_r += qRed(pixel);
                    sum_g += qGreen(pixel);
                    sum_b += qBlue(pixel);
                    pixels_num++;
                }

                // Bottom left (4 units away)
                if (i < s.width() - 4 &&( j > 3)) {
                    QRgb pixel = tmp_image.pixel(i + 4, j - 4);
                    sum_r += qRed(pixel);
                    sum_g += qGreen(pixel);
                    sum_b += qBlue(pixel);
                    pixels_num++;
                }

                // Bottom (4 units away)
                if (i < s.width() - 4) {
                    QRgb pixel = tmp_image.pixel(i + 4, j);
                    sum_r += qRed(pixel);
                    sum_g += qGreen(pixel);
                    sum_b += qBlue(pixel);
                    pixels_num++;
                }

                // Bottom right (4 units away)
                if (i < s.width() - 4 && j < s.height() - 4) {
                    QRgb pixel = tmp_image.pixel(i + 4, j + 4);
                    sum_r += qRed(pixel);
                    sum_g += qGreen(pixel);
                    sum_b += qBlue(pixel);
                    pixels_num++;
                }

                // Calculate average and assign to the pixel in the original image
                s.setPixel(i, j, qRgb(sum_r / pixels_num, sum_g / pixels_num, sum_b / pixels_num));
            }
        }
    }
}
void filters:: crop(QImage& image, int x, int y, int w, int h) {
    // Create a new QImage object to store the cropped image
    QImage croppedImage(w, h, image.format());

    // Copy pixels from the original image to the cropped image
    for (int i = x; i < w + x; ++i) {
        for (int j = y; j < h + y; ++j) {
            if (i >= 0 && i < image.width() && j >= 0 && j < image.height()) {
                croppedImage.setPixelColor(i - x, j - y, image.pixelColor(i, j));
            }
        }
    }

    // Update the original image to the cropped image
    image = croppedImage;
}
void filters::fancy1_frame(QImage& img) {
    // Define the thickness of the white lines
    int thickness1 = 20;
    int thickness2 = 10;

    // Create a white color scalar
    QRgb white = qRgb(255, 255, 255);

    // Add the first set of white lines
    // Top line
    for (int x = 0; x < img.width(); x++) {
        for (int t = 0; t < thickness1; t++) {
            img.setPixel(x, t, white);
        }
    }

    // Bottom line
    for (int x = 0; x < img.width(); x++) {
        for (int t = 0; t < thickness1; t++) {
            img.setPixel(x, img.height() - 1 - t, white);
        }
    }

    // Left line
    for (int y = 0; y < img.height(); y++) {
        for (int t = 0; t < thickness1; t++) {
            img.setPixel(t, y, white);
        }
    }

    // Right line
    for (int y = 0; y < img.height(); y++) {
        for (int t = 0; t < thickness1; t++) {
            img.setPixel(img.width() - 1 - t, y, white);
        }
    }

    // Add the second set of white lines inside the first set
    // Top line
    for (int x = thickness1 + 20; x < img.width() - (thickness1 + 20); x++) {
        for (int t = 0; t < thickness2; t++) {
            img.setPixel(x, t + thickness1 + 20, white);
        }
    }

    // Bottom line
    for (int x = thickness1 + 20; x < img.width() - (thickness1 + 20); x++) {
        for (int t = 0; t < thickness2; t++) {
            img.setPixel(x, img.height() - 1 - (t + thickness1 + 20), white);
        }
    }

    // Left line
    for (int y = thickness1 + 20; y < img.height() - (thickness1 + 20); y++) {
        for (int t = 0; t < thickness2; t++) {
            img.setPixel(t + thickness1 + 20, y, white);
        }
    }

    // Right line
    for (int y = thickness1 + 20; y < img.height() - (thickness1 + 20); y++) {
        for (int t = 0; t < thickness2; t++) {
            img.setPixel(img.width() - 1 - (t + thickness1 + 20), y, white);
        }
    }
}
void filters::resizeImage(QImage& image, int newWidth, int newHeight) {
    // Create a new image object with the specified dimensions
    QImage resizedImage(newWidth, newHeight, image.format());

    // Calculate the ratio of old image width and height to new width and height
    float x_ratio = static_cast<float>(image.width() - 1) / newWidth;
    float y_ratio = static_cast<float>(image.height() - 1) / newHeight;

    // Iterate over each pixel in the resized image
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // Calculate the nearest integer coordinates in the old image
            float nearestX = x_ratio * x;
            float nearestY = y_ratio * y;
            int x1 = static_cast<int>(nearestX);
            int y1 = static_cast<int>(nearestY);

            // Calculate the differences for interpolation
            float x_diff = nearestX - x1;
            float y_diff = nearestY - y1;

            // Interpolate each color channel separately using bilinear interpolation
            QRgb pixel1 = image.pixel(x1, y1);
            QRgb pixel2 = image.pixel(x1 + 1, y1);
            QRgb pixel3 = image.pixel(x1, y1 + 1);
            QRgb pixel4 = image.pixel(x1 + 1, y1 + 1);

            int red = static_cast<int>((1 - x_diff) * (1 - y_diff) * qRed(pixel1) +
                                       x_diff * (1 - y_diff) * qRed(pixel2) +
                                       (1 - x_diff) * y_diff * qRed(pixel3) +
                                       x_diff * y_diff * qRed(pixel4));

            int green = static_cast<int>((1 - x_diff) * (1 - y_diff) * qGreen(pixel1) +
                                         x_diff * (1 - y_diff) * qGreen(pixel2) +
                                         (1 - x_diff) * y_diff * qGreen(pixel3) +
                                         x_diff * y_diff * qGreen(pixel4));

            int blue = static_cast<int>((1 - x_diff) * (1 - y_diff) * qBlue(pixel1) +
                                        x_diff * (1 - y_diff) * qBlue(pixel2) +
                                        (1 - x_diff) * y_diff * qBlue(pixel3) +
                                        x_diff * y_diff * qBlue(pixel4));

            // Set the interpolated color in the resized image
            QRgb newPixel = qRgb(red, green, blue);
            resizedImage.setPixel(x, y, newPixel);
        }
    }

    // Update the original image with the resized image
    image = resizedImage;
}
void filters:: skew(QImage& image, double angle) {
    // Flip the image horizontally before skewing
    flip_horizontal(image);

    // Convert angle from degrees to radians
    double radians = angle * (M_PI / 180.0);

    int width = image.width();
    int height = image.height();

    // Calculate dimensions of the skewed image
    int newWidth = width + static_cast<int>(abs(height * tan(radians)))/ 2;
    int newHeight = height;

    // Create a new image to store the skewed result
    QImage skewedImage(newWidth, newHeight, image.format());

    // Perform skewing by mapping pixels from the original image to the skewed image
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // Calculate original coordinates
            int srcX = x - static_cast<int>((y * std::tan(radians)) / 2);
            int srcY = y;

            // Check if the original coordinates are within bounds
            if (srcX >= 0 && srcX < width && srcY >= 0 && srcY < height) {
                // Copy pixel values from the original image to the skewed image
                skewedImage.setPixelColor(x, y, image.pixelColor(srcX, srcY));
            } else {
                // Set background pixels to white
                skewedImage.setPixelColor(x, y, QColor(Qt::white));
            }
        }
    }

    // Replace the original image with the skewed image
    image = skewedImage;
    crop(image,0,0,newWidth,newHeight);
    // Flip the image horizontally after skewing
    flip_horizontal(image);
}
void filters::merge(QImage& image, QImage& image2) {
    // Check if the images are in RGB format, convert to RGB if not
    if (image.format() != QImage::Format_RGB888) {
        image = image.convertToFormat(QImage::Format_RGB888);
    }
    if (image2.format() != QImage::Format_RGB888) {
        image2 = image2.convertToFormat(QImage::Format_RGB888);
    }

    // Determine the dimensions of the merged image
    int newWidth = std::max(image.width(), image2.width());
    int newHeight = std::max(image.height(), image2.height());

    // Create an output image with the merged dimensions
    QImage output(newWidth, newHeight, QImage::Format_RGB888);

    // Resize both images to match the merged dimensions
    resizeImage(image, newWidth, newHeight);
    resizeImage(image2, newWidth, newHeight);

    // Merge the two images pixel by pixel
    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            // Get the RGB values of the corresponding pixels from both images
            QRgb pixel1 = image.pixel(i, j);
            QRgb pixel2 = image2.pixel(i, j);

            // Calculate the average value of RGB components for merging
            int red = (qRed(pixel1) + qRed(pixel2)) / 2;
            int green = (qGreen(pixel1) + qGreen(pixel2)) / 2;
            int blue = (qBlue(pixel1) + qBlue(pixel2)) / 2;

            // Set the merged pixel value in the output image
            QRgb mergedPixel = qRgb(red, green, blue);
            output.setPixel(i, j, mergedPixel);
        }
    }

    // Update the original image with the merged result
    image = output;
}
void filters::Contrast_plus(QImage& image) {
    float factor = 1.25f;
    float midpoint = 127.5f;
    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            QRgb pixel = image.pixel(x, y);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            // Apply contrast adjustment to each color channel
            float newRed = (red - midpoint) * factor + midpoint;
            float newGreen = (green - midpoint) * factor + midpoint;
            float newBlue = (blue - midpoint) * factor + midpoint;

            // Clamp the new values to the range [0, 255]
            newRed = std::min(255.0f, std::max(0.0f, newRed));
            newGreen = std::min(255.0f, std::max(0.0f, newGreen));
            newBlue = std::min(255.0f, std::max(0.0f, newBlue));

            // Set the adjusted pixel values in the image
            image.setPixel(x, y, qRgb(static_cast<int>(newRed), static_cast<int>(newGreen), static_cast<int>(newBlue)));
        }
    }
}
void filters::Contrast_minus(QImage& image) {
    float factor = 0.75f;
    float midpoint = 127.5f;
    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            QRgb pixel = image.pixel(x, y);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            // Apply contrast reduction to each color channel
            float newRed = (red - midpoint) * factor + midpoint;
            float newGreen = (green - midpoint) * factor + midpoint;
            float newBlue = (blue - midpoint) * factor + midpoint;

            // Clamp the new values to the range [0, 255]
            newRed = std::min(255.0f, std::max(0.0f, newRed));
            newGreen = std::min(255.0f, std::max(0.0f, newGreen));
            newBlue = std::min(255.0f, std::max(0.0f, newBlue));

            // Set the adjusted pixel values in the image
            image.setPixel(x, y, qRgb(static_cast<int>(newRed), static_cast<int>(newGreen), static_cast<int>(newBlue)));
        }
    }
}
void filters::applySepiaTone(QImage& image) {

    int width = image.width();
    int height = image.height();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            QRgb pixel = image.pixel(x, y);
            int r = qRed(pixel);
            int g = qGreen(pixel);
            int b = qBlue(pixel);

            int newR = static_cast<int>((0.393 * r) + (0.769 * g) + (0.189 * b));
            int newG = static_cast<int>((0.349 * r) + (0.686 * g) + (0.168 * b));
            int newB = static_cast<int>((0.272 * r) + (0.534 * g) + (0.131 * b));

            // Clamp RGB values to ensure they are within [0, 255]
            newR = std::min(std::max(newR, 0), 255);
            newG = std::min(std::max(newG, 0), 255);
            newB = std::min(std::max(newB, 0), 255);

            image.setPixel(x, y, qRgb(newR, newG, newB));
        }
    }
}
void filters::no_aspect(QImage& image, int newWidth, int newHeight) {
    // Create a new QImage object with resized dimensions
    QImage resizedImage(newWidth, newHeight, image.format());
    // Calculate the ratio of old image width and height to new width and height
    float x_ratio = static_cast<float>(image.width() - 1) / newWidth;
    float y_ratio = static_cast<float>(image.height() - 1) / newHeight;

    // Iterate over each pixel in the resized image
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // Calculate the nearest integer coordinates in the old image
            float nearestX = x_ratio * x;
            float nearestY = y_ratio * y;
            int x1 = static_cast<int>(nearestX);
            int y1 = static_cast<int>(nearestY);

            // Calculate the differences for interpolation
            float x_diff = nearestX - x1;
            float y_diff = nearestY - y1;

            // Interpolate each color channel separately using bilinear interpolation
            QRgb pixel1 = image.pixel(x1, y1);
            QRgb pixel2 = image.pixel(x1 + 1, y1);
            QRgb pixel3 = image.pixel(x1, y1 + 1);
            QRgb pixel4 = image.pixel(x1 + 1, y1 + 1);

            int red = static_cast<int>((1 - x_diff) * (1 - y_diff) * qRed(pixel1) +
                                       x_diff * (1 - y_diff) * qRed(pixel2) +
                                       (1 - x_diff) * y_diff * qRed(pixel3) +
                                       x_diff * y_diff * qRed(pixel4));

            int green = static_cast<int>((1 - x_diff) * (1 - y_diff) * qGreen(pixel1) +
                                         x_diff * (1 - y_diff) * qGreen(pixel2) +
                                         (1 - x_diff) * y_diff * qGreen(pixel3) +
                                         x_diff * y_diff * qGreen(pixel4));

            int blue = static_cast<int>((1 - x_diff) * (1 - y_diff) * qBlue(pixel1) +
                                        x_diff * (1 - y_diff) * qBlue(pixel2) +
                                        (1 - x_diff) * y_diff * qBlue(pixel3) +
                                        x_diff * y_diff * qBlue(pixel4));

            // Set the interpolated color in the resized image
            QRgb newPixel = qRgb(red, green, blue);
            resizedImage.setPixel(x, y, newPixel);
        }
    }

    // Assign the resized image data to the original image
    image = resizedImage;
}
void filters::aspect_width(QImage& image, int newWidth) {
    // Calculate the new height based on the aspect ratio
    int newHeight = static_cast<int>(static_cast<float>(image.height()) / image.width() * newWidth);

    // Create a new QImage object with resized dimensions
    QImage resizedImage(newWidth, newHeight, image.format());
    // Calculate the ratio of old image width and height to new width and height
    float x_ratio = static_cast<float>(image.width() - 1) / newWidth;
    float y_ratio = static_cast<float>(image.height() - 1) / newHeight;

    // Iterate over each pixel in the resized image
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // Calculate the nearest integer coordinates in the old image
            float nearestX = x_ratio * x;
            float nearestY = y_ratio * y;
            int x1 = static_cast<int>(nearestX);
            int y1 = static_cast<int>(nearestY);

            // Calculate the differences for interpolation
            float x_diff = nearestX - x1;
            float y_diff = nearestY - y1;

            // Interpolate each color channel separately using bilinear interpolation
            QRgb pixel1 = image.pixel(x1, y1);
            QRgb pixel2 = image.pixel(x1 + 1, y1);
            QRgb pixel3 = image.pixel(x1, y1 + 1);
            QRgb pixel4 = image.pixel(x1 + 1, y1 + 1);

            int red = static_cast<int>((1 - x_diff) * (1 - y_diff) * qRed(pixel1) +
                                       x_diff * (1 - y_diff) * qRed(pixel2) +
                                       (1 - x_diff) * y_diff * qRed(pixel3) +
                                       x_diff * y_diff * qRed(pixel4));

            int green = static_cast<int>((1 - x_diff) * (1 - y_diff) * qGreen(pixel1) +
                                         x_diff * (1 - y_diff) * qGreen(pixel2) +
                                         (1 - x_diff) * y_diff * qGreen(pixel3) +
                                         x_diff * y_diff * qGreen(pixel4));

            int blue = static_cast<int>((1 - x_diff) * (1 - y_diff) * qBlue(pixel1) +
                                        x_diff * (1 - y_diff) * qBlue(pixel2) +
                                        (1 - x_diff) * y_diff * qBlue(pixel3) +
                                        x_diff * y_diff * qBlue(pixel4));

            // Set the interpolated color in the resized image
            QRgb newPixel = qRgb(red, green, blue);
            resizedImage.setPixel(x, y, newPixel);
        }
    }
    // Assign the resized image data to the original image
    image = resizedImage;
}
void filters::aspect_height(QImage& image, int newHeight) {
    // Calculate the new width based on the aspect ratio
    int newWidth = static_cast<int>(static_cast<float>(image.width()) / image.height() * newHeight);

    // Create a new QImage object with resized dimensions
    QImage resizedImage(newWidth, newHeight, image.format());

    // Calculate the ratio of old image width and height to new width and height
    float x_ratio = static_cast<float>(image.width() - 1) / newWidth;
    float y_ratio = static_cast<float>(image.height() - 1) / newHeight;

    // Iterate over each pixel in the resized image
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // Calculate the nearest integer coordinates in the old image
            float nearestX = x_ratio * x;
            float nearestY = y_ratio * y;
            int x1 = static_cast<int>(nearestX);
            int y1 = static_cast<int>(nearestY);

            // Calculate the differences for interpolation
            float x_diff = nearestX - x1;
            float y_diff = nearestY - y1;

            // Interpolate each color channel separately using bilinear interpolation
            QRgb pixel1 = image.pixel(x1, y1);
            QRgb pixel2 = image.pixel(x1 + 1, y1);
            QRgb pixel3 = image.pixel(x1, y1 + 1);
            QRgb pixel4 = image.pixel(x1 + 1, y1 + 1);

            int red = static_cast<int>((1 - x_diff) * (1 - y_diff) * qRed(pixel1) +
                                       x_diff * (1 - y_diff) * qRed(pixel2) +
                                       (1 - x_diff) * y_diff * qRed(pixel3) +
                                       x_diff * y_diff * qRed(pixel4));

            int green = static_cast<int>((1 - x_diff) * (1 - y_diff) * qGreen(pixel1) +
                                         x_diff * (1 - y_diff) * qGreen(pixel2) +
                                         (1 - x_diff) * y_diff * qGreen(pixel3) +
                                         x_diff * y_diff * qGreen(pixel4));

            int blue = static_cast<int>((1 - x_diff) * (1 - y_diff) * qBlue(pixel1) +
                                        x_diff * (1 - y_diff) * qBlue(pixel2) +
                                        (1 - x_diff) * y_diff * qBlue(pixel3) +
                                        x_diff * y_diff * qBlue(pixel4));

            // Set the interpolated color in the resized image
            QRgb newPixel = qRgb(red, green, blue);
            resizedImage.setPixel(x, y, newPixel);
        }
    }
    // Assign the resized image data to the original image
    image = resizedImage;
}
void filters::simple(QImage& s, int thickness, QString color) {
    int factor = 25 * 2 * (thickness - 1);

    QImage output(s.width() + 50 + factor, s.height() + 50 + factor, QImage::Format_RGB32);

    QColor frameColor;
    if (color == "White")
        frameColor = QColor(255, 255, 255);
    else if (color == "Black")
        frameColor = QColor(0, 0, 0);
    else if (color == "Red")
        frameColor = QColor(255, 0, 0);
    else if (color == "Blue")
        frameColor = QColor(0, 0, 255);
    else if (color == "Green")
        frameColor = QColor(0, 255, 0);
    else if (color == "Yellow")
        frameColor = QColor(255, 255, 0);
    else if (color == "Purple")
        frameColor = QColor(255, 0, 255);
    else if (color == "Orange")
        frameColor = QColor(255, 165, 0);
    else if (color == "Dark Grey")
        frameColor = QColor(105, 105, 105);
    else if (color == "Indigo")
        frameColor = QColor(7, 82, 100);
    else {
        std::cerr << "Invalid color choice." << std::endl;
        return;
    }

    for (int i = 0; i < output.width(); ++i) {
        for (int j = 0; j < output.height(); ++j) {
            if (i < 25 * thickness || i >= s.width() + 25 * thickness ||
                j < 25 * thickness || j >= s.height() + 25 * thickness) {
                output.setPixelColor(i, j, frameColor);
            } else {
                output.setPixelColor(i, j, s.pixelColor(i - 25 * thickness, j - 25 * thickness));
            }
        }
    }

    // Update the original image with the framed image
    s = output;
}
void filters:: fancy1(QImage& img) {
    // Define the thickness of the white lines
    int thickness1 = 20;
    int thickness2 = 10;

    // Create a white color
    QRgb white = qRgb(255, 255, 255);

    // Add the first set of white lines
    // Top line
    for (int x = 0; x < img.width(); x++) {
        for (int t = 0; t < thickness1; t++) {
            img.setPixelColor(x, t, white);
        }
    }

    // Bottom line
    for (int x = 0; x < img.width(); x++) {
        for (int t = 0; t < thickness1; t++) {
            img.setPixelColor(x, img.height() - 1 - t, white);
        }
    }

    // Left line
    for (int y = 0; y < img.height(); y++) {
        for (int t = 0; t < thickness1; t++) {
            img.setPixelColor(t, y, white);
        }
    }

    // Right line
    for (int y = 0; y < img.height(); y++) {
        for (int t = 0; t < thickness1; t++) {
            img.setPixelColor(img.width() - 1 - t, y, white);
        }
    }

    // Add the second set of white lines inside the first set
    // Top line
    for (int x = thickness1 + 20; x < img.width() - (thickness1 + 20); x++) {
        for (int t = 0; t < thickness2; t++) {
            img.setPixelColor(x, t + thickness1 + 20, white);
        }
    }

    // Bottom line
    for (int x = thickness1 + 20; x < img.width() - (thickness1 + 20); x++) {
        for (int t = 0; t < thickness2; t++) {
            img.setPixelColor(x, img.height() - 1 - (t + thickness1 + 20), white);
        }
    }

    // Left line
    for (int y = thickness1 + 20; y < img.height() - (thickness1 + 20); y++) {
        for (int t = 0; t < thickness2; t++) {
            img.setPixelColor(t + thickness1 + 20, y, white);
        }
    }

    // Right line
    for (int y = thickness1 + 20; y < img.height() - (thickness1 + 20); y++) {
        for (int t = 0; t < thickness2; t++) {
            img.setPixelColor(img.width() - 1 - (t + thickness1 + 20), y, white);
        }
    }
}
void filters:: white(QImage& img) {
    QImage output(img.width() + 10, img.height() + 10,img.format());
    output.fill(Qt::white); // Fill the entire image with white

    // Copy the original image to the center of the output image
    for (int i = 5; i < output.width() - 5; ++i) {
        for (int j = 5; j < output.height() - 5; ++j) {
            output.setPixelColor(i, j, img.pixelColor(i - 5, j - 5));
        }
    }

    // Update the original image with the framed image
    img = output;
}

void filters:: black(QImage& img) {
    QImage output(img.width() + 20, img.height() + 20,img.format());
    output.fill(Qt::black); // Fill the entire image with black

    // Copy the original image to the center of the output image
    for (int i = 10; i < output.width() - 10; ++i) {
        for (int j = 10; j < output.height() - 10; ++j) {
            output.setPixelColor(i, j, img.pixelColor(i - 10, j - 10));
        }
    }

    // Update the original image with the framed image
    img = output;
}

void filters:: frame(QImage& img, int choice) {
    if (choice == 1) {
        // Call the fancy1 function if choice is 1
        fancy1(img);
    } else if (choice == 2) {
        // Apply white and black frame alternately six times
        for (int i = 0; i < 6; ++i) {
            white(img);
            black(img);
        }
    }
}
