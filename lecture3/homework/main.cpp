#include "io/my_camera.hpp"
#include "tasks/yolo.hpp"
#include "opencv2/opencv.hpp"
#include "tools/img_tools.hpp"

int main()
{
    // 初始化相机、yolo类
    std::string config_path = "./configs/yolo.yaml";
    auto_aim::YOLO yolo(config_path);
    myCamera cam = myCamera();

    while (1) {
        // 调用相机读取图像
        cv::Mat img = cam.read();

        // 调用yolo识别装甲板
        std::list<auto_aim::Armor> armors = yolo.detect(img);

        // 标记
        for (auto_aim::Armor armor : armors)
        {
            tools::draw_points(img, armor.points, {0, 0, 255});
            std::string text = auto_aim::COLORS[armor.color] + auto_aim::ARMOR_NAMES[armor.name];
            tools::draw_text(img, text, (cv::Point)armor.points[0], {0, 0, 255});
        }

        // 显示图像
        cv::resize(img, img, cv::Size(640, 480));
        cv::imshow("img", img);
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    return 0;
}