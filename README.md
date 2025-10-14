# Rubika OpenGL 2025-2026

This is the repository used by the **OpenGL** lesson. 

1. [Threshold 0](#threshold-0)
2. [Threshold 1](#threshold-1)
3. [Threshold 2](#threshold-2)

## Threshold 0

This repository contains a working solution that includes all the dependencies we will need. Everything has already been set up. The program will display an empty windows. The purpose of this all project is to draw in this window.
- **glad** : OpenGL loaded which patches function pointers depending of the OS. (You shouldn't have to use it either).
- **glfw** : Multi-platform library for OpenGL which provides simple API to create windows, contexts... (You shouldn't have to use it).
- **glm** : Mathematics library ffor graphics software based on OpenGL.
- **KHR** : Glad's dependency. (You shouldn't have to use it).
- **stb** : Image loading/decoding from file/memory.

For any question about OpenGL API, use https://docs.gl/ with **gl3** option.

## Threshold 1

The purpose of this threshold is to draw a simple rectangle in the window. To do so, we will start by drawing a single triangle.

You are free to implement to way you want. If you want to be guided, you can read the following section which will give you the different steps to follow to achieve this threshold, the functions that should be used... Once again, you can ignore it and try by yourself.

### Step 0

As discussed in class, many things must be set up. Each step will focus on a specific aspect that must be set up. Let's start with the VBO.

The purpose of this step is to give the GPU a list of vertices that must be drawn.
```cpp
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};
```

The way the CPU "talks" to the GPU is always the same. We will define the way to do it once:
1. First, we have to "generate" it, using the right function that will return us an id (several if we want to generate more objects).
This id is the most important thing because it is the only way we have (CPU side) to communicate with the GPU
2. Then, we have to tell the GPU that all next calls have to be applied on the given id.
We bind the id we want to use and then the function A, B, C... will be applied on the object behind the id we gave
3. You can now call any function.

Once the vbo is bound, we can send the vertices to the GPU by allocating a buffer object's data. Finally, we have to describe to the GPU the content of the buffer we have just sent. This description will be used later on the shader side. To be able to used it shader side, it must be enable

This image might help you understand the attribute description
![img](https://learnopengl.com/img/getting-started/vertex_attribute_pointer.png)

Here are a list of useful functions (that you will need to use):
- glGenBuffers
- glBindBuffer
- glBufferData
- glDeleteBuffers
- glVertexAttribPointer
- glEnableVertexAttribArray

### Step 1

Let's talk about the shader part. For now, We will provide you with the vertex shader and the fragment shader. We will focus on shaders on the next shaders.
Here are the two shaders we are going to use for this threshold:
```cpp
	const char* vertexShaderSource = "#version 330 core\n"
		"in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
```

Such as the VBO, we have to tell the GPU that we are going to create a new shader, which will give us an id that we can use later. Then, we will send the source code of our shader to the GPU and finally, compile it. Because compilation can fail, it is important to get compilation error and more importantly, to know that we cannot rely on this shader.

Here are a list of useful functions (that you will need to use):
- glCreateShader
- glShaderSource
- glCompileShader
- glGetShaderiv
- glGetShaderInfoLog

### Step 2

Next step, we have to specify which shaders we want to use in our program. There are default vertex shader and fragment shader in case we don't provide them. The given vertex shader is close to the default one (for now) but the fragment shader is not.
To do so, we have to create a program and then we have to attach our shaders to this program. Finally, we have to link the attached shaders. Such as the compilation part of the shader, it is important to watch the link errors, print them if there are and more importantly, to handle the errors.

Once the link phase is done, our program has been setup so we can use it. Our shader has been attached to our program, so can delete the shader object we have created to free some space GPU side. This is a good habit to take to free objects if we dont use them.

Here are a list of useful functions (that you will need to use):
- glCreateProgram
- glLinkProgram
- glUseProgram
- glDeleteProgram
- glDeleteShader

### Step 3

During the last steps, we have seen how to declare and use a VBO, create our program and use it. The only part that is missing is too draw our object. Our code should look like:
1. Setup the VBO 
  - Copy the content of our buffer to the GPU
  - Describe the content of the buffer
2. Use the program
3. Draw

What if we have another object? We have to redo the first point once again with other data. It doesn't seem much because we are using only a single attribute. But in real situation, we are going to use multiple vertex attributes with lots of different objects. Re-implementing the VBO at different places (in the init phase and in the draw phase) will be really painful and risky.

To solve that problem, we are going to store all our VBO information in a VAO that we are going to initialize once. Then, if we want to draw a specific VBO, we are going to use our VAO instead and everything will be setup. Replacing tens of lines for each object by a single one.

To do so, before we have to create our VAO using the right function. Then, we have to bind our VAO so every later function will be applied to that VAO. And that's it. Setting up a VAO is a two lines phases. Create it and bind it before binding your VBO.

Here are a list of useful functions (that you will need to use):
* glGenVertexArrays
* glBindVertexArray
* glDeleteVertexArrays

### Step 4

The setup has been finished, it is time to use what we have created and draw. To do so:
1. Use the program you have created
2. Bind the VAO you want to draw
3. Draw! 

Here are a list of useful functions (that you will need to use):
* glUseProgram
* glBindVertexArray
* glDrawArrays

### Recap

At this stage, you should be able to display an orange triangle. Otherwise, something must be wrong on your side. Here is a quick recap of what you have to do:
**Initialization**
1. Create and bind your VAO
2. Create and bind your VBO
3. Send the buffer data to the GPU
4. Describe the content of the buffer
5. Create your vertex shader and your fragment shader
6. Compile them
7. Create your program
8. Attach your shaders to your program
9. Link your shaders 

**Drawing**
1. Use your program
2. Bind the VAO you want to draw
3. Draw

**Deinit**
1. Delete everything you have created

### Step 5

Let's draw the rectanle now. A rectangle is composed of two triangles, so the easiest way to draw it would be to add more vertices and draw two triangles at the right place. Modify your code to use this array
```cpp
float vertices[] = {
    // first triangle
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f,  // top left 
    // second triangle
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
}; 
```
It would work fine but by looking at the data in the array, we can see that some of them are duplicated (which is normal). We have 6 vertices where 4 are necessary (~50% overhead for a simple shape. It is terrible for complex mesh).

The solution is to have a list of vertices and to define our shape by index in this list
```cpp
float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};  
```

This index array is call an EBO (Element Buffer Object) and is defined and used in the same way as a VBO. Create it, bind it and send the content of the buffer to the GPU. You don't need to define the content of the buffer because we know it is a index buffer.
Now it has been setup, we just have to draw the elements.

Here are a list of useful functions (that you will need to use):
- glGenBuffers
- glBindBuffer
- glDrawElements
- glDeleteBuffers

## Threshold 2

The purpose of this threshold is to regroup all the shader logic into a class to avoid code duplication and provide a simple API to later use.

### Step 0

Create two different resource files that will contain our shaders. Instead of having our shader in a string (which is difficult to read and maintain), use a dedicated files is much easier. There is several different naming conventions. You are free to use the one you want:
- Use the `glsl` extension and the filename to determine which file refers to each shader
- Use the `glslv` and `glslf` extensions for vertex shader and fragment shader
- Use the `vs` and `fs` extensions for vertex shader and fragment shader
- Use the `vert` and `frag` extensions for vertex shader and fragment shader
- ...

### Step 1

Create a `Shader` class that will contain our vertex shader and our fragment shader. Here is a proposition
```cpp
#include <glad/glad.h>
#include <string>

class Shader
{
public:
    Shader();
	~Shader();
    
	// Read both file to init the vertex shader and the fragment shader
	bool Init(const char* vertexPath, const char* fragmentPath);

	// Use the corresponding program
    void Use();

private:
    GLuint ProgramID;
};
```

Once this class has been implemented, use it in your code from the previous threshold.

### Step 2

#### Types

GLSL is a C-like language that is use to write shader logic. Here is a list of all available types:
- bool
- int
- uint
- float
- double
- bvecn (where n can bu2, 3, or 4) : vector of bool
- ivecn (where n can bu2, 3, or 4) : vector of int
- uvecn (where n can bu2, 3, or 4) : vector of uint
- vecn (where n can bu2, 3, or 4) : vector of float
- dvecn (where n can bu2, 3, or 4) : vector of double

Such as C, you can declare static array of any type
```c
vec3 arr[5];
```

To access a data of a vector, you must use the x, y, z or w member. You can also combine them.
```cpp
vec2 someVec;
vec4 otherVec = someVec.xyxx;
vec3 thirdVec = otherVec.zyy;

or 

vec4 someVec;
someVec.wzyx = vec4(1.0, 2.0, 3.0, 4.0);
someVec.zx = vec2(3.0, 5.0);
```

Such as C, you can declare structure
```cpp
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
```

#### In and Out

Each shader can specify inputs and outputs using the **in** and **out** keywords and wherever an output variable matches with an input variable of the next shader stage they're passed along. The vertex shader must receive input otherwise it is pretty useless. The vertex shader is the first shader to be called, so it will receive the data we sent to the GPU with our VBO. We will assume that it needs the 3D position as an input. It is the same for the fragment shader which must output a color (which is a vec3). That is why the given shader from the previous threshold have an input and an output.

```cpp
in vec3 aPos;

or

out vec4 FragColor;
```

As an exercise for this step:
- Draw only one triangle and modify your shaders to flip the triangle upside down
- Modify your shaders to define the color of the triangle in the vertex shader


### Step 3

Uniforms are another way to pass data from our application on the CPU to the shaders on the GPU. Uniforms are however slightly different compared to vertex attributes. First of all, uniforms are global. Global, meaning that a uniform variable is unique per shader program object, and can be accessed from any shader at any stage in the shader program. Second, whatever you set the uniform value to, uniforms will keep their values until they're either reset or updated.

```cpp
#version 330 core
out vec4 FragColor;
  
uniform vec4 ourColor;

void main()
{
    FragColor = ourColor;
}  
```

Let's modify our `Shader` class to add few function to manipulate `uniform`.
```cpp
void SetInt(const std::string& name, int value) const;   
void SetFloat(const std::string& name, float value) const;
```

Finally, modify your entire program (CPU and GPU side) to modify the color of your triangle each frame (using the time for instance)

Here are a list of useful functions (that you will need to use):
- glGetUniformLocation
- glUniform (several variants of this function exist depending of the type you want to pass to the GPU)
- glfwGetTime

### Step 4

Another way to pass data from CPU to shaders is to use the attributes as we did for position in our VBO. Let's modify the buffer to include a new attribute, the color of the vertex.
```cpp
float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};    
```

This image might help you understand the attribute description
![img](https://learnopengl.com/img/getting-started/vertex_attribute_pointer_interleaved.png)

As you might notice, it is really painful to add an attribute. Let's simplify the all process. Create a structure that contains the same members.
```cpp
	struct Vertices
	{
		float position[3];
		float color[3];
	};
```

Then modify the vertices array to use the structure we have created
```cpp
	Vertices vertices[] =
	{
		{ 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f },   // bottom right
		{ -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f },	// bottom left
		{ 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f }    // top 
	};
```

The stride between two position is equal to the size of the entire structure, that can easily be found thanks to `sizeof`.
The pointer of the first member is also easily foundable using the `offsetof` keyword. You can now modify your calls to `glVertexAttribPointer` using those keywords. Thanks to that, you won't be bothered anymore by the stride, offset... anymore and adding a new attribute won't make you change anything.

Finally, you have to modify your vertex shader to use this new attribute. You must declare a new input variable (a vec3 to match what we sent) and pass it to the fragment shader.