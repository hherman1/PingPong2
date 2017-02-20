#include "ExampleApp.h"

using namespace glm;
using namespace std;

namespace basicgraphics {
	ExampleApp::ExampleApp(int argc, char** argv, std::string windowName, int windowWidth, int windowHeight) : BaseApp(argc, argv, windowName, windowWidth, windowHeight)
	{
        lastTime = glfwGetTime();

		ball.reset(new Ball());
		_box.reset(new Box(vec3(-0.5, -0.5, -0.5), vec3(0.5, 0.5, 0.5), vec4(1.0, 0.0, 0.0, 1.0)));
        _angle = 0;
        
        // Initialize the cylinders that make up the model. We're using unique_ptrs here so they automatically deallocate.
        paddle.reset(new Cylinder(vec3(0, 0, -0.5), vec3(0, 0, 0.5), 8.0, vec4(0.5, 0, 0, 1.0)));
        handle.reset(new Cylinder(vec3(0, -7.5, 0), vec3(0, -16, 0), 1.5, vec4(0.3, 0.4, 0, 1.0)));
	}

	ExampleApp::~ExampleApp() {}

	void ExampleApp::onUpdate(chrono::milliseconds m) {
		float seconds = m.count() / 1000.0;
		_angle += radians(120.0) * seconds;
		ball->update(m);
		
		
	}
    
    
void ExampleApp::onEvent(shared_ptr<Event> event) {
        string name = event->getName();
        if (name == "kbd_ESC_down") {
            glfwSetWindowShouldClose(_window, 1);
        }
        else if (name == "mouse_pointer") {
            vec2 mouseXY = event->get2DData();
            
            int width, height;
            glfwGetWindowSize(_window, &width, &height);
            
            // This block of code maps the 2D position of the mouse in screen space to a 3D position
            // 20 cm above the ping pong table.  It also rotates the paddle to make the handle move
            // in a cool way.  It also makes sure that the paddle does not cross the net and go onto
            // the opponent's side.
            float xneg1to1 = mouseXY.x / width * 2.0 - 1.0;
            float y0to1 = mouseXY.y / height;
            mat4 rotZ = toMat4(angleAxis(glm::sin(-xneg1to1), vec3(0, 0, 1)));
            
            glm::vec3 lastPaddlePos = glm::column(paddleFrame, 3);
            paddleFrame = glm::translate(mat4(1.0), vec3(xneg1to1 * 100.0, 20.0, glm::max(y0to1 * 137.0 + 20.0, 0.0))) * rotZ;
            vec3 newPos = glm::column(paddleFrame, 3);
            
            // This is a weighted average.  Update the velocity to be 10% the velocity calculated
            // at the previous frame and 90% the velocity calculated at this frame.
            paddleVel = 0.1f*paddleVel + 0.9f*(newPos - lastPaddlePos);
        }
        else if (name == "kbd_SPACE_up") {
            // This is where you can "serve" a new ball from the opponent's side of the net
            // toward you when the spacebar is released. I found that a good initial position for the ball is: (0, 30, -130).
            // And, a good initial velocity is (0, 200, 400).  As usual for this program, all 
            // units are in cm.
            
        } else if (name == "kbd_SPACE_down") {
            ball->launch();
            }
    
        else if (name == "mouse_pointer") {
            mouse_pos = event->get2DData();
            }
            else {
                cout << name << endl;
                }
    
    
        }
    
    void ExampleApp::onSimulation(double rdt) {
        // rdt is the change in time (dt) in seconds since the last call to onSimulation
        // So, you can slow down the simulation by half if you divide it by 2.
        rdt *= 0.25;
        
        // Here are a few other values that you may find useful..
        // Radius of the ball = 2cm
        // Radius of the paddle = 8cm
        // Acceleration due to gravity = 981cm/s^2 in the negative Y direction
        // See the diagram in the assignment handout for the dimensions of the ping pong table
        
    }


	void ExampleApp::onRenderGraphics() {
		// Setup the view matrix to set where the camera is located
		Table table;
        
        double curTime = glfwGetTime();
        onSimulation(curTime - lastTime);
        lastTime = curTime;
        
        
        glm::vec3 eye_world = glm::vec3(0, 70, 150);
		//glm::vec3 eye_world = glm::vec3(0,1.4,TABLE_FRONT + 1.4);
		glm::vec3 lightPos = eye_world*2.0f + vec3(0,10,0);
        //glm::mat4 view = glm::lookAt(eye_world, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		glm::mat4 view = glm::lookAt(eye_world, glm::vec3(0,TABLE_HEIGHT,-TABLE_LENGTH/3), glm::vec3(0,1,0));
        
        
		
		// Setup the projection matrix so that things are rendered in perspective
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)_windowWidth / (GLfloat)_windowHeight, 0.1f, 500.0f);
		//glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)_windowWidth / (GLfloat)_windowHeight, 0.01f, 100.0f);
		// Setup the model matrix
		glm::mat4 model = glm::mat4(1.0);

		//_angle += radians(1.0);
		model = model;

		// Update shader variables
		_shader.setUniform("view_mat", view);
		_shader.setUniform("projection_mat", projection);
		_shader.setUniform("model_mat", model);
		_shader.setUniform("eye_world", eye_world);
		_shader.setUniform("lightPos", lightPos);

		
        paddle->draw(_shader, paddleFrame);
        handle->draw(_shader, paddleFrame);

		_box->draw(_shader, model);
		table.draw(_shader, model);
		ball->draw(_shader, model);
	}

}
//	void ExampleApp::onEvent(shared_ptr<Event> event) {
//		string name = event->getName();
//		if (name == "kbd_ESC_down") {
//			glfwSetWindowShouldClose(_window, 1);
//		}
//		else if (name == "kbd_SPACE_down") {
//			ball->launch();
//		}
//		else if (name == "mouse_pointer") {
//			mouse_pos = event->get2DData();
//
//		}
//		else {
//			cout << name << endl;
//		}
//	}


