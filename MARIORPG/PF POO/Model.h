#pragma once
#include <string>
#include "glm.h"
#include "BMPLoader.h"
using namespace std;

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
