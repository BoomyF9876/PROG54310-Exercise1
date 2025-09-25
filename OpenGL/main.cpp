#include "StandardIncludes.h"
#include "GameController.h"

int main()
{
	GameController* gameController = new GameController();
	gameController->Initialize();
	gameController->RunGame();
}
