#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Image{
public:
    struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;

    };

    struct Pixel{
        unsigned char Blue;
        unsigned char Green;
        unsigned char Red;
    };

public:
    vector<Pixel> Pixels;
    Header NewHeader;

    Image();
    Image(char idLength, char colorMapType, char dataTypeCode, short colorMapOrigin, short colorMapLength, char colorMapDepth,
          short xOrigin, short yOrigin, short width, short height, char bitsPerPixel, char imageDescriptor, vector<Pixel> Pixes);

};

void Print(Image new_Image);
Image Reading(string opened_file);
void Writing(string new_file, Image newImage);

void Multiply(Image& P1, Image& P2, Image& result);

void Multiply(Image& P1, float red, float green, float blue, Image& result);

void Screen(Image& P1, Image& P2, Image& result);

void Subtract(Image& P1, Image& P2, Image& result);

void Addition(Image& P1, Image& P2, Image& result);

void Addition(Image& P1, const string& color, int factor, Image& result);

void Overlay(Image& P1, Image& P2, Image& result);
void Combine(Image& P1, Image& P2, Image& P3, Image& result);
void Flip(Image& P1, Image& result);
void Channel_Write(Image& P1);
void Channel_Red(Image& P1, Image& result);
void Channel_Green(Image& P1, Image& result);
void Channel_Blue(Image& P1, Image& result);


int Clamp(int value);
float Conditional(float P1, float P2);

Image::Image(){
    NewHeader.idLength = 0;
    NewHeader.colorMapType = 0;
    NewHeader.dataTypeCode = 0;
    NewHeader.colorMapOrigin = 0;
    NewHeader.colorMapLength = 0;
    NewHeader.colorMapDepth = 0;
    NewHeader.xOrigin = 0;
    NewHeader.yOrigin = 0;
    NewHeader.width = 0;
    NewHeader.height = 0;
    NewHeader.bitsPerPixel = 0;
    NewHeader.imageDescriptor= 0;
}

Image::Image(char idLength, char colorMapType, char dataTypeCode, short colorMapOrigin, short colorMapLength, char colorMapDepth,
             short xOrigin, short yOrigin, short width, short height, char bitsPerPixel, char imageDescriptor, vector<Pixel> Pixes){

    NewHeader.idLength = idLength;
    NewHeader.colorMapType = colorMapType;
    NewHeader.dataTypeCode = dataTypeCode;
    NewHeader.colorMapOrigin = colorMapOrigin;
    NewHeader.colorMapLength = colorMapLength;
    NewHeader.colorMapDepth = colorMapDepth;
    NewHeader.xOrigin = xOrigin;
    NewHeader.yOrigin = yOrigin;
    NewHeader.width = width;
    NewHeader.height = height;
    NewHeader.bitsPerPixel = bitsPerPixel;
    NewHeader.imageDescriptor= imageDescriptor;
    Pixels = Pixes;
}

Image Reading(string opened_file) {
    //Open file and read the info
    ifstream inF(opened_file, ios::in | ios::binary);

    //read header file from image
    char idLength;
    inF.read((char*)(&idLength), 1);
    char colorMapType;
    inF.read((char*)(&colorMapType), 1);
    char dataTypeCode;
    inF.read((char*)(&dataTypeCode), 1);
    short colorMapOrigin;
    inF.read((char*)(&colorMapOrigin), 2);
    short colorMapLength;
    inF.read((char*)(&colorMapLength), 2);
    char colorMapDepth;
    inF.read((char*)(&colorMapDepth), 1);
    short xOrigin;
    inF.read((char*)(&xOrigin), 2);
    short yOrigin;
    inF.read((char*)(&yOrigin), 2);
    short width;
    inF.read((char*)(&width), 2);
    short height;
    inF.read((char*)(&height), 2);
    char bitsPerPixel;
    inF.read((char*)(&bitsPerPixel), 1);
    char imageDescriptor;
    inF.read((char*)(&imageDescriptor), 1);
    int area = int(width)*int(height);

    vector<Image::Pixel> Pixes;

    for (int i = 0; i < area; i++) {
        //Create pixel and read data
        Image::Pixel newPixel;
        inF.read((char*)(&newPixel.Blue), 1);
        inF.read((char*)(&newPixel.Green), 1);
        inF.read((char*)(&newPixel.Red), 1);
        Pixes.push_back(newPixel);
    }

    return Image(idLength, colorMapType, dataTypeCode, colorMapOrigin, colorMapLength, colorMapDepth, xOrigin,
                 yOrigin, width, height, bitsPerPixel, imageDescriptor, Pixes);

}

