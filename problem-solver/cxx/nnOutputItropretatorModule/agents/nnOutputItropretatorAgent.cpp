/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include <sc-memory/cpp/sc_stream.hpp>
#include <sc-kpm/sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-kpm/sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-kpm/sc-agents-common/utils/AgentUtils.hpp>
#include <vector>

#include "nnOutputItropretatorAgent.hpp"
#include "keynodes/keynodes.hpp"


using namespace std;
using namespace utils;

namespace nnOutputItropretator
{

SC_AGENT_IMPLEMENTATION(NNOutputItropretatorAgent)
{
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);

  ScAddr image = IteratorUtils::getFirstByOutRelation(ms_context.get(), questionNode, Keynodes::rrel_1);
  ScAddr nn_result = IteratorUtils::getFirstByOutRelation(ms_context.get(), questionNode, Keynodes::rrel_2);


  if(!ms_context->HelperCheckEdge(Keynodes::image, image, ScType::EdgeAccessConstPosPerm))
   return SC_RESULT_ERROR_INVALID_PARAMS;

  if(!ms_context->HelperCheckEdge(Keynodes::action_use_ann, nn_result, ScType::EdgeAccessConstPosPerm))
   return SC_RESULT_ERROR_INVALID_PARAMS;

  ScIterator5Ptr iterator5 = ms_context->Iterator5(nn_result, ScType::EdgeDCommonConst, ScType::NodeConstTuple, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_nn_answer);

  ScAddr set_of_answers;
  if (iterator5->Next())
  {
   set_of_answers = iterator5->Get(2);
  }
  else
   return SC_RESULT_ERROR_INVALID_PARAMS;


  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);
  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, set_of_answers);
  AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);
  return SC_RESULT_OK;
}
}
