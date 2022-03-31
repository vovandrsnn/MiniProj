//
// Created by vovandrsnn on 3/31/22.
//

void BFS(Dot start, const Image& image, std::vector<Dot>& black_Dots);

Dot GetLeftest(std::vector<Dot>& Dots);

Dot GetRightest(std::vector<Dot>& Dots);

Dot GetLowest(std::vector<Dot>& Dots);

Dot GetHighest(std::vector<Dot>& Dots);

bool AreSimilar(int a, int b);

bool AreSimilar(Dot a, Dot b);

bool IsIntersection(const Dot& start, const Image& image);

std::vector<Dot> PotentialDotFinder(const Image& image);

int RemoveBadDots(const std::vector<Dot>& potential_intersections);

