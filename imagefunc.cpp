//
// Created by vovandrsnn on 3/31/22.
//

#include "image.hpp"

Dot::Dot(int x, int y): x(x), y(y) {}

bool Dot::operator==(const Dot& other) const {
  return x == other.x && y == other.y;
}

bool Dot::operator!=(const Dot& other) const {
  return !(*this == other);
}

size_t Image::GetRows() const {
  return is_white_.size();
}

size_t Image::GetColumns() const {
  return is_white_[0].size();
}

std::vector<Dot> Image::GetNeighbours(Dot Dot) const {
  return GetNeighbours(Dot.x, Dot.y);
}

bool Image::IsWhite(int x, int y) const {
  return is_white_[x][y];
}

bool Image::IsWhite(const Dot& Dot) const {
  return IsWhite(Dot.x, Dot.y);
}

bool Image::IsWhite(const uchar& color) const{
  return color == 0;
}

bool Image::IsCorrect(int x, int y) const {
  return x >= 0 && x < is_white_.size() &&
      y >= 0 && y < is_white_[0].size();
}

Image::Image(cv::Mat image) : is_white_(image.rows, std::vector<uchar>(image.cols)) {
  for (int i = 0; i < image.rows; i++) {
    for (int j = 0; j < image.cols; j++) {
      uchar color = image.at<uchar>(i, j);
      is_white_[i][j] = IsWhite(color);
    }
  }
}

std::vector<Dot> Image::GetNeighbours(int x, int y) const{
  std::vector<Dot> neighbours;
  if (IsCorrect(x + 1, y)) {
    neighbours.emplace_back(x + 1, y);
  }
  if (IsCorrect(x, y + 1)) {
    neighbours.emplace_back(x, y + 1);
  }
  if (IsCorrect(x - 1, y)) {
    neighbours.emplace_back(x - 1, y);
  }
  if (IsCorrect(x, y - 1)) {
    neighbours.emplace_back(x, y - 1);
  }
  return neighbours;
}
