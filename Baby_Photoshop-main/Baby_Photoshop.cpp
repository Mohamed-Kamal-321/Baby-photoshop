// File: CS112_A3_Part3_S25_20230582_20231233_20230349.cpp
// Purpose: This is an image processing (or photo editing) software like PhotoShop allows you to load an image and apply
//some filters to it and then save it again.
// Section: S25
//                           Name                           ID                  Filter                                    Email                     
           
// Author_3:     Mohamed Kamal Ahmed                    (20230349):      (3,6,9,12)+bonus(14,15,17,21)              elkpir666@gmail.com
//System diagram
//https://www.mindmeister.com/app/map/3243395418?t=31QgJsP2iE


#include <iostream>
using namespace std;
#include "Image_Class.h"
#include<string>
#include<cmath>
#include <random>
#include <algorithm>
void flip(Image& s) {
    // Create a new image object with the same dimensions as the original image
    Image x(s.width, s.height);

    // Prompt the user to choose between horizontal and vertical flip
    string user_choice;
    cout << "1-Horizontal flip\n2-Vertical flip\n";
    cin >> user_choice;

    // Validate user input
    while (user_choice != "1" and user_choice != "2") {
        cout << "Please choose 1 or 2\n";
        cin >> user_choice;
    }

    // Perform horizontal flip
    if (user_choice == "1") {
        for (int i = 0; i < s.width; ++i) {
            for (int j = 0; j < s.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    // Flip pixels horizontally
                    x(s.width - 1 - i, j, k) = s(i, j, k);
                }
            }
        }
    }
    // Perform vertical flip
    else {
        for (int i = 0; i < s.width; ++i) {
            for (int j = 0; j < s.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    // Flip pixels vertically
                    x(i, s.height - 1 - j, k) = s(i, j, k);
                }
            }
        }
    }
    // Notify user about successful flipping
    cout << "The image has been flipped successfully" << endl;

    // Replace the original image with the flipped image
    s = x;
}
void Black_and_White(Image& s) {
    // Iterate over each pixel in the image
    for (int i = 0; i < s.width; ++i) {
        for (int j = 0; j < s.height; ++j) {
            // Calculate the average of the RGB values for the current pixel
            int avg = (s(i, j, 0) + s(i, j, 1) + s(i, j, 2)) / 3;
            // Iterate over each color channel (R, G, B)
            for (int k = 0; k < 3; ++k) {
                // Set each color channel to either 0 (black) or 255 (white) based on the average value
                if (avg < 128)
                    s(i, j, k) = 0; // If the average is less than 128, set the channel to 0 (black)
                else
                    s(i, j, k) = 255; // If the average is greater than or equal to 128, set the channel to 255 (white)
            }
        }
    }
    // Notify the user that the black & white filter has been applied successfully
    cout << "Black & White filter has been done successfully" << endl;
}
void crop(Image& s) {
    // Declare variables to store cropping parameters
    int x, y, w, h;

    // Prompt the user to enter the starting position (x, y) for cropping
    cout << "Enter the starting position in x and y format:" << endl;
    cin >> x >> y;

    // Prompt the user to enter the dimensions (width, height) of the cropped image
    cout << "Enter the dimensions of the cropped image:" << endl;
    cin >> w >> h;

    // Ensure that the cropping parameters are within the bounds of the original image
    while (x + w > s.width or y + h > s.height) {
        cout << "Please re-enter the starting position in x and y format:" << endl;
        cin >> x >> y;
        cout << "Please re-enter the dimensions of the cropped image:" << endl;
        cin >> w >> h;
    }

    // Create a new Image object to store the cropped image
    Image v(w, h);

    // Copy pixels from the original image to the cropped image
    for (int i = x; i < w + x; ++i) {
        for (int j = y; j < h + y; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Adjust the coordinates to fit within the cropped image and copy pixel values
                v(i - x, j - y, k) = s(i, j, k);
            }
        }
    }

    // Notify the user that the image has been cropped successfully
    cout << "The image has been cropped successfully" << endl;

    // Update the original image to the cropped image
    s = v;
}
void crop(Image& s,int x,int y, int w,int h) {

    Image v(w, h);

    // Copy pixels from the original image to the cropped image
    for (int i = x; i < w + x; ++i) {
        for (int j = y; j < h + y; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Adjust the coordinates to fit within the cropped image and copy pixel values
                v(i - x, j - y, k) = s(i, j, k);
            }
        }
    }

    // Update the original image to the cropped image
    s = v;
}
void invert(Image& s) {
    // Iterate over each pixel in the image
    for (int i = 0; i < s.width; ++i) {
        for (int j = 0; j < s.height; ++j) {
            // Iterate over each color channel (R, G, B)
            for (int k = 0; k < 3; ++k) {
                // Invert each color channel by subtracting its value from 255
                s(i, j, k) = 255 - s(i, j, k);
            }
        }
    }

    // Notify the user that the invert filter has been applied successfully
    cout << "Invert filter has been done successfully" << endl;
}
void greyscale(Image& s) {
    // Iterate over each pixel in the image
    for (int i = 0; i < s.width; ++i) {
        for (int j = 0; j < s.height; ++j) {
            // Calculate the average of the RGB values for the current pixel
            int avg = (s(i, j, 0) + s(i, j, 1) + s(i, j, 2)) / 3;
            // Set each color channel (R, G, B) to the average value to achieve greyscale
            for (int k = 0; k < 3; ++k) {
                s(i, j, k) = avg;
            }
        }
    }

    // Notify the user that the greyscale filter has been applied successfully
    cout << "Greyscale filter has been done successfully" << endl;
}
void resizeImage(Image& image) {
    int newWidth, newHeight;
    char aspectChoice;

    // Ask the user if they want to keep the aspect ratio
    cout << "Do you want to keep the aspect ratio? (y/n): ";
    cin >> aspectChoice;

    // Validate user input for aspect ratio choice
    while (true) {
        if (aspectChoice == 'y' || aspectChoice == 'Y' || aspectChoice == 'n' || aspectChoice == 'N') {
            break;
        }
        cout << "Invalid choice. Please enter y or n" << endl;
        cin >> aspectChoice;
    }

    // If the user wants to keep the aspect ratio
    if (aspectChoice == 'y' || aspectChoice == 'Y') {
        char dimensionChoice;
        float aspectRatio = static_cast<float>(image.width) / image.height;

        // Ask the user if they want to specify new width or height
        cout << "Do you want to specify the new width or the new height? (w/h): ";
        cin >> dimensionChoice;

        // Calculate new dimensions based on user choice and aspect ratio
        if (dimensionChoice == 'w' || dimensionChoice == 'W') {
            cout << "Enter the new width: ";
            cin >> newWidth;
            newHeight = static_cast<int>(newWidth / aspectRatio);
        }
        else if (dimensionChoice == 'h' || dimensionChoice == 'H') {
            cout << "Enter the new height: ";
            cin >> newHeight;
            newWidth = static_cast<int>(newHeight * aspectRatio);
        }
        else {
            // Handle invalid dimension choice
            while (true) {
                if (dimensionChoice == 'w' || dimensionChoice == 'W' || dimensionChoice == 'h' ||
                    dimensionChoice == 'H') {
                    break;
                }
                cout << "Invalid choice. Please enter w or h" << endl;
                cin >> dimensionChoice;
            }
        }
    }
    else {
        // If the user doesn't want to keep the aspect ratio, directly specify new dimensions
        cout << "Enter the new width: ";
        cin >> newWidth;
        cout << "Enter the new height: ";
        cin >> newHeight;
    }

    // Create a new Image object with resized dimensions
    Image resizedImage(newWidth, newHeight);

    // Resizing using bilinear interpolation
    float x_ratio = static_cast<float>(image.width - 1) / newWidth;
    float y_ratio = static_cast<float>(image.height - 1) / newHeight;
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            float nearestX = x_ratio * x;
            float nearestY = y_ratio * y;
            int x1 = static_cast<int>(nearestX);
            int y1 = static_cast<int>(nearestY);
            float x_diff = nearestX - x1;
            float y_diff = nearestY - y1;
            for (int c = 0; c < 3; ++c) {
                // Bilinear interpolation formula for each color channel
                float interpolated_value = (1 - x_diff) * (1 - y_diff) * image(x1, y1, c) +
                    x_diff * (1 - y_diff) * image(x1 + 1, y1, c) +
                    (1 - x_diff) * y_diff * image(x1, y1 + 1, c) +
                    x_diff * y_diff * image(x1 + 1, y1 + 1, c);
                resizedImage.setPixel(x, y, c, static_cast<unsigned char>(interpolated_value));
            }
        }
    }

    // Assign the resized image data to the original image
    image = resizedImage;
    cout << "Image has been resized successfully." << endl;
}
void resizeImage(Image& image, int newWidth, int newHeight) {
    // Create a new image object with the specified dimensions
    Image resizedImage(newWidth, newHeight);

    // Calculate the ratio of old image width and height to new width and height
    float x_ratio = static_cast<float>(image.width - 1) / newWidth;
    float y_ratio = static_cast<float>(image.height - 1) / newHeight;

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

            // Iterate over each color channel (R, G, B)
            for (int c = 0; c < 3; ++c) {
                // Bilinear interpolation formula
                float interpolated_value = (1 - x_diff) * (1 - y_diff) * image(x1, y1, c) +
                    x_diff * (1 - y_diff) * image(x1 + 1, y1, c) +
                    (1 - x_diff) * y_diff * image(x1, y1 + 1, c) +
                    x_diff * y_diff * image(x1 + 1, y1 + 1, c);

                // Set the interpolated value in the resized image
                resizedImage.setPixel(x, y, c, static_cast<unsigned char>(interpolated_value));
            }
        }
    }

    // Update the original image with the resized image
    image = resizedImage;
}
void rotate(Image& image) {
    // Display rotation options
    cout << "1-Rotate by 90 degrees" << endl
        << "2-Rotate by 180 degrees" << endl
        << "3-Rotate by 270 degrees" << endl;

    char degree;
    cout << "Choose a number from 1 to 3: ";
    cin >> degree;

    // Validate user input for rotation degree choice
    while (degree != '1' && degree != '2' && degree != '3') {
        cout << "Invalid choice. Please choose a number from 1 to 3: ";
        cin >> degree;
    }

    // Perform rotation based on user choice
    if (degree == '1') {
        // Rotate by 90 degrees
        Image rotated(image.height, image.width);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    rotated(image.height - 1 - j, i, k) = image(i, j, k);
                }
            }
        }
        image = rotated;
    }
    else if (degree == '2') {
        // Rotate by 180 degrees
        Image rotated(image.width, image.height);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    rotated(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
                }
            }
        }
        image = rotated;
    }
    else {
        // Rotate by 270 degrees
        Image rotated(image.height, image.width);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    rotated(j, image.width - 1 - i, k) = image(i, j, k);
                }
            }
        }
        image = rotated;
    }

    cout << "Image has been rotated successfully." << endl;
}
void merge(Image& image) {
    string filename;
    cout << "Please enter the name of the second image you want to merge followed by its extension: ";
    cin >> filename;

    // Load the second image
    Image image2(filename);

    // Determine the dimensions of the merged image
    int newWidth = max(image.width, image2.width);
    int newHeight = max(image.height, image2.height);

    // Create an output image with the merged dimensions
    Image output(newWidth, newHeight);

    // Resize both images to match the merged dimensions
    resizeImage(image, newWidth, newHeight);
    resizeImage(image2, newWidth, newHeight);

    // Merge the two images pixel by pixel
    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Calculate the average value of corresponding pixels from both images
                output(i, j, k) = (image(i, j, k) + image2(i, j, k)) / 2;
            }
        }
    }

    // Update the original image with the merged result
    image = output;

    cout << "Images have been merged successfully." << endl;
}
void warm(Image& s) {
    // Iterate over each pixel in the image
    for (int i = 0; i < s.width; ++i) {
        for (int j = 0; j < s.height; ++j) {
            // Iterate over each color channel (R, G, B)
            for (int k = 0; k < 3; ++k) {

                s(i, j, k) = static_cast<unsigned char>(
                    s(i, j, k) * .825 + .175 * 255.0 * (k == 0 || k == 1));

            }
        }
    }
    cout << "Natural sunlight filter has been done successfully" << endl;

}
void old_tv(Image& image) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-25, 25);
    // Apply noise to each pixel
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int r = image(i, j, 0);
            int g = image(i, j, 1);
            int b = image(i, j, 2);

            int noise = dis(gen);
            r = clamp(r + noise, 0, 255);
            g = clamp(g + noise, 0, 255);
            b = clamp(b + noise, 0, 255);

            image(i, j, 0)=r;
            image(i, j, 1)=g;
            image(i, j, 2)=b;
        }
        cout << "Old TV filter has been applied successfully." << endl;

    }
}
void purple(Image& s) {
    // Iterate over each pixel in the image
    for (int i = 0; i < s.width; ++i) {
        for (int j = 0; j < s.height; ++j) {
            // Decrease the green channel intensity by 25%
            s(i, j, 1) = s(i, j, 1) * 0.75;

            // Iterate over each color channel (R, G, B)
            for (int k = 0; k < 3; ++k) {
                // Increase the intensity of each channel by 20%, clamping to 255
                s(i, j, k) = min(s(i, j, k) * 1.2, 255.0);
            }
        }
    }
    cout << "Purple filter has been applied successfully." << endl;
}
void infrared(Image& s) {
    // Iterate over each pixel in the image
    for (int i = 0; i < s.width; ++i) {
        for (int j = 0; j < s.height; ++j) {
            // This loop is empty and does not perform any operations on pixels
            // It seems to be a leftover or placeholder, so it can be removed
        }
    }

    // Iterate over each pixel in the image again to apply the infrared filter
    for (int i = 0; i < s.width; ++i) {
        for (int j = 0; j < s.height; ++j) {
            // Reduce the intensity of the red channel by 90%
            s(i, j, 0) = s(i, j, 0) * 0.1;

            // Invert each color channel by subtracting its value from 255
            for (int k = 0; k < 3; ++k) {
                s(i, j, k) = (255 - s(i, j, k));
            }
        }
    }

    cout << "Infrared filter has been applied successfully." << std::endl;
}
void skew(Image& s) {
    double skewAngle;
    cout << "Please enter the angle you want to skew with (1-90): ";
    cin >> skewAngle;

    // Validate the angle input
    bool validAngle = false;
    while (!validAngle) {
        if (skewAngle >= 1 && skewAngle <= 90) {
            validAngle = true;
        }
        else {
            cout << "Invalid angle. Please enter an angle between 1-90: ";
            cin >> skewAngle;
        }
    }

    // Create a temporary image for transformation
    Image z(s.width, s.height);
    for (int i = 0; i < s.width; ++i) {
        for (int j = 0; j < s.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                z(s.width - 1 - i, j, k) = s(i, j, k);
            }
        }
    }
    s = z;

    // Calculate skew transformation parameters
    double rad = skewAngle * M_PI / 180.0;
    int newWidth = s.width + static_cast<int>(abs(s.height * tan(rad)))/ 2;
    int newHeight=s.height;
    Image output(newWidth, newHeight);




