#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef min
#undef max
#undef RGB
#include <imgui.h>
//#include <IconsFontAwesome6.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include "cppdraw.h"

GLFWwindow* window;

void Draw()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	glfwSetWindowTitle(window, "test");
	ImGui::SetNextWindowPos({ 0, 0 });
	int tmpWidth, tmpHeight;
	glfwGetWindowSize(window, &tmpWidth, &tmpHeight);
	ImGui::SetNextWindowSize({ (float)tmpWidth, (float)tmpHeight });
	bool tmpOpen;
	if (ImGui::Begin("###test", &tmpOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
	{
		if (ImGui::IsWindowAppearing())
		{
			glfwSetWindowSize(window, 800, 600);
			glfwSetWindowAttrib(window, GLFW_RESIZABLE, true);
			glfwSetWindowAttrib(window, GLFW_DECORATED, true);
		}
		newFrame();
		draw();
		ImGui::End();
	}
	ImGui::PopStyleVar();
}

static void glfw_error_callback(int error, const char* description)
{
	std::cerr << "Glfw Error: " << description;
}

// On Windows if you want to avoid console window to be shown
// Use /SUBSYSTEM:WINDOWS and implement wWinMain instead
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
	const char* glsl_version = "#version 100";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

	// Create window with graphics context
	window = glfwCreateWindow(1280, 720, "Test", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
	//glfwMaximizeWindow(window);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// TODO: Load custom style and fonts from the ImRAD INI file
	//ImRad::LoadStyle("my-style.ini");

	// Alternatively set ImGui style and fonts manually
	// Read 'docs/FONTS.md' for more instructions and details.
	ImGui::StyleColorsDark();

	/*
	io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 20.0f * ioUserData.dpiScale);

	ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	//icons_config.PixelSnapH = true;
	io.Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_FAR, 18.0f * ioUserData.dpiScale, &icons_config, icons_ranges);
	io.Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_FAS, 18.0f * ioUserData.dpiScale, &icons_config, icons_ranges);
	*/

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (true)
	{
		if (glfwWindowShouldClose(window))
			break;

		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		Draw();

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
