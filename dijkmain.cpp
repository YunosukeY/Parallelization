#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include "clock.h"

std::deque<unsigned> NearestPath(
				 unsigned nodeSize,
				 const std::vector<unsigned>& edgeIndices1,
				 const std::vector<unsigned>& edgeIndices2,
				 const std::vector<double>& edgeDistances,
				 unsigned startNode, unsigned goalNode
				 );

int main()
{
  unsigned n, m;
  unsigned start, goal;
  std::cin >> n >> m;
  std::cin >> start >> goal;

  std::vector<unsigned> edgeIndices1;
  std::vector<unsigned> edgeIndices2;
  std::vector<double> edgeDistances;
  
  unsigned p, q;
  double cost;
  for (size_t i = 0; i < m; ++i)
    {
      std::cin >> p >> q >> cost;
      edgeIndices1.push_back(p);
      edgeIndices2.push_back(q);
      edgeDistances.push_back(cost);
    }

  start_counter();

  const auto path = NearestPath(n, edgeIndices1, edgeIndices2, edgeDistances, start, goal);
  for(auto i : path)
    {
      std::cout << i << "\n";
    }

  print_counter();
}
