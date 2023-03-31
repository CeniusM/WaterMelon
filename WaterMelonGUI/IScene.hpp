#include "SDL.h"

class IScene
{
public:
	IScene();
	~IScene();

	virtual void Update();
	virtual void Render();


private:

};

IScene::IScene()
{
}

IScene::~IScene()
{
}