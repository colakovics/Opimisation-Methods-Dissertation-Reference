// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignmentAlgorithm.h"

SolvingAssignment* AssignmentAlgorithm::solve(ProblemInitialState* problem) //Moved this to be a generic method in AssignmentAlgorithm
{
	tuple<SolvingAssignment*, vector<tuple<int, double, double>>*>* result = this->subSolve(problem);

	SolvingAssignment* solution;
	vector<tuple<int, double, double>>* targetDangerRankedList;
	std::tie(solution, targetDangerRankedList) = *result;

	delete targetDangerRankedList;
	delete result;
	return solution;
}
