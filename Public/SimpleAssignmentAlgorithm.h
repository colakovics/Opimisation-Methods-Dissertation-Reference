// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssignmentAlgorithm.h"

/**
 * 
 */
class KTSP_MULTIPLE_DEFEND_API SimpleAssignmentAlgorithm : public AssignmentAlgorithm
{
protected:
	tuple<SolvingAssignment*, vector<tuple<int, double, double>>*>* subSolve(ProblemInitialState* problem);

public:
	SimpleAssignmentAlgorithm();
	~SimpleAssignmentAlgorithm();
};
