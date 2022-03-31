//
// Created by vovandrsnn on 3/31/22.
//

#include "image.hpp"
#include "cmd.hpp"

int main(int argc, char** argv) {
  if (argc < 3) {
    std::cout << "You need to provide name of png image and number of vertices\n";
    return 1;
  }

  std::string image_path = argv[1];
  int vert_num = atoi(argv[2]);
  Image image(cv::imread(image_path, cv::IMREAD_GRAYSCALE));

  std::vector<Dot> temp_dots = TempDots(image);
  int intersections_count = RemoveBadDots(temp_dots);

  std::cout << intersections_count - vert_num << std::endl;
}
