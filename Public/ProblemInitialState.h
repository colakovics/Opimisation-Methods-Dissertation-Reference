// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <tuple>
#include <vector>
#include <string>
using std::vector;
using std::tuple;

/**
 * 
 */
class KTSP_MULTIPLE_DEFEND_API ProblemInitialState
{
public:
	ProblemInitialState(vector<tuple<int, double, double, double>> targets, int numberOfPursuers);

	//ProblemInitialState(std::string filepath); This will read a CSV file to initialise the problem.

	~ProblemInitialState();

	vector<tuple<int, double, double, double>>* getTargets();

	int getNumberOfPursuers();

private:
	vector<tuple<int, double, double, double>> targets;	//Vector of targets: tuple - ID, x position, y position, speed (<= 1)
	int numberOfPursuers;	
};
