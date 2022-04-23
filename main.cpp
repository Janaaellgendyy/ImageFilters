// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: Photoshop.cpp
// Last Modification Date: 22/04/2022
// Author1 and ID and Group: Jana Wael 20211026 s9
// Author2 and ID and Group: Maria Ehab 20210312 s9
// Author3 and ID and Group: Merna Islam 20210500 s9
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
unsigned char Image2[SIZE][SIZE];

// List of all declaration of functions used.
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
void enlarge();
void shuffle();
//_________________________________________

int main(){
    char startChoice, flipChoice, mirrorChoice;
    string choice5;
    cout << "Welcome!" << endl;
    loadImage();   //Taking the image from the user he wants to apply edits on, then creating the start menu to choose from.
    cout << "Please select a filter to apply or 0 to exit:" << endl;
    cout << " 1- Black & White Filter \n 2- Invert Filter \n 3- Merge Filter \n 4- Flip Image \n 5- Darken and Lighten Image \n 6- Rotate Image \n 7- Detect Image Edges \n 8- Enlarge Image \n 9- Shrink Image \n a- Mirror 1/2 Image \n b- Shuffle Image \n c- Blur Image \n s- Save the image to a file \n 0- Exit" << endl;
    cin >> startChoice;
    switch (startChoice){  // Using switch statements to track each case based on the choice of the user.
        case '1':          // 1- Black & White Filter
            black_white();
            saveImage();
            return 0;
        case '2':          // 2- Invert Filter
            invert_image();
            saveImage();
            return 0;
        case '3':         // 3- Merge Filter
            mergeImage ();
            saveImage();
            return 0;
        case '4':         // 4- Flip Image
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
        case '5':         // 5- Darken and Lighten Image
            cout << "would you like to lighten or darken your photo?" << endl;
            cin >> choice5;
            if (choice5 == "darken") {
                darken();
                saveImage();
            } else{
                lighten();
                saveImage();
            }
        case '6':         // 6- Rotate Image
            rotate_image();
            saveImage();
            return 0;
        case '7':         // 7- Detect Image Edges
            detectImage();
            saveImage();
            return 0;
        case '8':         // 8- Enlarge Image
            enlarge();
            saveImage();
            return 0;
        case '9':         // 9- Shrink Image
            shrink();
            saveImage();
            return 0;
        case 'a':         // a- Mirror 1/2 Image
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
            return 0;
        case 'b':         //  b- Shuffle Image
            shuffle();
            saveImage();
            return 0;
        case 'c':         // c- Blur Image
            blur();
            saveImage();
            return 0;
        case 's':         // s- Save the image to a file
            saveImage();
            return 0;
        case '0':         // 0- Exit
            cout << "Thank You! The program ends here" << endl;
            break;
        default:         // Display error if no inputs from above entered
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
    for (int i = 0; i < SIZE; i++) {  // Creating a for loop to run over all pixels and calculate their average
        for (int j = 0; j < SIZE; j++) {
            avg += image[i][j];
        }
    }
    avg /= (SIZE * SIZE); // Divide this average by the total number of pixels

    for (int i = 0; i < SIZE; i++) {  // Then looping over each pixel again to ask if that pixel greater that the average
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > avg)
                image[i][j] = 255;   // then change that pixel to white
            else
                image[i][j] = 0;     // Otherwise, change that pixel to black
        }
    }
}

//_________________________________________
void flipHorizontally(){

    for (int j = 0; j < SIZE; j++) { // A loop that runs over the columns in the image
        int start = 0;
        int end = SIZE - 1;
        while (start < end){ // The loop runs until it access half of the rows
            swap(image[start][j], image[end][j]); // Swap the image in the first row with the image in the last row
            start++;
            end--;
        }
    }
}

//_________________________________________
void flipVertically(){

    for (int i = 0; i < SIZE; i++) { // A loop that runs over the rows in the image
        int start = 0;
        int end = SIZE - 1;
        while (start < end){ // The loop runs until it access half of the columns
            swap(image[i][start], image[i][end]); // Swap the image in the first column with the image in the last column
            start++;
            end--;
        }
    }
}

