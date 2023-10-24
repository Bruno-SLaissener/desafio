#include <iostream>

#include <gst/gst.h>
//#include "yolov5_detector.hpp"
#include "yolov5_builder.hpp"

// namespace bClass{
//     #include "yolov5_builder.hpp"
// }

void builder(void){
    yolov5::Precision precision = yolov5::PRECISION_FP32;
    yolov5::Builder builder;
    yolov5::Result r = builder.init();
    r = builder.buildEngine("./yolov5s.onnx", "./yolov5s.engine", precision);
}


int main(int arg, char *argv[]) {
    
    builder();

    //Testing the yolo lib
    //yolov5::Detector detector;
    //yolov5::Result r = detector.init();
    
    GstElement *pipeline = nullptr;
    GstBus *bus = nullptr;
    GstMessage *msg = nullptr;

    // gstreamer initialization
    gst_init(&arg, &argv);

    // building pipeline
    pipeline = gst_parse_launch("v4l2src device=/dev/video2 ! tee name=t \ 
                                t. ! video/x-raw,format=YUY2,width=640,height=480,framerate=30/1 ! queue !  identity ! shmsink wait-for-connection=0 socket-path=/app_code/tmp/tmpsock  shm-size=20000000 sync=true \
                                t. ! xvimagesink ",
            nullptr);

    //cv::VideoCapture capture;
    //capture.open("shmsrc socket-path=/app_code/tmp/tmpsock  ! video/x-raw, format=YUY2, width=640, height=480, framerate=30/1 ! decodebin ! videoconvert ! appsink");

    //std::cout << capture.isOpened() << std::endl;

    // start playing
    gst_element_set_state(pipeline, GST_STATE_PLAYING);


    //wait until error or EOS ( End Of Stream )
    bus = gst_element_get_bus(pipeline);
    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                     static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

    // free memory
    if (msg != nullptr)
        gst_message_unref(msg);
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
}