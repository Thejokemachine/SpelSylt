#include "GameJamGame/Gameplay/Controller/AIController.h"

#include "GameJamGame/Gameplay/World/WorldProbe.h"

#include "GameJamGame/Gameplay/Tree/Tree.h"
#include "GameJamGame/Gameplay/Pawn.h"

#include "GameJamGame/Gameplay/World/ProbeConstructor.h"

#include <SpelSylt/Math/CommonMath.h>


//------------------------------------------------------------------

using namespace tree;

//------------------------------------------------------------------

CAIController::CAIController()
	: Probe(CProbeConstructor::ConstructProbe())
	, OwningPawn(nullptr)
	, Direction(0.f, 0.f)
	, Target(0.f, 0.f)
{
	Probe.AddFilter<CTree>();
}

//------------------------------------------------------------------

void CAIController::RegisterPawn(const CPawn& InPawn) const
{
	OwningPawn = &InPawn;
}

//------------------------------------------------------------------

void CAIController::Update()
{
	Probe.ProbeForData();

	const sf::Vector2f& ControlledPawnPosition = OwningPawn->GetPosition();

	Probe.ForEachProbed([this, &ControlledPawnPosition](const SWorldObject & InProbedObject) {
		Direction = InProbedObject.Position - ControlledPawnPosition;
		});

	Math::Normalize(Direction);
}

//------------------------------------------------------------------

const sf::Vector2f& CAIController::GetDirection() const
{
	return Direction;
}

//------------------------------------------------------------------

const sf::Vector2f& CAIController::GetTarget() const
{
	return Target;
}

//------------------------------------------------------------------
