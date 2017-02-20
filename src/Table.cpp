#include "Table.h"



using namespace basicgraphics;

Table::Table():
box(Box(vec3(-(TABLE_WIDTH*60)/2, TABLE_HEIGHT, -(TABLE_LENGTH*35)), vec3((TABLE_WIDTH*60)/2, TABLE_TOP*5, (TABLE_LENGTH*60)/2), vec4(0, 1, 0, 1)))
{
}


Table::~Table()
{
}

void Table::draw(basicgraphics::GLSLProgram & shader, const glm::mat4 & modelMatrix)
{
    box.draw(shader, modelMatrix);
}
