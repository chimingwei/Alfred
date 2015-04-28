#include "opencv2/opencv.hpp"
#include "opencv2/contrib/contrib.hpp"
//#include "opencv2/core.hpp"
//#include "opencv2/face.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/objdetect.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//#include <system>


using namespace cv;
using namespace std;

string fn_lbp;
string fn_csv;
int deviceId;
Ptr<FaceRecognizer> model;
int im_width;
int im_height;
const int samplesToTake = 10;

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

extern "C" int add_user(const char* userName){
    printf("Starting add user script for %s...\n",userName);
    char command[100];
    sprintf(command,"mkdir faces/%s",userName);
    int status = system(command);
    if(status == 0){
        CascadeClassifier lbp_cascade;
        lbp_cascade.load(fn_lbp);
        // Get a handle to the Video device:
        VideoCapture cap(deviceId);
        char imName[sizeof(userName)/sizeof(char)+50];
        // char* imName = (char*)malloc(sizeof(userName)+50);
        strcpy(imName,userName);
        // Check if we can use this device at all:
        if(!cap.isOpened()) {
            cerr << "Capture Device ID " << deviceId << "cannot be opened." << endl;
            return -1;
        }
         cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
         cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
//         cap.set(CV_CAP_PROP_FOURCC, CV_FOURCC('H', '2', '6', '4'));
        // Holds the current frame from the Video device:
        printf("Taking pictures of you %s so I can recognize your face MUWHAHAHAHA...\n",userName);
        Mat frame;
	int j = 0;
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
            for(int i = 0; i < faces.size(); i++) {
                // Process face by face:
                //Rect face_i = faces[i];
                // Crop the face from the image. So simple with OpenCV C++:
                Mat face = Mat(original,faces[i]);;
                // Resize images.
                Mat face_resized;
                resize(face, face_resized, Size(300, 300), 1.0, 1.0, INTER_CUBIC);
                sprintf(imName,"faces/%s/%s%d.jpg",userName,userName,j);
                imwrite(imName,face_resized);
		j++;
            }
	   if(j>15){break;}
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
    deviceId =1; 

    // These vectors hold the images and corresponding labels:
    vector<Mat> images;
    vector<int> labels;
    // Read in the data (fails if no valid input filename is given, but you'll get an error message):
    try {
        read_csv(fn_csv, images, labels);
    } catch (Exception& e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }
    im_width = images[0].cols;
    im_height = images[0].rows;
    // Create a FaceRecognizer and train it on the given images:
    model = createLBPHFaceRecognizer();
    model->train(images, labels);
}

extern "C" int predict(){
    CascadeClassifier lbp_cascade;
    lbp_cascade.load(fn_lbp);
    int averagePrediction[samplesToTake];
    int sampleCount = 0;
    for (int i = 0; i < samplesToTake-1; ++i){averagePrediction[i] = -1;}
    // Get a handle to the Video device:
    VideoCapture cap(deviceId);
    // Check if we can use this device at all:
    if(!cap.isOpened()) {
        cerr << "Capture Device ID " << deviceId << "cannot be opened." << endl;
        return -1;
    }
     //cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
     //cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
//     cap.set(CV_CAP_PROP_FOURCC, CV_FOURCC('H', '2', '6', '4'));
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
        for(int i = 0; i < faces.size(); i++) {
            // Process face by face:
            Rect face_i = faces[i];
            // Crop the face from the image. So simple with OpenCV C++:
            Mat face = gray(face_i);
            Mat face_resized;
            cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);

            int prediction = model->predict(face_resized);
	          double confidence = 0.0;
	          model->predict(face_resized,prediction,confidence);

            if(i<samplesToTake-1){
                averagePrediction[sampleCount] =confidence<100?prediction:-1;
                //averagePrediction[sampleCount] =prediction;
                sampleCount++;
            }else{
                break;
            }
            // printf("\n%d",prediction);
             rectangle(original, face_i, CV_RGB(150,150,150), 1);

            // // Create the text we will annotate the box with:
            string box_text = format("User %d, %f", prediction,confidence);

            // // Calculate the position for annotated text (make sure we don't
            // // put illegal values in there):
             int pos_x = std::max(face_i.tl().x - 10, 0);
             int pos_y = std::max(face_i.tl().y - 10, 0);

            // // And now put it into the image:
            putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(150,150,150), 2.0);
        }
        if(sampleCount>samplesToTake-1){break;}
        // Show the result:
         imshow("face_recognizer", original);
        // And display it:
        char key = (char) waitKey(20);
        // Exit this loop on escape:
         if(key == 27)
             break;
    }

    return getPopularElement(averagePrediction);
}

