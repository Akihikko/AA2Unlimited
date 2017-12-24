#include "StdAfx.h"
#include "Files\PersistentStorage.h"

namespace Shared {
	namespace Triggers {

		/*
		 * List of possible Expressions
		 */

		Value Thread::GetTriggeringCard(std::vector<Value>&) {
			return this->eventData->card;
		}

		//int ()
		Value Thread::GetThisCard(std::vector<Value>& params) {
			return this->thisCard;
		}

		Value Thread::GetPC(std::vector<Value>&) {
			auto pc = Shared::GameState::getPlayerCharacter();
			return pc->m_seat;
		}

		//bool (int)
		Value Thread::IsSeatFilled(std::vector<Value>& params) {
			int card = params[0].iVal;
			if (card > 24) return Value(false);
			CharInstData* cardInst = &AAPlay::g_characters[card];
			return Value(cardInst->IsValid());
		}

		//int ()
		Value Thread::GetDaysPassed(std::vector<Value>& params) {
			return ExtVars::AAPlay::GameTimeData()->nDays;
		}

		Value Thread::GetCurrentDay(std::vector<Value>& params) {
			return ExtVars::AAPlay::GameTimeData()->day;
		}

		Value Thread::GetCurrentPeriod(std::vector<Value>& params) {
			return ExtVars::AAPlay::GameTimeData()->currentPeriod;
		}

		/*
		 * Int stuff
		 */

		 //int (int min, int max)
		Value Thread::GetRandomInt(std::vector<Value>& params) {
			int range = params[1].iVal - params[0].iVal + 1;
			int r = rand() % range + params[0].iVal;
			return Value(r);
		}

		Value Thread::AddIntegers(std::vector<Value>& params) {
			return Value(params[0].iVal + params[1].iVal);
		}

		Value Thread::SubstractIntegers(std::vector<Value>& params) {
			return Value(params[0].iVal - params[1].iVal);
		}
		//int(int,int)
		Value Thread::DivideIntegers(std::vector<Value>& params) {
			return Value(params[0].iVal / params[1].iVal);
		}
		//int(int,int)
		Value Thread::MultiplyIntegers(std::vector<Value>& params) {
			return Value(params[0].iVal * params[1].iVal);
		}
		//int(float)
		Value Thread::Float2Int(std::vector<Value>& params) {
			int i = int(params[0].fVal);
			return Value(i);
		}
		//int(string)
		Value Thread::StrLength(std::vector<Value>& params) {
			auto str = params[0].strVal;
			return Value((int)str->size());
		}
		//int(string source, string substring)
		Value Thread::FirstIndexOf(std::vector<Value>& params) {
			auto source = params[0].strVal;
			auto sub = params[1].strVal;
			int match = (int)source->find(sub->c_str());
			if (match == std::wstring::npos) match = -1;
			return Value(match);
		}
		//int(string source, int from, string substring)
		Value Thread::FirstIndexOfFrom(std::vector<Value>& params) {
			auto source = params[0].strVal;
			auto sub = params[1].strVal;
			int from = params[2].iVal;
			int match = (int)source->find(sub->c_str(), from);
			if (match == std::wstring::npos) match = -1;
			return Value(match);
		}
		//int(string)
		Value Thread::String2Int(std::vector<Value>& params) {
			int i = _wtoi(params[0].strVal->c_str());
			if (errno == EINVAL)
			{
				return Value(TEXT("Conversion failed"));
			}
			return Value(i);
		}

		/*
		* Bool stuff
		*/

		//bool(bool)
		Value Thread::BoolNot(std::vector<Value>& params) {
			return !params[0].bVal;
		}

		//bool(int,int)
		Value Thread::GreaterThanIntegers(std::vector<Value>& params) {
			return params[0].iVal > params[1].iVal;
		}
		//bool(int,int)
		Value Thread::GreaterEqualsIntegers(std::vector<Value>& params) {
			return params[0].iVal >= params[1].iVal;
		}
		//bool(int,int)
		Value Thread::EqualsIntegers(std::vector<Value>& params) {
			return params[0].iVal == params[1].iVal;
		}
		//bool(int,int)
		Value Thread::NotEqualsIntegers(std::vector<Value>& params) {
			return params[0].iVal != params[1].iVal;
		}
		//bool(int,int)
		Value Thread::LessEqualsIntegers(std::vector<Value>& params) {
			return params[0].iVal <= params[1].iVal;
		}
		//bool(int,int)
		Value Thread::LessThanIntegers(std::vector<Value>& params) {
			return params[0].iVal < params[1].iVal;
		}

		//bool(string,string)
		Value Thread::EqualsStrings(std::vector<Value>& params) {
			return *(params[0].strVal) == *(params[1].strVal);
		}
		//bool(float,float)
		Value Thread::GreaterThanFloats(std::vector<Value>& params) {
			return params[0].fVal > params[1].fVal;
		}
		//bool(float,float)
		Value Thread::GreaterEqualsFloats(std::vector<Value>& params) {
			return params[0].fVal >= params[1].fVal;
		}
		//bool(float,float)
		Value Thread::EqualsFloats(std::vector<Value>& params) {
			return params[0].fVal == params[1].fVal;
		}
		//bool(float,float)
		Value Thread::NotEqualsFloats(std::vector<Value>& params) {
			return params[0].fVal != params[1].fVal;
		}
		//bool(float,float)
		Value Thread::LessEqualsFloats(std::vector<Value>& params) {
			return params[0].fVal <= params[1].fVal;
		}
		//bool(float,float)
		Value Thread::LessThanFloats(std::vector<Value>& params) {
			return params[0].fVal < params[1].fVal;
		}
		//bool(int)
		Value Thread::IsInterruptAction(std::vector<Value>& params) {
			int interruptActions[] = {
				ExtClass::ConversationId::INTERRUPT_COMPETE, ExtClass::ConversationId::INTERRUPT_STOP_QUARREL, ExtClass::ConversationId::INTERRUPT_WHAT_ARE_YOU_DOING,
				ExtClass::ConversationId::H_END, ExtClass::ConversationId::H_NOTE, ExtClass::ConversationId::BREAK_CHAT, ExtClass::ConversationId::BREAK_H
			};
			for each (int action in interruptActions)
			{
				if (action == params[0].iVal) return Value(true);
			}
			return Value(false);
		}
		//bool(int)
		Value Thread::IsMinnaAction(std::vector<Value>& params) {
			int minnaActions[] = {
				ExtClass::ConversationId::MINNA_BE_FRIENDLY, ExtClass::ConversationId::MINNA_CLUB, ExtClass::ConversationId::MINNA_COME, ExtClass::ConversationId::MINNA_EAT, ExtClass::ConversationId::MINNA_H, ExtClass::ConversationId::MINNA_KARAOKE, ExtClass::ConversationId::MINNA_LUNCH, ExtClass::ConversationId::MINNA_REST, ExtClass::ConversationId::MINNA_SPORTS, ExtClass::ConversationId::MINNA_STUDY
			};
			for each (int action in minnaActions)
			{
				if (action == params[0].iVal) return Value(true);
			}
			return Value(false);
		}
		//bool(int)
		Value Thread::IsForceAction(std::vector<Value>& params) {
			int forceActions[] = {
				ExtClass::ConversationId::FIGHT, ExtClass::ConversationId::FORCE_H, ExtClass::ConversationId::FORCE_IGNORE, ExtClass::ConversationId::FORCE_PUT_THIS_ON, ExtClass::ConversationId::FORCE_SHOW_THAT, ExtClass::ConversationId::INSULT, ExtClass::ConversationId::SLAP
			};
			for each (int action in forceActions)
			{
				if (action == params[0].iVal) return Value(true);
			}
			return Value(false);
		}
		//bool(int)
		Value Thread::IsSexAction(std::vector<Value>& params) {
			int sexActions[] = {
				ExtClass::ConversationId::FOLLOW_ME_H, ExtClass::ConversationId::FORCE_H, ExtClass::ConversationId::MINNA_H, ExtClass::ConversationId::NORMAL_H, ExtClass::ConversationId::NO_PROMPT_H, ExtClass::ConversationId::SKIP_CLASS_H, ExtClass::ConversationId::SKIP_CLASS_SURPRISE_H, ExtClass::ConversationId::STUDY_HOME_H, ExtClass::ConversationId::LEWD_REWARD
			};
			for each (int action in sexActions)
			{
				if (action == params[0].iVal) return Value(true);
			}
			return Value(false);
		}
		//bool(int)
		Value Thread::IsNoPromptAction(std::vector<Value>& params) {
			int noPromptActions[] = {
				ExtClass::ConversationId::EXPLOITABLE_LINE, ExtClass::ConversationId::FORCE_BREAKUP, ExtClass::ConversationId::GOOD_BYE_KISS, ExtClass::ConversationId::GOOD_MORNING_KISS, ExtClass::ConversationId::I_SAW_SOMEONE_HAVE_H, ExtClass::ConversationId::I_WILL_CHEAT, ExtClass::ConversationId::MURDER, ExtClass::ConversationId::MURDER_NOTICE, ExtClass::ConversationId::NEVERMIND, ExtClass::ConversationId::NO_PROMPT_H, ExtClass::ConversationId::NO_PROMPT_KISS, ExtClass::ConversationId::REVEAL_PREGNANCY, ExtClass::ConversationId::SHAMELESS, ExtClass::ConversationId::SLAP, ExtClass::ConversationId::SOMEONE_GOT_CONFESSED_TO, ExtClass::ConversationId::SOMEONE_LIKES_YOU, ExtClass::ConversationId::STOP_FOLLOWING, ExtClass::ConversationId::TOGETHER_FOREVER
			};
			for each (int action in noPromptActions)
			{
				if (action == params[0].iVal) return Value(true);
			}
			return Value(false);
		}
		//bool(int)
		Value Thread::IsGameOverAction(std::vector<Value>& params) {
			int gameOverActions[] = {
				ExtClass::ConversationId::MURDER, ExtClass::ConversationId::REVEAL_PREGNANCY, ExtClass::ConversationId::TOGETHER_FOREVER
			};
			for each (int action in gameOverActions)
			{
				if (action == params[0].iVal) return Value(true);
			}
			return Value(false);
		}
		//bool(int)
		Value Thread::IsNoTargetAction(std::vector<Value>& params) {
			int noTargetActions[] = {
				ExtClass::ConversationId::CHANGE_CLOTHES, ExtClass::ConversationId::DO_CLUB, ExtClass::ConversationId::DO_EXERCISE, ExtClass::ConversationId::DO_STUDY
			};
			for each (int action in noTargetActions)
			{
				if (action == params[0].iVal) return Value(true);
			}
			return Value(false);
		}
		//bool(float)
		Value Thread::RollFloat(std::vector<Value>& params) {
			if (params[0].fVal <= 0.0) return Value(false);
			float roll = General::GetRandomFloat(0.0f, 1.0f);
			return Value(roll <= params[0].fVal);
		}
		//bool(int)
		Value Thread::RollInt(std::vector<Value>& params) {
			if (params[0].iVal <= 0) return Value(false);
			int range = 100;
			int roll = rand() % range + 1;
			return Value(roll <= params[0].iVal);
		}


		/*
		 * float stuff
		 */

		 //float (float min, float max)
		Value Thread::GetRandomFloat(std::vector<Value>& params) {
			return Value(General::GetRandomFloat(params[0].fVal, params[1].fVal));
		}

		Value Thread::AddFloats(std::vector<Value>& params) {
			return Value(params[0].fVal + params[1].fVal);
		}

		Value Thread::SubstractFloats(std::vector<Value>& params) {
			return Value(params[0].fVal - params[1].fVal);
		}

