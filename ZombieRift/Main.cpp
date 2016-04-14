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

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "MyMesh class", NULL, NULL);
	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

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

	Camera* camera = Camera::GetInstance();
	camera->SetPosition(glm::vec3(15.0f, 10.0f, 0.0f));
	camera->SetTarget(glm::vec3(0.0f, 0.0f, 0.0f));
	camera->SetUp(glm::vec3(0.0f, 1.0f, 0.0f));

	Shape* myShape = new Shape();

	myShape->GenCube(5.0f,
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 1.0f));

	CubeObject* cube = new CubeObject();

	float counter = 0;
	do{

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw stuff and do update log here

		// Update
		if (glfwGetKey(window, GLFW_KEY_A)) {
			cube->SetColor(glm::vec3(0.0f, 1.0f, 1.0f));
			camera->MoveSideways(-0.01f);
		}
		if (glfwGetKey(window, GLFW_KEY_D)) {
			camera->MoveSideways(0.01f);
		}
		if (glfwGetKey(window, GLFW_KEY_W)) {
			camera->MoveVertical(0.1f);
		}
		if (glfwGetKey(window, GLFW_KEY_S)) {
			camera->MoveVertical(-0.1f);
		}
		glm::mat4 transformations = glm::mat4(1.0f);
		transformations = glm::rotate(transformations, counter / 10, 0.0f, 1.0f, 0.0f);
		transformations *= glm::translate(glm::vec3(5.0, 0, 0));

		// Draw
		myShape->RenderShape(transformations, camera->GetView(), camera->GetProjection(false));
		cube->draw();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		counter++;

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
	glfwWindowShouldClose(window) == 0);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}