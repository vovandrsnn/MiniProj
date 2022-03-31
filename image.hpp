//
// Created by vovandrsnn on 3/31/22.
//

#ifndef UNTITLED__SOURCE_H_
#include <iostream>
#include <vector>
#include <queue>

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>

#define INC 20

struct Dot {
  Dot() = default;
  Dot(int x, int y);

  int x = 0;
  int y = 0;

  bool operator==(const Dot& other) const;
  bool operator!=(const Dot& other) const;
};


class Image {
 public:
  explicit Image(cv::Mat image);

  size_t GetRows() const;
  size_t GetColumns() const;

  std::vector<Dot> GetNeighbours(Dot Dot) const;
  std::vector<Dot> GetNeighbours(int x, int y) const;

  bool IsWhite(int x, int y) const;

  bool IsWhite(const Dot& Dot) const;

 private:
  bool IsWhite(const uchar& color) const;

  bool IsCorrect(int x, int y) const;

  std::vector<std::vector<uchar>> is_white_;
};

#endif //UNTITLED__SOURCE_H_
