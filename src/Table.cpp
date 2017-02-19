#include "Table.h"


using namespace basicgraphics;

Table::Table():
	box(Box(vec3(0, 0, 0), vec3(5, 5, 5), vec4(1, 1, 1, 1)))
{
}


Table::~Table()
{
}

void Table::draw(basicgraphics::GLSLProgram & shader, const glm::mat4 & modelMatrix)
{
	box.draw(shader, modelMatrix);
}
