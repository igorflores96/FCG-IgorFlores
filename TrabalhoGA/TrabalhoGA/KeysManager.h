#include "Sprite.h"

class KeysManager
{
protected:
	int keysQuantity = 0;

public:

	void AddKey();
	inline void ResetKeys() { keysQuantity = 0; }
	bool CheckColision(Sprite& key, Sprite &character);
	bool CanOpenGate();
};

