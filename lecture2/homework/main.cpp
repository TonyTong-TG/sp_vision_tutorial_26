#include "tools.hpp"

int main()
{
    // Read img
    cv::Mat img = cv::imread("./img/test_1.jpg");
    if (img.empty())
    {
        std::cout << "fail to load image" << std::endl;
        return -1;
    }

    img = resize(img, 640);

    // Show the result
    cv::imshow("Result", img);
    cv::waitKey(0);

    return 0;
}
