#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    GameController* gameController = (GameController*)glfwGetWindowUserPointer(window);    
    if (key == GLFW_KEY_V && action == GLFW_PRESS)
    {
        WindowController::GetInstance().ResizeWindow(*gameController->resIt);
        gameController->camera->SetProjection(*gameController->resIt);
        gameController->MoveResIterator();
        std::cout << "V Pressed!" << std::endl;
    }
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        gameController->camera = new Camera(*gameController->camIt);
        gameController->camera->SetProjection(WindowController::GetInstance().GetResolution());
        gameController->MoveCamIterator();
        std::cout << "C Pressed!" << std::endl;
    }
}
void GameController::Handle_Player_Movement(int input_code, glm::vec3 movement)
{
    if (glfwGetKey(window, input_code) == GLFW_PRESS)
    {
        player->TranslateWorld(movement);
    }
}

GameController::GameController()
{
    resOptions = {
        Resolution(640, 200),
        Resolution(1280, 384),
        Resolution(1280, 768)
    };
    resIt = resOptions.begin();

    camOptions = {
        Camera({1280, 768}, {100, 100, 2}, {0, 0, 0}, {1, 1, 0}),
        Camera({1280, 768}, {100, 100, 2}, {0, 0, 0}, {0, 1, 1}),
        Camera({1280, 768}, {100, 100, 2}, {0, 0, 0}, {0, 1, 0})
    };
    camIt = camOptions.begin();
}

GameController::~GameController()
{
    if (player != nullptr)
    {
        delete player;
        player = nullptr;
    }

    if (enemy != nullptr)
    {
        delete enemy;
        enemy = nullptr;
    }

    if (shader != nullptr)
    {
        delete shader;
        shader = nullptr;
    }

    if (camera != nullptr)
    {
        delete camera;
        camera = nullptr;
    }
}

void GameController::MoveResIterator()
{
    if (resIt != resOptions.end() - 1) {
        resIt++;
    }
    else {
        resIt = resOptions.begin();
    }
}

void GameController::MoveCamIterator()
{
    if (camIt != camOptions.end() - 1) {
        camIt++;
    }
    else {
        camIt = camOptions.begin();
    }
}

void GameController::Initialize()
{
    window = WindowController::GetInstance().GetWindow();
    M_ASSERT(glewInit() == GLEW_OK, "Unable");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glEnable(GL_CULL_FACE);

    camera = new Camera(
        WindowController::GetInstance().GetResolution(),
        { 0, 0, 50 }, { 0, 0, 0 }, { 0, 1, 0 }
    );
}

void GameController::RunGame()
{
    shader = new Shader();
    player = new Mesh();
    enemy = new Mesh();

    shader->LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");    
    player->Create(shader);
    enemy->Create(shader);

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, key_callback);
    do {
        glClear(GL_COLOR_BUFFER_BIT);
        System::Windows::Forms::Application::DoEvents();

        Handle_Player_Movement(GLFW_KEY_W, { 0, 0.02f, 0 });
        Handle_Player_Movement(GLFW_KEY_A, { -0.02f, 0, 0 });
        Handle_Player_Movement(GLFW_KEY_S, { 0, -0.02f, 0 });
        Handle_Player_Movement(GLFW_KEY_D, { 0.02f, 0, 0 });

        player->Render(camera->GetProjection() * camera->GetView());
        enemy->Render(camera->GetProjection() * camera->GetView());

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0
    );
}
