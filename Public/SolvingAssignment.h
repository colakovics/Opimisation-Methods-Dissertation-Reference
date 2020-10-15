// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
using std::vector;

/**
 * 
 */
class KTSP_MULTIPLE_DEFEND_API SolvingAssignment
{
public:
	SolvingAssignment(vector<vector<int>>* solution);
	~SolvingAssignment();

private:
	vector<vector<int>>* solution;	//2D vector, one vertical column for each pursuer, ints refer to the ID of the target they chase in order of the vector storage
		/*	[1][2]
			[3][7]-------->This vector would imply pursuer 1 (the first column) goes for target 1, then 3, then 6, then 4, while pursuer 2 (the second column) would go for target 2, then 7, then 5.
			[6][5]
			[4]
		*/
};
