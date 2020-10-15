// Fill out your copyright notice in the Description page of Project Settings.


#include "SolvingAssignment.h"

SolvingAssignment::SolvingAssignment(vector<vector<int>>* solution)
	:solution(solution)
{
}

SolvingAssignment::~SolvingAssignment()
{
	delete solution;
}
