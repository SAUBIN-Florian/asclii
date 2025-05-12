#include <iostream>
#include <unordered_map>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "logger.hpp"


void doc() {
    std::cout << R"(
    Usage: asclii [options]
    
    Options:
        --help          Show this help message
        --img <file>    Specify an image file
        --verbose       Enable verbose logging
    )" << std::endl;
    exit(0);
}

void img_to_ascii(cv::Mat& img) {
    std::string ascii_chars = " .:-=*#%@";
    int levels = ascii_chars.length();

    // bloc sampling values
    int block_h = 6;
    int block_w = 3;

    for (int y = 0; y < img.rows; y += block_h) {
        for (int x = 0; x < img.cols; x += block_w) {
            int sum = 0;
            int count = 0;

            for (int dy = 0; dy < block_h && (y + dy) < img.rows; ++dy) {
                for (int dx = 0; dx < block_w && (x + dx) < img.cols; ++dx) {
                    sum += img.at<uchar>(y + dy, x + dx);
                    ++count;
                }
            }

            int avg = sum / count;
            int index = avg * levels / 256;
            std::cout << ascii_chars[index];
        }
        std::cout << "\n";
    }
}

int main(int argc, char* argv[]) {
    std::string bin_path = argv[0];
    std::unordered_map<std::string, std::string> args;

    for (int i = 1; i < argc; i+=2) {
        if (i + 1 < argc) {
            args[argv[i]] = std::string(argv[i + 1]);
        } else if (std::string(argv[i]) == "--help") {
            doc();
        } else if (std::string(argv[i]) == "--verbose") {
            Logger::lvl(PropertyLevel::TRACE_LOG);
        } else {
            Logger::error_log("Missing value argument for %s", argv[i]);
            exit(1);
        }
    }
    
    if (args.find("--img") != args.end()) {
        cv::Mat img = cv::imread(args.at("--img"), cv::IMREAD_GRAYSCALE);
        Logger::trace_log("image: [%d * %d] found at %s", img.cols, img.rows, args.at("--img").c_str());
        
        double aspect_ratio = 0.55;
        int new_width = 400;
        int new_height = (img.cols / img.rows) * new_width * aspect_ratio;
        cv::resize(img, img, cv::Size(new_width, new_height));

        img_to_ascii(img);
    }

    Logger::trace_log("Exit Program");
    return 0;
}