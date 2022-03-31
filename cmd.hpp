//
// Created by vovandrsnn on 3/31/22.
//

#ifndef UNTITLED__SOURCE_H_

void Bfs(Dot start, const Image& image, std::vector<Dot>& black_Dots);

Dot LeftOne(std::vector<Dot>& Dots);

Dot RightOne(std::vector<Dot>& Dots);

Dot LowOne(std::vector<Dot>& Dots);

Dot HighOne(std::vector<Dot>& Dots);

bool IsSame(int a, int b);

bool IsSame(Dot a, Dot b);

bool IsIntersection(const Dot& start, const Image& image);

std::vector<Dot> TempDots(const Image& image);

int RemoveBadDots(const std::vector<Dot>& potential_intersections);
#endif //UNTITLED__SOURCE_H_
