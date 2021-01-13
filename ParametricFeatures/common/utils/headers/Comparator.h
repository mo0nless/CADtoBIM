#pragma once

#include <math.h>
#include <vector>

using namespace std;

namespace Common
{
	namespace Utilities
	{

		struct Comparator {

			static bool Comparator::isEqual(double n1, double n2)
			{
				/* some small number such as 1e-5 */
				const double epsilon = 1e-5;
				return abs(n1 - n2) <= epsilon * abs(n1);
			}

			static bool Comparator::isEqual(vector<double> v1, vector<double> v2)
			{
				if (v1.size() != v2.size())
				{
					return false;
				}

				for (size_t i = 0; i < v1.size(); i++)
				{
					if (!isEqual(v1[i], v2[i])) {
						return false;
					}
				}
				return true;

			}
		};
	}
}