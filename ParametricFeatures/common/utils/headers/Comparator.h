#pragma once

/**
 * @file Comparator.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <math.h>
#include <vector>

using namespace std;

namespace Common
{
	namespace Utilities
	{
		/**
		 * @brief Number comparator for geometric operation
		 * 
		 */
		struct Comparator {
			
			/**
			 * @brief Check if two number are equal for some small number such as 1e-5
			 * 
			 * @param n1 number 1
			 * @param n2 number 2
			 * @return true 
			 * @return false 
			 */
			static bool Comparator::isEqual(double n1, double n2)
			{
				/* some small number such as 1e-5 */
				const double epsilon = 1e-5;
				return abs(n1 - n2) <= epsilon * abs(n1);
			}

			/**
			 * @brief Check if two vector are equal 
			 * 
			 * @param v1 vector 1
			 * @param v2 vector 2
			 * @return true 
			 * @return false 
			 */
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