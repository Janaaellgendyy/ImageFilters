#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage ();
void saveImage ();
void darken();
void lighten();

int main(){
    int choice;
    string choice5;
    cout << "Welcome!" << endl;
    loadImage();
    cout << "Please select a filter to apply or 0 to exit:" << endl;
    cout << " 1- Black & White Filter \n 2- Invert Filter \n 3- Merge Filter \n 4- Flip Image \n 5- Darken and Lighten Image \n 6- Rotate Image \n 7- Detect Image Edges \n 8- Enlarge Image \n 9- Shrink Image \n a- Mirror 1/2 Image \n b- Shuffle Image \n c- Blur Image \n s- Save the image to a file \n 0- Exit" << endl;
    cin >> choice;
    if (choice == 5){
        cout << "would you like to lighten or darken your photo?" << endl;
        cin >> choice5;
        if (choice5 == "darken") {
            darken();
            return 0;
        } else{
            lighten();
            return 0;
        }
    }
    saveImage();
}

//_________________________________________
void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_________________________________________
void darken () {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = (image[i][j]) / 2;

        }
    }
}
//_________________________________________
void lighten(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ( image[i][j] + ( image[i][j] / 2) > 255){
                image[i][j] = 255;
            }
            else{
                image[i][j] =  image[i][j] + ( image[i][j] / 2);
            }


        }
    }


}