void Print(Image new_Image){
    cout << int(new_Image.NewHeader.idLength) << endl;
    cout << int(new_Image.NewHeader.colorMapType) << endl;
    cout << int(new_Image.NewHeader.dataTypeCode) << endl;
    cout << int(new_Image.NewHeader.colorMapOrigin) << endl;
    cout << int(new_Image.NewHeader.colorMapLength) << endl;
    cout << int(new_Image.NewHeader.colorMapDepth) << endl;
    cout << int(new_Image.NewHeader.xOrigin) << endl;
    cout << int(new_Image.NewHeader.yOrigin) << endl;
    cout << int(new_Image.NewHeader.width) << endl;
    cout << int(new_Image.NewHeader.height) << endl;
    cout << int(new_Image.NewHeader.bitsPerPixel) << endl;
    cout << int(new_Image.NewHeader.imageDescriptor) << endl;
}

void Writing(string new_file, Image newImage) {
    fstream F(new_file, ios_base::out | ios_base::binary);

    //write info from the newfile to image
    F.write((char *) (&newImage.NewHeader.idLength), 1);
    F.write((char *) (&newImage.NewHeader.colorMapType), 1);
    F.write((char *) (&newImage.NewHeader.dataTypeCode), 1);
    F.write((char *) (&newImage.NewHeader.colorMapOrigin), 2);
    F.write((char *) (&newImage.NewHeader.colorMapLength), 2);
    F.write((char *) (&newImage.NewHeader.colorMapDepth), 1);
    F.write((char *) (&newImage.NewHeader.xOrigin), 2);
    F.write((char *) (&newImage.NewHeader.yOrigin), 2);
    F.write((char *) (&newImage.NewHeader.width), 2);
    F.write((char *) (&newImage.NewHeader.height), 2);
    F.write((char *) (&newImage.NewHeader.bitsPerPixel), 1);
    F.write((char *) (&newImage.NewHeader.imageDescriptor), 1);
    int area = int(newImage.NewHeader.width) * int(newImage.NewHeader.height);


    for (int i = 0; i < area; i++) {
        //Read pixels from class and write to new file
        F.write((char *) (&newImage.Pixels[i].Blue), 1);
        F.write((char *) (&newImage.Pixels[i].Green), 1);
        F.write((char *) (&newImage.Pixels[i].Red), 1);
    }


}

//task 1, 3, 4
void Multiply(Image& P1, Image& P2, Image& result) {
    ///(NP1) * (NP2)
    int area = int(P1.NewHeader.width) * int(P1.NewHeader.height);
    vector<Image::Pixel> Pixes;

    for (int i = 0; i < area; i++) {
        Image::Pixel newPixel;

        //Blue Pixel
        float newBlueP1 = float(P1.Pixels[i].Blue)/255;
        float newBlueP2 = float(P2.Pixels[i].Blue)/255;
        float newBlueP3 = ((newBlueP1 * newBlueP2) * 255) + 0.5f;



        unsigned char newBlue = char(newBlueP3);

        //Green Pixel
        float newGreenP1 = float(P1.Pixels[i].Green)/255;
        float newGreenP2 = float(P2.Pixels[i].Green)/255;
        float newGreenP3 = ((newGreenP1 * newGreenP2) * 255) + 0.5f;

        unsigned char newGreen = char(newGreenP3);

        //Red Pixel
        float newRedP1 = float(P1.Pixels[i].Red)/255;
        float newRedP2 = float(P2.Pixels[i].Red)/255;
        float newRedP3 = ((newRedP1 * newRedP2) * 255) + 0.5f;

        unsigned char newRed = char(newRedP3);

        newPixel.Blue = newBlue;
        newPixel.Green = newGreen;
        newPixel.Red = newRed;

        Pixes.push_back(newPixel);

    }

    result.NewHeader.idLength = P1.NewHeader.idLength;
    result.NewHeader.colorMapType = P1.NewHeader.colorMapType;
    result.NewHeader.dataTypeCode = P1.NewHeader.dataTypeCode;
    result.NewHeader.colorMapOrigin = P1.NewHeader.colorMapOrigin;
    result.NewHeader.colorMapLength = P1.NewHeader.colorMapLength;
    result.NewHeader.colorMapDepth = P1.NewHeader.colorMapDepth;
    result.NewHeader.xOrigin = P1.NewHeader.xOrigin;
    result.NewHeader.yOrigin = P1.NewHeader.yOrigin;
    result.NewHeader.width = P1.NewHeader.width;
    result.NewHeader.height = P1.NewHeader.height;
    result.NewHeader.bitsPerPixel = P1.NewHeader.bitsPerPixel;
    result.NewHeader.imageDescriptor = P1.NewHeader.imageDescriptor;
    result.Pixels = Pixes;


}
//task 7

