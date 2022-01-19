#pragma once
#include <string>
using namespace std;
#include "glm.h"
#include "BMPLoader.h"

namespace EDXFramework {

class Model {
public:
	Model(string modelPath, string texturePath, bool mode);
	virtual ~Model();
	void Draw();
private:
	GLMmodel* model;
	BMPClass texture;
	unsigned int textureId;
	unsigned int drawMode;
};

}