// Apply the skew transformation
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // Calculate original coordinates
            int srcX = x - static_cast<int>((y * tan(rad)) / 2);
            int srcY = y;

            // Check if the original coordinates are within bounds
            if (srcX >= 0 && srcX < s.width && srcY >= 0 && srcY < s.height) {
                // Copy pixel values from the original image to the skewed image
                for (int c = 0; c < 3; ++c) {
                    output.setPixel(x, y, c, s.getPixel(srcX, srcY, c));
                }
            } else {
                // Set background pixels to white
                for (int c = 0; c < 3; ++c) {
                    output.setPixel(x, y, c, 255); // Assuming white color (255, 255, 255) for simplicity
                }
            }
        }
    }

    s=output;
    // Reverse the skew transformation
    Image x(s.width, s.height);
    for (int i = 0; i < s.width; ++i) {
        for (int j = 0; j < s.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                x(s.width - 1 - i, j, k) = output(i, j, k);
            }
        }
    }
    s = x;

    // Display success message
    cout << "Image has been skewed successfully by angle " << skewAngle << endl;
}
void lighten_and_darken(Image& s) {
    cout << "1-Lighten\n2-Darken\n";
    int choice;
    cin >> choice;

    // Validate the choice input
    bool valid = false;
    while (!valid) {
        if (choice >= 1 && choice <= 2) {
            valid = true;
        }
        else {
            cout << "Invalid choice. Please enter 1 or 2: ";
            cin >> choice;
        }
    }

    // Apply the selected operation (lighten or darken)
    if (choice == 1) {
        // Lighten the image by 50%
        for (int i = 0; i < s.width; i++) {
            for (int j = 0; j < s.height; j++) {
                for (int k = 0; k < 3; k++) { // Assuming RGB channels
                    int newVal = s(i, j, k) * 1.5; // Lighten by 50%
                    s(i, j, k) = min(newVal, 255); // Ensure the value is not greater than 255
                }
            }
        }
    }
    else {
        // Darken the image by 50%
        for (int i = 0; i < s.width; i++) {
            for (int j = 0; j < s.height; j++) {
                for (int k = 0; k < 3; k++) {
                    int newVal = s(i, j, k) * 0.5; // Darken by 50%
                    s(i, j, k) = max(newVal, 0); // Ensure the value is not less than 0
                }
            }
        }
    }

    cout << "Lighten and darken filter has been applied successfully" << endl;
}
void Detect_Image_Edges(Image& s) {
    // Convert the image to grayscale
    for (int i = 0; i < s.width; ++i) {
        for (int j = 0; j < s.height; ++j) {
            // Calculate the average of the RGB values for the current pixel
            int avg = (s(i, j, 0) + s(i, j, 1) + s(i, j, 2)) / 3;
            // Set each color channel (R, G, B) to the average value to achieve greyscale
            for (int k = 0; k < 3; ++k) {
                s(i, j, k) = avg;
            }
        }
    }

    // Apply edge detection
    Image new_image(s.width, s.height);

    int threshold = 50; // Adjust threshold as needed

    for (int i = 1; i < s.width - 1; i++) {
        for (int j = 1; j < s.height - 1; j++) {
            int current = s(i, j, 0); // Grayscale value of the current pixel

            // Calculate differences with neighboring pixels
            int top = s(i + 1, j, 0) - current;
            int bottom = s(i - 1, j, 0) - current;
            int right = s(i, j + 1, 0) - current;
            int left = s(i, j - 1, 0) - current;
            int top_right = s(i + 1, j + 1, 0) - current;
            int bottom_left = s(i - 1, j - 1, 0) - current;
            int top_left = s(i + 1, j - 1, 0) - current;
            int bottom_right = s(i - 1, j + 1, 0) - current;

            // Check if any difference is above threshold
            if (top > threshold || bottom > threshold || right > threshold || left > threshold ||
                top_right > threshold || bottom_left > threshold || top_left > threshold || bottom_right > threshold) {
                new_image(i, j, 0) = new_image(i, j, 1) = new_image(i, j, 2) = 0; // Set pixel to black (edge)
            }
            else {
                new_image(i, j, 0) = new_image(i, j, 1) = new_image(i, j, 2) = 255; // Set pixel to white (background)
            }
        }

    }

    s = new_image; // Update the input image with the edge-detected image
    cout << "Detect image edges filter has been done successfully" << endl;

}
void blur(Image& s) {
    Image tmp_image = s;
    int sum, pixels_num;
    for (int i = 0; i < s.width; i++) {
        for (int j = 0; j < s.height; j++) {
            for (int k = 0; k < s.channels; k++) {
                sum = 0, pixels_num = 1;

                // Top left (4 units away)
                if (i > 3 && j > 3) {
                    sum += tmp_image(i - 4, j - 4, k);
                    pixels_num++;
                }

                // Top (4 units away)
                if (i > 3) {
                    sum += tmp_image(i - 4, j, k);
                    pixels_num++;
                }

                // Top right (4 units away)
                if (i > 3 && j < s.height - 4) {
                    sum += tmp_image(i - 4, j + 4, k);
                    pixels_num++;
                }

                // Left (4 units away)
                if (j > 3) {
                    sum += tmp_image(i, j - 4, k);
                    pixels_num++;
                }

                // Right (4 units away)
                if (j < s.height - 4) {
                    sum += tmp_image(i, j + 4, k);
                    pixels_num++;
                }

                // Bottom left (4 units away)
                if (i < s.width - 4 && j > 3) {
                    sum += tmp_image(i + 4, j - 4, k);
                    pixels_num++;
                }

                // Bottom (4 units away)
                if (i < s.width - 4) {
                    sum += tmp_image(i + 4, j, k);
                    pixels_num++;
                }

                // Bottom right (4 units away)
                if (i < s.width - 4 && j < s.height - 4) {
                    sum += tmp_image(i + 4, j + 4, k);
                    pixels_num++;
                }

                // Calculate average and assign to the pixel in the original image
                s(i, j, k) = round(sum / pixels_num);
            }
        }
    }
    cout << "Blur filter has been done successfully" << endl;

}
void simple(Image& s) {
    int thickness; // Thickness of the frame
    bool validThickness = false;
    cout << "Enter the thickness of the frame (1, 2, or 3): ";
    cin >> thickness;
    while (!validThickness) {
        if (thickness >= 1 && thickness <= 3) {
            validThickness = true;
        }
        else {
            cout << "Invalid thickness. Please enter 1, 2, or 3: ";
            cin >> thickness;
        }
    }

    int factor = 25 * 2 * (thickness - 1);

    Image output(s.width + 50 + factor, s.height + 50 + factor);
    int color;
    bool validColor = false;
    cout << "Which frame color do you want?" << endl
        << "1-White" << endl
        << "2-Black" << endl
        << "3-Red" << endl
        << "4-Blue" << endl
        << "5-Green" << endl
        << "6-Yellow" << endl
        << "7-Purple" << endl
        << "8-Orange" << endl
        << "9-Dark grey" << endl
        << "10-Indigo" << endl;
    cout << "Please choose a number from 1 to 10: ";
    cin >> color;
    while (!validColor) {
        if (color >= 1 && color <= 10) {
            validColor = true;
        }
        else {
            cout << "Invalid choice. Please choose a number from 1 to 10: ";
            cin >> color;
        }
    }
    int RGB[3];

    if (color == 1) {
        RGB[0] = 255; RGB[1] = 255; RGB[2] = 255;
    }
    else if (color == 2) {
        RGB[0] = 0; RGB[1] = 0; RGB[2] = 0;
    }
    else if (color == 3) {
        RGB[0] = 255; RGB[1] = 0; RGB[2] = 0;
    }
    else if (color == 4) {
        RGB[0] = 0; RGB[1] = 0; RGB[2] = 255;
    }
    else if (color == 5) {
        RGB[0] = 0; RGB[1] = 255; RGB[2] = 0;
    }
    else if (color == 6) {
        RGB[0] = 255; RGB[1] = 255; RGB[2] = 0;
    }
    else if (color == 7) {
        RGB[0] = 255; RGB[1] = 0; RGB[2] = 255;
    }
    else if (color == 8) {
        RGB[0] = 255; RGB[1] = 165; RGB[2] = 0;
    }
    else if (color == 9) {
        RGB[0] = 105; RGB[1] = 105; RGB[2] = 105;
    }
    else if (color == 10) {
        RGB[0] = 7; RGB[1] = 82; RGB[2] = 100;
    }
    for (int i = 0; i < output.width; ++i) {
        for (int j = 0; j < output.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (i < 25 * thickness || i >= s.width + 25 * thickness ||
                    j < 25 * thickness || j >= s.height + 25 * thickness) {
                    output(i, j, 0) = RGB[0];
                    output(i, j, 1) = RGB[1];
                    output(i, j, 2) = RGB[2];
                }
                else {
                    output(i, j, k) = s(i - 25 * thickness, j - 25 * thickness, k);
                }
            }
        }
    }

    // Update the original image with the framed image
    s = output;
}
void fancy1(Image& img) {
    // Define the thickness of the white lines
    int thickness1 = 20;
    int thickness2 = 10;

    // Create a white color scalar
    unsigned char white[3] = { 255, 255, 255 };

    // Add the first set of white lines
    // Top line
    for (int x = 0; x < img.width; x++) {
        for (int t = 0; t < thickness1; t++) {
            for (int c = 0; c < img.channels; c++) {
                img(x, t, c) = white[c];
            }
        }
    }

    // Bottom line
    for (int x = 0; x < img.width; x++) {
        for (int t = 0; t < thickness1; t++) {
            for (int c = 0; c < img.channels; c++) {
                img(x, img.height - 1 - t, c) = white[c];
            }
        }
    }

    // Left line
    for (int y = 0; y < img.height; y++) {
        for (int t = 0; t < thickness1; t++) {
            for (int c = 0; c < img.channels; c++) {
                img(t, y, c) = white[c];
            }
        }
    }

    // Right line
    for (int y = 0; y < img.height; y++) {
        for (int t = 0; t < thickness1; t++) {
            for (int c = 0; c < img.channels; c++) {
                img(img.width - 1 - t, y, c) = white[c];
            }
        }
    }

    // Add the second set of white lines inside the first set
    // Top line
    for (int x = thickness1 + 20; x < img.width - (thickness1 + 20); x++) {
        for (int t = 0; t < thickness2; t++) {
            for (int c = 0; c < img.channels; c++) {
                img(x, t + thickness1 + 20, c) = white[c];
            }
        }
    }

    // Bottom line
    for (int x = thickness1 + 20; x < img.width - (thickness1 + 20); x++) {
        for (int t = 0; t < thickness2; t++) {
            for (int c = 0; c < img.channels; c++) {
                img(x, img.height - 1 - (t + thickness1 + 20), c) = white[c];
            }
        }
    }

    // Left line
    for (int y = thickness1 + 20; y < img.height - (thickness1 + 20); y++) {
        for (int t = 0; t < thickness2; t++) {
            for (int c = 0; c < img.channels; c++) {
                img(t + thickness1 + 20, y, c) = white[c];
            }
        }
    }

    // Right line
    for (int y = thickness1 + 20; y < img.height - (thickness1 + 20); y++) {
        for (int t = 0; t < thickness2; t++) {
            for (int c = 0; c < img.channels; c++) {
                img(img.width - 1 - (t + thickness1 + 20), y, c) = white[c];
            }
        }
    }
}
void white(Image& s) {
    // Create an output image with 10-pixel border
    Image output(s.width + 10, s.height + 10);

    // Iterate over each pixel in the output image
    for (int i = 0; i < output.width; ++i) {
        for (int j = 0; j < output.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Check if the pixel is within the border area
                if (i < 5 || i >= s.width + 5 ||
                    j < 5 || j >= s.height + 5) {
                    // Set the pixel color to white (RGB: 255, 255, 255)
                    output(i, j, 0) = 255;
                    output(i, j, 1) = 255;
                    output(i, j, 2) = 255;
                }
                else {
                    // Copy the pixel value from the original image to the output image
                    output(i, j, k) = s(i - 5, j - 5, k);
                }
            }
        }
    }

    // Update the original image with the framed image
    s = output;
}
void black(Image& s) {
    // Create an output image with a 10-pixel black border
    Image output(s.width + 20, s.height + 20);

    // Iterate over each pixel in the output image
    for (int i = 0; i < output.width; ++i) {
        for (int j = 0; j < output.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Check if the pixel is within the border area
                if (i < 10 || i >= s.width + 10 ||
                    j < 10 || j >= s.height + 10) {
                    // Set the pixel color to black (RGB: 0, 0, 0)
                    output(i, j, 0) = 0;
                    output(i, j, 1) = 0;
                    output(i, j, 2) = 0;
                }
                else {
                    // Copy the pixel value from the original image to the output image
                    output(i, j, k) = s(i - 10, j - 10, k);
                }
            }
        }
    }

    // Update the original image with the framed image
    s = output;
}
void frame(Image& img) {
    // Prompt the user to choose between a simple or fancy frame
    cout << "1-Simple frame\n2-Fancy frame\n";
    int choice;
    cin >> choice;

    // Validate the user's choice
    bool validFrame = false;
    while (!validFrame) {
        if (choice >= 1 && choice <= 2) {
            validFrame = true;
        }
        else {
            cout << "Invalid choice. Please enter 1 or 2: ";
            cin >> choice;
        }
    }

    // Apply the chosen frame type
    if (choice == 1) {
        // Apply the simple frame
        simple(img);
    }
    else {
        // Prompt the user to choose between two fancy frames
        cout << "1-Fancy frame 1\n2-Fancy frame 2\n";
        int choice2;
        cin >> choice2;

        // Validate the user's choice for the fancy frame
        bool valid = false;
        while (!valid) {
            if (choice2 >= 1 && choice2 <= 2) {
                valid = true;
            }
            else {
                cout << "Invalid choice. Please enter 1 or 2: ";
                cin >> choice2;
            }
        }

        // Apply the chosen fancy frame
        if (choice2 == 1) {
            fancy1(img);
        }
        else {
            // Apply multiple iterations of white and black frames for a special effect
            for (int i = 0; i < 6; ++i) {
                white(img);
                black(img);
            }
        }
    }

    cout << "Frame has been added successfully." << endl;
}
void Contrast_Decontrast(Image& image) {
    float factor;
    float midpoint = 127.5f; // Assuming RGB channels have values in [0, 255]
    cout << "1-Contrast\n2-Decontrast\n";
    int choice;
    cin >> choice;

    // Validate the choice input
    bool valid = false;
    while (!valid) {
        if (choice >= 1 && choice <= 2) {
            valid = true;
        }
        else {
            cout << "Invalid choice. Please enter 1 or 2: ";
            cin >> choice;
        }
    }

    // Apply the selected operation (Contrast or decontrast)
    if (choice == 1) {
        factor = 1.25;
        // Iterate through each pixel of the image
        for (int y = 0; y < image.height; ++y) {
            for (int x = 0; x < image.width; ++x) {
                // Iterate through each color channel
                for (int c = 0; c < image.channels; ++c) {
                    // Retrieve the pixel value
                    unsigned char &pixelValue = image.getPixel(x, y, c);

                    // Apply contrast adjustment
                    float newValue = (pixelValue - midpoint) * factor + midpoint;

                    // Clamp the new value to the range [0, 255]
                    newValue = min(255.0f, max(0.0f, newValue));

                    // Update the pixel value
                    pixelValue = static_cast<unsigned char>(newValue);
                }
            }
        }
    }
    else {
        factor = .75;
        // Iterate through each pixel of the image
        for (int y = 0; y < image.height; ++y) {
            for (int x = 0; x < image.width; ++x) {
                // Iterate through each color channel
                for (int c = 0; c < image.channels; ++c) {
                    // Retrieve the pixel value
                    unsigned char &pixelValue = image.getPixel(x, y, c);

                    // Apply contrast adjustment
                    float newValue = (pixelValue - midpoint) * factor + midpoint;

                    // Clamp the new value to the range [0, 255]
                    newValue = min(255.0f, max(0.0f, newValue));

                    // Update the pixel value
                    pixelValue = static_cast<unsigned char>(newValue);
                }
            }
        }
    }

    cout << "Lighten and darken filter has been applied successfully" << endl;
}
void Sepia_tone(Image& image){
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            // Get the pixel values directly from the image data
            unsigned char& pixelR = image.getPixel(x, y, 0);
            unsigned char& pixelG = image.getPixel(x, y, 1);
            unsigned char& pixelB = image.getPixel(x, y, 2);

            // Perform the color transformation
            int newR = static_cast<int>((0.393 * pixelR) + (0.769 * pixelG) + (0.189 * pixelB));
            int newG = static_cast<int>((0.349 * pixelR) + (0.686 * pixelG) + (0.168 * pixelB));
            int newB = static_cast<int>((0.272 * pixelR) + (0.534 * pixelG) + (0.131 * pixelB));

            // Clamp RGB values to ensure they are within [0, 255]
            newR = min(max(newR, 0), 255);
            newG = min(max(newG, 0), 255);
            newB = min(max(newB, 0), 255);

            // Update the pixel values in the image data
            pixelR = static_cast<unsigned char>(newR);
            pixelG =  static_cast<unsigned char>(newG);
            pixelB =  static_cast<unsigned char>(newB);
        }
    }
}
void blur_edges(Image& s) {
    Image tmp_image = s;
    int sum_r, sum_g, sum_b, pixels_num;
    float x = s.width * 0.05f;
    float y = s.height * 0.05f;

    for (int i = 0; i < s.width; i++) {
        for (int j = 0; j < s.height; j++) {
            sum_r = 0, sum_g = 0, sum_b = 0, pixels_num = 1;

            // Check if the pixel is near the edges
            bool nearEdge = (i < x || i >= s.width - x || j < y || j >= s.height - y);

            if (nearEdge) {
                // Top left (4 units away)
                if (i > 3 && j > 3) {
                    sum_r += tmp_image(i - 4, j - 4, 0);
                    sum_g += tmp_image(i - 4, j - 4, 1);
                    sum_b += tmp_image(i - 4, j - 4, 2);
                    pixels_num++;
                }

                // Top (4 units away)
                if (i > 3) {
                    sum_r += tmp_image(i - 4, j, 0);
                    sum_g += tmp_image(i - 4, j, 1);
                    sum_b += tmp_image(i - 4, j, 2);
                    pixels_num++;
                }

                // Top right (4 units away)
                if (i > 3 && j < s.height - 4) {
                    sum_r += tmp_image(i - 4, j + 4, 0);
                    sum_g += tmp_image(i - 4, j + 4, 1);
                    sum_b += tmp_image(i - 4, j + 4, 2);
                    pixels_num++;
                }

                // Left (4 units away)
                if (j > 3) {
                    sum_r += tmp_image(i, j - 4, 0);
                    sum_g += tmp_image(i, j - 4, 1);
                    sum_b += tmp_image(i, j - 4, 2);
                    pixels_num++;
                }

                // Right (4 units away)
                if (j < s.height - 4) {
                    sum_r += tmp_image(i, j + 4, 0);
                    sum_g += tmp_image(i, j + 4, 1);
                    sum_b += tmp_image(i, j + 4, 2);
                    pixels_num++;
                }

                // Bottom left (4 units away)
                if (i < s.width - 4 && j > 3) {
                    sum_r += tmp_image(i + 4, j - 4, 0);
                    sum_g += tmp_image(i + 4, j - 4, 1);
                    sum_b += tmp_image(i + 4, j - 4, 2);
                    pixels_num++;
                }

                // Bottom (4 units away)
                if (i < s.width - 4) {
                    sum_r += tmp_image(i + 4, j, 0);
                    sum_g += tmp_image(i + 4, j, 1);
                    sum_b += tmp_image(i + 4, j, 2);
                    pixels_num++;
                }

                // Bottom right (4 units away)
                if (i < s.width - 4 && j < s.height - 4) {
                    sum_r += tmp_image(i + 4, j + 4, 0);
                    sum_g += tmp_image(i + 4, j + 4, 1);
                    sum_b += tmp_image(i + 4, j + 4, 2);
                    pixels_num++;
                }

                // Calculate average and assign to the pixel in the original image
                s(i, j, 0) = sum_r / pixels_num;
                s(i, j, 1) = sum_g / pixels_num;
                s(i, j, 2) = sum_b / pixels_num;
            }
        }
    }
}
void oil_paint(Image& img) {
    int width = img.width;
    int height = img.height;
    int radius = 3;
    float intensity_levels = 5.0f; // Use float for better precision
    for (int y = radius; y < height - radius; y++) {
        for (int x = radius; x < width - radius; x++) {
            vector<int> IntensityCount(intensity_levels, 0);
            vector<int> nSumR(intensity_levels, 0);
            vector<int> nSumG(intensity_levels, 0);
            vector<int> nSumB(intensity_levels, 0);
            for (int dy = -radius; dy <= radius; dy++) {
                for (int dx = -radius; dx <= radius; dx++) {
                    int xx = x + dx;
                    int yy = y + dy;

                    int r = img(xx, yy, 0);
                    int g = img(xx, yy, 1);
                    int b = img(xx, yy, 2);

                    // Calculate intensity level
                    int Intensity = int((((r + g + b) / 3.0f) * intensity_levels) / 255.0f);
                    //Intensity = clamp(Intensity, 0, static_cast<int>(intensity_levels) - 1); // Clamp intensity level
                    int i = Intensity;
                    IntensityCount[i]++;
                    nSumR[i] += r;
                    nSumG[i] += g;
                    nSumB[i] += b;
                }
            }
            int Max = 0;
            int maxIndex = 0;
            for (int i = 0; i < intensity_levels; i++) {
                if (IntensityCount[i] > Max) {
                    Max = IntensityCount[i];
                    maxIndex = i;
                }
            }
            // Calculate average RGB values
            int avgR = clamp(nSumR[maxIndex] / Max, 0, 255); // Clamp RGB values
            int avgG = clamp(nSumG[maxIndex] / Max, 0, 255);
            int avgB = clamp(nSumB[maxIndex] / Max, 0, 255);

            img(x, y, 0) = avgR;
            img(x, y, 1) = avgG;
            img(x, y, 2) = avgB;
        }
    }
}

