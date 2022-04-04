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
    string choice;
    cout << "would you like to lighten or darken your photo?" << endl;
    cin >> choice;
    if (choice == "darken") {
        loadImage();
        darken();
        saveImage();
        return 0;
    } else{
        loadImage();
        lighten();
        saveImage();
        return 0;
    }

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