//_________________________________________
void darken () {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            //divide image pixels by 2 to lower their value to be darker
            image[i][j] = (image[i][j]) / 2;

        }
    }
}

//_________________________________________
void lighten(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            //check if image after adding half the pixels to it is greater than white pixel value then make it white
            if ( image[i][j] + ( image[i][j] / 2) > 255){
                image[i][j] = 255;
            }
            else{
                // if not then add half the pixels value to be lighter
                image[i][j] =  image[i][j] + ( image[i][j] / 2);
            }
        }
    }
}

//_________________________________________
void mergeImage (){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            //load the pixels of first image to 2d array called secondImage
            secondImage[i][j] = image[i][j];

        }
    }
    loadImage();

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            //add pixels of first image and second image and divide by 2 (get average)
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
    // Creating an option menu for the user to choose from
    cout << "choose an option between the following: " << endl;
    cout << "1.rotate 90 degree " << endl;
    cout << "2.rotate 180 degree " << endl;
    cout << "3.rotate 270 degree " << endl;
    cin >> x;
    if (x == 1) { // Inside the first option
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = i; j < SIZE - i - 1; j++) {

                int temp = image[i][j]; // We create a temporary variable to store the image in
                image[i][j] = image[SIZE - 1 - j][i];
                image[SIZE - 1 - j][i] = image[SIZE - 1 - i][SIZE - 1 - j];
                image[SIZE - 1 - i][SIZE - 1 - j] = image[j][SIZE - 1 - i];
                image[j][SIZE - 1 - i] = temp;
            }
        }

    }
    else if (x == 2) { // Inside the second option
        for (int i = 0; i < SIZE / 2; i++){
            for (int j = 0; j < SIZE; j++) {
                swap(image[i][j], image[SIZE - i - 1][SIZE - j - 1]);
            }
        }

    }
    else{ // Inside the third option
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = i; j < SIZE - i - 1; j++) {

                int temp = image[i][j]; // We create a temporary variable to store the image in
                image[i][j] = image[SIZE - 1 - j][i];
                image[SIZE - 1 - j][i] = image[SIZE - 1 - i][SIZE - 1 - j];
                image[SIZE - 1 - i][SIZE - 1 - j] = image[j][SIZE - 1 - i];
                image[j][SIZE - 1 - i] = temp;
            }
        }

        for (int i = 0; i < SIZE / 2; i++){ // We create another for loop that runs over the first half of the rows
            for (int j = 0; j < SIZE; j++) { // A nested loop to access all the columns in that row
                swap(image[i][j], image[SIZE - i - 1][SIZE - j - 1]);
            }
        }

    }
}

//_________________________________________
void detectImage(){
    long avg = 0;
    for (int i = 0; i < SIZE; i++) {  // A loop that runs over all the pixels to calculate the average
        for (int j = 0; j < SIZE; j++) {
            avg += image[i][j];
        }
    }
    avg /= (SIZE * SIZE);

    for (int i = 0; i < SIZE; i++) { //Compare that average with the difference between the pixels
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j]-image[i+1][j] > avg/6){ //comparing between the pixel and the one below to it in the same column
                image[i][j] = 0;
            }else if (image[i][j]-image[i][j+1] > avg/6){ //comparing between the pixel and the one next to it in the same row
                image[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) { // Run over all the pixels to check it is not black then it is converted to white
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
            //if we shrink by 1/2 the value we divide the index if pixels by 2
                secondImage[i][j] = 255;
                secondImage[i/2][j/2] = image[i][j];
            }
        }
    }
    else if(choice == 2){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                //if we shrink by 1/3 the value we divide the index if pixels by 3
                secondImage[i][j] = 255;
                secondImage[i/3][j/3] = image[i][j];
            }

        }

    }
    else {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                //if we shrink by 1/4 the value we divide the index if pixels by 4
                secondImage[i][j] = 255;
                secondImage[i/4][j/4] = image[i][j];
            }

        }

    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            //load result image to image array again
            image[i][j] = secondImage[i][j];
        }
    }
}

