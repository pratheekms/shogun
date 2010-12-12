/*
*
*    MultiBoost - Multi-purpose boosting package
*
*    Copyright (C) 2010   AppStat group
*                         Laboratoire de l'Accelerateur Lineaire
*                         Universite Paris-Sud, 11, CNRS
*
*    This file is part of the MultiBoost library
*
*    This library is free software; you can redistribute it 
*    and/or modify it under the terms of the GNU General Public
*    License as published by the Free Software Foundation; either
*    version 2.1 of the License, or (at your option) any later version.
*
*    This library is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public
*    License along with this library; if not, write to the Free Software
*    Foundation, Inc., 51 Franklin St, 5th Floor, Boston, MA 02110-1301 USA
*
*    Contact: Balazs Kegl (balazs.kegl@gmail.com)
*             Norman Casagrande (nova77@gmail.com)
*             Robert Busa-Fekete (busarobi@gmail.com)
*
*    For more information and up-to-date version, please visit
*        
*                       http://www.multiboost.org/
*
*/


/**
* \file SingleStumpLearner.h A single threshold decision stump learner. 
*/

#ifndef __ENUM_LEARNER2_H
#define __ENUM_LEARNER2_H

#include "classifier/boosting/WeakLearners/FeaturewiseLearner.h"
#include "classifier/boosting/Utils/Args.h"

#include <vector>
#include <queue>
#include <fstream>
#include <cassert>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

namespace shogun {

/**
* A \b single threshold decision stump learner. 
* There is ONE and ONE ONLY threshold here.
*/
class EnumLearner2 : public FeaturewiseLearner
{
public:

   /**
   * The destructor. Must be declared (virtual) for the proper destruction of 
   * the object.
   */
   virtual ~EnumLearner2() {}

   /**
   * Returns itself as object.
   * \remark It uses the trick described in http://www.parashift.com/c++-faq-lite/serialization.html#faq-36.8
   * for the auto-registering classes.
   * \date 21/05/2007
   */
   virtual BaseLearner* subCreate() { return new EnumLearner2(); }

   /**
   * Run the learner to build the classifier on the given data.
   * \param pData The pointer to the data.
   * \see BaseLearner::run
   * \date 21/05/2007
   */
   virtual float run();

   /**
   * Save the current object information needed for classification,
   * that is the _u vector.
   * \param outputStream The stream where the data will be saved
   * \param numTabs The number of tabs before the tag. Useful for indentation
   * \remark To fully save the object it is \b very \b important to call
   * also the super-class method.
   * \date 21/05/2007
   */
   virtual void save(ofstream& outputStream, int numTabs = 0);

   /**
   * Load the xml file that contains the serialized information
   * needed for the classification and that belongs to this class.
   * \param st The stream tokenizer that returns tags and values as tokens
   * \see save()
   * \date 21/05/2007
   */
   virtual void load(nor_utils::StreamTokenizer& st);

   /**
   * Copy all the info we need in classify().
   * pBaseLearner was created by subCreate so it has the correct (sub) type.
   * Usually one must copy the same fields that are loaded and saved. Don't 
   * forget to call the parent's subCopyState().
   * \param pBaseLearner The sub type pointer into which we copy.
   * \see save
   * \see load
   * \see classify
   * \see ProductLearner::run()
   * \date 25/05/2007
   */
   virtual void subCopyState(BaseLearner *pBaseLearner);

   /**
   * The same discriminative function as below, but called with a data point. 
   * \param pData The input data.
   * \param pointIdx The index of the data point.
   * \return \phi[(int)pointIdx]
   * \date 21/05/2007
   */
   virtual float phi(float val, int classIdx) const;


   /**
   * Generate a similarity matrix over the coordinates. In the case of collaborative filtering, this means that we will find the user who has similarar votes.
   * \date 16/03/2009
   */

   virtual void generateSimilarityMatrix( void );
   virtual const char* get_name() const { return "EnumLearner2"; }
protected:

   static vector< int > _clusters;
   static int _k;
   vector<float> _u;
   //static vector<float> _prevU;
};

//////////////////////////////////////////////////////////////////////////

} // end of namespace shogun

#endif // __ENUM_LEARNER_H
