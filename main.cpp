// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: Photoshop.cpp
// Last Modification Date: 22/04/2022
// Author1 and ID and Group: Jana Wael 20211026
// Author2 and ID and Group: Maria Ehab 20210312
// Author3 and ID and Group: Merna Islam 20210500
// Teaching Assistant: Eng/ Afaf
// Purpose: To practice 2D arrays.

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;

unsigned char image[SIZE][SIZE];
unsigned char secondImage[SIZE][SIZE];


void loadImage ();
void saveImage ();
void black_white();
void flipHorizontally();
void flipVertically();
void darken();
void lighten();
void mergeImage ();
void invert_image();
void rotate_image();
void shrink();
void blur();
void mirrorLeft();
void mirrorRight();
void mirrorUpper();
void mirrorDown();
void detectImage();


int main(){
    char startChoice, flipChoice, mirrorChoice;
    string choice5;
    cout << "Welcome!" << endl;
    loadImage();
    cout << "Please select a filter to apply or 0 to exit:" << endl;
    cout << " 1- Black & White Filter \n 2- Invert Filter \n 3- Merge Filter \n 4- Flip Image \n 5- Darken and Lighten Image \n 6- Rotate Image \n 7- Detect Image Edges \n 8- Enlarge Image \n 9- Shrink Image \n a- Mirror 1/2 Image \n b- Shuffle Image \n c- Blur Image \n s- Save the image to a file \n 0- Exit" << endl;
    cin >> startChoice;
    switch (startChoice){
        case '1':
            black_white();
            saveImage();
            return 0;
        case '2':
            invert_image();
            saveImage();
            return 0; // Invert filter here
        case '3':
            mergeImage ();
            saveImage();
            return 0;
        case '4':
            cout << "Would you like to flip (h)orizontally or (v)ertically?" << endl;
            cin >> flipChoice;
            if (flipChoice == 'v'){
                flipVertically();
            }else if (flipChoice == 'h'){
                flipHorizontally();
            } else {
                cout << "Invalid letter entered, please try again!" << endl;
            }
            saveImage();
            return 0;
        case '5':
            cout << "would you like to lighten or darken your photo?" << endl;
            cin >> choice5;
            if (choice5 == "darken") {
                darken();
                saveImage();
            } else{
                lighten();
                saveImage();
            }
        case '6':
            rotate_image();
            saveImage();
            return 0; // Rotate Image here
        case '7':
            detectImage();
            saveImage();
            return 0; // Detect Image Edges here
        case '8':
            saveImage();
            return 0; // Enlarge Image here
        case '9':
            shrink();
            saveImage();
            return 0; // Shrink Image here
        case 'a':
            cout << "Would you to Mirror (l)eft, (r)ight, (u)pper, or (d)own side?" << endl;
            cin >> mirrorChoice;
            if (mirrorChoice == 'l') {
                mirrorLeft();
            } else if (mirrorChoice == 'r') {
                mirrorRight();
            }  else if (mirrorChoice == 'u') {
                mirrorUpper();
            }  else if (mirrorChoice == 'd') {
                mirrorDown();
            } else {
                cout << "Invalid character entered, please try again! (l,r,u,d) " << endl;
            }
            saveImage();
            return 0; // Mirror 1/2 Image here
        case 'b':
            saveImage();
            return 0; // Shuffle Image here
        case 'c':
            blur();
            saveImage();
            return 0; // Blur Image here
        case 's':
            return 0; // Save the image to a file
        case '0':
            cout << "Thank You! The program ends here" << endl;
            break;
        default:
            cout << "Invalid value entered, Please try again!" << endl;
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
void black_white() {
    long avg = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            avg += image[i][j];
        }
    }
    avg /= (SIZE * SIZE);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > avg)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}

//_________________________________________
void flipHorizontally(){

    for (int j = 0; j < SIZE; j++) {
        int start = 0;
        int end = SIZE - 1;
        while (start < end){
            swap(image[start][j], image[end][j]);
            start++;
            end--;
        }
    }
}

