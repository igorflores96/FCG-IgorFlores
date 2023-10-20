#include "Sprite.h"

class GameManager
{
protected:
	
	int keys;
	int widht, height;

public:
	

	
	Sprite background, character, mazeWall;
	Shader shader;
	void StartGame();
	void Draw();
	void Update();
	int SetupTexture(string filePath, int& width, int& height);
};

