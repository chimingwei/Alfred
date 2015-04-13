// #include "facerec.h"

#include "opencv2/opencv.hpp"
#include "opencv2/contrib/contrib.hpp"
// #include "opencv2/core.hpp"
// #include "opencv2/face.hpp"
// #include "opencv2/highgui.hpp"
// #include "opencv2/imgproc.hpp"
// #include "opencv2/objdetect.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//#include <system>


using namespace cv;
using namespace std;

// int add_user(const char* userName, string fn_lbp, int deviceId);
// void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';');
string fn_lbp;
string fn_csv;
int deviceId;
Ptr<FaceRecognizer> model;
int im_width;
int im_height;
int samplesToTake = 25;

extern "C" int getPopularElement(int a[samplesToTake])
{
  int count = 1, tempCount;
  int popular = a[0];
  int temp = 0;
  for (int i = 0; i < (samplesToTake - 1); i++)
  {
    temp = a[i];
    tempCount = 0;
    for (int j = 1; j < samplesToTake; j++)
    {
      if (temp == a[j])
        tempCount++;
    }
    if (tempCount > count)
    {
      popular = temp;
      count = tempCount;
    }
  }
  return popular;
}

extern "C" int add_user(const char* userName, string fn_lbp, int deviceId){
    printf("Starting add user script for %s...\n",userName);
    char command[100];
    sprintf(command,"mkdir faces/%s",userName);
    int status = system(command);
    if(status == 0){
        CascadeClassifier lbp_cascade;
        lbp_cascade.load(fn_lbp);
        // Get a handle to the Video device:
        VideoCapture cap(deviceId);
        char imName[sizeof(userName)/sizeof(char)+5];
        // char* imName = (char*)malloc(sizeof(userName)+50);
        strcpy(imName,userName);
        // Check if we can use this device at all:
        if(!cap.isOpened()) {
            cerr << "Capture Device ID " << deviceId << "cannot be opened." << endl;
            return -1;
        }
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 352);
        cap.set(CV_CAP_PROP_FRAME_HEIGHT, 288);

        // Holds the current frame from the Video device:
        printf("Taking pictures of you %s so I can recognize your face MUWHAHAHAHA...\n",userName);
        Mat frame;
        for(int j = 0;j<10;j++) {
            cap >> frame;
            // Clone the current frame:
            Mat original = frame.clone();
            // Convert the current frame to grayscale:
            Mat gray;
            cvtColor(original, gray, CV_BGR2GRAY);
            // Find the faces in the frame:
            vector< Rect_<int> > faces;
            lbp_cascade.detectMultiScale(gray, faces);
            // haar_cascade.detectMultiScale(gray, faces);
            // At this point you have the position of the faces in
            // faces. Now we'll get the faces, make a prediction and
            // annotate it in the video. Cool or what?
            for(int i = 0; i < faces.size(); i++) {
                // Process face by face:
                Rect face_i = faces[i];
                // Crop the face from the image. So simple with OpenCV C++:
                Mat face = gray(face_i);
                // Resize images.
                Mat face_resized;
                cv::resize(face, face_resized, Size(200, 200), 1.0, 1.0, INTER_CUBIC);
                sprintf(imName,"faces/%s/%s%d.jpg",userName,userName,j);
                imwrite(imName,face_resized);
                // printf("Shift face slightly");
                // sleep(1);

            }
        }
        printf("%s's pictures completed. Adding to list\n",userName);
        system("rm faces.csv && python CreateCSV.py faces/ >> faces.csv");
        return 0;
    }
    printf("Error: User exists.\n");
    return 1;


}

extern "C" void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