//_________________________________________
void flipVertically(){

    for (int i = 0; i < SIZE; i++) {
        int start = 0;
        int end = SIZE - 1;
        while (start < end){
            swap(image[i][start], image[i][end]);
            start++;
            end--;
        }
    }
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

//_________________________________________
void mergeImage (){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            secondImage[i][j] = image[i][j];

        }
    }
    loadImage();

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + secondImage[i][j]) / 2;
        }

    }
}
//_________________________________________
void invert_image()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255 - image[i][j];
        }
    }
}
//_________________________________________
void rotate_image() {
    int x;
    cout << "choose an option between the following: " << endl;
    cout << "1.rotate 90 degree " << endl;
    cout << "2.rotate 180 degree " << endl;
    cout << "3.rotate 270 degree " << endl;
    cin >> x;
    if (x == 1) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = i; j < SIZE - i - 1; j++) {

                int temp = image[i][j];
                image[i][j] = image[SIZE - 1 - j][i];
                image[SIZE - 1 - j][i] = image[SIZE - 1 - i][SIZE - 1 - j];
                image[SIZE - 1 - i][SIZE - 1 - j] = image[j][SIZE - 1 - i];
                image[j][SIZE - 1 - i] = temp;
            }
        }

    }
    else if (x == 2) {
        for (int i = 0; i < SIZE / 2; i++)
        {
            for (int j = 0; j < SIZE; j++) {
                swap(image[i][j], image[SIZE - i - 1][SIZE - j - 1]);
            }
        }

    }
    else{
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = i; j < SIZE - i - 1; j++) {

                int temp = image[i][j];
                image[i][j] = image[SIZE - 1 - j][i];
                image[SIZE - 1 - j][i] = image[SIZE - 1 - i][SIZE - 1 - j];
                image[SIZE - 1 - i][SIZE - 1 - j] = image[j][SIZE - 1 - i];
                image[j][SIZE - 1 - i] = temp;
            }
        }

        for (int i = 0; i < SIZE / 2; i++)
        {
            for (int j = 0; j < SIZE; j++) {
                swap(image[i][j], image[SIZE - i - 1][SIZE - j - 1]);
            }
        }

    }
}

//_________________________________________
void detectImage(){
    long avg = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            avg += image[i][j];
        }
    }
    avg /= (SIZE * SIZE);
    cout << avg;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j]-image[i+1][j] > avg/6){
                image[i][j] = 0;
            }else if (image[i][j]-image[i][j+1] > avg/6){
                image[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] != 0){
                image[i][j] = 255;
            }
        }
    }
}

//_________________________________________
void shrink(){
    int choice;
    cout << "please choose weather you like to shrink image by\n 1) 1/2\n 2) 1/3\n 3) 1/4\n ";
    cin >> choice;
    if (choice == 1){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

                secondImage[i][j] = 255;
                secondImage[i/2][j/2] = image[i][j];
            }
        }
    }
    else if(choice == 2){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

                secondImage[i][j] = 255;
                secondImage[i/3][j/3] = image[i][j];
            }

        }

    }
    else {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

                secondImage[i][j] = 255;
                secondImage[i/4][j/4] = image[i][j];
            }

        }

    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = secondImage[i][j];
        }
    }
}

//_________________________________________
void mirrorLeft() {

    for (int i = 0; i < SIZE; i++) {
        int start = 0;
        int end = SIZE - 1;

        while (start <= end) {
            image[i][start] = image[i][end];
            start++;
            end--;
        }
    }
}

//_________________________________________
void mirrorRight() {
    for (int i = 0; i < SIZE; i++) {
        int start = 0;
        int end = SIZE - 1;

        while (start <= end) {
            image[i][end] = image[i][start];
            start++;
            end--;
        }
    }
}
//_________________________________________
void mirrorUpper(){
    for (int i = 0; i < SIZE; i++) {
        int start = 0;
        int end = SIZE - 1;

        while (start <= end) {
            image[end][i] = image[start][i];
            start++;
            end--;
        }
    }
}

//_________________________________________
void mirrorDown(){

    for (int i = 0; i < SIZE; i++) {
        int start = 0;
        int end = SIZE - 1;

        while (start <= end) {
            image[start][i] = image[end][i];
            start++;
            end--;
        }
    }
}

//_________________________________________
void blur(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + image[i-1][j] + image[i][j-1] + image[i-1][j-1] + image[i+1][j] + image[i][j+1] + image[i+1][j+1] + image[i+1][j-1] + image[i-1][j+1])/9;

        }

    }
}