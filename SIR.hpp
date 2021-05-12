#ifndef SIR_HPP
#define SIR_HPP

#include <cassert>
#include <stdexcept>
#include <vector>

namespace Contagion {

struct State {
  int S = 0;
  int I = 0;
  int R = 0;

  double beta = 0.;
  double gamma = 0.;
};

class SIR {
  State s0{};
  int duration = 0.;
  int N = 0;

 public:
  // tenere sotto controlla la conversione fra int e double

  SIR(State const& s, int d) : s0{s}, duration{d}, N{s.S + s.I + s.R} {};

  std::vector<State> evolve() {
    std::vector<State> evo{s0};
    State s = s0;
    if (N <= 0) throw std::runtime_error{"invalid populaton number"};
    for (int i = 0; i != duration; ++i) {
      State const& previous = evo.back();
      s.S = previous.S * (1 - (previous.beta * previous.I) / N);
      s.I = previous.I *
            (1 + ((previous.beta * previous.S) / N) - previous.gamma);
      // s.R = previous.R + previous.gamma * previous.I;
      s.R = N - (s.S + s.I);
      assert(s.S >= 0 && s.I >= 0 && s.R >= 0);
      assert(s.S + s.R + s.I == N);
      evo.push_back(s);
    }

    return evo;
  };
};

}  // namespace Contagion

#endif
