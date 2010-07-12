/*
 * SymbolicFactorGraph.cpp
 *
 *  Created on: Oct 29, 2009
 *      Author: Frank Dellaert
 */

#include <iostream>
#include <fstream>
#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include "Ordering.h"
#include "SymbolicFactorGraph.h"
#include "SymbolicBayesNet.h"
#include "inference-inl.h"
#include "LieConfig-inl.h"

using namespace std;

namespace gtsam {

	// Explicitly instantiate so we don't have to include everywhere
	template class FactorGraph<SymbolicFactor>;

	/* ************************************************************************* */
  boost::shared_ptr<SymbolicConditional>
  SymbolicFactorGraph::eliminateOne(const Symbol& key){
		return gtsam::eliminateOne<SymbolicFactor,SymbolicConditional>(*this, key);
  }

	/* ************************************************************************* */
	SymbolicBayesNet
	SymbolicFactorGraph::eliminate(const Ordering& ordering)
	{
		SymbolicBayesNet bayesNet;

		BOOST_FOREACH(const Symbol& key, ordering) {
			SymbolicConditional::shared_ptr conditional =
					gtsam::eliminateOne<SymbolicFactor,SymbolicConditional>(*this,key);
			bayesNet.push_back(conditional);
		}
		return bayesNet;
	}

	/* ************************************************************************* */
	SymbolicBayesNet
	SymbolicFactorGraph::eliminateFrontals(const Ordering& ordering)
	{
		return eliminate(ordering);
	}

	/* ************************************************************************* */
}
