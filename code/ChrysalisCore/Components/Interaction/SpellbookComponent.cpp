#include <StdAfx.h>

#include "SpellbookComponent.h"
#include <CryCore/StaticInstanceList.h>
#include "CrySchematyc/Env/Elements/EnvComponent.h"
#include "CrySchematyc/Env/IEnvRegistrar.h"
#include "Components/Player/PlayerComponent.h"


namespace Chrysalis
{
static void RegisterSpellbookComponent(Schematyc::IEnvRegistrar& registrar)
{
	Schematyc::CEnvRegistrationScope scope = registrar.Scope(IEntity::GetEntityScopeGUID());
	{
		Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(CSpellbookComponent));
		// Functions
		{
		}
	}
}


void CSpellbookComponent::ReflectType(Schematyc::CTypeDesc<CSpellbookComponent>& desc)
{
	desc.SetGUID(CSpellbookComponent::IID());
	desc.SetEditorCategory("Actors");
	desc.SetLabel("Spellbook");
	desc.SetDescription("Allow interaction with spells for this entity.");
	desc.SetIcon("icons:ObjectTypes/light.ico");

	desc.SetComponentFlags({IEntityComponent::EFlags::Singleton});

	// Keep a collection of spells available for use.
	desc.AddMember(&CSpellbookComponent::m_spellCollection, 'spcl', "SpellCollection", "Spell Collection", "List of spells which may be cast.", SSpellCollection {});
}


// ***
// *** IEntityComponent
// ***


void CSpellbookComponent::Initialize()
{
}


// ***
// *** CSpellbookComponent
// ***


void CSpellbookComponent::AddInteraction(IInteractionPtr interaction)
{
	m_Interactions.push_back(interaction);
}


void CSpellbookComponent::RemoveInteraction(string verb)
{
	m_Interactions.erase(std::remove_if(m_Interactions.begin(), m_Interactions.end(),
		[&](IInteractionPtr i) { return i->GetVerb().compare(verb) == 0; }),
		m_Interactions.end());
}


std::vector<string> CSpellbookComponent::GetVerbs(bool includeHidden)
{
	std::vector<string> verbs;

	for (auto& it : m_Interactions)
	{
		if (it->IsEnabled())
		{
			if ((!it->IsHidden()) || ((it->IsHidden()) && includeHidden))
			{
				verbs.push_back(it->GetVerb());
			}
		}
	}

	return verbs;
}


IInteractionWeakPtr CSpellbookComponent::GetInteraction(string verb)
{
	for (auto& it : m_Interactions)
	{
		if ((it->GetVerb().compare(verb) == 0) && (it->IsEnabled()))
		{
			return it;
		}
	}

	CryLogAlways("There's no interaction verb for %s", verb.c_str());

	return std::weak_ptr<IInteraction>();
}


IInteractionWeakPtr CSpellbookComponent::SelectInteractionVerb(string verb)
{
	for (auto& it : m_Interactions)
	{
		if ((it->GetVerb().compare(verb) == 0) && (it->IsEnabled()))
		{
			m_selectedInteraction = it;
			return it;
		}
	}

	return std::weak_ptr<IInteraction>();
}


void CSpellbookComponent::ClearInteractionVerb()
{
	m_selectedInteraction = nullptr;
}


void CSpellbookComponent::OnInteractionStart(IActor& actor)
{
	CRY_ASSERT_MESSAGE(m_selectedInteraction, "Be sure to set an interaction before attempting to call it.");
	m_selectedInteraction->OnInteractionStart(actor);
}


void CSpellbookComponent::OnInteractionTick(IActor& actor)
{
	CRY_ASSERT_MESSAGE(m_selectedInteraction, "Be sure to set an interaction before attempting to call it.");
	m_selectedInteraction->OnInteractionTick(actor);
}


void CSpellbookComponent::OnInteractionComplete(IActor& actor)
{
	CRY_ASSERT_MESSAGE(m_selectedInteraction, "Be sure to set an interaction before attempting to call it.");
	m_selectedInteraction->OnInteractionComplete(actor);
}

CRY_STATIC_AUTO_REGISTER_FUNCTION(&RegisterSpellbookComponent)
}