// Main function of the programme
int main() {
    // Print welcome message
    cout << "Welcome to Baby Photoshop Programme " << endl;

    // Prompt user to enter the name of the image file
    string filename;
    cout << "Please enter the name of the image you want to process followed by its extension:";
    cin >> filename;

    // Create an Image object using the provided filename
    Image img(filename);

    // Main program loop
    while (true) {
        // Display menu options
        cout << "What do you want to do?" << endl
            << "1- Add new image" << endl
            << "2- Black & White filter" << endl
            << "3- Flip filter" << endl
            << "4- Crop filter" << endl
            << "5- Invert Filter" << endl
            << "6- Greyscale filter" << endl
            << "7- Merge filter" << endl
            << "8- Rotate filter" << endl
            << "9- Darken and Lighten filter" << endl
            << "10- Frame filter" << endl
            << "11- Detect Edges filter" << endl
            << "12- Resize filter" << endl
            << "13- Blur filter" << endl
            << "14- Natural sunlight filter" << endl
            << "15- Old TV filter" << endl
            << "16- Purple filter" << endl
            << "17- Oil Painting filter" << endl
            << "18- Infrared filter" << endl
            << "19- Skew filter" << endl
            << "20- Contrast and Decontrast filter" << endl
            << "21- Sepia tone filter" << endl
            << "22- Blur edges filter" << endl
            << "23- Reset the image" << endl
            << "24- Save the image" << endl
            << "25- Exit" << endl;

        // Prompt user for choice
        string user_choice1;
        cin >> user_choice1;

        // Validate user input
        while (stoi(user_choice1) < 1 or stoi(user_choice1) > 25) {
            cout << "Please enter a valid choice" << endl;
            cin >> user_choice1;
        }

        // Process user's choice
        if (user_choice1 == "1") {
            // Prompt user for the name of the new image file
            cout << "Please enter the name of the image you want to process followed by its extension:";
            cin >> filename;
            // Create a new Image object with the provided filename
            Image img2(filename);
            // Replace the current image with the new one
            img = img2;
            cout << "The new image has been added successfully" << endl;
        }
        else if (user_choice1 == "2") {
            // Apply black & white filter to the image
            Black_and_White(img);
        }
        else if (user_choice1 == "3") {
            // Apply flip filter to the image
            flip(img);
        }
        else if (user_choice1 == "4") {
            // Apply crop filter to the image
            crop(img);
        }
        else if (user_choice1 == "5") {
            // Apply invert filter to the image
            invert(img);
        }
        else if (user_choice1 == "6") {
            // Apply greyscale filter to the image
            greyscale(img);
        }
        else if (user_choice1 == "7") {
            // Apply merge filter to the image
            merge(img);
        }
        else if (user_choice1 == "8") {
            // Apply rotate filter to the image
            rotate(img);
        }
        else if (user_choice1 == "9") {
            // Apply darken and lighten filter to the image
            lighten_and_darken(img);
        }
        else if (user_choice1 == "10") {
            // Apply frame filter to the image
            frame(img);
        }
        else if (user_choice1 == "11") {
            // Apply detect edges filter to the image
            Detect_Image_Edges(img);
        }
        else if (user_choice1 == "12") {
            // Apply resize filter to the image
            resizeImage(img);
        }
        else if (user_choice1 == "13") {
            // Apply blur filter to the image
            blur(img);
        }
        else if (user_choice1 == "14") {
            // Apply detect edges filter to the image
            warm(img);
        }
        else if (user_choice1 == "15") {
            // Apply old tv filter to the image
            old_tv(img);
        }
        else if (user_choice1 == "16") {
            // Apply purple filter to the image
            purple(img);
        }
        else if (user_choice1 == "17") {
            // Apply oil_painting filter to the image
            oil_paint(img);
        }
        else if (user_choice1 == "18") {
            // Apply infrared filter to the image
            infrared(img);
        }
        else if (user_choice1 == "19") {
            // Apply skew filter to the image
            skew(img);
        }
        else if (user_choice1 == "20") {
            // Apply Contrast_Decontrast filter to the image
            Contrast_Decontrast(img);
        }
        else if (user_choice1 == "21") {
            // Apply Sepia_tone filter to the image
            Sepia_tone(img);
        }
        else if (user_choice1 == "22") {
            // Apply blur edges filter to the image
            blur_edges(img);
        }
        else if (user_choice1 == "23") {
            // Reset the image to its original state
            Image img3(filename);
            img = img3;
            cout << "The image has been reset successfully" << endl;
        }
        else if (user_choice1 == "24") {
            // Prompt user for saving options
            string user_choice;
            cout << "1-Save changes on the same file\n2-Save changes on new file\n";
            cin >> user_choice;
            // Validate user input
            while (user_choice != "1" and user_choice != "2") {
                cout << "Please choose 1 or 2\n";
                cin >> user_choice;
            }
            if (user_choice == "1") {
                // Save changes to the same file
                img.saveImage(filename);
                cout << "The image has been saved successfully with the following name: " << filename << endl;
            }
            else {
                // Prompt user for the name of the new image file
                string output;
                cout << "Please enter image name to store new image\n";
                cout << "and specify extension .jpg, .bmp, .png, .tga:";
                cin >> output;
                // Save changes to a new file
                img.saveImage(output);
                cout << "The image has been saved successfully with the following name: " << output << endl;
            }
            // Exit the program
            cout << "Thank you for using Baby Photoshop!" << endl;

        }
        else break;
    }
    return 0;
}