//_________________________________________
void mirrorLeft() {

    for (int i = 0; i < SIZE; i++) {  // A loop that runs over all the rows.
        int start = 0;  // using two variables "start" for the first column and "end" for the last column
        int end = SIZE - 1;

        while (start <= end) {
            image[i][start] = image[i][end]; // The pixel in the last column replaces that in the first column
            start++; // Increment in the start to access the next column
            end--;   // decrement in the end to access the previous column
        }            // Until all columns are accessed
    }
}

//_________________________________________
void mirrorRight() {
    for (int i = 0; i < SIZE; i++) {  // A loop that runs over all the rows.
        int start = 0;
        int end = SIZE - 1;

        while (start <= end) {
            image[i][end] = image[i][start]; // The pixel in the first column replaces that in the last column
            start++;
            end--;
        }
    }
}
//_________________________________________
void mirrorUpper(){
    for (int i = 0; i < SIZE; i++) { // A loop that runs over all the columns.
        int start = 0;
        int end = SIZE - 1;

        while (start <= end) {
            image[end][i] = image[start][i]; // The pixel in the first row replaces that in the last row
            start++;
            end--;
        }
    }
}

//_________________________________________
void mirrorDown(){

    for (int i = 0; i < SIZE; i++) { // A loop that runs over all the columns.
        int start = 0;
        int end = SIZE - 1;

        while (start <= end) {
            image[start][i] = image[end][i]; // The pixel in the last row replaces that in the first row
            start++;
            end--;
        }
    }
}

//_________________________________________
void blur(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            //get every index around the first one and divide by 9
            image[i][j] = (image[i][j] + image[i-1][j] + image[i][j-1] + image[i-1][j-1] + image[i+1][j] + image[i][j+1] + image[i+1][j+1] + image[i+1][j-1] + image[i-1][j+1])/9;

        }

    }
}

//_________________________________________
void enlarge() {
    char inputChoice;
    int quarterImage[SIZE/2][SIZE/2];
    cout << "Which quarter to enlarge? 1, 2, 3 or 4: ";
    cin >> inputChoice; //the user inputs the quarter number
    switch (inputChoice) //to test every case
        case '1': { //first quarter
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0; j < SIZE / 2; j++) {
                    quarterImage[i][j] = image[i][j];
                }
            }
            for (int i = 0; i < SIZE; i++) {
                int m = 0;
                for (int j = 0; j < SIZE; j++) {
                    if ((j + 1) % 2 == 0) {
                        for (int k = (j - 1); k <= j; k++) {
                            image[i][k] = quarterImage[i/2][m];
                            image[i+1][k] = quarterImage[i/2][m];
                        }
                        m+=1;
                    }
                }//the pixels of the first quarter are enlarged to 256
            }
        break;
        case '2': //second quarter
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = SIZE / 2, k = 0; j < SIZE; j++, k++) {
                        quarterImage[i][k] = image[i][j];
                    }
                }
            for (int i = 0; i < SIZE; i++) {
                int m =0;
                for (int j = 0; j < SIZE; j++) {
                    if ((j + 1) % 4 == 0) {
                        for (int k = (j - 3); k <= j; k++) {
                            image[i][k] = quarterImage[i/2][m];
                            image[i+1][k] = quarterImage[i/2][m];
                        }
                        m += 1;
                    }

                }//the pixels of the second quarter are enlarged to 256
            }
        break;
        case '3': //third quarter
            for (int i = SIZE / 2, k = 0; i < SIZE; i++, k++) {
                for (int j = 0; j < SIZE / 2; j++) {
                        quarterImage[k][j] = image[i][j];
                    }//the pixels of the third quarter are enlarged to 256
                }
            for (int i = 0; i < SIZE; i++) {
                int m =0;
                for (int j = 0; j < SIZE; j++) {
                    if ((j + 1) % 4 == 0) {
                        for (int k = (j - 3); k <= j; k++) {
                            image[i][k] = quarterImage[i/2][m];
                            image[i+1][k] = quarterImage[i/2][m];
                        }
                        m += 1;
                    }
                }//the pixels of the third quarter are enlarged to 256
            }
        break;
        case '4': //4th quarter
                for (int i = SIZE / 2, c = 0; i < SIZE; i++, c++) {
                    for (int j = SIZE / 2, k = 0; j < SIZE; j++, k++) {
                        quarterImage[c][k] = image[i][j];
                    }
                }
            for (int i = 0; i < SIZE; i++) {
                int m =0;
                for (int j = 0; j < SIZE; j++) {
                    if ((j + 1) % 4 == 0) {
                        for (int k = (j - 3); k <= j; k++) {
                            image[i][k] = quarterImage[i/2][m];
                            image[i+1][k] = quarterImage[i/2][m];
                        }
                        m += 1;
                    }
                }//the pixels of the 4th quarter are enlarged to 256
            }
        break;
        }
}
//_________________________________________
void shuffle(){
        unsigned char quad1[SIZE][SIZE];
        unsigned char quad2[SIZE][SIZE];
        unsigned char quad3[SIZE][SIZE];
        unsigned char quad4[SIZE][SIZE]; //declaring four images for each quad to shuffle between them
        char w, x, y, z;
        int r = 0, c = 0;
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                quad1[r][c] = image[i][j];
                c += 1;
            }
        }
        r += 1;
        c = 0;
            //this loop for making first quad equal to the first quad in original picture
    r=0,c=0; //returning back to zero for each loop so not to work on increased value for them
    for (int i = 0; i < SIZE/2; i++) {
        for (int j = SIZE / 2; j < SIZE; j++) {
            quad2[r][c] = image[i][j];
            c += 1;
        }
        r += 1;
        c = 0;
    }
