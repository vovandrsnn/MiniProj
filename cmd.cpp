//
// Created by vovandrsnn on 3/31/22.
//

#include "image.hpp"
#include "cmd.hpp"


void BFS(Dot start, const Image& image, std::vector<Dot>& black_Dots) {
  std::vector<std::vector<char>> used(image.GetRows(), std::vector<char>(image.GetColumns()));
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
    if (!image.IsWhite(next)) {
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

Dot GetLeftest(std::vector<Dot>& Dots) {
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

Dot GetRightest(std::vector<Dot>& Dots) {
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

Dot GetLowest(std::vector<Dot>& Dots) {
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

Dot GetHighest(std::vector<Dot>& Dots) {
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

bool AreSimilar(int a, int b) {
  return std::abs(a - b) < INC;
}

bool AreSimilar(Dot a, Dot b) {
  return AreSimilar(a.x, b.x) && AreSimilar(a.y, b.y);
}

bool IsIntersection(const Dot& start, const Image& image) {
  std::vector<Dot> black_Dots;
  BFS(start, image, black_Dots);

  Dot leftest = GetLeftest(black_Dots);
  Dot rightest = GetRightest(black_Dots);
  Dot lowest = GetLowest(black_Dots);
  Dot highest = GetHighest(black_Dots);

  std::vector<Dot> external_Dots;
  external_Dots.push_back(leftest);
  external_Dots.push_back(rightest);
  external_Dots.push_back(lowest);
  external_Dots.push_back(highest);

  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      if (AreSimilar(external_Dots[i], external_Dots[j])) {
        return false;
      }
    }
  }
  return true;
}

std::vector<Dot> PotentialDotFinder(const Image& image) {
  std::vector<Dot> potential_intersections;

  for (int i = 0; i < image.GetRows(); i += INC) {
    for (int j = 0; j < image.GetColumns(); j += INC) {
      if (image.IsWhite(i, j)) {
        if (IsIntersection({i, j}, image)) {
          potential_intersections.emplace_back(i, j);
          i += 20;
        }
      }
    }
  }
  return potential_intersections;
}

int RemoveBadDots(const std::vector<Dot>& potential_intersections) {
  int intersections_count = 0;

  std::vector<char> is_bad_Dot(potential_intersections.size());
  for (int i = 0; i < potential_intersections.size(); i++) {
    for (int j = i + 1; j < potential_intersections.size(); j++) {
      if (AreSimilar(potential_intersections[i], potential_intersections[j])) {
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



