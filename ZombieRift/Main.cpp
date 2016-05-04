/*--------------------------------------------------------------------------------------------------
Code from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
modified by labigm@rit.edu
--------------------------------------------------------------------------------------------------*/
// Include standard headers
#include "Main.h"
#include "LSystem.h"

GLFWwindow* window;

int main(void)
{
	bool debug = false;
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	int width = 1280;
	int height = 800;

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, "MyMesh class", NULL, NULL);
	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window with OpenGL 3.3.  Attempting 3.1\n");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
		window = glfwCreateWindow(width, height, "MyMesh class", NULL, NULL);
		if (window == NULL)
		{
			fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");

			glfwTerminate();
			return -1;
		}
	}
	glfwMakeContextCurrent(window);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Sky Blue background
	glClearColor(0.529f, 0.807f, 0.9803f, 0.0f);
	glClearDepth(1.0f);
	
	Model* myModel = new Model("Default");

	GameManager::window = window;
	GameManager* game = GameManager::GetInstance();

	Camera* camera = Camera::GetInstance();
	camera->SetPosition(glm::vec3(0.0f, 0.0f, 15.0f));

	// - SET THE ACTIVE SCENE HERE -
	game->SetCurrentScene(new A10Scene);

	static double target_frame_rate = 60;
	static double frame_start = 0;
	do{

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw debug information(such as bounding boxes)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		game->DrawDebug();

		// Draw
		if(debug == false)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// Limit the frame rate to 60fps
		double wait_time = 1.0 / (target_frame_rate);
		double deltaTime = glfwGetTime() - frame_start;
		double dur = 1000.0 * (wait_time - deltaTime) + 0.5;
		int durDW = (int)dur;
		if (durDW > 0) // ensures that we don't have a dur > 0.0 which converts to a durDW of 0.
		{
			Sleep((DWORD)durDW);
		}
		double frame_end = glfwGetTime();
		deltaTime = frame_end - frame_start;
		frame_start = frame_end;
		game->Draw();

		std::cout << deltaTime << std::endl;

		// Update
		game->Update(deltaTime);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_SEMICOLON))
			debug == false ? debug = true : debug = false;
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
	glfwWindowShouldClose(window) == 0);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	//Clean up the game!
	GameManager::ReleaseInstance();

	return 0;
}

