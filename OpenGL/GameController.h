#pragma once

#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

class GameController
{
public:
	GameController();
	~GameController();

	void Initialize();
	void RunGame();
	void MoveResIterator();
	void MoveCamIterator();

	Shader* shader = nullptr;
	Mesh* mesh = nullptr;
	Camera* camera = nullptr;

	std::vector<Resolution> resOptions;
	std::vector<Resolution>::iterator resIt;

	std::vector<Camera> camOptions;
	std::vector<Camera>::iterator camIt;

};

#endif

