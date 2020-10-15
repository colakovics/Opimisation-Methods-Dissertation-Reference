// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SolvingAssignment.h"
#include "ProblemInitialState.h"

/**
 *	Interface for an assignment algorithm. 
 */
class KTSP_MULTIPLE_DEFEND_API AssignmentAlgorithm
{
public:
	SolvingAssignment* solve(ProblemInitialState* problem);
		//This class should only call 'subSolve' from itself, discard & delete the danger ranking vector, then return the SolvingAssignment pointer

protected:
	virtual tuple<SolvingAssignment*, vector<tuple<int, double, double>>*>* subSolve(ProblemInitialState* problem) = 0;	//This should be where the majority of work is done for the algorithm
};