void Multiply(Image& P1, float red, float green, float blue, Image& result){
    int area = int(P1.NewHeader.width) * int(P1.NewHeader.height);
    vector<Image::Pixel> Pixes;

    for (int i = 0; i < area; i++) {
        Image::Pixel newPixel;

        //Blue Pixel
        float newBlueP3 = Clamp((P1.Pixels[i].Blue * blue));
        unsigned char newBlue = char(newBlueP3);

        //Green Pixel
        float newGreenP3 = Clamp((P1.Pixels[i].Green * green));
        unsigned char newGreen = char(newGreenP3);

        //Red Pixel
        float newRedP3 = Clamp((P1.Pixels[i].Red * red));
        unsigned char newRed = char(newRedP3);

        newPixel.Blue = newBlue;
        newPixel.Green = newGreen;
        newPixel.Red = newRed;

        Pixes.push_back(newPixel);

    }
    result.NewHeader.idLength = P1.NewHeader.idLength;
    result.NewHeader.colorMapType = P1.NewHeader.colorMapType;
    result.NewHeader.dataTypeCode = P1.NewHeader.dataTypeCode;
    result.NewHeader.colorMapOrigin = P1.NewHeader.colorMapOrigin;
    result.NewHeader.colorMapLength = P1.NewHeader.colorMapLength;
    result.NewHeader.colorMapDepth = P1.NewHeader.colorMapDepth;
    result.NewHeader.xOrigin = P1.NewHeader.xOrigin;
    result.NewHeader.yOrigin = P1.NewHeader.yOrigin;
    result.NewHeader.width = P1.NewHeader.width;
    result.NewHeader.height = P1.NewHeader.height;
    result.NewHeader.bitsPerPixel = P1.NewHeader.bitsPerPixel;
    result.NewHeader.imageDescriptor = P1.NewHeader.imageDescriptor;
    result.Pixels = Pixes;
}
//task 3
void Screen(Image& P1, Image& P2, Image& result){
    ///1 - [(1 - NP1) * (1 - NP2)]
    int area = int(P1.NewHeader.width) * int(P1.NewHeader.height);
    vector<Image::Pixel> Pixes;

    for (int i = 0; i < area; i++) {
        Image::Pixel newPixel;

        //Blue Pixel
        float newBlueP1 = float(P1.Pixels[i].Blue)/255;
        float newBlueP2 = float(P2.Pixels[i].Blue)/255;
        float newBlueP3 = ((1 - (1-newBlueP1)*(1-newBlueP2)) * 255) + 0.5f;

        unsigned char newBlue = char(newBlueP3);

        //Green Pixel
        float newGreenP1 = float(P1.Pixels[i].Green)/255;
        float newGreenP2 = float(P2.Pixels[i].Green)/255;
        float newGreenP3 = ((1 - (1-newGreenP1)*(1-newGreenP2)) * 255) + 0.5f;

        unsigned char newGreen = char(newGreenP3);

        //Red Pixel
        float newRedP1 = float(P1.Pixels[i].Red)/255;
        float newRedP2 = float(P2.Pixels[i].Red)/255;
        float newRedP3 = ((1 - (1-newRedP1)*(1-newRedP2)) * 255) + 0.5f;

        unsigned char newRed = char(newRedP3);

        newPixel.Blue = newBlue;
        newPixel.Green = newGreen;
        newPixel.Red = newRed;

        Pixes.push_back(newPixel);

    }

    result.NewHeader.idLength = P1.NewHeader.idLength;
    result.NewHeader.colorMapType = P1.NewHeader.colorMapType;
    result.NewHeader.dataTypeCode = P1.NewHeader.dataTypeCode;
    result.NewHeader.colorMapOrigin = P1.NewHeader.colorMapOrigin;
    result.NewHeader.colorMapLength = P1.NewHeader.colorMapLength;
    result.NewHeader.colorMapDepth = P1.NewHeader.colorMapDepth;
    result.NewHeader.xOrigin = P1.NewHeader.xOrigin;
    result.NewHeader.yOrigin = P1.NewHeader.yOrigin;
    result.NewHeader.width = P1.NewHeader.width;
    result.NewHeader.height = P1.NewHeader.height;
    result.NewHeader.bitsPerPixel = P1.NewHeader.bitsPerPixel;
    result.NewHeader.imageDescriptor = P1.NewHeader.imageDescriptor;
    result.Pixels = Pixes;

}

