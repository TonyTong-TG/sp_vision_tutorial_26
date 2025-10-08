#include "tasks/buff_detector.hpp"
#include "tasks/buff_solver.hpp"
#include "io/camera.hpp"
#include <chrono>
#include <nlohmann/json.hpp>
#include "tools/plotter.hpp"
#include <opencv2/opencv.hpp>

int main()
{
    io::Camera camera(2.5, 16.9, "2bdf:0001");
    std::chrono::steady_clock::time_point timestamp;
    tools::Plotter plotter;
    auto_buff::Buff_Detector detector;
    auto_buff::Buff_Solver solver;
    while(true){
        cv::Mat img;
        camera.read(img, timestamp);
        auto fanblades = detector.detect(img);
        nlohmann::json data;
        cv::Mat CM, RM;
        if (fanblades.size())
        {
            solver.solvePnP(fanblades[0], CM, RM);
            data["centerX"] = CM.at<double>(0);
            data["centerY"] = CM.at<double>(1);
            data["centerZ"] = CM.at<double>(2);
            data["rotationX"] = RM.at<double>(0);
            data["rotationY"] = RM.at<double>(1);
            data["rotationZ"] = RM.at<double>(2);
            plotter.plot(data);
        }

        cv::resize(img, img, {}, 0.8, 0.8);
        cv::imshow("Detection Results", img);
        if (cv::waitKey(30) == 27)
        { // 按ESC键退出
            break;
        }
    }
    return 0;
}