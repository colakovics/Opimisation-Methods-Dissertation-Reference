// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleAssignmentAlgorithm.h"
#include <tuple>
#include <vector>
#include <cmath>
using std::get;

SimpleAssignmentAlgorithm::SimpleAssignmentAlgorithm()
{
}

SimpleAssignmentAlgorithm::~SimpleAssignmentAlgorithm()
{
}

bool targetComparison(tuple<int, double, double> &leftTarget, tuple<int, double, double> &rightTarget)
{
	if (get<1>(leftTarget) < get<1>(rightTarget))
	{
		return true;
	}
	else
	{
		return false;
	}
}

double findRoundtripTime(tuple<int, double, double> &target, double &timePassed)
{
	return (((get<1>(target) - timePassed) * get<2>(target)) / (1 + get<2>(target))) * 2;
}

bool assignNonCriticalPursuers(double &timePassed, vector<bool> &targetsCaught, vector<double> &busyUntil, vector<tuple<int, double, double>> &targetDangerRankedList, vector<vector<int>> &solution)
{
	auto dangerIter = --targetDangerRankedList.end();
	auto caughtIter = --targetsCaught.end();
	bool jobsDone = false;

	for (int i = 1; i <= busyUntil.size() && !jobsDone; i++)	//For each non-critical pursuer; 'i' is set up to properly reference the pursuers in 'solution'
	{
		if (busyUntil[(i - 1)] <= timePassed) //If the 'i'th pursuer is at the origin and not chasing a target...
		{
			//Iterate backwards through targets until reaching either an unassigned target OR the beginning of all targets
			while (*caughtIter)
			{
				if (caughtIter == targetsCaught.begin())
				{
					jobsDone = true;
					break;
				}
				else
				{
					dangerIter--;
					caughtIter--;
				}
			}

			//Either all targets have been reached, or we can assign pursuer i to the target at DangerIter
			if (!jobsDone)
			{
				busyUntil[(i - 1)] += findRoundtripTime(*dangerIter, timePassed);
				solution[i].push_back(get<0>(*dangerIter));
			}
		}
	}

	//Return the bool showing whether we finished the solution
	return jobsDone;
}

tuple<SolvingAssignment*, vector<tuple<int, double, double>>*>* packageTheSolution(vector<vector<int>> &solution, vector<tuple<int, double, double>> &targetDangerRankedList)
{
	SolvingAssignment* solved = new SolvingAssignment(&solution);
	return new tuple<SolvingAssignment*, vector<tuple<int, double, double>>*> (std::make_tuple(solved, &targetDangerRankedList));
}

tuple<SolvingAssignment*, vector<tuple<int, double, double>>*>* SimpleAssignmentAlgorithm::subSolve(ProblemInitialState* problem)
{
	vector<tuple<int, double, double, double>>* targets = problem->getTargets();

	//Instantiate solution vector (see SolvingAssignment.h for definition)
	vector<vector<int>> solution = {};
	
	//Add 2D vectors for each pursuer
	for (int i = 0; i < problem->getNumberOfPursuers(); i++)
	{
		solution.push_back({});
	}

	//Create ranked list of targets by danger
	vector<tuple<int, double, double>> targetDangerRankedList = {};

	//Break if there are no targets; no activity is the correct activity for the empty problem
	if (targets->empty())
	{
		return packageTheSolution(solution, targetDangerRankedList);
	}

	//Otherwise...
	for (int i = 0; i < targets->size(); i++)	//For all targets in the problem...
	{
		tuple<int, double, double, double> target = (*targets)[i];
		int targetID = get<0>(target);
		double targetDanger = sqrt(pow(get<1>(target), 2) + pow(get<2>(target), 2)) / get<3>(target);
		tuple<int, double, double> targetTuple = std::make_tuple(targetID, targetDanger, get<3>(target));	//Make a tuple out of the target's ID, it's calculated danger value, and its speed

		auto iter = targetDangerRankedList.begin();	//Insert using linear search; currently O(n^2), could be O(n*log2(n)) if Binary Search used, consider using std::upper_bound for this
		while (targetComparison(targetTuple, *iter) == false)
		{
			iter++;
		}
		targetDangerRankedList.insert(iter, targetTuple);	//Insert it before that found tuple - i.e. sort them in order of ascending danger value
	}

	//Important info
	auto mostDangerousUncaught = targetDangerRankedList.begin();
	double timePassed = 0.0; //This will be adding lots of small floats together into a sum; consider using Kahan Summation Algorithm to avoid error
	vector<bool> targetsCaught(targetDangerRankedList.size(), false);
	auto mostDangerousBool = targetsCaught.begin();
	vector<double> busyUntil(problem->getNumberOfPursuers() - 1, 0.0);

	while (std::find(targetsCaught.begin(), targetsCaught.end(), false) != targetsCaught.end())
	{
		//Time until most dangerous target hits the origin
		double greatestDanger_timeUntilCollission = get<1>(*mostDangerousUncaught) - timePassed;

		//Assign all the available non-critical pursuers to the least dangerous targets
		if (assignNonCriticalPursuers(timePassed, targetsCaught, busyUntil, targetDangerRankedList, solution))
		{
			break;
		}

		//Pursuer 1: go through targets, from least to most dangerous, and grab those that you can without missing the most dangerous target, then finally grab the most dangerous
		auto dangerIter = --targetDangerRankedList.end();
		auto caughtIter = --targetsCaught.end();
		while (dangerIter > mostDangerousUncaught) 
		{
			if (findRoundtripTime(*dangerIter, timePassed) <= greatestDanger_timeUntilCollission && !(*caughtIter))
			{
				timePassed += findRoundtripTime(*dangerIter, timePassed);
				greatestDanger_timeUntilCollission -= timePassed;
				*caughtIter = true;
				solution[0].push_back(get<0>(*dangerIter));

				//When a target gets intercepted and time passes, it is possible non-critical pursuers are free; try and use these after each Pursuer1 assignment to remain optimal
				if (assignNonCriticalPursuers(timePassed, targetsCaught, busyUntil, targetDangerRankedList, solution))
				{
					break;
				}
			}
			dangerIter--;
			caughtIter--;
		}

		if (!*mostDangerousBool) 
		{
			timePassed += findRoundtripTime(*mostDangerousUncaught, timePassed);
			*mostDangerousBool = true;
			solution[0].push_back(get<0>(*mostDangerousUncaught));
			mostDangerousBool++;
			mostDangerousUncaught++;
		}
	}

	//Instantiate a SolvingAssignment based on 'solution', create a pointer to targetDangerRankedList, and return them in a vector
	return packageTheSolution(solution, targetDangerRankedList);
}