void Subtract(Image& P1, Image& P2, Image& result){
    ///P1 - P2
    int area = int(P1.NewHeader.width) * int(P1.NewHeader.height);
    vector<Image::Pixel> Pixes;

    for (int i = 0; i < area; i++) {
        Image::Pixel newPixel;
        //add the blue from P1 and P2 together and clamp if less than 0 or greater than 255
        int newBlue = int(P1.Pixels[i].Blue) - int(P2.Pixels[i].Blue);
        int newGreen = int(P1.Pixels[i].Green) - int(P2.Pixels[i].Green);
        int newRed = int(P1.Pixels[i].Red) - int(P2.Pixels[i].Red);

        //Clamp below 0 and above 255
        newPixel.Blue = Clamp(newBlue);
        newPixel.Green = Clamp(newGreen);
        newPixel.Red = Clamp(newRed);

        Pixes.push_back(newPixel);
    }

    result.NewHeader.idLength = P1.NewHeader.idLength;
    result.NewHeader.colorMapType = P1.NewHeader.colorMapType;
    result.NewHeader.dataTypeCode = P1.NewHeader.dataTypeCode;
    result.NewHeader.colorMapOrigin = P1.NewHeader.colorMapOrigin;
    result.NewHeader.colorMapLength = P1.NewHeader.colorMapLength;
    result.NewHeader.colorMapDepth = P1.NewHeader.colorMapDepth;
    result.NewHeader.xOrigin = P1.NewHeader.xOrigin;
    result.NewHeader.yOrigin = P1.NewHeader.yOrigin;
    result.NewHeader.width = P1.NewHeader.width;
    result.NewHeader.height = P1.NewHeader.height;
    result.NewHeader.bitsPerPixel = P1.NewHeader.bitsPerPixel;
    result.NewHeader.imageDescriptor = P1.NewHeader.imageDescriptor;
    result.Pixels = Pixes;

}

