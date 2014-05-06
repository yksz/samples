#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char** argv)
{
    CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY);
    if (capture == NULL) {
        fprintf(stderr, "ERROR: a camera is not found\n");
        return EXIT_FAILURE;
    }
    char* window = "Camera Capture";
    cvNamedWindow(window, CV_WINDOW_AUTOSIZE);

    while (1) {
        IplImage* image = cvQueryFrame(capture);
        cvShowImage(window, image);

        int key = cvWaitKey(1);
        if (key == 0x1b) // Esc
            break;
    }

    cvReleaseCapture(&capture);
    cvDestroyWindow(window);
    return 0;
}