extern "C" void init(){
    fn_lbp = string("lbpcascades/lbpcascade_frontalface.xml");
    fn_csv = string("faces.csv");
    deviceId = atoi("video0");

    // These vectors hold the images and corresponding labels:
    vector<Mat> images;
    vector<int> labels;
    // Read in the data (fails if no valid input filename is given, but you'll get an error message):
    try {
        read_csv(fn_csv, images, labels);
    } catch (cv::Exception& e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }
    // Get the height from the first image. We'll need this
    // later in code to reshape the images to their original
    // size AND we need to reshape incoming faces to this size:
    im_width = images[0].cols;
    im_height = images[0].rows;
    // Create a FaceRecognizer and train it on the given images:
    model = createLBPHFaceRecognizer();
    // model = createEigenFaceRecognizer();
    // model = createFisherFaceRecognizer();
    // Ptr<face::FaceRecognizer> model = face::createLBPHFaceRecognizer();
    // Ptr<face::FaceRecognizer> model = face::createEigenFaceRecognizer();
    // Ptr<face::FaceRecognizer> model = face::createFisherFaceRecognizer();

    model->train(images, labels);

}

extern "C" int predict(){
    CascadeClassifier lbp_cascade;
    lbp_cascade.load(fn_lbp);
    int averagePrediction[samplesToTake];
    int sampleCount = 0;
    // for (int i = 0; i < samplesToTake-1; ++i){averagePrediction[i] = 0;}
    // Get a handle to the Video device:
    VideoCapture cap(deviceId);
    // Check if we can use this device at all:
    if(!cap.isOpened()) {
        cerr << "Capture Device ID " << deviceId << "cannot be opened." << endl;
        return -1;
    }
//     cap.set(CV_CAP_PROP_FRAME_WIDTH, 352);
//     cap.set(CV_CAP_PROP_FRAME_HEIGHT, 288);
    // Holds the current frame from the Video device:
    Mat frame;
    for(;;) {
        cap >> frame;
        // Clone the current frame:
        Mat original = frame.clone();
        // Convert the current frame to grayscale:
        Mat gray;
        cvtColor(original, gray, CV_BGR2GRAY);
        // Find the faces in the frame:
        vector< Rect_<int> > faces;
        lbp_cascade.detectMultiScale(gray, faces);
        // haar_cascade.detectMultiScale(gray, faces);
        // At this point you have the position of the faces in
        // faces. Now we'll get the faces, make a prediction and
        // annotate it in the video. Cool or what?
        for(int i = 0; i < faces.size(); i++) {
            // Process face by face:
            Rect face_i = faces[i];
            // Crop the face from the image. So simple with OpenCV C++:
            Mat face = gray(face_i);
            // Resizing the face is necessary for Eigenfaces and Fisherfaces. You can easily
            // verify this, by reading through the face recognition tutorial coming with OpenCV.
            // Resizing IS NOT NEEDED for Local Binary Patterns Histograms, so preparing the
            // input data really depends on the algorithm used.
            //
            // I strongly encourage you to play around with the algorithms. See which work best
            // in your scenario, LBPH should always be a contender for robust face recognition.
            //
            // Since I am showing the Fisherfaces algorithm here, I also show how to resize the
            // face you have just found:
            Mat face_resized;
            cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
            // Now perform the prediction, see how easy that is:
            int prediction = model->predict(face_resized);
            if(i<samplesToTake-1){
                averagePrediction[sampleCount] = prediction;
                sampleCount++;
            }else{
                break;
            }
            // printf("\n%d",prediction);
            // And finally write all we've found out to the original image!
            // First of all draw a green rectangle around the detected face:
            // rectangle(original, face_i, CV_RGB(150,150,150), 1);

            // // Create the text we will annotate the box with:
            // string box_text = format("User %d", prediction);

            // // Calculate the position for annotated text (make sure we don't
            // // put illegal values in there):
            // int pos_x = std::max(face_i.tl().x - 10, 0);
            // int pos_y = std::max(face_i.tl().y - 10, 0);

            // // And now put it into the image:
            // putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(150,150,150), 2.0);
        }
        if(sampleCount>samplesToTake-1){
            break;
        }
        // Show the result:
        // imshow("face_recognizer", original);
        // And display it:
        // char key = (char) waitKey(20);
        // Exit this loop on escape:
        // if(key == 27)
            // break;
    }

    return getPopularElement(averagePrediction);
}

