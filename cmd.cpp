//
// Created by vovandrsnn on 3/31/22.
//

#include "image.hpp"
#include "cmd.hpp"

void Bfs(Dot start, const Image& image, std::vector<Dot>& black_Dots) {
  std::vector<std::vector<char>> used(image.Height(), std::vector<char>(image.Width()));
  std::queue<Dot> queue;
  queue.push(start);
  used[start.x][start.y] = true;

  size_t white = 0;
  size_t black = 1; // start Dot
  const size_t MIN_ITERATION_COUNT = 200;
  const size_t MAX_ITERATION_COUNT = 400;

  while (!queue.empty() && (white / black == 0 || white + black < MIN_ITERATION_COUNT) &&
      black + white < MAX_ITERATION_COUNT) {
    Dot next = queue.front();
    queue.pop();
    if (!image.IsDotHere(next)) {
      black_Dots.push_back(next);
    }
    for (auto p : image.GetNeighbours(next)) {
      if (!used[p.x][p.y]) {
        queue.push(p);
        used[p.x][p.y] = true;
      }
    }
  }
}

Dot LeftOne(std::vector<Dot>& Dots) {
  Dot best_Dot;
  int min_x = INT_MAX;
  for (auto p : Dots) {
    if (p.x < min_x) {
      best_Dot = p;
      min_x = p.x;
    }
  }
  return best_Dot;
}

Dot HighOne(std::vector<Dot>& Dots) {
  Dot best_Dot;
  int max_y = INT_MIN;
  for (auto p : Dots) {
    if (max_y < p.y) {
      best_Dot = p;
      max_y = p.y;
    }
  }
  return best_Dot;
}

Dot LowOne(std::vector<Dot>& Dots) {
  Dot best_Dot;
  int min_y = INT_MIN;
  for (auto p : Dots) {
    if (p.y < min_y) {
      best_Dot = p;
      min_y = p.y;
    }
  }
  return best_Dot;
}

Dot RightOne(std::vector<Dot>& Dots) {
  Dot best_Dot;
  int max_x = INT_MIN;
  for (auto p : Dots) {
    if (max_x < p.x) {
      best_Dot = p;
      max_x = p.x;
    }
  }
  return best_Dot;
}

bool IsSame(int a, int b) {
  return std::abs(a - b) < INC;
}

bool IsSame(Dot a, Dot b) {
  return IsSame(a.x, b.x) && IsSame(a.y, b.y);
}

bool IsIntersection(const Dot& start, const Image& image) {
  std::vector<Dot> black_Dots;
  Bfs(start, image, black_Dots);

  Dot leftest = LeftOne(black_Dots);
  Dot rightest = RightOne(black_Dots);
  Dot lowest = LowOne(black_Dots);
  Dot highest = HighOne(black_Dots);

  std::vector<Dot> external_Dots;
  external_Dots.push_back(leftest);
  external_Dots.push_back(rightest);
  external_Dots.push_back(lowest);
  external_Dots.push_back(highest);

  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      if (IsSame(external_Dots[i], external_Dots[j])) {
        return false;
      }
    }
  }
  return true;
}

std::vector<Dot> TempDots(const Image& image) {
  std::vector<Dot> temp_dots;

  for (int i = 0; i < image.Height(); i += INC) {
    for (int j = 0; j < image.Width(); j += INC) {
      if (image.IsDotHere(i, j)) {
        if (IsIntersection({i, j}, image)) {
          temp_dots.emplace_back(i, j);
          i += 20;
        }
      }
    }
  }
  return temp_dots;
}

int RemoveBadDots(const std::vector<Dot>& temp_dots) {
  int intersections_count = 0;

  std::vector<char> is_bad_Dot(temp_dots.size());
  for (int i = 0; i < temp_dots.size(); i++) {
    for (int j = i + 1; j < temp_dots.size(); j++) {
      if (IsSame(temp_dots[i], temp_dots[j])) {
        is_bad_Dot[j] = true;
      }
    }
  }

  for (auto is_bad : is_bad_Dot) {
    if (!is_bad) {
      intersections_count++;
    }
  }
  return intersections_count;
}
