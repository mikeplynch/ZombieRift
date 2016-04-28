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
	//camera->SetTarget(glm::vec3(0.0f, 0.0f, 0.0f));
	//camera->Se(glm::vec3(0.0f, 1.0f, 0.0f));

	Scene* scene = new Scene;

	CubeObject* cube = new CubeObject();

	BoxObject* box = new BoxObject(1.0f, 10.0f, 2.0f);
	box->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
	box->m_translations = glm::vec3(2.0f, 1.0f, 0.0f);
	box->m_name = "box";
	box->m_visible = false;

	PlayerBox* player = new PlayerBox();
	player->m_name = "player";
	player->m_translations = glm::vec3(0.0f, 2.0f, 0.0f);
	player->m_visible = false;
	
	//scene->AddObject(cube);
	scene->AddObject(box);
	scene->AddObject(player);

	Colony* myColony = new Colony(5, 5, 5);
	myColony->RandomizeState(80);
	myColony->AddToScene(scene);

	game->SetCurrentScene(scene);

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
		HandleInput(camera);
		if(counter % 100 == 0)
			myColony->Update();
		if(counter % 3000 == 0)
			myColony->RandomizeState(80);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		counter++;

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
	glfwWindowShouldClose(window) == 0);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	delete cube;
	delete box;

	return 0;
}

void HandleInput(Camera* camera) {
	if (glfwGetKey(window, GLFW_KEY_LEFT)) 
	{
		camera->ChangeYaw(0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT)) 
	{
		camera->ChangeYaw(-0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)) 
	{
		camera->ChangePitch(-0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_UP)) 
	{
		camera->ChangePitch(0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_A)) 
	{
		camera->MoveSideways(-0.01f);
	}
	if (glfwGetKey(window, GLFW_KEY_D)) 
	{
		camera->MoveSideways(0.01f);
	}
	if (glfwGetKey(window, GLFW_KEY_W)) 
	{
		camera->MoveForward(0.01f);
	}
	if (glfwGetKey(window, GLFW_KEY_S)) 
	{
		camera->MoveForward(-0.01f);
	}
}