		Value Thread::DivideFloats(std::vector<Value>& params) {
			return Value(params[0].fVal / params[1].fVal);
		}

		Value Thread::MultiplyFloats(std::vector<Value>& params) {
			return Value(params[0].fVal * params[1].fVal);
		}

		Value Thread::Int2Float(std::vector<Value>& params) {
			float v = float(params[0].iVal);
			return Value(v);
		}
		//float(string)
		Value Thread::String2Float(std::vector<Value>& params) {
			float f = _wtof(params[0].strVal->c_str());
			if (errno == EINVAL)
			{
				return Value(TEXT("Conversion failed"));
			}
			return Value(f);
		}

		/*
		 * string stuff
		 */

		 //string(string, int, int)
		Value Thread::SubString(std::vector<Value>& params) {
			std::wstring& str = *params[0].strVal;
			int from = params[1].iVal;
			if (from < 0) from = str.size() - from;
			int length = params[2].iVal;
			if (length < 0) length = 0;

			return Value(str.substr(from, length));
		}

		//string(string, string)
		Value Thread::StringConcat(std::vector<Value>& params) {
			auto string1 = params[0].strVal;
			auto string2 = params[1].strVal;

			return Value(*string1 + *string2);
		}
		//string(int)
		Value Thread::IntToString(std::vector<Value>& params) {
			auto intVal = params[0].iVal;

			return Value(std::to_wstring(intVal));
		}
		//string(float)
		Value Thread::FloatToString(std::vector<Value>& params) {
			auto floatVal = params[0].fVal;

			return Value(std::to_wstring(floatVal));
		}
		//string(float)
		Value Thread::BoolToString(std::vector<Value>& params) {
			auto boolVal = params[0].bVal;

			return Value(std::to_wstring(boolVal));
		}
		//string(int from, int length, string newStr)
		Value Thread::StringReplace(std::vector<Value>& params) {
			std::wstring& str = *params[0].strVal;

			int from = params[1].iVal;
			if (from < 0) from = str.size() - from;

			int length = params[2].iVal;
			if (length < 0) length = 0;

			std::wstring newStr = *params[3].strVal;

			return Value(str.replace(from, length, newStr));
		}

		/*
		 * card attributes
		 */
		 //int(int)
		Value Thread::GetCardVirtue(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value(cardInst->m_char->m_charData->m_character.virtue);
		}

		//bool(int, int)
		Value Thread::GetCardTrait(std::vector<Value>& params) {
			int card = params[0].iVal;
			int trait = params[1].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value(cardInst->m_char->m_charData->m_traitBools[trait]);
		}

		//int(int)
		Value Thread::GetCardPersonality(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value(cardInst->m_char->m_charData->m_bPersonality);
		}

		//int(int)
		Value Thread::GetCardVoicePitch(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value(cardInst->m_char->m_charData->m_voicePitch);
		}

		//int(int)
		Value Thread::GetCardClub(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value(cardInst->m_char->m_charData->m_club);
		}

		//int(int)
		Value Thread::GetCardClubValue(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value((int)cardInst->m_char->m_charData->m_character.clubValue);
		}

		//int(int)
		Value Thread::GetCardClubRank(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value(cardInst->m_char->m_charData->m_character.clubClassRanking);
		}

		//int(int)
		Value Thread::GetCardIntelligence(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value(cardInst->m_char->m_charData->m_character.intelligence);
		}

		//int(int)
		Value Thread::GetCardIntelligenceValue(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value((int)cardInst->m_char->m_charData->m_character.intelligenceValue);
		}

		//int(int)
		Value Thread::GetCardIntelligenceRank(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value(cardInst->m_char->m_charData->m_character.intelligenceClassRank);
		}

		//int(int)
		Value Thread::GetCardStrength(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value(cardInst->m_char->m_charData->m_character.strength);
		}

		//int(int)
		Value Thread::GetCardStrengthValue(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value((int)cardInst->m_char->m_charData->m_character.strengthValue);
		}

		//int(int)
		Value Thread::GetCardStrengthRank(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value(cardInst->m_char->m_charData->m_character.strengthClassRank);
		}
		//int(int)
		Value Thread::GetCardSociability(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value(cardInst->m_char->m_charData->m_character.sociability);
		}

		//string(int)
		Value Thread::GetCardFirstName(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value(cardInst->m_char->m_charData->m_forename);
		}

		//string(int)
		Value Thread::GetCardSecondName(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value(cardInst->m_char->m_charData->m_surname);
		}

		//string(int)
		Value Thread::GetCardDescription(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(TEXT(""));

			return Value(cardInst->m_char->m_charData->m_description);
		}

		//int(int)
		Value Thread::GetCardPartnerCount(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(0);

			return Value((int)cardInst->m_char->m_characterStatus->m_partnerCount);

		}

		//int(int)
		Value Thread::GetCardOrientation(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(-1);

			return Value((int)cardInst->m_char->m_charData->m_character.orientation);
		}

		//float(int, int)
		Value Thread::GetCardOrientationMultiplier(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(0);

			int towards = params[0].iVal;
			CharInstData* towardsInst = &AAPlay::g_characters[towards];
			if (!towardsInst->IsValid()) return Value(0);

			float multiplier = 0.0;
			if (cardInst->m_char->m_charData->m_gender == towardsInst->m_char->m_charData->m_gender)
			{
				if (cardInst->m_char->m_charData->m_character.orientation >= 2) multiplier = 1.0;	//bi, lean homos, homos
				else if (cardInst->m_char->m_charData->m_character.orientation != 0) multiplier = 0.5;	//lean het
			}
			else
			{
				if (cardInst->m_char->m_charData->m_character.orientation <= 2) multiplier = 1.0;	//het, lean het, bi
				else if (cardInst->m_char->m_charData->m_character.orientation != 4) multiplier = 0.5;	//lean homo
			}

			return Value(multiplier);
		}

		//int(int)
		Value Thread::GetCardGender(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(0);

			return Value((int)cardInst->m_char->m_charData->m_gender);
		}

		//int(int,int)
		Value Thread::GetCardLovePoints(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(0);
			int cardTowards = params[1].iVal;
			CharInstData* towardsInst = &AAPlay::g_characters[cardTowards];
			if (!towardsInst->IsValid()) return Value(0);

			auto* relations = cardInst->m_char->GetRelations();
			auto* it = relations->m_start;
			for (it; it != relations->m_end; it++) {
				if (it->m_targetSeat == cardTowards) break;
			}
			if (it == relations->m_end) return Value(0);

			return Value(it->m_lovePoints + it->m_loveCount * 30);

		}

		//int(int,int)
		Value Thread::GetCardLikePoints(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(0);
			int cardTowards = params[1].iVal;
			CharInstData* towardsInst = &AAPlay::g_characters[cardTowards];
			if (!towardsInst->IsValid()) return Value(0);

			auto* relations = cardInst->m_char->GetRelations();
			auto* it = relations->m_start;
			for (it; it != relations->m_end; it++) {
				if (it->m_targetSeat == cardTowards) break;
			}
			if (it == relations->m_end) return Value(0);

			return Value(it->m_likePoints + it->m_likeCount * 30);
		}

		//int(int,int)
		Value Thread::GetCardDislikePoints(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(0);
			int cardTowards = params[1].iVal;
			CharInstData* towardsInst = &AAPlay::g_characters[cardTowards];
			if (!towardsInst->IsValid()) return Value(0);

			auto* relations = cardInst->m_char->GetRelations();
			auto* it = relations->m_start;
			for (it; it != relations->m_end; it++) {
				if (it->m_targetSeat == cardTowards) break;
			}
			if (it == relations->m_end) return Value(0);

			return Value(it->m_dislikePoints + it->m_dislikeCount * 30);
		}

		//int(int,int)
		Value Thread::GetCardHatePoints(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(0);
			int cardTowards = params[1].iVal;
			CharInstData* towardsInst = &AAPlay::g_characters[cardTowards];
			if (!towardsInst->IsValid()) return Value(0);

			auto* relations = cardInst->m_char->GetRelations();
			auto* it = relations->m_start;
			for (it; it != relations->m_end; it++) {
				if (it->m_targetSeat == cardTowards) break;
			}
			if (it == relations->m_end) return Value(0);

			return Value(it->m_hatePoints + it->m_hateCount * 30);
		}

		//bool(int,int)		 
		Value Thread::IsLover(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			if (!cardInst->IsValid()) return Value(0);
			int cardTowards = params[1].iVal;
			CharInstData* towardsInst = &AAPlay::g_characters[cardTowards];
			if (!towardsInst->IsValid()) return Value(0);

			return Value((bool)cardInst->m_char->m_lovers[cardTowards]);
		}

		//bool(int)
		Value Thread::GetHasLovers(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[card];
			if (!instance->IsValid()) {
				return Value(false);
			}
			else {
				for (int i = 0; i < 25; i++) {
					CharInstData* target = &AAPlay::g_characters[i];
					if (target->IsValid()) {
						if (instance->m_char->m_lovers[i]) return Value(true);
					}
				}
				return Value(false);
			}
		}

