/*--------------------------------------------------------------------------------------------------
Code from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
modified by labigm@rit.edu
--------------------------------------------------------------------------------------------------*/
// Include standard headers
#include "Main.h"

GLFWwindow* window;

int main(void)
{
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
	int width = 1024;
	int height = 768;

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, "MyMesh class", NULL, NULL);
	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window with OpenGL 3.3.  Attempting 3.1\n");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		window = glfwCreateWindow(width, height, "MyMesh class", NULL, NULL);
		if (window == NULL)
		{
			fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		}
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glEnable(GL_DEPTH_TEST);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GameManager::window = window;
	GameManager* game = GameManager::GetInstance();

	Camera* camera = Camera::GetInstance();
	camera->SetPosition(glm::vec3(0.0f, 0.0f, 15.0f));

	Colony* myColony = nullptr;

	// - SET THE ACTIVE SCENE HERE -
	game->SetCurrentScene(new A11Scene);

	int counter = 0;
	do{

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		game->Draw();
		// Draw debug information(such as bounding boxes)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		game->DrawDebug();

		// Update
		game->Update();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		counter++;

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
	glfwWindowShouldClose(window) == 0);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	//Clean up the game!
	GameManager::ReleaseInstance();

	return 0;
}

