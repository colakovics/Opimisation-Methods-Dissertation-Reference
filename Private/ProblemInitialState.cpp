// Fill out your copyright notice in the Description page of Project Settings.


#include "ProblemInitialState.h"
#include <fstream>
#include <iostream>

ProblemInitialState::ProblemInitialState(vector<tuple<int, double, double, double>> targets, int numberOfPursuers)
	:targets(targets), numberOfPursuers(numberOfPursuers)
{
}

/*
ProblemInitialState::ProblemInitialState(std::string filename)
{
	std::ifstream inputFile;
	inputFile.open(filename);
	int numberOfPursuers = 
}
*/

ProblemInitialState::~ProblemInitialState()
{
}

vector<tuple<int, double, double, double>>* ProblemInitialState::getTargets()
{
	return &targets;
}

int ProblemInitialState::getNumberOfPursuers()
{
	return numberOfPursuers;
}