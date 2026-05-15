// ITHub 2026


#include "SandboxGameModeBase.h"
#include "SandboxPawnBase.h"

ASandboxGameModeBase::ASandboxGameModeBase()
{
	DefaultPawnClass = ASandboxPawnBase::StaticClass();
}
