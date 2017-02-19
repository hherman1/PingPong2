#include "ExampleApp.h"

using namespace glm;
using namespace std;

namespace basicgraphics {
	ExampleApp::ExampleApp(int argc, char** argv, std::string windowName, int windowWidth, int windowHeight) : BaseApp(argc, argv, windowName, windowWidth, windowHeight)
	{
		ball = make_unique<Ball>();
		_box.reset(new Box(vec3(-0.5, -0.5, -0.5), vec3(0.5, 0.5, 0.5), vec4(1.0, 0.0, 0.0, 1.0)));
        _angle = 0;
	}

	ExampleApp::~ExampleApp() {}

	void ExampleApp::onUpdate(chrono::milliseconds m) {
		float seconds = m.count() / 1000.0;
		_angle += radians(180.0) * seconds;
		ball->update(m);
		
	}

	void ExampleApp::onRenderGraphics() {
		// Setup the view matrix to set where the camera is located
		Table table;

		glm::vec3 eye_world = glm::vec3(0,TABLE_HEIGHT*1.5,TABLE_LENGTH/2 + 0.8);
		glm::mat4 view = glm::lookAt(eye_world, glm::vec3(0,TABLE_HEIGHT,-TABLE_LENGTH/3), glm::vec3(0,1,0));
		
		// Setup the projection matrix so that things are rendered in perspective
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)_windowWidth / (GLfloat)_windowHeight, 0.01f, 100.0f);
		// Setup the model matrix
		glm::mat4 model = glm::mat4(1.0);

		glm::mat4 rotate = glm::toMat4(glm::angleAxis((float)radians(20.0f), vec3(1, 0, 0)));//glm::toMat4(glm::angleAxis(_angle, vec3(0, 1, 0))) * glm::toMat4(glm::angleAxis((float)radians(20.0), vec3(1.0, 0.0, 0.0)));
		//_angle += radians(1.0);
		model = model;

		// Update shader variables
		_shader.setUniform("view_mat", view);
		_shader.setUniform("projection_mat", projection);
		_shader.setUniform("model_mat", model);
		_shader.setUniform("eye_world", eye_world);
		_shader.setUniform("lightPos", vec3(0,2*TABLE_HEIGHT,0));


		

		_box->draw(_shader, model);
		table.draw(_shader, model);
		ball->draw(_shader, model);
	}

	void ExampleApp::onEvent(shared_ptr<Event> event) {
		string name = event->getName();
		if (name == "kbd_ESC_down") {
			glfwSetWindowShouldClose(_window, 1);
		}
		else if (name == "kbd_SPACE_down") {
			ball->launch();
		}
		else {
			cout << name << endl;
		}
	}
}