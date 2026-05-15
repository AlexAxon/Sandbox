// ITHub 2026


#include "SandboxGameModeBase.h"
#include "SandboxPawnBase.h"
#include "SandboxPlayerControllerBase.h"

ASandboxGameModeBase::ASandboxGameModeBase()
{
	DefaultPawnClass = ASandboxPawnBase::StaticClass();
	PlayerControllerClass = ASandboxPlayerControllerBase::StaticClass();
}
