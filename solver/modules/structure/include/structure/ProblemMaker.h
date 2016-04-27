
#include <structure/Problem.h>
#include <util/ClockWiseFor.h>
#include <random>
#include <vector>
#include <cmath>

class ProblemMaker{
public:
	//等面積問題作成
	static Problem MakeEqualAreaProblem();
	
	//ランダム問題作成
	static Problem MakeRandomProblem();
};