//this loop for making second quad equal to the second quad in original picture
    r=0,c=0;
    for (int i = SIZE / 2; i < SIZE; i++) {
        for (int j = 0; j < SIZE / 2; j++){
            quad3[r][c] = image[i][j];
            c+=1;
        }
        r += 1;
        c=0;
    }
//this loop for making third quad equal to the third quad in original picture
    r=0,c=0;
    for (int i = SIZE / 2; i < SIZE; i++) {
        for (int j = SIZE / 2; j < SIZE; j++) {
            quad4[r][c] = image[i][j];
            c += 1;
        }
        r += 1;
        c = 0;
    }
//this loop for making fourth quad equal to the fourth quad in original picture
    cout << "Please enter shuffle order ";
    cin >> w >> x >> y >> z;
    r = 0,c = 0;
    switch (w) {
        case '1' :
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0; j < SIZE / 2; j++) {
                    image[i][j] = quad1[r][c];
                    c += 1;
                }
                r += 1;
                c = 0;
            }
//the increments for replacing each pixel in the photo
            break;
            //if the user enters first quad to be replaced with first quad , the new declared quad image will be replaced in the original photo
        case '2' :
            for (int i = 0; i < SIZE/2; i++) {
                for (int j = 0; j < SIZE/2; j++){
                    image[i][j] = quad2[r][c];
                    c += 1;
                }
                r += 1;
                c = 0;
            }
            break;
            //if the user enters first quad to be replaced with second quad , the new declared quad image will be replaced in the original photo
        case '3':
            for (int i = 0; i < SIZE/2; i++) {
                for (int j = 0; j < SIZE / 2; j++){
                    image[i][j] =quad3[r][c];
                    c += 1;
                }
                r += 1;
                c = 0;
            }
            break;
            //if the user enters first quad to be replaced with third quad , the new declared quad image will be replaced in the original photo
        case '4' :
            for (int i = 0; i < SIZE/2; i++) {
                for (int j = 0; j < SIZE/2; j++) {
                    image[i][j] = quad4[r][c];
                    c += 1;
                }
                r += 1;
                c = 0;
            }
            break;
            //if the user enters first quad to be replaced with fourth quad , the new declared quad image will be replaced in the original photo
            r=0,c=0;
            switch (x) { //the same as first case goes here but instead we're working on the second quad and putting in it what the user ordered
                case '1' :
                    for (int i = 0; i < SIZE / 2; i++) {
                        for (int j = SIZE / 2; j < SIZE; j++) {
                            image[i][j] = quad1[r][c];
                            c += 1;
                        }
                        r += 1;
                        c = 0;
                    }
                    break;

                case '2' :
                    for (int i = 0; i < SIZE/2; i++) {
                        for (int j = SIZE / 2; j < SIZE; j++){
                            image[i][j] = quad2[r][c];
                            c += 1;
                        }
                        r += 1;
                        c = 0;
                    }
                    break;
                case '3':
                    for (int i = 0; i < SIZE/2; i++) {
                        for (int j = SIZE / 2; j < SIZE; j++){
                            image[i][j] =quad3[r][c];
                            c += 1;
                        }
                        r += 1;
                        c = 0;
                    }
                    break;
                case '4' :
                    for (int i = 0; i < SIZE/2; i++) {
                        for (int j = SIZE / 2; j < SIZE; j++) {
                            image[i][j] = quad4[r][c];
                            c += 1;
                        }
                        r += 1;
                        c = 0;
                    }
                    break;
                    r=0,c=0;
                    switch(y){
                        for (int i = 0; i < SIZE / 2; i++) {
                    for (int j = SIZE/2; j < SIZE; j++) {
                     image[i][j] = quad1[r][c];
                         c += 1;
                    }
                     r += 1;
                     c = 0;
                 }
                 break;
             case '2' :
                 for (int i = 0; i < SIZE/2; i++) {
                     for (int j = SIZE/2; j < SIZE; j++) {
                         image[i][j] = quad2[r][c];
                         c += 1;
                     }
                     r += 1;
                     c = 0;
                 }
                 break;
             case '3':
                for (int i = 0; i < SIZE/2; i++) {
                     for (int j = SIZE/2; j < SIZE; j++) {
                         image[i][j] =quad3[r][c];
                         c += 1;
                     }
                     r += 1;
                     c = 0;
                 }
                 break;
             case '4' :
                 for (int i = 0; i < SIZE/2; i++) {
                     for (int j = SIZE/2; j < SIZE; j++) {
                         image[i][j] = quad4[r][c];
                         c += 1;
                     }
                     r += 1;
                     c = 0;
                 }
                 break;
         }
         r=0,c=0;
         switch (y) { //working the third quad
             case '1' :
                 for (int i = SIZE/2; i < SIZE; i++) {
                     for (int j = 0; j < SIZE / 2; j++) {
                         image[i][j] = quad1[r][c];
                         c += 1;
                     }
                     r += 1;
                     c = 0;
                 }
                 break;
             case '2' :
                for (int i = SIZE/2; i < SIZE; i++) {
                     for (int j = 0; j < SIZE/2; j++) {
                         image[i][j] = quad2[r][c];
                         c += 1;
                     }
                     r += 1;
                     c = 0;
                 }
                 break;
            case '3':
                 for (int i = SIZE/2; i < SIZE; i++) {
                     for (int j = 0; j < SIZE / 2; j++) {
                         image[i][j] =quad3[r][c];
                         c += 1;
                     }
                     r += 1;
                     c = 0;
                 }
                 break;
             case '4' :
                 for (int i = SIZE/2; i < SIZE; i++) {
                     for (int j = 0; j < SIZE/2; j++) {
                         image[i][j] = quad4[r][c];
                         c += 1;
                     }
                     r += 1;
                     c = 0;
                 }
                 break;
         }
         r=0,c=0;

         switch (z) { //working on fourth quad
             case '1' :
                 for (int i = SIZE/2; i < SIZE; i++) {
                     for (int j = SIZE/2; j < SIZE; j++) {
                         image[i][j] = quad1[r][c];
                         c += 1;
                     }
                     r += 1;
                     c = 0;
                 }
                 break;

             case '2' :
                 for (int i =SIZE/2; i < SIZE; i++) {
                     for (int j = SIZE/2; j < SIZE; j++) {
                         image[i][j] = quad2[r][c];
                         c += 1;
                     }
                     r += 1;
                     c = 0;
                 }
                 break;

             case '3':
                 for (int i = SIZE/2; i < SIZE; i++) {
                     for (int j = SIZE/2; j < SIZE ; j++) {
                         image[i][j] =quad3[r][c];
                         c += 1;
                     }
                     r += 1;
                     c = 0;
                 }
                 break;

             case '4' :
                 for (int i = SIZE/2; i < SIZE; i++) {
                     for (int j = SIZE/2; j < SIZE; j++) {
                         image[i][j] = quad4[r][c];
                         c += 1;
                     }
                     r += 1;
                     c = 0;
                 }
                 break;
                    }
                    }
            }
}

// The program ends here!