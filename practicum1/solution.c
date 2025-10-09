#include <stdio.h>
#include <stdlib.h>

// Structure to hold grayscale pixel data
typedef struct {
    unsigned char value;
} PixelGray;

char fileFormat[2];
int maxGreyValue;

// Function to read a PGM image into a 2D array
PixelGray** readPGM(const char* filename, int* width, int* height){
    FILE* myfile = NULL;
    myfile = fopen(filename, "rb");
    if (myfile == NULL){
        printf("error opening the file.");
        fclose(myfile);
        return NULL;
    }

    fscanf(myfile, "%2s", fileFormat);
    //printf("file format is: %2s \n", fileFormat); 
    fscanf(myfile, "%d", width);
    fscanf(myfile, "%d", height);
    //printf("width is: %d \nheight is: %d\n", *width, *height);
    fscanf(myfile, "%d", &maxGreyValue);
    fgetc(myfile);
    //printf("max grey value is: %d \n", maxGreyValue); 

    PixelGray **matrix = (PixelGray**) malloc(*height * sizeof(PixelGray*));
    if (matrix == NULL){
        printf("error allocating matrix memory.");
        fclose(myfile);
        return NULL;
    }
    for (int i = 0; i < *height; i++){
        matrix[i] = (PixelGray*)malloc(*width * sizeof(PixelGray));
        if (matrix[i] == NULL){
            printf("error allocating width memory.");
            fclose(myfile);
            return NULL;
        }
    }

    for (int i = 0; i < *height; i++){
        for (int j = 0; j < *width; j++){
            fread(&matrix[i][j].value, sizeof(unsigned char), 1, myfile);
        }
    }

    fclose(myfile);
    return matrix;
} 


// Function to write a 2D matrix as a PGM image
void writePGM(const char* filename, PixelGray** matrix, int* width, int* height){
    FILE* myfile = NULL;
    myfile = fopen(filename, "wb");
    if (myfile == NULL){
        printf("error opening the file.");
        return;
    }
    
    fprintf(myfile, "%s\n", fileFormat);
    fprintf(myfile, "%d %d\n", *width, *height);
    fprintf(myfile, "%d\n", maxGreyValue);
    
    for (int i = 0; i < *height; i++){
        for (int j = 0; j < *width; j++){
            fwrite(&matrix[i][j].value, sizeof(unsigned char), 1, myfile);
        }
    }
    
    fclose(myfile);
}


// Function to threshold the image matrix
PixelGray** threshold(PixelGray** matrix, int* width, int* height){ // if >80 - make it 255 (black) else its 0 (white)
    PixelGray **thresholdMatrix = (PixelGray**) malloc(*height * sizeof(PixelGray*));
    if (thresholdMatrix == NULL){
        printf("error allocating matrix memory.");
        return NULL;
    }
    for (int i = 0; i < *height; i++){
        thresholdMatrix[i] = (PixelGray*)malloc(*width * sizeof(PixelGray));
        if (thresholdMatrix[i] == NULL){
            printf("error allocating width memory.");
            return NULL;
        }
    }

    for (int i = 0; i < *height; i++){
        for (int j = 0; j < *width; j++){
            if (matrix[i][j].value > 80)
                thresholdMatrix[i][j].value = 255;
            else
                thresholdMatrix[i][j].value = 0;
        }
    }

    return thresholdMatrix;
}



// Function to rotate the image matrix
PixelGray** rotate(PixelGray** matrix, int* width, int* height){
   
    PixelGray **newMatrix = (PixelGray**) malloc(*width * sizeof(PixelGray*));
    if (newMatrix == NULL){
        printf("error allocating newMatrix memory.");
        return NULL;
    }
    for (int i = 0; i < *width; i++){
        newMatrix[i] = (PixelGray*)malloc(*height * sizeof(PixelGray));
        if (newMatrix[i] == NULL){
            printf("error allocating memory.");
            return NULL;
        }
    }

    for (int i = 0; i < *height; i++){
        for (int j = 0; j < *width; j++){
            newMatrix[j][i].value = matrix[i][j].value;
        }
    }

    int thingy = *width;
    *width = *height;
    *height = thingy;

    return newMatrix;
}


//main function - DO NOT MODIFY
int main() {
    int width, height;  // variable to hold width and height. Use reference in other functions

    PixelGray** image_original = readPGM("Mickey.pgm", &width, &height);        
    // Now you have the grayscale image data in the 'image_original' 2D array

    // Access pixel data using image[row][col].value
    // For example, to access the pixel at row=2, col=3:
    // unsigned char pixel_value = image[2][3].value;

    // Create a new 2D array 'image_thresh' to store the threshold image
    PixelGray** image_thresh = threshold(image_original, &width, &height);
    //write the image data as "threshold.pgm"
    writePGM("threshold.pgm", image_thresh, &width, &height);

    // Create a new 2D array 'image_rotate' to store the rotated image
    PixelGray** image_rotate = rotate(image_original, &width, &height);
    //write the image data as "rotate.pgm"
    writePGM("rotate.pgm", image_rotate, &width, &height);

    image_rotate = rotate(image_rotate, &width, &height);
    //write the image data as "rotate_again.pgm"
    writePGM("rotate_again.pgm", image_rotate, &width, &height);

    // Free the allocated memory when you're done
    for (int i = 0; i < height; ++i) {
        free(image_original[i]);
        free(image_thresh[i]);
        free(image_rotate[i]);
    }
    free(image_original);
    free(image_thresh);
    free(image_rotate);   
    return 0;
}