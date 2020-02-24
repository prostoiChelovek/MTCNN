/*
  Copyright (C) 2017 Open Intelligent Machines Co.,Ltd

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "tensorflow_mtcnn.hpp"
#include "mtcnn.hpp"

int main(int argc, char *argv[]) {
    const char *type = "tensorflow";
    double ftick, etick;
    double ticksPerUs;

    int res;

    while ((res = getopt(argc, argv, "t:")) != -1) {
        if (res == 't') {
            type = optarg;
        }
    }

    cv::VideoCapture camera(0);
    if (!camera.isOpened()) {
        std::cerr << "failed to open camera" << std::endl;
        return 1;
    }

    std::string model_dir = "./models";

    mtcnn *p_mtcnn = mtcnn_factory::create_detector(type);

    if (p_mtcnn == nullptr) {
        std::cerr << type << " is not supported" << std::endl;
        std::cerr << "supported types: ";
        std::vector<std::string> type_list = mtcnn_factory::list();
        for (const auto &i : type_list)
            std::cerr << " " << i;
        std::cerr << std::endl;
        return EXIT_FAILURE;
    }

    p_mtcnn->set_threshold(0.75, 0.81, 0.88);

    ticksPerUs = cv::getTickFrequency() / 1000000;

    p_mtcnn->load_model(model_dir);
    cv::Mat frame;
    std::vector<face_box> face_info;

    do {
        camera >> frame;

        if (!frame.data) {
            std::cerr << "Capture video failed" << std::endl;
            break;
        }

        ftick = cv::getCPUTickCount();
        p_mtcnn->detect(frame, face_info);
        etick = cv::getCPUTickCount();

        for (auto &box : face_info) {
            /*draw box */
            cv::rectangle(frame, cv::Point(box.x0, box.y0),
                          cv::Point(box.x1, box.y1), cv::Scalar(0, 255, 0), 1);

            /* draw landmark */
            for (int l = 0; l < 5; l++) {
                cv::circle(frame, cv::Point(box.landmark.x[l],
                                            box.landmark.y[l]), 5, cv::Scalar(0, 0, 255), -1);
            }
        }

        std::cout << "total detected: " << face_info.size() << " faces. used " << (etick - ftick) / ticksPerUs << " us"
                  << std::endl;

        cv::imshow("Result", frame);
        face_info.clear();
    } while (cv::waitKey(1) != 27);

    return 0;
}
