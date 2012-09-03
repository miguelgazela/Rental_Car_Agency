/*
 * functions.h
 *
 *  Created on: 20 de Out de 2011
 *      Author: migueloliveira
 */

#ifndef BINARYSEARCH_H_
#define BINARYSEARCH_H_

#include <vector>
#include <string>
#include <sstream>
using namespace std;

template <class Comparable>
int BinarySearch(const vector<Comparable*> &v, Comparable x)
{
	int left = 0, right = v.size() - 1;
	while(left <= right)
	{
		int middle = (left + right) / 2;
		if (*(v.at(middle)) < x)
			left = middle + 1;
		else if (x < *(v.at(middle)))
			right = middle - 1;
		else
			return middle; //encontrou
	}
	return -1; //nao encontrou
}

#endif /* BINARYSEARCH_H_ */
