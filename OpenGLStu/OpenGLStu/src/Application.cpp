#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

#include "VertexArray.h"

#include "Shader.h"
#include "Texture.h"

int main(void)
{
	GLFWwindow* window;

	///Initialize the library
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 481, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
	
	{
		float positions[] = {
		-0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
		 0, 1, 2,
		 2, 3, 0
		};

		unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao)); // Create our Vertex Array Object  
		GLCall(glBindVertexArray(vao)); // Bind our Vertex Array Object so we can use it  

		VertexArray va;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

	
		IndexBuffer ib(indices, 6);

		///shader
		Shader shader("res/shaders/Basic.shader");
		shader.Bind();

		///Uniform
	//	shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

		Texture texture("res/texture/index.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		///Unbind index buffer and fragment buffer
		va.UnBind();
		shader.UnBind();
		vb.Unbind();
		ib.Unbind();

		Renderer renderer;
		float r = 0.0f;
		float increment = 0.05f;
		///loop until the use close the window
		while (!glfwWindowShouldClose(window))
		{
			///Render here
			renderer.Clear();

			shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

			renderer.Draw(va, ib, shader);

			if (r > 1.0f)
				increment = -0.5f;
			if (r < 0.0f)
				increment = 0.5f;

			r += increment;
			///Swap front and back buffers
			glfwSwapBuffers(window);

			///Poll for and process events
			glfwPollEvents();
		}
		//glDeleteProgram(shader);
	}
	

	
	glfwTerminate();
	return 0;
}