#include <iostream>

#include <gst/gst.h>
#include "yolov5_detector.hpp"



int main(int arg, char *argv[]) {

    //Testing the yolo lib
    yolov5::Detector detector;
    yolov5::Result r = detector.init();

    GstElement *pipeline = nullptr;
    GstBus *bus = nullptr;
    GstMessage *msg = nullptr;

    // gstreamer initialization
    gst_init(&arg, &argv);

    // building pipeline
    pipeline = gst_parse_launch(
            "v4l2src device=/dev/video0 ! xvimagesink",
            nullptr);
            //"playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm",

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