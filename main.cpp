#include <iostream>
#include <fstream>
#include "reader.h"
#include <cstring>
using namespace std;

//g++ --std=c++11 src/main.cpp -o tester
//g++ --std=c++11 main.cpp -o tester

///fail tests
//tester output/out.tga input/testfile
///invalid file name

//tester output/out.tga input/testfile.tga
///file does not exist

//tester out.tga input/car.tga nonexistent
///invalid method name

//tester out.tga input/car.tga multiply
///missing argument

//tester out.tga input/car.tga multiply input/test
///invalid file name

//tester out.tga input/car.tga addred input/none.tga
///invalid argument, expected number

//./project2.out out.tga input/car.tga scaleblue
///missing argument

//tester out.tga input/car.tga flip scaleblue
///missing argument


///First 10 Tests
//tester output/part1.tga input/layer1.tga multiply input/pattern1.tga
//tester output/part2.tga input/car.tga subtract input/layer2.tga
//tester output/part3.tga input/layer1.tga multiply input/pattern2.tga screen input/text.tga
//tester output/part4.tga input/layer2.tga multiply input/circles.tga subtract input/pattern2.tga
//tester output/part5.tga input/layer1.tga overlay input/pattern1.tga
//tester output/part6.tga input/car.tga addgreen 200
//tester output/part7.tga input/car.tga scalered 4 scaleblue 0
//tester output/part8_r.tga input/car.tga onlyred
//tester output/part8_b.tga input/car.tga onlyblue
//tester output/part8_g.tga input/car.tga onlygreen
//tester output/part9.tga input/layer_red.tga combine input/layer_green.tga input/layer_blue.tga
//tester output/part10.tga input/text2.tga flip


///Extra 9 tests
//tester --help
//tester
//tester output/out.tga input/car.tga multiply input/part1.tga
//tester output/out1.tga input/car.tga multiply input/part1.tga screen input/part2.tga
//tester output/out2.tga input/car.tga flip flip flip flip
//tester output/out3.tga input/car.tga scalegreen 5
//tester output/out.tga
//tester output/out.tga input/part1.tga weirdmethod

//C:\Users\CUBS5\OneDrive\Documents\project2\output

int main(int argc, char* argv[])
{
    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        cout << "Project 2: Image Processing, Spring 2023" << endl << endl;
        cout << "Usage: " << endl;
        cout << "./project2.out [output] [firstImage] [method] [...]" << endl;
    }

    //fixme need to fix how it throws and catches errors
    //fixme it displays errors when help or nothing called
    //if (argc > 2) {
        string result = argv[1];
    //(result.find(".tga") != string::npos) and (
        Image Tracking_Image = Reading(argv[2]);

        for (int i = 2; i < argc; i++) {
            //fixme testing

            if (strcmp(argv[i], "multiply") == 0) {
                //multiply file 1 by file 2
                //string Alpha = argv[i-1];
                string Beta = argv[i + 1];

                //Image P1 = Reading(Alpha);
                Image P2 = Reading(Beta);
                Multiply(Tracking_Image, P2, Tracking_Image);
                Writing(result, Tracking_Image);
                continue;
            }

            if (strcmp(argv[i], "combine") == 0) {
                //Combine 3 files
                string Alpha = argv[i + 1];
                string Beta = argv[i + 2];

                Image P1 = Reading(Alpha);
                Image P2 = Reading(Beta);
                Combine(Tracking_Image, P1, P2, Tracking_Image);
                Writing(result, Tracking_Image);
                continue;
            }

            if (strcmp(argv[i], "subtract") == 0) {
                //subtract file 1 by file 2
                //string Alpha = argv[i-1];
                string Beta = argv[i + 1];

                //Image P1 = Reading(Alpha);
                Image P2 = Reading(Beta);
                Subtract(Tracking_Image, P2, Tracking_Image);
                Writing(result, Tracking_Image);
                continue;
            }

            if (strcmp(argv[i], "overlay") == 0) {
                //Overlay file 1 by file 2
                string Beta = argv[i + 1];

                Image P2 = Reading(Beta);
                Overlay(Tracking_Image, P2, Tracking_Image);
                Writing(result, Tracking_Image);
                continue;
            }

            if (strcmp(argv[i], "screen") == 0) {
                //screen file 1 by file 2
                string Beta = argv[i + 1];

                //Image P1 = Reading(Alpha);
                Image P2 = Reading(Beta);
                Screen(Tracking_Image, P2, Tracking_Image);
                Writing(result, Tracking_Image);
                continue;
            }

            if (strcmp(argv[i], "flip") == 0) {
                //flip the tracking image
                Flip(Tracking_Image, Tracking_Image);
                Writing(result, Tracking_Image);
                continue;
            }

            if (strcmp(argv[i], "onlyred") == 0) {
                //retrieves red channel from image
                Channel_Red(Tracking_Image, Tracking_Image);
                Writing(result, Tracking_Image);
                continue;
            }

            if (strcmp(argv[i], "onlygreen") == 0) {
                //retrieves green channel from input
                Channel_Green(Tracking_Image, Tracking_Image);
                Writing(result, Tracking_Image);
                continue;
            }

            if (strcmp(argv[i], "onlyblue") == 0) {
                //retrieves blue channel from input
                Channel_Blue(Tracking_Image, Tracking_Image);
                Writing(result, Tracking_Image);
                continue;
            }

            if (strcmp(argv[i], "addred") == 0) {
                //add certain value to red channel
                int add = stoi(argv[i + 1]);
                Addition(Tracking_Image, "red", add, Tracking_Image);
                Writing(result, Tracking_Image);
                continue;
            }

            if (strcmp(argv[i], "addgreen") == 0) {
                //add certain value to green channel
                int add = stoi(argv[i + 1]);
                Addition(Tracking_Image, "green", add, Tracking_Image);
                Writing(result, Tracking_Image);
                continue;
            }

            if (strcmp(argv[i], "addblue") == 0) {
                //add certain value to blue channel
                int add = stoi(argv[i + 1]);
                Addition(Tracking_Image, "blue", add, Tracking_Image);
                Writing(result, Tracking_Image);
                continue;
            }

            if (strcmp(argv[i], "scalered") == 0) {
                //multiply value of red to channel
                int factor = stoi(argv[i + 1]);
                Multiply(Tracking_Image, factor, 1, 1, Tracking_Image);
                Writing(result, Tracking_Image);
                continue;
            }

            if (strcmp(argv[i], "scalegreen") == 0) {
                //multiply value of green to channel
                int factor = stoi(argv[i + 1]);
                Multiply(Tracking_Image, 1, factor, 1, Tracking_Image);
                Writing(result, Tracking_Image);
                continue;
            }

            if (strcmp(argv[i], "scaleblue") == 0) {
                //multiply value of blue to channel
                int factor = stoi(argv[i + 1]);
                Multiply(Tracking_Image, 1, 1, factor, Tracking_Image);
                Writing(result, Tracking_Image);
                continue;
            }

            if (string(argv[i]).find(".tga") != string::npos){
                continue;
            }
            if(stoi(argv[i]) or strcmp(argv[i], "0") == 0){
                continue;
            }
            else{
                cout << "Invalid method name." << endl;
            }

        }

    return 0;
}