		//int(int)
		Value Thread::GetStrongestMood(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[card];
			if (!instance->IsValid()) {
				return Value(0);
			}
			auto moods1 = instance->m_char->GetMoods1();
			auto moods2 = instance->m_char->GetMoods2();
			DWORD moods[12] = {
				moods1[0],
				moods1[1],
				moods1[2],
				moods1[3],
				moods1[4],
				moods1[5],
				moods1[6],
				moods1[7],
				moods1[8],
				moods2[0],
				moods2[1],
				moods2[2]
			};
			int moodStrength[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

			for (int i = 0; i < 12; i++) {
				moodStrength[moods[i % 9]]++;
			}
			int strongestMood = 0;
			for (int i = 0; i < 9; i++) {
				if (moodStrength[i] > moodStrength[strongestMood]) strongestMood = i;
			}
			return Value(strongestMood);
		}

		//int(int card, int mood)
		Value Thread::GetMoodStrength(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[card];
			if (!instance->IsValid()) {
				return Value(0);
			}
			auto moods1 = instance->m_char->GetMoods1();
			auto moods2 = instance->m_char->GetMoods2();
			DWORD moods[12] = {
				moods1[0],
				moods1[1],
				moods1[2],
				moods1[3],
				moods1[4],
				moods1[5],
				moods1[6],
				moods1[7],
				moods1[8],
				moods2[0],
				moods2[1],
				moods2[2]
			};
			int moodStrength[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			for (int i = 0; i < 12; i++) {
				moodStrength[moods[i % 9]]++;
			}
			return Value(moodStrength[params[1].iVal % 9]);
		}

		//int(int, string, int)
		Value Thread::GetCardStorageInt(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* inst = &AAPlay::g_characters[card];
			if (!inst->IsValid()) return params[2];
			auto store = PersistentStorage::ClassStorage::getStorage(Shared::GameState::getCurrentClassSaveName());
			auto result = store.getCardInt(inst, *params[1].strVal);
			if (result.isValid) return Value(result.value);
			else return Value(params[2].iVal);
		}
		//float(int, string, float)
		Value Thread::GetCardStorageFloat(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* inst = &AAPlay::g_characters[card];
			if (!inst->IsValid()) return params[2];
			auto store = PersistentStorage::ClassStorage::getStorage(Shared::GameState::getCurrentClassSaveName());
			auto result = store.getCardFloat(inst, *params[1].strVal);
			if (result.isValid) return Value(result.value);
			else return Value(params[2].fVal);
		}
		//string(int, string, string)
		Value Thread::GetCardStorageString(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* inst = &AAPlay::g_characters[card];
			if (!inst->IsValid()) return params[2];

			auto store = PersistentStorage::ClassStorage::getStorage(Shared::GameState::getCurrentClassSaveName());
			auto result = store.getCardString(inst, *params[1].strVal);
			if (result.isValid) return Value(General::CastToWString(result.value));
			else return Value(*params[2].strVal);
		}
		//bool(int, string, bool)
		Value Thread::GetCardStorageBool(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* inst = &AAPlay::g_characters[card];
			if (!inst->IsValid()) return params[2];

			auto store = PersistentStorage::ClassStorage::getStorage(Shared::GameState::getCurrentClassSaveName());
			auto result = store.getCardBool(inst, *params[1].strVal);
			if (result.isValid) return Value(result.value);
			else return Value(params[2].bVal);
		}
		//int(int, int)
		Value Thread::GetPregnancyRisk(std::vector<Value>& params) {
			int card = params[0].iVal;
			int dayOfCycle = (params[1].iVal - 1) % 14; // 2 weeks cycle, first Monday is a 2nd day in DaysPassed but 1st index in pregnancyRisks, so -1
			CharInstData* inst = &AAPlay::g_characters[card];
			if (!inst->IsValid()) {
				return 3;
			}
			else {
				return inst->m_char->m_charData->m_pregnancyRisks[dayOfCycle];
			}
		}
		//int(int, int)
		Value Thread::GetSexCompatibility(std::vector<Value>& params) {
			int card = params[0].iVal;
			int target = params[1].iVal;
			CharInstData* cardInst = &AAPlay::g_characters[card];
			CharInstData* targetInst = &AAPlay::g_characters[target];
			
			if (!cardInst->IsValid() || !targetInst->IsValid()) {
				return 0;
			}
			else {
				return Value((int)cardInst->m_char->m_charData->m_hCompatibility[target]);
			}
		}

		//int(int)
		Value Thread::GetCurrentSyle(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* inst = &AAPlay::g_characters[card];
			if (!inst->IsValid()) {
				return Value(0);
			}
			else {
				return Value(inst->m_cardData.GetCurrAAUSet());
			}
		}

		//int(string)
		Value Thread::GetStyle(std::vector<Value>& params) {
			int seat = params[0].iVal;
			std::wstring* styleName = params[1].strVal;
			if (!AAPlay::g_characters[seat].m_char) {
				return Value(0);
			}
			return Value(AAPlay::g_characters[seat].m_cardData.FindStyleIdxByName(styleName));
		}
		
		//bool(int)
		Value Thread::GetSexExperience(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[card];
			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((bool)instance->m_char->m_charData->m_character.h_experience);
			}
		}

		//bool(int)
		Value Thread::GetAnalSexExperience(std::vector<Value>& params) {
			int card = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[card];
			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((bool)instance->m_char->m_charData->m_character.a_h_experience);
			}
		}

		//int(string)
		Value Thread::FindSeat(std::vector<Value>& params) {
			std::wstring* fullName = params[0].strVal;
			CharInstData* instance;
			for (int i = 0; i < 25; i++) {
				instance = &AAPlay::g_characters[i];
				if (!instance->IsValid()) {
					continue;
				}
				else {
					std::wstring iFullName;
					iFullName += *Value(instance->m_char->m_charData->m_forename).strVal;
					iFullName += L" ";
					iFullName += *Value(instance->m_char->m_charData->m_surname).strVal;
					if (iFullName == *fullName) return Value(i);
				}
			}
			return Value(-1);
		}

		//int(int)
		Value Thread::GetNpcStatus(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* inst = &AAPlay::g_characters[seat];
			if (!inst->IsValid())
			{
				return -1;
			}
			else
			{
				return Value((int)inst->m_char->m_characterStatus->m_npcStatus->m_status);
			}
		}

		//string(int)
		Value Thread::GetCardLastHPartner(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			if (!instance->IsValid()) {
				return Value("-");
			}
			else {
				return Value(instance->m_char->m_characterStatus->m_latestHPartner);
			}
		}
		//string(int)
		Value Thread::GetCardFirstHPartner(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			if (!instance->IsValid()) {
				return Value("-");
			}
			else {
				return Value(instance->m_char->m_characterStatus->m_firstHPartner);
			}
		}

		//string(int)
		Value Thread::GetCardFirstAnalPartner(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			if (!instance->IsValid()) {
				return Value("-");
			}
			else {
				return Value(instance->m_char->m_characterStatus->m_firstAnalPartner);
			}
		}

		//int(int)
		Value Thread::GetCardRejectCount(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((int)instance->m_char->m_characterStatus->m_rejectCount);
			}
		}