void Addition(Image& P1, Image& P2, Image& result){
    ///P1 + P2
    int area = int(P1.NewHeader.width) * int(P1.NewHeader.height);
    vector<Image::Pixel> Pixes;

    for (int i = 0; i < area; i++) {
        Image::Pixel newPixel;
        //add the blue from P1 and P2 together and clamp if less than 0 or greater than 255
        int newBlue = int(P1.Pixels[i].Blue) + int(P2.Pixels[i].Blue);
        int newGreen = int(P1.Pixels[i].Green) + int(P2.Pixels[i].Green);
        int newRed = int(P1.Pixels[i].Red) + int(P2.Pixels[i].Red);

        //Clamp below 0 and above 255
        newPixel.Blue = Clamp(newBlue);
        newPixel.Green = Clamp(newGreen);
        newPixel.Red = Clamp(newRed);

        Pixes.push_back(newPixel);
    }
    result.NewHeader.idLength = P1.NewHeader.idLength;
    result.NewHeader.colorMapType = P1.NewHeader.colorMapType;
    result.NewHeader.dataTypeCode = P1.NewHeader.dataTypeCode;
    result.NewHeader.colorMapOrigin = P1.NewHeader.colorMapOrigin;
    result.NewHeader.colorMapLength = P1.NewHeader.colorMapLength;
    result.NewHeader.colorMapDepth = P1.NewHeader.colorMapDepth;
    result.NewHeader.xOrigin = P1.NewHeader.xOrigin;
    result.NewHeader.yOrigin = P1.NewHeader.yOrigin;
    result.NewHeader.width = P1.NewHeader.width;
    result.NewHeader.height = P1.NewHeader.height;
    result.NewHeader.bitsPerPixel = P1.NewHeader.bitsPerPixel;
    result.NewHeader.imageDescriptor = P1.NewHeader.imageDescriptor;
    result.Pixels = Pixes;
}
//task 6
void Addition(Image& P1, const string& color, int factor, Image& result){
    int area = int(P1.NewHeader.width) * int(P1.NewHeader.height);
    vector<Image::Pixel> Pixes;

    for (int i = 0; i < area; i++) {
        Image::Pixel newPixel;

        if (color == "blue"){
            //change blue color
            int newBlue = int(P1.Pixels[i].Blue) + factor;

            newPixel.Blue = Clamp(newBlue);
            newPixel.Green = P1.Pixels[i].Green;
            newPixel.Red = P1.Pixels[i].Red;
        }

        if (color == "green"){
            //change green color
            int newGreen = int(P1.Pixels[i].Green) + factor;

            newPixel.Green = Clamp(newGreen);
            newPixel.Blue = P1.Pixels[i].Blue;
            newPixel.Red = P1.Pixels[i].Red;
        }

        if (color == "red"){
            int newRed = int(P1.Pixels[i].Red) + factor;

            newPixel.Red = Clamp(newRed);
            newPixel.Blue = P1.Pixels[i].Blue;
            newPixel.Green = P1.Pixels[i].Green;
        }

        Pixes.push_back(newPixel);
    }
    result.NewHeader.idLength = P1.NewHeader.idLength;
    result.NewHeader.colorMapType = P1.NewHeader.colorMapType;
    result.NewHeader.dataTypeCode = P1.NewHeader.dataTypeCode;
    result.NewHeader.colorMapOrigin = P1.NewHeader.colorMapOrigin;
    result.NewHeader.colorMapLength = P1.NewHeader.colorMapLength;
    result.NewHeader.colorMapDepth = P1.NewHeader.colorMapDepth;
    result.NewHeader.xOrigin = P1.NewHeader.xOrigin;
    result.NewHeader.yOrigin = P1.NewHeader.yOrigin;
    result.NewHeader.width = P1.NewHeader.width;
    result.NewHeader.height = P1.NewHeader.height;
    result.NewHeader.bitsPerPixel = P1.NewHeader.bitsPerPixel;
    result.NewHeader.imageDescriptor = P1.NewHeader.imageDescriptor;
    result.Pixels = Pixes;
}
//task 5
void Overlay(Image& P1, Image& P2, Image& result){
    ///if NP2 <= 0.5 then 2 * NP1 * NP2
    ///if NP2 > 0.5 then 1 - [2*(1 - NP1) * (1 - NP2)]
    int area = int(P1.NewHeader.width) * int(P1.NewHeader.height);
    vector<Image::Pixel> Pixes;

    for (int i = 0; i < area; i++) {
        Image::Pixel newPixel;

        //Blue Pixel
        float newBlueP1 = float(P1.Pixels[i].Blue)/255;
        float newBlueP2 = float(P2.Pixels[i].Blue)/255;

        unsigned char newBlue = Conditional(newBlueP1, newBlueP2);

        //Green Pixel
        float newGreenP1 = float(P1.Pixels[i].Green)/255;
        float newGreenP2 = float(P2.Pixels[i].Green)/255;

        unsigned char newGreen = Conditional(newGreenP1, newGreenP2);

        //Red Pixel
        float newRedP1 = float(P1.Pixels[i].Red)/255;
        float newRedP2 = float(P2.Pixels[i].Red)/255;

        unsigned char newRed = Conditional(newRedP1, newRedP2);

        newPixel.Blue = newBlue;
        newPixel.Green = newGreen;
        newPixel.Red = newRed;

        Pixes.push_back(newPixel);
    }
    result.NewHeader.idLength = P1.NewHeader.idLength;
    result.NewHeader.colorMapType = P1.NewHeader.colorMapType;
    result.NewHeader.dataTypeCode = P1.NewHeader.dataTypeCode;
    result.NewHeader.colorMapOrigin = P1.NewHeader.colorMapOrigin;
    result.NewHeader.colorMapLength = P1.NewHeader.colorMapLength;
    result.NewHeader.colorMapDepth = P1.NewHeader.colorMapDepth;
    result.NewHeader.xOrigin = P1.NewHeader.xOrigin;
    result.NewHeader.yOrigin = P1.NewHeader.yOrigin;
    result.NewHeader.width = P1.NewHeader.width;
    result.NewHeader.height = P1.NewHeader.height;
    result.NewHeader.bitsPerPixel = P1.NewHeader.bitsPerPixel;
    result.NewHeader.imageDescriptor = P1.NewHeader.imageDescriptor;
    result.Pixels = Pixes;
}
//task 9
void Combine(Image& P1, Image& P2, Image& P3, Image& result){
    int area = int(P1.NewHeader.width) * int(P1.NewHeader.height);
    vector<Image::Pixel> Pixes;

    for (int i = 0; i < area; i++) {
        Image::Pixel newPixel;

        //Red Pixel
        unsigned char newRed = P1.Pixels[i].Red;

        //Green Pixel
        unsigned char newGreen = P2.Pixels[i].Green;

        //Blue Pixel
        unsigned char newBlue = P3.Pixels[i].Blue;

        newPixel.Blue = newBlue;
        newPixel.Green = newGreen;
        newPixel.Red = newRed;

        Pixes.push_back(newPixel);
    }
    result.NewHeader.idLength = P1.NewHeader.idLength;
    result.NewHeader.colorMapType = P1.NewHeader.colorMapType;
    result.NewHeader.dataTypeCode = P1.NewHeader.dataTypeCode;
    result.NewHeader.colorMapOrigin = P1.NewHeader.colorMapOrigin;
    result.NewHeader.colorMapLength = P1.NewHeader.colorMapLength;
    result.NewHeader.colorMapDepth = P1.NewHeader.colorMapDepth;
    result.NewHeader.xOrigin = P1.NewHeader.xOrigin;
    result.NewHeader.yOrigin = P1.NewHeader.yOrigin;
    result.NewHeader.width = P1.NewHeader.width;
    result.NewHeader.height = P1.NewHeader.height;
    result.NewHeader.bitsPerPixel = P1.NewHeader.bitsPerPixel;
    result.NewHeader.imageDescriptor = P1.NewHeader.imageDescriptor;
    result.Pixels = Pixes;
}
//task 10
void Flip(Image& P1, Image& result){
    //flip 180 degrees
    int area = int(P1.NewHeader.width) * int(P1.NewHeader.height);
    vector<Image::Pixel> Pixes;

    for (int i = area - 1; i >= 0; i--) {
        Image::Pixel newPixel;

        newPixel.Blue = P1.Pixels[i].Blue;
        newPixel.Green = P1.Pixels[i].Green;
        newPixel.Red = P1.Pixels[i].Red;

        Pixes.push_back(newPixel);
    }
    result.NewHeader.idLength = P1.NewHeader.idLength;
    result.NewHeader.colorMapType = P1.NewHeader.colorMapType;
    result.NewHeader.dataTypeCode = P1.NewHeader.dataTypeCode;
    result.NewHeader.colorMapOrigin = P1.NewHeader.colorMapOrigin;
    result.NewHeader.colorMapLength = P1.NewHeader.colorMapLength;
    result.NewHeader.colorMapDepth = P1.NewHeader.colorMapDepth;
    result.NewHeader.xOrigin = P1.NewHeader.xOrigin;
    result.NewHeader.yOrigin = P1.NewHeader.yOrigin;
    result.NewHeader.width = P1.NewHeader.width;
    result.NewHeader.height = P1.NewHeader.height;
    result.NewHeader.bitsPerPixel = P1.NewHeader.bitsPerPixel;
    result.NewHeader.imageDescriptor = P1.NewHeader.imageDescriptor;
    result.Pixels = Pixes;
}
//task 8
void Channel_Write(Image& P1, Image& Red_Result){
    int area = int(P1.NewHeader.width) * int(P1.NewHeader.height);
    vector<Image::Pixel> Red_Pixels;
    vector<Image::Pixel> Blue_Pixels;
    vector<Image::Pixel> Green_Pixels;

    for (int i = 0; i < area; i++) {
        Image::Pixel newPixel;

        newPixel.Blue = P1.Pixels[i].Red;
        newPixel.Green = P1.Pixels[i].Red;
        newPixel.Red = P1.Pixels[i].Red;

        Red_Pixels.push_back(newPixel);
    }
    for (int i = 0; i < area; i++) {
        Image::Pixel newPixel;

        newPixel.Blue = P1.Pixels[i].Green;
        newPixel.Green = P1.Pixels[i].Green;
        newPixel.Red = P1.Pixels[i].Green;

        Green_Pixels.push_back(newPixel);
    }
    for (int i = 0; i < area; i++) {
        Image::Pixel newPixel;

        newPixel.Blue = P1.Pixels[i].Blue;
        newPixel.Green = P1.Pixels[i].Blue;
        newPixel.Red = P1.Pixels[i].Blue;

        Blue_Pixels.push_back(newPixel);
    }

    Image red_image(P1.NewHeader.idLength, P1.NewHeader.colorMapType, P1.NewHeader.dataTypeCode, P1.NewHeader.colorMapOrigin, P1.NewHeader.colorMapLength,
                    P1.NewHeader.colorMapDepth, P1.NewHeader.xOrigin, P1.NewHeader.yOrigin, P1.NewHeader.width,
                    P1.NewHeader.height, P1.NewHeader.bitsPerPixel, P1.NewHeader.imageDescriptor, Red_Pixels);
    Image green_image(P1.NewHeader.idLength, P1.NewHeader.colorMapType, P1.NewHeader.dataTypeCode, P1.NewHeader.colorMapOrigin, P1.NewHeader.colorMapLength,
                      P1.NewHeader.colorMapDepth, P1.NewHeader.xOrigin, P1.NewHeader.yOrigin, P1.NewHeader.width,
                      P1.NewHeader.height, P1.NewHeader.bitsPerPixel, P1.NewHeader.imageDescriptor, Green_Pixels);
    Image blue_image(P1.NewHeader.idLength, P1.NewHeader.colorMapType, P1.NewHeader.dataTypeCode, P1.NewHeader.colorMapOrigin, P1.NewHeader.colorMapLength,
                     P1.NewHeader.colorMapDepth, P1.NewHeader.xOrigin, P1.NewHeader.yOrigin, P1.NewHeader.width,
                     P1.NewHeader.height, P1.NewHeader.bitsPerPixel, P1.NewHeader.imageDescriptor, Blue_Pixels);

    Writing("part8_r.tga", red_image);
    Writing("part8_g.tga", green_image);
    Writing("part8_b.tga", blue_image);

}
void Channel_Red(Image& P1, Image& result){
    int area = int(P1.NewHeader.width) * int(P1.NewHeader.height);
    vector<Image::Pixel> Red_Pixels;
    for (int i = 0; i < area; i++) {
        Image::Pixel newPixel;
        newPixel.Blue = P1.Pixels[i].Red;
        newPixel.Green = P1.Pixels[i].Red;
        newPixel.Red = P1.Pixels[i].Red;
        Red_Pixels.push_back(newPixel);
    }
    result.NewHeader.idLength = P1.NewHeader.idLength;
    result.NewHeader.colorMapType = P1.NewHeader.colorMapType;
    result.NewHeader.dataTypeCode = P1.NewHeader.dataTypeCode;
    result.NewHeader.colorMapOrigin = P1.NewHeader.colorMapOrigin;
    result.NewHeader.colorMapLength = P1.NewHeader.colorMapLength;
    result.NewHeader.colorMapDepth = P1.NewHeader.colorMapDepth;
    result.NewHeader.xOrigin = P1.NewHeader.xOrigin;
    result.NewHeader.yOrigin = P1.NewHeader.yOrigin;
    result.NewHeader.width = P1.NewHeader.width;
    result.NewHeader.height = P1.NewHeader.height;
    result.NewHeader.bitsPerPixel = P1.NewHeader.bitsPerPixel;
    result.NewHeader.imageDescriptor = P1.NewHeader.imageDescriptor;
    result.Pixels = Red_Pixels;
}
void Channel_Green(Image& P1, Image& result){
    int area = int(P1.NewHeader.width) * int(P1.NewHeader.height);
    vector<Image::Pixel> Green_Pixels;
    for (int i = 0; i < area; i++) {
        Image::Pixel newPixel;
        newPixel.Blue = P1.Pixels[i].Green;
        newPixel.Green = P1.Pixels[i].Green;
        newPixel.Red = P1.Pixels[i].Green;
        Green_Pixels.push_back(newPixel);
    }
    result.NewHeader.idLength = P1.NewHeader.idLength;
    result.NewHeader.colorMapType = P1.NewHeader.colorMapType;
    result.NewHeader.dataTypeCode = P1.NewHeader.dataTypeCode;
    result.NewHeader.colorMapOrigin = P1.NewHeader.colorMapOrigin;
    result.NewHeader.colorMapLength = P1.NewHeader.colorMapLength;
    result.NewHeader.colorMapDepth = P1.NewHeader.colorMapDepth;
    result.NewHeader.xOrigin = P1.NewHeader.xOrigin;
    result.NewHeader.yOrigin = P1.NewHeader.yOrigin;
    result.NewHeader.width = P1.NewHeader.width;
    result.NewHeader.height = P1.NewHeader.height;
    result.NewHeader.bitsPerPixel = P1.NewHeader.bitsPerPixel;
    result.NewHeader.imageDescriptor = P1.NewHeader.imageDescriptor;
    result.Pixels = Green_Pixels;
}
void Channel_Blue(Image& P1, Image& result){
    int area = int(P1.NewHeader.width) * int(P1.NewHeader.height);
    vector<Image::Pixel> Blue_Pixels;
    for (int i = 0; i < area; i++) {
        Image::Pixel newPixel;
        newPixel.Blue = P1.Pixels[i].Blue;
        newPixel.Green = P1.Pixels[i].Blue;
        newPixel.Red = P1.Pixels[i].Blue;
        Blue_Pixels.push_back(newPixel);
    }
    result.NewHeader.idLength = P1.NewHeader.idLength;
    result.NewHeader.colorMapType = P1.NewHeader.colorMapType;
    result.NewHeader.dataTypeCode = P1.NewHeader.dataTypeCode;
    result.NewHeader.colorMapOrigin = P1.NewHeader.colorMapOrigin;
    result.NewHeader.colorMapLength = P1.NewHeader.colorMapLength;
    result.NewHeader.colorMapDepth = P1.NewHeader.colorMapDepth;
    result.NewHeader.xOrigin = P1.NewHeader.xOrigin;
    result.NewHeader.yOrigin = P1.NewHeader.yOrigin;
    result.NewHeader.width = P1.NewHeader.width;
    result.NewHeader.height = P1.NewHeader.height;
    result.NewHeader.bitsPerPixel = P1.NewHeader.bitsPerPixel;
    result.NewHeader.imageDescriptor = P1.NewHeader.imageDescriptor;
    result.Pixels = Blue_Pixels;
}

int Clamp(int value){
    if (value < 0){
        return 0;
    }

    if (value > 255){
        return 255;
    }

    else {
        return value;
    }

}
float Conditional(float P1, float P2){
    if (P2 <= 0.5){
        float newColorP3 = (2 * P1 * P2 * 255) + 0.5f;
        return char(newColorP3);
    }

    else {
        float newColorP3 = ((1 -(2 * (1-P1) * (1-P2))) * 255) + 0.5f;
        return char(newColorP3);
    }
}