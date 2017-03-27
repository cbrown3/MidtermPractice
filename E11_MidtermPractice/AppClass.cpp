#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma endregion
#pragma region FEEL FREE TO USE THIS CLOCK
	//Calculate delta and total times
	static double dTotalTime = 0.0; //Total time of the simulation
	double dDeltaTime = m_pSystem->LapClock(); //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 
#pragma endregion
#pragma region YOUR CODE GOES HERE

	vector3 locs[] = 
	{
		vector3(0.0f, 0.0f, 0.0f),
		vector3(0.0f, 5.0f, 0.0f),
		vector3(0.0f, 0.0f, 0.0f)
	};

	vector3 v3From = vector3();
	vector3 v3To = vector3();
	float percentage = MapValue((float)dTotalTime, 0.0f, 1.0f, 0.0f, 0.2f);

	static int indexer = 0;

	v3From = locs[indexer];

	v3To = locs[indexer + 1];

	if (percentage > 1.0f)
	{
		dTotalTime = 0.0f;
		indexer++;
	}
	if (indexer >= 2)
	{
		v3From = locs[indexer];
		indexer = 0;
		v3To = locs[indexer];
	}
	vector3 v3Current = glm::lerp(v3From, v3To, percentage);
	m_m4Steve = glm::translate(v3Current);

	//the distance from the center
	matrix4 steveDistance = glm::translate(0.0f, 1.0f, 0.0f);

	//orbiting around the center
	matrix4 steveRotation = glm::rotate(IDENTITY_M4, (float)(dTotalTime)*72.0f, vector3(0.0f, 0.0f, 1.0f));

	//m_m4Steve = m_m4Steve * steveDistance;

	m_m4Steve = m_m4Steve * steveRotation;

#pragma endregion
#pragma region DOES NOT NEED CHANGES
	//Set the model matrix
	m_pMeshMngr->SetModelMatrix(m_m4Steve, "Steve");
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("Seconds:");
	m_pMeshMngr->PrintLine(std::to_string(dTotalTime), RERED);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}
