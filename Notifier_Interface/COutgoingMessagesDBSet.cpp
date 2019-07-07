#include "stdafx.h"
#include "COutgoingMessagesDBSet.h"

COutgoingMessagesDBSet::COutgoingMessagesDBSet(DBContext& db) : ITable("outgoing_messages", db)
{

	vTableColSpecifications.push_back(TableColSpecification(1, sizeof(OUTGOING_MESSAGES::nId),"id", ColType(Int), (int)offsetof(OUTGOING_MESSAGES, nId),true));
	vTableColSpecifications.push_back(TableColSpecification(2, sizeof(OUTGOING_MESSAGES::szStatus), "status", ColType(String), (int)offsetof(OUTGOING_MESSAGES, szStatus)));
	vTableColSpecifications.push_back(TableColSpecification(3, sizeof(OUTGOING_MESSAGES::nPriorityId),  "priority_id", ColType(Int), (int)offsetof(OUTGOING_MESSAGES, nPriorityId)));
	vTableColSpecifications.push_back(TableColSpecification(4, sizeof(OUTGOING_MESSAGES::szType),  "type", ColType(String), (int)offsetof(OUTGOING_MESSAGES, szType)));
	vTableColSpecifications.push_back(TableColSpecification(5, sizeof(OUTGOING_MESSAGES::nCampaignId),  "campaign_id", ColType(Int), (int)offsetof(OUTGOING_MESSAGES, nCampaignId)));
	vTableColSpecifications.push_back(TableColSpecification(6, sizeof(OUTGOING_MESSAGES::nToClientId), "to_client_id", ColType(Int), (int)offsetof(OUTGOING_MESSAGES, nToClientId)));
	vTableColSpecifications.push_back(TableColSpecification(7, sizeof(OUTGOING_MESSAGES::szMsgSubject), "message_subject", ColType(String), (int)offsetof(OUTGOING_MESSAGES, szMsgSubject)));
	vTableColSpecifications.push_back(TableColSpecification(8, sizeof(OUTGOING_MESSAGES::szMsgText), "message_text", ColType(String), (int)offsetof(OUTGOING_MESSAGES, szMsgText)));
	vTableColSpecifications.push_back(TableColSpecification(9, sizeof(OUTGOING_MESSAGES::szResTemplName), "resource_template_name", ColType(String), (int)offsetof(OUTGOING_MESSAGES, szResTemplName)));
	vTableColSpecifications.push_back(TableColSpecification(10, sizeof(OUTGOING_MESSAGES::szResTemplCode),  "resourse_template_code", ColType(String), (int)offsetof(OUTGOING_MESSAGES, szResTemplCode)));
	vTableColSpecifications.push_back(TableColSpecification(11, sizeof(OUTGOING_MESSAGES::szHtmlData), "html_data", ColType(String), (int)offsetof(OUTGOING_MESSAGES, szHtmlData)));
}

