//IO
#include <iostream>
//GST
#include <gst/gst.h>
//Opencv
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>


int main(int arg, char *argv[]) {
    std::cout << "STARTED" << std::endl;

    GstElement *pipeline = nullptr;
    GstBus *bus = nullptr;
    GstMessage *msg = nullptr;

    // gstreamer initialization
    gst_init(&arg, &argv);

    // building pipeline
    pipeline = gst_parse_launch("v4l2src device=/dev/video0 ! video/x-raw,format=YUY2,width=640,height=480,framerate=30/1 ! queue !  identity ! shmsink wait-for-connection=1 socket-path=/app_code/tmp/tmpsock  shm-size=20000000 sync=true",
            nullptr);
            

    // start playing
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    cv::Mat frame;

    cv::VideoCapture cap;

    cap.open("shmsrc socket-path=/app_code/tmp/tmpsock ! video/x-raw, format=YUY2, width=640, height=480, pixel-aspect-ratio=1/1, framerate=30/1 ! decodebin ! videoconvert ! appsink");

    std::cout << "Ok4" << std::endl;
    //std::string gst_str = "appsrc ! videoconvert ! shmsink socket-path=/gst/tmp/out sync=true wait-for-connection=false shm-size=10000000";
    
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            std::cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        std::cout << "Width : " << frame.cols << std::endl;
        std::cout << "Height: " << frame.rows << std::endl;
        if (cv::waitKey(5) >= 0)
            break;
    }
    
    

    //wait until error or EOS ( End Of Stream )
    //bus = gst_element_get_bus(pipeline);
    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                     static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
    std::cout << "OK3" << std::endl;

    // free memory
    if (msg != nullptr)
        gst_message_unref(msg);
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);



    return 0;
}