		//int(int)
		Value Thread::GetCardWinCount(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((int)instance->m_char->m_characterStatus->m_winningOverSomeoneCount);
			}
		}

		//int(int)
		Value Thread::GetCardVictoryCount(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((int)instance->m_char->m_characterStatus->m_victoryCount);
			}
		}

		//int(int)
		Value Thread::GetCardSkipCount(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((int)instance->m_char->m_characterStatus->m_classesSkipped);
			}
		}

		//int(int, int)
		Value Thread::GetCardCumStatInVagina(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			int target = params[1].iVal;
			CharInstData* targetInstance = &AAPlay::g_characters[target];

			if (!instance->IsValid() || !targetInstance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((int)instance->m_char->m_characterStatus->m_cumInVagina[target]);
			}
		}

		//int(int, int)
		Value Thread::GetCardCumStatInAnal(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			int target = params[1].iVal;
			CharInstData* targetInstance = &AAPlay::g_characters[target];

			if (!instance->IsValid() || !targetInstance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((int)instance->m_char->m_characterStatus->m_cumInAnal[target]);
			}
		}

		//int(int, int)
		Value Thread::GetCardCumStatInMouth(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			int target = params[1].iVal;
			CharInstData* targetInstance = &AAPlay::g_characters[target];

			if (!instance->IsValid() || !targetInstance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((int)instance->m_char->m_characterStatus->m_cumSwallowed[target]);
			}
		}

		//int(int)
		Value Thread::GetCardCumStatInVaginaTotal(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];

			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				int totalCums = 0;
				for (int i = 0; i < 25; i++)
				{
					if (i != seat && AAPlay::g_characters[i].IsValid())
					{
						totalCums += (int)instance->m_char->m_characterStatus->m_cumInVagina[i];
					}
				}
				return Value(totalCums);
			}
		}

		//int(int)
		Value Thread::GetCardCumStatInAnalTotal(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];

			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				int totalCums = 0;
				for (int i = 0; i < 25; i++)
				{
					if (i != seat && AAPlay::g_characters[i].IsValid())
					{
						totalCums += (int)instance->m_char->m_characterStatus->m_cumInAnal[i];
					}
				}
				return Value(totalCums);
			}
		}
		
		//int(int)
		Value Thread::GetCardCumStatInMouthTotal(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];

			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				int totalCums = 0;
				for (int i = 0; i < 25; i++)
				{
					if (i != seat && AAPlay::g_characters[i].IsValid())
					{
						totalCums += (int)instance->m_char->m_characterStatus->m_cumSwallowed[i];
					}
				}
				return Value(totalCums);
			}
		}

		//int(int, int)
		Value Thread::GetCardCumStatTotalCum(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			int target = params[1].iVal;
			CharInstData* targetInstance = &AAPlay::g_characters[target];

			if (!instance->IsValid() || !targetInstance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((int)instance->m_char->m_characterStatus->m_totalCum[target]);
			}
		}

		//int(int)
		Value Thread::GetCardCumStatTotalCumTotal(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];

			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				int totalCums = 0;
				for (int i = 0; i < 25; i++)
				{
					if (i != seat && AAPlay::g_characters[i].IsValid())
					{
						totalCums += (int)instance->m_char->m_characterStatus->m_totalCum[i];
					}
				}
				return Value(totalCums);
			}
		}

		//int(int, int)
		Value Thread::GetCardCumStatClimaxCount(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			int target = params[1].iVal;
			CharInstData* targetInstance = &AAPlay::g_characters[target];

			if (!instance->IsValid() || !targetInstance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((int)instance->m_char->m_characterStatus->m_climaxCount[target]);
			}
		}

		//int(int)
		Value Thread::GetCardCumStatClimaxCountTotal(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];

			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				int totalCums = 0;
				for (int i = 0; i < 25; i++)
				{
					if (i != seat && AAPlay::g_characters[i].IsValid())
					{
						totalCums += (int)instance->m_char->m_characterStatus->m_climaxCount[i];
					}
				}
				return Value(totalCums);
			}
		}

		//int(int, int)
		Value Thread::GetCardCumStatSimClimaxCount(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			int target = params[1].iVal;
			CharInstData* targetInstance = &AAPlay::g_characters[target];

			if (!instance->IsValid() || !targetInstance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((int)instance->m_char->m_characterStatus->m_simultaneousClimax[target]);
			}
		}

		//int(int)
		Value Thread::GetCardCumStatSimClimaxCountTotal(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];

			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				int totalCums = 0;
				for (int i = 0; i < 25; i++)
				{
					if (i != seat && AAPlay::g_characters[i].IsValid())
					{
						totalCums += (int)instance->m_char->m_characterStatus->m_simultaneousClimax[i];
					}
				}
				return Value(totalCums);
			}
		}

		//int(int, int)
		Value Thread::GetCardCumStatCondomsUsed(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			int target = params[1].iVal;
			CharInstData* targetInstance = &AAPlay::g_characters[target];

			if (!instance->IsValid() || !targetInstance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((int)instance->m_char->m_characterStatus->m_condomsUsed[target]);
			}
		}

		//int(int)
		Value Thread::GetCardCumStatCondomsUsedTotal(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];

			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				int totalCums = 0;
				for (int i = 0; i < 25; i++)
				{
					if (i != seat && AAPlay::g_characters[i].IsValid())
					{
						totalCums += (int)instance->m_char->m_characterStatus->m_condomsUsed[i];
					}
				}
				return Value(totalCums);
			}
		}

		//int(int)
		Value Thread::GetCardCumStatRiskyCums(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			int target = params[1].iVal;
			CharInstData* targetInstance = &AAPlay::g_characters[target];

			if (!instance->IsValid() || !targetInstance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((int)instance->m_char->m_characterStatus->m_riskyCum[target]);
			}
		}
		//int(int)
		Value Thread::GetCardCumStatRiskyCumsTotal(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];

			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				int totalCums = 0;
				for (int i = 0; i < 25; i++)
				{
					if (i != seat && AAPlay::g_characters[i].IsValid())
					{
						totalCums += (int)instance->m_char->m_characterStatus->m_riskyCum[i];
					}
				}
				return Value(totalCums);
			}
		}


		//int(int, int)
		Value Thread::GetCardVaginalSex(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			int target = params[1].iVal;
			CharInstData* targetInstance = &AAPlay::g_characters[target];

			if (!instance->IsValid() || !targetInstance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((int)instance->m_char->m_characterStatus->m_vaginalH[target]);
			}
		}

		//int(int)
		Value Thread::GetCardVaginalSexTotal(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];

			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				int totalCums = 0;
				for (int i = 0; i < 25; i++)
				{
					if (i != seat && AAPlay::g_characters[i].IsValid())
					{
						totalCums += (int)instance->m_char->m_characterStatus->m_vaginalH[i];
					}
				}
				return Value(totalCums);
			}
		}

		//int(int, int)
		Value Thread::GetCardAnalSex(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			int target = params[1].iVal;
			CharInstData* targetInstance = &AAPlay::g_characters[target];

			if (!instance->IsValid() || !targetInstance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((int)instance->m_char->m_characterStatus->m_analH[target]);
			}
		}

		//int(int)
		Value Thread::GetCardAnalSexTotal(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];

			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				int totalCums = 0;
				for (int i = 0; i < 25; i++)
				{
					if (i != seat && AAPlay::g_characters[i].IsValid())
					{
						totalCums += (int)instance->m_char->m_characterStatus->m_analH[i];
					}
				}
				return Value(totalCums);
			}
		}

		//int(int, int)
		Value Thread::GetCardAllSex(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			int target = params[1].iVal;
			CharInstData* targetInstance = &AAPlay::g_characters[target];

			if (!instance->IsValid() || !targetInstance->IsValid()) {
				return Value(0);
			}
			else {
				return Value((int)instance->m_char->m_characterStatus->m_totalH[target]);
			}
		}

		//int(int)
		Value Thread::GetCardAllSexTotal(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];

			if (!instance->IsValid()) {
				return Value(0);
			}
			else {
				int totalCums = 0;
				for (int i = 0; i < 25; i++)
				{
					if (i != seat && AAPlay::g_characters[i].IsValid())
					{
						totalCums += (int)instance->m_char->m_characterStatus->m_totalH[i];
					}
				}
				return Value(totalCums);
			}
		}

		//string(int)
		Value Thread::GetCardLoversItem(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			if (!instance->IsValid()) {
				return Value("");
			}
			else {
				return Value(instance->m_char->m_charData->m_item1);
			}
		}

		//string(int)
		Value Thread::GetCardFriendItem(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			if (!instance->IsValid()) {
				return Value("");
			}
			else {
				return Value(instance->m_char->m_charData->m_item2);
			}
		}

		//string(int)
		Value Thread::GetCardSexualItem(std::vector<Value>& params) {
			int seat = params[0].iVal;
			CharInstData* instance = &AAPlay::g_characters[seat];
			if (!instance->IsValid()) {
				return Value("");
			}
			else {
				return Value(instance->m_char->m_charData->m_item3);
			}
		}


		/*
		 * Event Response
		 */

		 //PERIOD_ENDS
		 //int()
		Value Thread::GetEndingPeriod(std::vector<Value>& params) {
			if (this->eventData->GetId() != PERIOD_ENDS) return Value(0);
			return ((PeriodEndsData*)eventData)->oldPeriod;
		}

		//int()
		Value Thread::GetStartingPeriod(std::vector<Value>& params) {
			if (this->eventData->GetId() != PERIOD_ENDS) return Value(0);
			return ((PeriodEndsData*)eventData)->newPeriod;
		}

		//bool()
		Value Thread::GetNpcResponseOriginalAnswer(std::vector<Value>& params) {
			if (this->eventData->GetId() != NPC_RESPONSE) return false;
			return ((NpcResponseData*)eventData)->originalResponse;
		}

		//bool()
		Value Thread::GetNpcResponseCurrentAnswer(std::vector<Value>& params) {
			if (this->eventData->GetId() != NPC_RESPONSE) return false;
			return ((NpcResponseData*)eventData)->changedResponse;
		}

		//int()
		Value Thread::GetNpcResponseTarget(std::vector<Value>& params) {
			if (this->eventData->GetId() != NPC_RESPONSE) return 0;
			return ((NpcResponseData*)eventData)->answeredTowards;
		}

		//int()
		Value Thread::GetNpcResponseConversation(std::vector<Value>& params) {
			if (this->eventData->GetId() != NPC_RESPONSE) return 0;
			return ((NpcResponseData*)eventData)->conversationId;
		}

		//int()
		Value Thread::GetNpcResponseOriginalPercent(std::vector<Value>& params) {
			if (this->eventData->GetId() != NPC_RESPONSE) return 0;
			return ((NpcResponseData*)eventData)->originalChance;
		}

		//int()
		Value Thread::GetNpcResponseCurrentPercent(std::vector<Value>& params) {
			if (this->eventData->GetId() != NPC_RESPONSE) return 0;
			return ((NpcResponseData*)eventData)->changedChance;
		}

		//NPC_WALK_TO_ROOM
		//int()
		Value Thread::GetNpcRoomTarget(std::vector<Value>& params) {
			if (this->eventData->GetId() != NPC_RESPONSE) return 0;
			return ((NpcResponseData*)eventData)->changedChance;
		}

		//int()
		Value Thread::GetNpcActionId(std::vector<Value>& params) {
			switch (this->eventData->GetId()) {
			case NPC_WANT_ACTION_NOTARGET:
				return ((NpcWantActionNoTargetData*)eventData)->action;
			case NPC_WANT_TALK_WITH:
				return ((NpcWantTalkWithData*)eventData)->action;
			case NPC_WANT_TALK_WITH_ABOUT:
				return ((NpcWantTalkWithAboutData*)eventData)->action;
				break;
			case PC_CONVERSATION_STATE_UPDATED:
				return ((PCConversationStateUpdatedData*)eventData)->action;
				break;
			default:
				return 0;
				break;
			}
		}


		//int()
		Value Thread::GetNpcTalkTarget(std::vector<Value>& params) {
			switch (this->eventData->GetId()) {
			case NPC_WANT_TALK_WITH:
				return ((NpcWantTalkWithData*)eventData)->conversationTarget;
			case NPC_WANT_TALK_WITH_ABOUT:
				return ((NpcWantTalkWithAboutData*)eventData)->conversationTarget;
				break;
			default:
				return 0;
				break;
			}
		}


		//int()
		Value Thread::GetNpcTalkAbout(std::vector<Value>& params) {
			switch (this->eventData->GetId()) {
			case NPC_WANT_TALK_WITH_ABOUT:
				return ((NpcWantTalkWithAboutData*)eventData)->conversationAbout;
				break;
			default:
				return 0;
				break;
			}
		}

		//int()
		Value Thread::GetConversationState(std::vector<Value>& params) {
			switch (this->eventData->GetId()) {
			case PC_CONVERSATION_STATE_UPDATED:
				return ((PCConversationStateUpdatedData*)eventData)->state;
				break;
			default:
				return 0;
				break;
			}
		}

		//int()
		Value Thread::GetConversationNpcResponse(std::vector<Value>& params) {
			switch (this->eventData->GetId()) {
			case PC_CONVERSATION_STATE_UPDATED:
				if (((PCConversationStateUpdatedData*)eventData)->npc_response >= 0) {
					return ((PCConversationStateUpdatedData*)eventData)->npc_response;
				}
				else return -1;
				break;
			default:
				return 0;
				break;
			}
		}

		//int(int idx)
		Value Thread::GetConversationActor(std::vector<Value>& params) {
			switch (this->eventData->GetId()) {
			case PC_CONVERSATION_STATE_UPDATED:
				if (Shared::GameState::getConversationCharacter(params[0].iVal))
					return Shared::GameState::getConversationCharacter(params[0].iVal)->m_seat;
				else return -1;
				break;
			default:
				return 0;
				break;
			}
		}

		//int()
		Value Thread::GetConversationPcResponse(std::vector<Value>& params) {
			switch (this->eventData->GetId()) {
			case PC_CONVERSATION_STATE_UPDATED:
				if (((PCConversationStateUpdatedData*)eventData)->pc_response >= 0) {
					return ((PCConversationStateUpdatedData*)eventData)->pc_response;
				}
				else return Value(-1);
				break;
			default:
				return 0;
				break;
			}
		}

		//int()
		Value Thread::GetConversationAction(std::vector<Value>& params) {
			switch (this->eventData->GetId()) {
			case PC_CONVERSATION_STATE_UPDATED:
				return Value(((PCConversationStateUpdatedData*)this->eventData)->action);
				break;
			default:
				return 0;
				break;
			}
		}

		//int()
		Value Thread::GetConversationAnswerId(std::vector<Value>& params) {
			switch (this->eventData->GetId()) {
			case PC_CONVERSATION_STATE_UPDATED:
				return Value(((PCConversationStateUpdatedData*)this->eventData)->conversationAnswerId);
				break;
			default:
				return 0;
				break;
			}
		}

		//int()
		Value Thread::GetConversationCurrentlyAnswering(std::vector<Value>& params) {
			switch (this->eventData->GetId()) {
			case PC_CONVERSATION_STATE_UPDATED:
				return Value(((PCConversationStateUpdatedData*)this->eventData)->currentlyAnswering);
				break;
			default:
				return 0;
				break;
			}
		}

		//int()
		Value Thread::GetEventID(std::vector<Value>& params) {
			return Value(this->eventData->GetId());
		}

		std::wstring g_ExpressionCategories[EXPRCAT_N] = {
			TEXT("General"),
			TEXT("Event Response"),
			TEXT("Math"),
			TEXT("Character Property"),
			TEXT("Comparision - Int"),
			TEXT("Comparision - String"),
			TEXT("Comparision - Bool"),
			TEXT("Comparision - Float"),
			TEXT("AAU Styles"),
			TEXT("Conversation"),
			TEXT("Strings")
		};


		/*
		 * Note that the first two expressions for each Type are handled specially as they represent variables and constants.
		 */
		std::vector<Expression> g_Expressions[N_TYPES] = {
			{ //INVALID
				{
					EXPR_CONSTANT, EXPRCAT_GENERAL,
					TEXT("Constant"), TEXT("Constant"), TEXT("An arbitrary constant to input"),
					{}, (TYPE_INVALID),
					NULL
				},
				{
					EXPR_VAR, EXPRCAT_GENERAL,
					TEXT("Variable"), TEXT("Variable"), TEXT("A Variable"),
					{}, (TYPE_INVALID),
					NULL
				},
				{
					EXPR_NAMEDCONSTANT, EXPRCAT_GENERAL,
					TEXT("Enumeration"), TEXT("Enumeration"), TEXT("A known constant with a name"),
					{}, (TYPE_INVALID),
					NULL
				},
			},
			{ //INT
				{
					EXPR_CONSTANT, EXPRCAT_GENERAL,
					TEXT("Constant"), TEXT("Constant"), TEXT("An arbitrary constant to input"),
					{ }, (TYPE_INT),
					NULL
				},
				{
					EXPR_VAR, EXPRCAT_GENERAL,
					TEXT("Variable"), TEXT("Variable"), TEXT("A Variable"),
					{ }, (TYPE_INT),
					NULL
				},
				{
					EXPR_NAMEDCONSTANT, EXPRCAT_GENERAL,
					TEXT("Enumeration"), TEXT("Enumeration"), TEXT("A known constant with a name"),
					{}, (TYPE_INT),
					NULL
				},
				{
					4, EXPRCAT_MATH,
					TEXT("Random Int"), TEXT("RandomInt(min: %p , max: %p )"), TEXT("Generates a random integer between the two arguments (including both)"),
					{(TYPE_INT), (TYPE_INT)}, (TYPE_INT),
					&Thread::GetRandomInt
				},
				{
					EXPR_INT_PLUS, EXPRCAT_MATH,
					TEXT("+"), TEXT("%p + %p"), TEXT("Adds two integers"),
					{ (TYPE_INT), (TYPE_INT) }, (TYPE_INT),
					&Thread::AddIntegers
				},
				{
					6, EXPRCAT_MATH,
					TEXT("-"), TEXT("%p - %p"), TEXT("Substracts two integers"),
					{ (TYPE_INT), (TYPE_INT) }, (TYPE_INT),
					&Thread::SubstractIntegers
				},
				{
					7, EXPRCAT_MATH,
					TEXT("/"), TEXT("%p / %p"), TEXT("Divide two integers"),
					{ (TYPE_INT), (TYPE_INT) }, (TYPE_INT),
					&Thread::DivideIntegers
				},
				{
					8, EXPRCAT_MATH,
					TEXT("*"), TEXT("%p * %p"), TEXT("Multiply two integers"),
					{ (TYPE_INT), (TYPE_INT) }, (TYPE_INT),
					&Thread::MultiplyIntegers
				},
				{
					9, EXPRCAT_EVENT,
					TEXT("Triggering Card"), TEXT("TriggerCard"), TEXT("The card that triggered the event that caused the trigger to run. "
					"Used by many events."),
					{  }, (TYPE_INT),
					&Thread::GetTriggeringCard
				},
				{
					10, EXPRCAT_EVENT,
					TEXT("This Card"), TEXT("ThisCard"), TEXT("The card to whom this trigger belongs to"),
					{}, (TYPE_INT),
					&Thread::GetThisCard
				},
				{
					11, EXPRCAT_EVENT,
					TEXT("Npc Answer - Target"), TEXT("AnswerTarget"), TEXT("In a NPC Answered event, the character the NPC answered to."),
					{}, (TYPE_INT),
					&Thread::GetNpcResponseTarget
				},
				{
					12, EXPRCAT_EVENT,
					TEXT("Npc Answer - Conversation"), TEXT("ConversationId"), TEXT("The Type of Question the NPC answered in a NPC Answered event."),
					{}, (TYPE_INT),
					&Thread::GetNpcResponseConversation
				},
				{
					13, EXPRCAT_EVENT,
					TEXT("Npc Room Target"), TEXT("RoomTarget"), TEXT("Room that the Npc Walks to in a Npc Walks to Room event."),
					{}, (TYPE_INT),
					&Thread::GetNpcRoomTarget
				},
				{
					14, EXPRCAT_EVENT,
					TEXT("Npc Action"), TEXT("ActionId"), TEXT("The Type of Action an Npc Wants to Perform in a no-target-action event, or the conversation "
					"id in the targeted actions."),
					{}, (TYPE_INT),
					&Thread::GetNpcActionId
				},
				{
					15, EXPRCAT_EVENT,
					TEXT("Npc Talk Target"), TEXT("TalkTarget"), TEXT("In a Npc Talk With, or Npc Talk With About event, this is the character the Npc talks with."),
					{}, (TYPE_INT),
					&Thread::GetNpcTalkTarget
				},
				{
					16, EXPRCAT_EVENT,
					TEXT("Npc Talk About"), TEXT("TalkAbout"), TEXT("In a Npc Talk With About event, this is the character the Npc talks about."),
					{}, (TYPE_INT),
					&Thread::GetNpcTalkAbout
				},
				{
					17, EXPRCAT_EVENT,
					TEXT("Period - Starting"), TEXT("StartPeriod"), TEXT("In a Period Ends Event, this is the new period starting."),
					{}, (TYPE_INT),
					&Thread::GetStartingPeriod
				},
				{
					18, EXPRCAT_EVENT,
					TEXT("Period - Ending"), TEXT("EndPeriod"), TEXT("In a Period Ends Event, this is the old period that ended."),
					{}, (TYPE_INT),
					&Thread::GetEndingPeriod
				},
				{
					19, EXPRCAT_CHARPROP,
					TEXT("Love Points"), TEXT("%p ::LOVE(towards: %p )"), TEXT("The total sum of love points. This includes the love history, "
					"where each entry translates to 30 points, but which are limited to 30 history entrys (=900 points) across all 4 categories, as well as "
					"single points, that have not added up to 30 and were therefor not converted to love history yet."),
					{ TYPE_INT, TYPE_INT }, (TYPE_INT),
					&Thread::GetCardLovePoints
				},
				{
					20, EXPRCAT_CHARPROP,
					TEXT("Like Points"), TEXT("%p ::LIKE(towards: %p )"), TEXT("The total sum of like points. This includes the like history, "
					"where each entry translates to 30 points, but which are limited to 30 history entrys (=900 points) across all 4 categories, as well as "
					"single points, that have not added up to 30 and were therefor not converted to like history yet."),
					{ TYPE_INT, TYPE_INT }, (TYPE_INT),
					&Thread::GetCardLikePoints
				},
				{
					21, EXPRCAT_CHARPROP,
					TEXT("Dislike Points"), TEXT("%p ::DISLIKE(towards: %p )"), TEXT("The total sum of dislike points. This includes the dislike history, "
					"where each entry translates to 30 points, but which are limited to 30 history entrys (=900 points) across all 4 categories, as well as "
					"single points, that have not added up to 30 and were therefor not converted to dislike history yet."),
					{ TYPE_INT, TYPE_INT }, (TYPE_INT),
					&Thread::GetCardDislikePoints
				},
				{
					22, EXPRCAT_CHARPROP,
					TEXT("Hate Points"), TEXT("%p ::HATE(towards: %p )"), TEXT("The total sum of hate points. This includes the hate history, "
					"where each entry translates to 30 points, but which are limited to 30 history entrys (=900 points) across all 4 categories, as well as "
					"single points, that have not added up to 30 and were therefor not converted to hate history yet."),
					{ TYPE_INT, TYPE_INT }, (TYPE_INT),
					&Thread::GetCardHatePoints
				},
				{
					23, EXPRCAT_MATH,
					TEXT("Float to Int"), TEXT("Int( %p )"), TEXT("Converts a Float to an Int by cutting off the decimals."),
					{ TYPE_FLOAT }, (TYPE_INT),
					&Thread::Float2Int
				},
				{
					24, EXPRCAT_CHARPROP,
					TEXT("Get Card Storage Int"), TEXT("%p ::GetInt(key: %p , default: %p )"),
					TEXT("Gets the integer from the given cards storage entry. If the entry doesnt exist or holds a value of a different type, "
					"it returns the default value instead"),
					{ TYPE_INT, TYPE_STRING, TYPE_INT }, (TYPE_INT),
					&Thread::GetCardStorageInt
				},
				{
					25, EXPRCAT_CHARPROP,
					TEXT("Virtue"), TEXT("%p ::Virtue"), TEXT("The virtue of this character."
					" 0 = Lowest ... 4 = Highest"),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardVirtue
				},
				{
					26, EXPRCAT_CHARPROP,
					TEXT("Personality"), TEXT("%p ::Personality"), TEXT("The personalityId of this character."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardPersonality
				},
				{
					27, EXPRCAT_CHARPROP,
					TEXT("Voice Pitch"), TEXT("%p ::Pitch"), TEXT("The voice pitch of this character."
					" 0 = Lowest ... 4 = Highest"),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardVoicePitch
				},
				{
					28, EXPRCAT_CHARPROP,
					TEXT("Club"), TEXT("%p ::Club"), TEXT("The clubId of this character."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardClub
				},
				{
					29, EXPRCAT_CHARPROP,
					TEXT("Club Value"), TEXT("%p ::ClubValue"), TEXT("The club value of this character."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardClubValue
				},
				{
					30, EXPRCAT_CHARPROP,
					TEXT("Club Rank"), TEXT("%p ::ClubRank"), TEXT("The club rank of this character."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardClubRank
				},
				{
					31, EXPRCAT_CHARPROP,
					TEXT("Intelligence"), TEXT("%p ::Intelligence"), TEXT("The intelligence of this character."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardIntelligence
				},
				{
					32, EXPRCAT_CHARPROP,
					TEXT("Intelligence Value"), TEXT("%p ::IntelligenceValue"), TEXT("The intelligence value of this character."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardIntelligenceValue
				},
				{
					33, EXPRCAT_CHARPROP,
					TEXT("Intelligence Rank"), TEXT("%p ::IntelligenceRank"), TEXT("The intelligence rank of this character."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardIntelligenceRank
				},
				{
					34, EXPRCAT_CHARPROP,
					TEXT("Strength"), TEXT("%p ::Strength"), TEXT("The strength of this character."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardStrength
				},
				{
					35, EXPRCAT_CHARPROP,
					TEXT("Strength Value"), TEXT("%p ::StrengthValue"), TEXT("The strength value of this character."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardStrengthValue
				},
				{
					36, EXPRCAT_CHARPROP,
					TEXT("Strength Rank"), TEXT("%p ::StrengthRank"), TEXT("The strength rank of this character."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardStrengthRank
				},
				{
					37, EXPRCAT_CHARPROP,
					TEXT("Sociability"), TEXT("%p ::Sociability"), TEXT("The sociability of this character."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardSociability
				},
				{
					38, EXPRCAT_CHARPROP,
					TEXT("Partners count"), TEXT("%p ::PartnersCount"), TEXT("The sexual partners count of this character."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardPartnerCount
				},
				{
					39, EXPRCAT_EVENT,
					TEXT("Npc Original Response Chance"), TEXT("OriginalResponsePercent"),
					TEXT("If executed in a trigger with the Npc Answers Event, this is displayed success chance that the interaction had in percents."),
					{}, (TYPE_INT),
					&Thread::GetNpcResponseOriginalPercent
				},
				{
					40, EXPRCAT_EVENT,
					TEXT("Npc Current Response Chance"), TEXT("CurrentResponsePercent"),
					TEXT("If executed in a trigger with the Npc Answers Event, this is the current interaction percent, modified by this or previously executed triggers "
					"using the Set Npc Response Percent Action"),
					{}, (TYPE_INT),
					&Thread::GetNpcResponseCurrentPercent
				},
				{
					41, EXPRCAT_CHARPROP,
					TEXT("Sex Orientation"), TEXT("%p ::Orientation"),
					TEXT("The sexual orientation of this character. 0 = Straight, 1 = Lean Straight , 2 = Bisexual , 3 = Lean Homo, 4 = Homo"),
					{TYPE_INT}, (TYPE_INT),
					&Thread::GetCardOrientation
				},
				{
					42, EXPRCAT_STRINGS,
					TEXT("String Length"), TEXT("Length( %p )"), TEXT("Retrieves the length of the given string"),
					{ TYPE_STRING }, (TYPE_INT),
					&Thread::StrLength
				},
				{
					43, EXPRCAT_STRINGS,
					TEXT("First Index Of"), TEXT("%p ::FirstIndexOf( str: %p )"), TEXT("Retrieves the first occurence of str string."),
					{ TYPE_STRING, TYPE_STRING }, (TYPE_INT),
					&Thread::FirstIndexOf
				},
				{
					44, EXPRCAT_MATH,
					TEXT("String to Int"), TEXT("Int( %p )"), TEXT("Converts a String to an Int."),
					{ TYPE_STRING }, (TYPE_INT),
					&Thread::String2Int
				},
				{
					45, EXPRCAT_STRINGS,
					TEXT("First Index Of Starting At"), TEXT("%p ::FirstIndexOf( str: %p , from: %p )"), TEXT("Retrieves the first occurence of str string starting from from: index."),
					{ TYPE_STRING, TYPE_STRING, TYPE_INT }, (TYPE_INT),
					&Thread::FirstIndexOfFrom
				},
				{
					46, EXPRCAT_CHARPROP,
					TEXT("Gender"), TEXT("%p ::Gender"), TEXT("Character's gender. 0 means Male, 1 means Female. No tumblr here."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardGender
				},
				{
					47, EXPRCAT_GENERAL,
					TEXT("Days Passed"), TEXT("DaysPassed"), TEXT("Days passed from the beginning of the save."),
					{}, (TYPE_INT),
					&Thread::GetDaysPassed
				},
				{
					48, EXPRCAT_GENERAL,
					TEXT("Current Day"), TEXT("CurrentDay"), TEXT("0=Sunday, 1=Monday... 6=Saturday."),
					{}, (TYPE_INT),
					&Thread::GetCurrentDay
				},
				{
					49, EXPRCAT_GENERAL,
					TEXT("Current Period"), TEXT("CurrentPeriod"), TEXT("10 = sleep, 1 = day, 2 = nothing to talk, 3 = first lesson,4 = first break, 5 = sports, 6 = second break, 7 = club, 8 = end, 9 = home again"),
					{}, (TYPE_INT),
					&Thread::GetCurrentPeriod
				},
				{
					50, EXPRCAT_CHARPROP,
					TEXT("Pregnancy Risk"), TEXT("%p ::PregnancyRisk(day: %p )"), TEXT("Pregnancy risk of %p character at %p day. 2 = dangerous, 1 = safe, 0 = normal"),
					{ (TYPE_INT), (TYPE_INT) }, (TYPE_INT),
					&Thread::GetPregnancyRisk
				},
				{
					51, EXPRCAT_CHARPROP,
					TEXT("Current Style"), TEXT("%p ::Style"), TEXT("Currently used Style."),
					{ (TYPE_INT) }, (TYPE_INT),
					&Thread::GetCurrentSyle
				},
				{
					52, EXPRCAT_CONVERSATION,
					TEXT("State"), TEXT("ConversationState"), TEXT("Current conversation state."),
					{}, (TYPE_INT),
					&Thread::GetConversationState
				},
				{
					53, EXPRCAT_CONVERSATION,
					TEXT("Actor"), TEXT("Actor:: %p "), TEXT("Conversation actor, listed from left to right."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetConversationActor
				},
				{
					54, EXPRCAT_CONVERSATION,
					TEXT("NPC Response"), TEXT("NPC Response"), TEXT("Returns NPC response in a conversation. 0 is \"Yes\", 1 is \"No\", 2 is \"Huh?\", -1 is undefined."),
					{}, (TYPE_INT),
					&Thread::GetConversationNpcResponse
				},
				{
					55, EXPRCAT_GENERAL,
					TEXT("Player Character"), TEXT("PC"), TEXT("Currently controlled character's seat."),
					{}, (TYPE_INT),
					&Thread::GetPC
				},
				{
					56, EXPRCAT_GENERAL,
					TEXT("Find Seat"), TEXT("Seat( %p )"), TEXT("Find a character with the provided full name(last name first name). Returns -1 if no such character is found"),
					{ TYPE_STRING }, (TYPE_INT),
					&Thread::FindSeat
				},
				{
					57, EXPRCAT_CHARPROP,
					TEXT("Reject Count"), TEXT("%p ::Rejects"), TEXT("Returns how many times this character was rejected."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardRejectCount
				},
				{
					58, EXPRCAT_CHARPROP,
					TEXT("Win Count"), TEXT("%p ::Wins"), TEXT("Returns how many times this character won when competing over someone."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardWinCount
				},
				{
					59, EXPRCAT_CHARPROP,
					TEXT("Victory Count"), TEXT("%p ::Victories"), TEXT("Returns how many times this character won in a fight."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardVictoryCount
				},
				{
					60, EXPRCAT_CHARPROP,
					TEXT("Skip Count"), TEXT("%p ::Skips"), TEXT("Returns how many times this character skipped a class."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardSkipCount
				},
				{
					61, EXPRCAT_CONVERSATION,
					TEXT("PC Response"), TEXT("PC Response"), TEXT("Returns PC response in a conversation. 0 is \"Yes\", 1 is \"No\", 2 is \"Huh?\", -1 is undefined."),
					{}, (TYPE_INT),
					&Thread::GetConversationPcResponse
				},
				{
					62, EXPRCAT_CONVERSATION,
					TEXT("Conversation ID"), TEXT("PC ConversationId"), TEXT("Returns conversationID of the PC conversation."),
					{}, (TYPE_INT),
					&Thread::GetConversationAction
				},
				{
					63, EXPRCAT_GENERAL,
					TEXT("Event ID"), TEXT("Event"), TEXT("Returns EventId."),
					{}, (TYPE_INT),
					&Thread::GetEventID
				},
				{
					64, EXPRCAT_CHARPROP,
					TEXT("Find Style"), TEXT("%p ::Style( %p )"), TEXT("Find Style index by name."),
					{ (TYPE_INT), TYPE_STRING }, (TYPE_INT),
					&Thread::GetStyle
				},
				{
					65, EXPRCAT_CHARPROP,
					TEXT("Get Mood Strength"), TEXT("%p ::Mood( %p )"), TEXT("Get mood strength for the chosen mood."),
					{ (TYPE_INT), TYPE_INT }, (TYPE_INT),
					&Thread::GetMoodStrength
				},
				{
					66, EXPRCAT_CHARPROP,
					TEXT("Get Strongest Mood"), TEXT("%p ::Mood"), TEXT("Get the most prevalent mood."),
					{ (TYPE_INT) }, (TYPE_INT),
					&Thread::GetStrongestMood
				},
				{
					67, EXPRCAT_CHARPROP,
					TEXT("Get H compatibility"), TEXT("%p ::Compatibility( %p )"), TEXT("Get compatibility with the selected character"),
					{ TYPE_INT, TYPE_INT }, (TYPE_INT),
					&Thread::GetSexCompatibility
				},
				{
					68, EXPRCAT_CHARPROP,
					TEXT("Get NPC Status"), TEXT("%p ::NpcStatus"), TEXT("Get NPC status of the character. Returns -1=invalid, 0=still, 1=settle in location, 2=move to location, 3=walk to character, 4=follow, 7=talk, 8=minna"),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetNpcStatus
				},
				{
					69, EXPRCAT_CONVERSATION,
					TEXT("Answer Action"), TEXT("AnswerId"), TEXT("After the npc made a positive or negative answer, this id will be what he answers with."),
					{}, (TYPE_INT),
					&Thread::GetConversationAnswerId
				},
				{
					70, EXPRCAT_CONVERSATION,
					TEXT("Is Answering"), TEXT("IsAnswering"), TEXT("�\\_(�*-*`)_/�"),
					{}, (TYPE_INT),
					&Thread::GetConversationCurrentlyAnswering
				},
				{
					71, EXPRCAT_CHARPROP,
					TEXT("Cum Stat - Vaginal"), TEXT("%p ::VaginalCums( %p )"), TEXT("Returns how many times this character got cummed inside their vagina by the other character."),
					{ TYPE_INT, TYPE_INT }, (TYPE_INT),
					&Thread::GetCardCumStatInVagina
				},
				{
					72, EXPRCAT_CHARPROP,
					TEXT("Cum Stat - Anal"), TEXT("%p ::AnalCums( %p )"), TEXT("Returns how many times this character got cummed inside their rectum by the other character."),
					{ TYPE_INT, TYPE_INT }, (TYPE_INT),
					&Thread::GetCardCumStatInAnal
				},
				{
					73, EXPRCAT_CHARPROP,
					TEXT("Cum Stat - Oral"), TEXT("%p ::OralCums( %p )"), TEXT("Returns how many times this character got cummed inside their mouth by the other character."),
					{ TYPE_INT, TYPE_INT }, (TYPE_INT),
					&Thread::GetCardCumStatInMouth
				},
				{
					74, EXPRCAT_CHARPROP,
					TEXT("Cum Stat - Total Vaginal"), TEXT("%p ::VaginalCumsTotal"), TEXT("Returns how many times this character got cummed inside their vagina."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardCumStatInVaginaTotal
				},
				{
					75, EXPRCAT_CHARPROP,
					TEXT("Cum Stat - Total Anal"), TEXT("%p ::AnalCumsTotal"), TEXT("Returns how many times this character got cummed inside their rectum."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardCumStatInAnalTotal
				},
				{
					76, EXPRCAT_CHARPROP,
					TEXT("Cum Stat - Total Oral"), TEXT("%p ::OralCumsTotal"), TEXT("Returns how many times this character got cummed inside their mouth."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardCumStatInMouthTotal
				},
				{
					77, EXPRCAT_CHARPROP,
					TEXT("Cum Stat - All"), TEXT("%p ::AllCums( %p )"), TEXT("Returns how many times this character got cummed inside by the other character."),
					{ TYPE_INT, TYPE_INT }, (TYPE_INT),
					&Thread::GetCardCumStatTotalCum
				},
				{
					78, EXPRCAT_CHARPROP,
					TEXT("Cum Stat - Total All"), TEXT("%p ::AllCumsTotal"), TEXT("Returns how many times this character got cummed inside."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardCumStatTotalCumTotal
				},
				{
					79, EXPRCAT_CHARPROP,
					TEXT("Climax Stat - Single"), TEXT("%p ::SingleClimax( %p )"), TEXT("Returns how many times this character climaxed while having sex with the other character."),
					{ TYPE_INT, TYPE_INT }, (TYPE_INT),
					&Thread::GetCardCumStatClimaxCount
				},
				{
					80, EXPRCAT_CHARPROP,
					TEXT("Climax Stat - Total Single"), TEXT("%p ::SingleClimaxTotal"), TEXT("Returns how many times this character climaxed while having sex."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardCumStatClimaxCountTotal
				},
				{
					81, EXPRCAT_CHARPROP,
					TEXT("Climax Stat - Simultaneous"), TEXT("%p ::SimClimax( %p )"), TEXT("Returns how many times this character climaxed together with the other character."),
					{ TYPE_INT, TYPE_INT }, (TYPE_INT),
					&Thread::GetCardCumStatClimaxCount
				},
				{
					82, EXPRCAT_CHARPROP,
					TEXT("Climax Stat - Total Simultaneous"), TEXT("%p ::SimClimaxTotal"), TEXT("Returns how many times this character climaxed together with everyone."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardCumStatClimaxCountTotal
				},
				{
					83, EXPRCAT_CHARPROP,
					TEXT("H Stat - Condoms Used"), TEXT("%p ::CondomsUsed( %p )"), TEXT("Returns how many times this character used condoms with the other character."),
					{ TYPE_INT, TYPE_INT }, (TYPE_INT),
					&Thread::GetCardCumStatCondomsUsed
				},
				{
					84, EXPRCAT_CHARPROP,
					TEXT("H Stat - Total Condoms Used"), TEXT("%p ::CondomsUsedTotal"), TEXT("Returns how many times this character used condoms."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardCumStatCondomsUsedTotal
				},
				{
					85, EXPRCAT_CHARPROP,
					TEXT("H Stat - Vaginal"), TEXT("%p ::VaginalH( %p )"), TEXT("Returns how many times this character had vaginal sex with the other character."),
					{ TYPE_INT, TYPE_INT }, (TYPE_INT),
					&Thread::GetCardVaginalSex
				},
				{
					86, EXPRCAT_CHARPROP,
					TEXT("H Stat - Total Vaginal"), TEXT("%p ::VaginalHTotal"), TEXT("Returns how many times this character had vaginal sex."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardVaginalSexTotal
				},
				{
					87, EXPRCAT_CHARPROP,
					TEXT("H Stat - Anal"), TEXT("%p ::VaginalH( %p )"), TEXT("Returns how many times this character had anal sex with the other character."),
					{ TYPE_INT, TYPE_INT }, (TYPE_INT),
					&Thread::GetCardAnalSex
				},
				{
					88, EXPRCAT_CHARPROP,
					TEXT("H Stat - Total Anal"), TEXT("%p ::AnalHTotal"), TEXT("Returns how many times this character had anal sex."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardAnalSexTotal
				},
				{
					89, EXPRCAT_CHARPROP,
					TEXT("H Stat - All"), TEXT("%p ::AllH( %p )"), TEXT("Returns how many times this character had sex with the other character."),
					{ TYPE_INT, TYPE_INT }, (TYPE_INT),
					&Thread::GetCardAllSex
				},
				{
					90, EXPRCAT_CHARPROP,
					TEXT("H Stat - Total All"), TEXT("%p ::AllHTotal"), TEXT("Returns how many times this character had sex."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardAllSexTotal
				},
				{
					91, EXPRCAT_CHARPROP,
					TEXT("Cum Stat - Risky"), TEXT("%p ::RiskyCums( %p )"), TEXT("Returns how many times this character got cummed inside on their risky days by the other character."),
					{ TYPE_INT, TYPE_INT }, (TYPE_INT),
					&Thread::GetCardCumStatRiskyCums
				},
				{
					92, EXPRCAT_CHARPROP,
					TEXT("Cum Stat - Total Risky"), TEXT("%p ::RiskyCumsTotal"), TEXT("Returns how many times this character got cummed inside on their risky days."),
					{ TYPE_INT }, (TYPE_INT),
					&Thread::GetCardCumStatRiskyCumsTotal
				},
			},

			{ //BOOL
				{
					EXPR_CONSTANT, EXPRCAT_GENERAL,
					TEXT("Constant"), TEXT("Constant"), TEXT("An arbitrary constant to input"),
					{}, (TYPE_BOOL),
					NULL
				},
				{
					EXPR_VAR, EXPRCAT_GENERAL,
					TEXT("Variable"), TEXT("Variable"), TEXT("A Variable"),
					{}, (TYPE_BOOL),
					NULL
				},
				{
					EXPR_NAMEDCONSTANT, EXPRCAT_GENERAL,
					TEXT("Enumeration"), TEXT("Enumeration"), TEXT("A known constant with a name"),
					{}, (TYPE_BOOL),
					NULL
				},
				{
					4,EXPRCAT_COMPARISION_BOOL,
					TEXT("Logical And"),TEXT("%p && %p"),TEXT("Logical and, including short-circut evaluation"),
					{ TYPE_BOOL, TYPE_BOOL },(TYPE_BOOL),
					NULL
				},
				{
					5, EXPRCAT_COMPARISION_BOOL,
					TEXT("Logical Or"),TEXT("%p || %p"), TEXT("Logical or, including short-circut evaluation"),
					{ TYPE_BOOL, TYPE_BOOL }, (TYPE_BOOL),
					NULL
				},
				{
					6, EXPRCAT_COMPARISION_INT,
					TEXT("Greater Than"), TEXT("%p > %p"), TEXT("Greater-Than"),
					{ TYPE_INT, TYPE_INT }, (TYPE_BOOL),
					&Thread::GreaterThanIntegers
				},
				{
					EXPR_BOOL_GTE_INT, EXPRCAT_COMPARISION_INT,
					TEXT("Greater Than or Equal"), TEXT("%p >= %p"), TEXT("Greater-Than or equal"),
					{ TYPE_INT, TYPE_INT }, (TYPE_BOOL),
					&Thread::GreaterEqualsIntegers
				},
				{
					8, EXPRCAT_COMPARISION_INT,
					TEXT("Equal"), TEXT("%p == %p"), TEXT("Equal"),
					{ TYPE_INT, TYPE_INT }, (TYPE_BOOL),
					&Thread::EqualsIntegers
				},
				{
					9, EXPRCAT_COMPARISION_INT,
					TEXT("Less Than or Equal"), TEXT("%p <= %p"), TEXT("less than or equal"),
					{ TYPE_INT, TYPE_INT }, (TYPE_BOOL),
					&Thread::LessEqualsIntegers
				},
				{
					10, EXPRCAT_COMPARISION_INT,
					TEXT("Less Than"), TEXT("%p < %p"), TEXT("less than"),
					{ TYPE_INT, TYPE_INT }, (TYPE_BOOL),
					&Thread::LessThanIntegers
				},
				{
					EXPR_BOOL_NOT, EXPRCAT_COMPARISION_BOOL,
					TEXT("Not"), TEXT("! %p"), TEXT("Logical Not"),
					{ TYPE_BOOL }, (TYPE_BOOL),
					&Thread::BoolNot
				},
				{
					12, EXPRCAT_COMPARISION_STRING,
					TEXT("String - Equal"), TEXT("%p == %p"), TEXT("Compares two strings"),
					{ TYPE_STRING, TYPE_STRING }, (TYPE_BOOL),
					&Thread::EqualsStrings
				},
				{
					13, EXPRCAT_COMPARISION_INT,
					TEXT("Not Equal"), TEXT("%p != %p"), TEXT("Not Equal"),
					{ TYPE_INT, TYPE_INT }, (TYPE_BOOL),
					&Thread::NotEqualsIntegers
				},
				{
					14, EXPRCAT_EVENT,
					TEXT("Npc Original Response"), TEXT("OriginalResponse"),
					TEXT("If executed in a trigger with the Npc Answers Event, this is the original Answer the NPC made"),
					{ }, (TYPE_BOOL),
					&Thread::GetNpcResponseOriginalAnswer
				},
				{
					15, EXPRCAT_EVENT,
					TEXT("Npc Current Response"), TEXT("CurrentResponse"),
					TEXT("If executed in a trigger with the Npc Answers Event, this is the current Answer, modified by this or previously executed Triggers. "
					"using the Set Npc Response Answer Action"),
					{ }, (TYPE_BOOL),
					&Thread::GetNpcResponseCurrentAnswer
				},
				{
					16, EXPRCAT_CHARPROP,
					TEXT("Is Seat Filled"), TEXT("%p ::IsSeatFilled"),
					TEXT("Whether the given Seat has a character behind it. Characters are identified using their seat number. Use this in a loop through all seats "
					"do determine if a character exists or not."),
					{ TYPE_INT }, (TYPE_BOOL),
					&Thread::IsSeatFilled
				},
				{
					17, EXPRCAT_CHARPROP,
					TEXT("Is Lover"), TEXT("%p ::HasLover( %p )"),
					TEXT("True if the characters are currently in a relationship. (technically, it checks if the first parameter is in a relationship with the second)"),
					{ TYPE_INT, TYPE_INT }, (TYPE_BOOL),
					&Thread::IsLover
				},
				{
					18,EXPRCAT_COMPARISION_FLOAT,
					TEXT("Greater Than"),TEXT("%p > %p"),TEXT("Greater-Than"),
					{ TYPE_FLOAT, TYPE_FLOAT },(TYPE_BOOL),
					&Thread::GreaterThanFloats
				},
				{
					19, EXPRCAT_COMPARISION_FLOAT,
					TEXT("Greater Than or Equal"), TEXT("%p >= %p"), TEXT("Greater-Than or equal"),
					{ TYPE_FLOAT, TYPE_FLOAT }, (TYPE_BOOL),
					&Thread::GreaterEqualsFloats
				},
				{
					20, EXPRCAT_COMPARISION_FLOAT,
					TEXT("Equal"), TEXT("%p == %p"), TEXT("Equal"),
					{ TYPE_FLOAT, TYPE_FLOAT }, (TYPE_BOOL),
					&Thread::EqualsFloats
				},
				{
					21, EXPRCAT_COMPARISION_FLOAT,
					TEXT("Less Than or Equal"), TEXT("%p <= %p"), TEXT("less than or equal"),
					{ TYPE_FLOAT, TYPE_FLOAT }, (TYPE_BOOL),
					&Thread::LessEqualsFloats
				},
				{
					22, EXPRCAT_COMPARISION_FLOAT,
					TEXT("Less Than"), TEXT("%p < %p"), TEXT("less than"),
					{ TYPE_FLOAT, TYPE_FLOAT }, (TYPE_BOOL),
					&Thread::LessThanFloats
				},
				{
					23, EXPRCAT_COMPARISION_FLOAT,
					TEXT("Not Equal"), TEXT("%p != %p"), TEXT("not equal"),
					{ TYPE_FLOAT, TYPE_FLOAT }, (TYPE_BOOL),
					&Thread::NotEqualsFloats
				},
				{
					24, EXPRCAT_CHARPROP,
					TEXT("Get Card Storage Bool"), TEXT("%p ::GetBool(key: %p , default: %p )"),
					TEXT("Gets the integer from the given cards storage entry. If the entry doesnt exist or holds a value of a different type, "
					"it returns the default value instead"),
					{ TYPE_INT, TYPE_STRING, TYPE_BOOL }, (TYPE_BOOL),
					&Thread::GetCardStorageBool
				},
				{
					25, EXPRCAT_CHARPROP,
					TEXT("Trait"), TEXT("%p ::Trait( %p )"), TEXT(""),
					{ TYPE_INT, TYPE_INT }, (TYPE_BOOL),
					&Thread::GetCardTrait
				},
				{
					26, EXPRCAT_GENERAL,
					TEXT("Check Interruption Action"), TEXT("%p ::isInterrupt"), TEXT("Returs true if INTERRUPT_COMPETE, INTERRUPT_STOP_QUARREL, INTERRUPT_WHAT_ARE_YOU_DOING, H_END, H_NOTE, BREAK_CHAT, BREAK_H"),
					{ TYPE_INT }, (TYPE_BOOL),
					&Thread::IsInterruptAction
				},
				{
					27, EXPRCAT_GENERAL,
					TEXT("Check Minna Action"), TEXT("%p ::isMinna"), TEXT("Returs true if MINNA_BE_FRIENDLY, MINNA_CLUB, MINNA_COME, MINNA_EAT, MINNA_H, MINNA_KARAOKE, MINNA_LUNCH, MINNA_REST, MINNA_SPORTS, MINNA_STUDY"),
					{ TYPE_INT }, (TYPE_BOOL),
					&Thread::IsMinnaAction
				},
				{
					28, EXPRCAT_GENERAL,
					TEXT("Check Force Action"), TEXT("%p ::isForce"), TEXT("Returns true if FIGHT, FORCE_H, FORCE_IGNORE, FORCE_PUT_THIS_ON, FORCE_SHOW_THAT, INSULT, SLAP"),
					{ TYPE_INT }, (TYPE_BOOL),
					&Thread::IsForceAction
				},
				{
					29, EXPRCAT_GENERAL,
					TEXT("Check Sex Action"), TEXT("%p ::isSex"), TEXT("Returns true if FOLLOW_ME_H, FORCE_H, MINNA_H, NORMAL_H, NO_PROMPT_H, SKIP_CLASS_H, SKIP_CLASS_SURPRISE_H, STUDY_HOME_H, LEWD_REWARD"),
					{ TYPE_INT }, (TYPE_BOOL),
					&Thread::IsSexAction
				},
				{
					30, EXPRCAT_GENERAL,
					TEXT("Check NoPrompt Action"), TEXT("%p ::isNoPrompt"), TEXT("Returns true if EXPLOITABLE_LINE, FORCE_BREAKUP, GOOD_BYE_KISS, GOOD_MORNING_KISS, I_SAW_SOMEONE_HAVE_H, I_WILL_CHEAT, MURDER, MURDER_NOTICE, NEVERMIND, NO_PROMPT_H, NO_PROMPT_KISS, REVEAL_PREGNANCY, SHAMELESS, SLAP, SOMEONE_GOT_CONFESSED_TO, SOMEONE_LIKES_YOU, STOP_FOLLOWING, TOGETHER_FOREVER"),
					{ TYPE_INT }, (TYPE_BOOL),
					&Thread::IsNoPromptAction
				},
				{
					31, EXPRCAT_GENERAL,
					TEXT("Check Game Over Action"), TEXT("%p ::isGameOver"), TEXT("Returns true if MURDER, REVEAL_PREGNANCY, TOGETHER_FOREVER"),
					{ TYPE_INT }, (TYPE_BOOL),
					&Thread::IsGameOverAction
				},
				{
					32, EXPRCAT_GENERAL,
					TEXT("Check No Target Action"), TEXT("%p ::isNoTarget"), TEXT("Returns true if CHANGE_CLOTHES, DO_CLUB, DO_EXERCISE, DO_STUDY"),
					{ TYPE_INT }, (TYPE_BOOL),
					&Thread::IsNoTargetAction
				},
				{
					33, EXPRCAT_MATH,
					TEXT("Roll Float"), TEXT("Roll( %p )"), TEXT("Generates a random [0.0, 1.0] float value and if it's less than or equal to the provided argument returns true. Arguments over 1.0 always roll success"),
					{ TYPE_FLOAT }, (TYPE_BOOL),
					&Thread::RollFloat
				},
				{
					34, EXPRCAT_MATH,
					TEXT("Roll Int"), TEXT("Roll( %p )"), TEXT("Generates a random [1, 100] integer value and if it's less than or equal to the provided argument returns true. Arguments over 100 always roll success"),
					{ TYPE_INT }, (TYPE_BOOL),
					&Thread::RollInt
				},
				{
					35, EXPRCAT_CHARPROP,
					TEXT("Sex Experience: Vaginal"), TEXT("%p ::SexXP"), TEXT("Returns true if the character is not a virgin."),
					{ TYPE_INT }, (TYPE_BOOL),
					&Thread::GetSexExperience
				},
				{
					36, EXPRCAT_CHARPROP,
					TEXT("Sex Experience: Anal"), TEXT("%p ::AnalXP"), TEXT("Returns true if the character is not an anal virgin."),
					{ TYPE_INT }, (TYPE_BOOL),
					&Thread::GetAnalSexExperience
				},
				{
					37, EXPRCAT_CHARPROP,
					TEXT("Has Lovers"), TEXT("%p ::HasLovers"), TEXT("Returns true if the character is in at least one rleationship."),
					{ TYPE_INT }, (TYPE_BOOL),
					&Thread::GetHasLovers
				},
			},
			{ //FLOAT
				{
					EXPR_CONSTANT, EXPRCAT_GENERAL,
					TEXT("Constant"), TEXT("Constant"), TEXT("An arbitrary constant to input"),
					{}, (TYPE_FLOAT),
					NULL
				},
				{
					EXPR_VAR, EXPRCAT_GENERAL,
					TEXT("Variable"), TEXT("Variable"), TEXT("A Variable"),
					{}, (TYPE_FLOAT),
					NULL
				},
				{
					EXPR_NAMEDCONSTANT, EXPRCAT_GENERAL,
					TEXT("Enumeration"), TEXT("Enumeration"), TEXT("A known constant with a name"),
					{}, (TYPE_FLOAT),
					NULL
				},
				{
					4, EXPRCAT_MATH,
					TEXT("Random Float"), TEXT("RandomFloat(min: %p , max: %p )"), TEXT("Generates a random float between the two arguments (including both)"),
					{ (TYPE_FLOAT), (TYPE_FLOAT) }, (TYPE_FLOAT),
					&Thread::GetRandomFloat
				},
				{
					EXPR_INT_PLUS, EXPRCAT_MATH,
					TEXT("+"), TEXT("%p + %p"), TEXT("Adds two floats"),
					{ (TYPE_FLOAT), (TYPE_FLOAT) }, (TYPE_FLOAT),
					&Thread::AddFloats
				},
				{
					6, EXPRCAT_MATH,
					TEXT("-"), TEXT("%p - %p"), TEXT("Substracts two floats"),
					{ (TYPE_FLOAT), (TYPE_FLOAT) }, (TYPE_FLOAT),
					&Thread::SubstractFloats
				},
				{
					7, EXPRCAT_MATH,
					TEXT("/"), TEXT("%p / %p"), TEXT("Divide two floats"),
					{ (TYPE_FLOAT), (TYPE_FLOAT) }, (TYPE_FLOAT),
					&Thread::DivideFloats
				},
				{
					8, EXPRCAT_MATH,
					TEXT("*"), TEXT("%p * %p"), TEXT("Multiply two floats"),
					{ (TYPE_FLOAT), (TYPE_FLOAT) }, (TYPE_FLOAT),
					&Thread::MultiplyFloats
				},
				{
					9, EXPRCAT_MATH,
					TEXT("Int to Float"), TEXT("Float( %p )"), TEXT("Converts an Int to Float"),
					{ TYPE_INT }, (TYPE_FLOAT),
					&Thread::Int2Float
				},
				{
					10,EXPRCAT_CHARPROP,
					TEXT("Get Card Storage Float"),TEXT("%p ::GetFloat(key: %p , default: %p )"),
					TEXT("Gets the integer from the given cards storage entry. If the entry doesnt exist or holds a value of a different type, "
					"it returns the default value instead"),
					{ TYPE_INT, TYPE_STRING, TYPE_FLOAT },(TYPE_FLOAT),
						&Thread::GetCardStorageFloat
				},
				{
					11, EXPRCAT_MATH,
					TEXT("String to Float"), TEXT("Float( %p )"), TEXT("Converts a String to a Float."),
					{ TYPE_STRING }, (TYPE_FLOAT),
					&Thread::String2Float
				},
				{
					12, EXPRCAT_CHARPROP,
					TEXT("Sex Orientation Multiplier"), TEXT("%p ::OrientationMultiplier(towards: %p )"),
					TEXT("The multiplier used when calculating interaction chances depending on actors' sex orientations and genders. Returns either 1.0, 0.5 or 0.0"),
					{ TYPE_INT, TYPE_INT }, (TYPE_FLOAT),
					&Thread::GetCardOrientationMultiplier
				},
			},
			{ //STRING
				{
					EXPR_CONSTANT, EXPRCAT_GENERAL,
					TEXT("Constant"), TEXT("Constant"), TEXT("An arbitrary constant to input"),
					{}, (TYPE_STRING),
					NULL
				},
				{
					EXPR_VAR, EXPRCAT_GENERAL,
					TEXT("Variable"), TEXT("Variable"), TEXT("A Variable"),
					{}, (TYPE_STRING),
					NULL
				},
				{
					EXPR_NAMEDCONSTANT, EXPRCAT_GENERAL,
					TEXT("Enumeration"), TEXT("Enumeration"), TEXT("A known constant with a name"),
					{}, (TYPE_STRING),
					NULL
				},
				{
					4, EXPRCAT_STRINGS,
					TEXT("Substring"), TEXT("%p ::Substring(startIdx: %p , length: %p )"), TEXT("A substring that starts at the first parameter (inclusive) and has "
					"a specific length"),
					{TYPE_STRING, TYPE_INT, TYPE_INT}, (TYPE_STRING),
					&Thread::SubString
				},
				{
					5, EXPRCAT_CHARPROP,
					TEXT("Last Name"), TEXT("%p ::LastName"), TEXT("The first name this character was given (the upper one on the default card image). "
					"Note that this may or may not be the family name depending on how the card maker ordered these."),
					{  TYPE_INT }, (TYPE_STRING),
						&Thread::GetCardFirstName
				},
				{
					6, EXPRCAT_CHARPROP,
					TEXT("First Name"), TEXT("%p ::FirstName"), TEXT("The second name this character was given (the lower one on the default card image). "
					"Note that this may or may not be the family name depending on how the card maker ordered these."),
					{ TYPE_INT }, (TYPE_STRING),
						&Thread::GetCardSecondName
				},
				{
					7, EXPRCAT_CHARPROP,
					TEXT("Get Card Storage String"), TEXT("%p ::GetStr(key: %p , default: %p )"),
					TEXT("Gets the integer from the given cards storage entry. If the entry doesnt exist or holds a value of a different type, "
					"it returns the default value instead"),
					{ TYPE_INT, TYPE_STRING, TYPE_STRING }, (TYPE_STRING),
						&Thread::GetCardStorageString
				},
				{
					8, EXPRCAT_CHARPROP,
					TEXT("+"), TEXT("%p + %p"), TEXT("Concatenate two strings"),
					{ (TYPE_STRING), (TYPE_STRING) }, (TYPE_STRING),
					&Thread::StringConcat
				},
				{
					9, EXPRCAT_MATH,
					TEXT("Int to String"), TEXT("String( %p )"), TEXT("Converts an Int to String"),
					{ (TYPE_INT) }, (TYPE_STRING),
					&Thread::IntToString
				},
				{
					10, EXPRCAT_MATH,
					TEXT("Float to String"), TEXT("String( %p )"), TEXT("Converts a Float to String"),
					{ (TYPE_FLOAT) }, (TYPE_STRING),
					&Thread::FloatToString
				},
				{
					11, EXPRCAT_MATH,
					TEXT("Bool to String"), TEXT("String( %p )"), TEXT("Converts a Bool to String"),
					{ (TYPE_BOOL) }, (TYPE_STRING),
					&Thread::BoolToString
				},
				{
					12, EXPRCAT_CHARPROP,
					TEXT("Description"), TEXT("%p ::Description"), TEXT("This character's description"),
					{ TYPE_INT }, (TYPE_STRING),
					&Thread::GetCardDescription
				},
				{
					13, EXPRCAT_STRINGS,
					TEXT("Replace substring"), TEXT("%p ::Replace( from: %p , to: %p , str: %p )"), TEXT("Replace substring starting from the from: and ending with to:"),
					{ TYPE_INT, TYPE_INT, TYPE_INT, TYPE_STRING }, (TYPE_STRING),
					&Thread::StringReplace
				},
				{
					14, EXPRCAT_CHARPROP,
					TEXT("Last Sex Partner"), TEXT("%p ::LastSex"), TEXT("Returns the full name of the last sex partner as it appears on the character sheet."),
					{ TYPE_INT }, (TYPE_STRING),
					&Thread::GetCardLastHPartner
				},
				{
					15, EXPRCAT_CHARPROP,
					TEXT("First Sex Partner"), TEXT("%p ::FirstSex"), TEXT("Returns the full name of the first sex partner as it appears on the character sheet."),
					{ TYPE_INT }, (TYPE_STRING),
					&Thread::GetCardFirstHPartner
				},
				{
					16, EXPRCAT_CHARPROP,
					TEXT("First Anal Partner"), TEXT("%p ::FirstSex"), TEXT("Returns the full name of the first sex partner as it appears on the character sheet."),
					{ TYPE_INT }, (TYPE_STRING),
					&Thread::GetCardFirstAnalPartner
				},
				{
					17, EXPRCAT_CHARPROP,
					TEXT("Item - Lover's"), TEXT("%p ::LoverItem"), TEXT("Returns the Lover's item"),
					{ TYPE_INT }, (TYPE_STRING),
					&Thread::GetCardLoversItem
				},
				{
					18, EXPRCAT_CHARPROP,
					TEXT("Item - Friend's"), TEXT("%p ::FriendItem"), TEXT("Returns the Friend's item"),
					{ TYPE_INT }, (TYPE_STRING),
					&Thread::GetCardFriendItem
				},
				{
					19, EXPRCAT_CHARPROP,
					TEXT("Item - Sexual"), TEXT("%p ::SexualItem"), TEXT("Returns the Sexual item"),
					{ TYPE_INT }, (TYPE_STRING),
					&Thread::GetCardSexualItem
				},
			}

		};



		ParameterisedExpression::ParameterisedExpression(Types type, DWORD exprId, const std::vector<ParameterisedExpression>& params) : ParameterisedExpression() {
			this->expression = Expression::FromId(type, exprId);
			this->actualParameters = params;
		}
		ParameterisedExpression::ParameterisedExpression(Types type, Value constant) : ParameterisedExpression() {
			this->expression = Expression::FromId(type, EXPR_CONSTANT);
			this->constant = constant;
		}
		ParameterisedExpression::ParameterisedExpression(Types type, std::wstring var) : ParameterisedExpression() {
			this->expression = Expression::FromId(type, EXPR_VAR);
			this->varName = var;
		}



	}
}