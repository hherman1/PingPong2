
#include "BaseApp.h"
#include "Table.h"
#include "Ball.h"

namespace basicgraphics {

	class ExampleApp : public BaseApp {
		public:
			ExampleApp(int argc, char** argv, std::string windowName, int windowWidth, int windowHeight);
			~ExampleApp();

		private:
			std::unique_ptr<Box> _box;
			glm::vec2 mouse_pos;
			float _angle;

			std::unique_ptr<Ball> ball;
        
        // The paddle is drawn with two cylinders
        std::unique_ptr<Cylinder> paddle;
        std::unique_ptr<Cylinder> handle;


			void onRenderGraphics() override;
			void onUpdate(std::chrono::milliseconds m) override;
			void onEvent(std::shared_ptr<Event> event) override;
        
        
        void onSimulation(double rdt);
        
        // Use these functions to access the current state of the paddle!
        glm::vec3 getPaddlePosition() { return glm::column(paddleFrame, 3); }
        glm::vec3 getPaddleNormal() { return glm::vec3(0,0,-1); }
        glm::vec3 getPaddleVelocity() { return paddleVel; }
        

        // This 4x4 matrix stores position and rotation data for the paddle.
        glm::mat4 paddleFrame;
        
        // This vector stores the paddle's current velocity.
        glm::vec3 paddleVel;
        
        // This holds the time value for the last time onSimulate was called
        double lastTime;
	};
}
