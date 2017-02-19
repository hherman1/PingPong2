#pragma once
#include "Box.h"
#include "GLSLProgram.h"
class Table
{
public:
	Table();
	~Table();
	basicgraphics::Box box;
	virtual void draw(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix);

};

