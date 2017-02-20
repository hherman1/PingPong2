#include "Ball.h"
#include "Table.h"

using namespace basicgraphics;
using namespace glm;

Ball::Ball() :
	_sphere(vec3(0, 0, 0), BALL_RADIUS*100, vec4(1, 1, 1, 1)),
	pos(0, (TABLE_TOP*100) + 0.5, 0),
	dir(0, 0, 0)
{
}


Ball::~Ball()
{
}

void Ball::draw(basicgraphics::GLSLProgram & shader, const glm::mat4 & modelMatrix)
{
	glm::mat4 model = modelMatrix * translate(mat4(1.0f), pos);
	_sphere.draw(shader, model);
}

void Ball::update(std::chrono::milliseconds ms)
{
	float seconds = ms.count() / 1000.0f;
	dir = dir + vec3(0, -9.8*seconds,0);
	pos = pos + (seconds*dir) +  dir * (0.5f * seconds * seconds);
	if (pos.y < TABLE_TOP*5 + BALL_RADIUS*100) {
        if (abs(pos.z) > TABLE_LENGTH*60 + BALL_RADIUS*100){
            dir.y = (0.9f);
            dir.z = 0.0;
        } else {
            pos.y = TABLE_TOP*5 + BALL_RADIUS*100;
            dir.y = dir.y * (-0.9f);
        }

    }
}

void Ball::launch()
{
	pos = vec3(0, (TABLE_TOP*100) + (BALL_RADIUS*100) + 0.5, -(TABLE_LENGTH*60) / 2);
	dir = vec3(0, 0, (TABLE_LENGTH*60)/4);
}
