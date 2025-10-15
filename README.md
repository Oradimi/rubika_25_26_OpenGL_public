# Rubika OpenGL 2025-2026

This is the repository used by the **OpenGL** lesson. 

1. [Threshold 0](#threshold-0)
2. [Threshold 1](#threshold-1)
3. [Threshold 2](#threshold-2)
3. [Threshold 3](#threshold-3)
3. [Threshold 4](#threshold-4)
3. [Threshold 5](#threshold-5)

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
	struct Vertex
	{
		float position[3];
		float color[3];
	};
```

Then modify the vertices array to use the structure we have created
```cpp
	Vertex vertices[] =
	{
		{ 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f },   // bottom right
		{ -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f },	// bottom left
		{ 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f }    // top 
	};
```

The stride between two position is equal to the size of the entire structure, that can easily be found thanks to `sizeof`.
The pointer of the first member is also easily foundable using the `offsetof` keyword. You can now modify your calls to `glVertexAttribPointer` using those keywords. Thanks to that, you won't be bothered anymore by the stride, offset... anymore and adding a new attribute won't make you change anything.

Finally, you have to modify your vertex shader to use this new attribute. You must declare a new input variable (a vec3 to match what we sent) and pass it to the fragment shader.

## Threshold 3

The purpose of this threshold is to add textures to our primitives.

### Step 0

In order to avoid having plenty of code in our `init` or our `draw` function, let's create a `Texture` class (as you did for the `Shader` class).
```cpp
class Texture
{
public:
    Texture();
	~Texture();
    
	// Read both file to init the vertex shader and the fragment shader
	bool Init(const char* texturePath);

    // Use the corresponding texture
    void Use();
};
```

About the `Init` function, the first thing we need to do, is to load the image in the memory using the path given as parameter. To do so, we are not going to make our own parser but use a dedicated library : `stb_image`. It has already been included in the repository, so, to use it, you must add to the cpp file that needs it:
```cpp
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
```

Then, use `stbi_load` to load the image in memory (the `req_comp` parameter won't be used for now and must be set to 0).

Depending of the texture you chose, you might need to flip it vertically. In that case, you need to call the following function before you call to `stbi_load`.
```cpp
stbi_set_flip_vertically_on_load(true);
```

You now have a buffer that contains your texture, we can use with OpenGl. Keep in mind that after that we use that buffer in an OpenGL context (after sending it to the GPU), we don't need anymore so we have to free it to avoid leaks.

Here are a list of useful functions (that you will need to use):
- stbi_load
- stbi_set_flip_vertically_on_load
- stbi_image_free

### Step 1

Now, it is OpenGL time! Create a texture and bind it as we did numerous times. Then, we have to configure the OpenGL texture the **wrapping** and **filtering**.

#### Wrapping

As an picture is better than a thousand words, the wrapping allows us to determine how the texture is supposed to handle itself beyond its limits
![img](https://open.gl/media/img/c3_clamping.png).

To do so, use the right function to set `GL_TEXTURE_WRAP_S` and `GL_TEXTURE_WRAP_T` to the value you want (because those parameter might be hard to find in the list of all parameters in the documentation, I help you on that). Depending of the value you picked, we might need to setup the border color (`GL_TEXTURE_BORDER_COLOR`).

#### Filtering

Filtering might be harder to see on a picture (in a markdonw file), so here is a brief explanation. Since texture coordinates are resolution independent, they won't always match a pixel exactly. That means that the GPU must determine which color to use in that situation. There are two solutions:
- Or we use `GL_NEAREST` and we will take the color of the nearest pixel, such as: ![img](https://learnopengl.com/img/getting-started/filter_nearest.png)
- Or we use `GL_LINEAR` and we will compute an interpolated value between the neighboring pixels of the texture. The nearer the position to a pixel the more that pixel will contribute in the interpolation such as:
![img](https://learnopengl.com/img/getting-started/filter_linear.png)

As a result ![img](https://open.gl/media/img/c3_filtering.png)

To do so, use the right function to set `GL_TEXTURE_MIN_FILTER` and `GL_TEXTURE_MAG_FILTER` to the value you want (because those parameter might be hard to find in the list of all parameters in the documentation, I help you on that).

Here are a list of useful functions (that you will need to use):
- glGenTextures
- glBindTexture
- glTexParameter

### Step 2

Our texture is configured, it is now time to send the buffer to the GPU using `glTexImage2D`. One of the paramater might confuse you : `level`. Let's talk a bit of mipmaps. Mipmap is a precalculated sequence of images, each of which has an image resolution which is a factor of two smaller than the previous. For instance, you want to render a texture on a very tiny object far in the background of your image, you will have difficulties finding the right color you should use (because you initial image is 4k). So, the GPU will use the right image from the mipmap sequence, which makes a more precise rendering, use less memory... You can provide different images and setup manually the mipmap (using the `level` parameter) or setting it to 0 and asks OpenGL to generate the mipmap based on the texture. 

Here are a list of useful functions (that you will need to use):
- glTexImage2D
- glGenerateMipmap

### Step 3
Our texture is now created, OpenGL side, we can use it.

Add a `float texCoord[2];` to your `Vertex` structure, modify the `vertices` array with the following code, and finally, don't forget to add this new attribute to your VBO declaration.
```cpp
	Vertex vertices[] =
	{
		// positions          // colors           // texture coords
		{  0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f }, // top right
		{  0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f }, // bottom right
		{ -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f }, // bottom left
		{ -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f }  // top left 
	};
```

As a temporary implementation (until next step), implement the `Use` function in our `Texture` class by using the corresponding bind function. That will be sufficient for now. Finally, call the `Use` function in the draw part, before binding your VAO.

Our attributes are setup and our texture is bound, we can now use it in our shaders. We have no use of this information in our vertex shader, so pass it to the fragment shader. Our texture is accessible through an uniform:
```glsl
uniform sampler2D ourTexture;
```
This type can be used in many way but let's start simple with the `texture` function such as
```glsl
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}
```

Congratulation, you have displayed your first texture!

As an exercise, combine data from your Vertex struct (color & texture).

#### Step 4

Let's get back a bit to think how everything works. How this uniform has been set?

The answer is : everythin works because we only have a single texture. This solution cannot work is we need multiple textures.

To do it right, you need to do is to remplace the content of the `Use` function by the sequence:
- Active the texture N (0 <= N <= 15)
- Bind the texture
- Set the uniform using the index N you used to activate the texture.

You might need to change the signature of the `Use` function. Feel free to add what is necessary.

Let's try it. Create a second instance of `Texture` based on a different file. Use both of those textures and modify your fragment shader to blend those two textures (using the `mix` function).

Here are a list of useful functions (that you will need to use):
- glActiveTexture
- glBindTexture

## Treshold 4 

The purpose of this threshold is to add another dimension to our project, from 2D to 3D.

### Step 0

Mathematics will be important from now, if you need, take time to review matrix & vectors computation. You might also need to review how to convert matrix from a space to another (for instance, from local space to world space).

We will the `glm` library for the mathematic aspect.

### Step 1

Let's start simple. Assume all our vertices are a translation in the local space. So to convert it to the local Position by the matrix of the object in the world space. For instance:
```cpp
glm::mat4 trans = glm::mat4(1.0f);
trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));  
```

We are going to use this matrix in our vertex shader. To do so, pass it from the CPU to the shader as a uniform.
- Add a new function `SetMatrix` in your `Shader` class (you might be interested by the `glm::value_ptr` function).
- Declare your uniform as a `mat4` in your vertex shader and combine it with your vertex position.

Your object should be rotated and smaller that it was at this stage.

As an exercise, update the matrix each frame (using the time for instance) to rotate, translate, scale... your object

### Step 2

In the previous threshold, we handled the local space. In the last step, we had handled the world space. In this step, we will handle the last two spaces : the view/camera space and the projection space.

The final equation of the position looks like :
<center>V*clip*=M*projection* ⋅ M*view* ⋅ M*world* ⋅ V*local*</center>

#### Projection

We have the choice between two differents kind of projection:
- **Orthographic projection**
> An orthographic projection matrix defines a cube-like frustum box that defines the clipping space where each vertex outside this box is clipped. When creating an orthographic projection matrix we specify the width, height and length of the visible frustum. The frustum looks a bit like a container: 
![img](https://learnopengl.com/img/getting-started/orthographic_frustum.png)

To use this projection use 
```cpp
glm::ortho(0.0f, width, 0.0f, height, near_clip, far_clip);
```

- **Perspective projection**
> If you ever were to enjoy the graphics the real life has to offer you'll notice that objects that are farther away appear much smaller. This effect is something we call perspective.
This effect is possible because the frustum is not a box anymore but a prism:
![img](https://learnopengl.com/img/getting-started/perspective_frustum.png)

To use this projection use 
```cpp
glm::perspective(fov_radians, (float) width/(float) height, near_clip, far_clip);
```

Here are a comparison of the two effects:
![img](https://europe1.discourse-cdn.com/unity/original/3X/8/6/86f70b34fdd7ad262170df029bcac8c8850105cb.png)
![img](https://learnopengl.com/img/getting-started/perspective_orthographic.png)

*I advise you to use the second one, but it is a you please*

#### View/Camera

The matrix of the camera/view a simple matrix in world space. Nothing to add here.

Let's combine them all. Here are value that you should use to display your panel as a 3D object:
- near_clip : 0.1f
- far_clip : 100.f
- (fov is applicable) : 45.f °
- camera's translation : `0.f, 0.f, -3.f`
- object's world rotation : -55.f °

With all those data, you should be able to display your panel as a *visible* 3D object. (To do so, pass every useful data to the shader).

### Step 3

Let's add panels. Deactivate EBO for a bit and use those vertices (color is not used in the fragment shader):
```cpp
Vertex vertices[] = {
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    {  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },

    { -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    {  0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    {  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    {  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    { -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },

    { -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },

    { 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    { 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },

    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    {  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    {  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    {  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },

    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    {  0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    {  0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f }
};
```
Don't forget to replace your draw call by
```cpp
glDrawArrays(GL_TRIANGLES, 0, 36);
```

Then, change the model rotation each frame such as
```cpp
model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
```

A cube should be displayed in a weird way. Some faces override some others in a unatural way, because depth is not taken into account.

We will need to activate the Z-buffer in the init (through the depth test). However, this buffer must be clear each frame. Otherwise, the depth of previous frame might interfer the draw of a new frame. TO do so, start each draw by clearing the `GL_COLOR_BUFFER_BIT` and the `GL_DEPTH_BUFFER_BIT`.

Here are a list of useful functions (that you will need to use):
- glEnable
- glClear

### Step 4

Add a lots of new cube using those position:
```cpp
glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};
```

## Threshold 5

The purpose of this threshold is to be able to control the camera.
- ZQSD to move the camera
- Mouse for rotation
- Scroll for zoom

### Step 0

You might need a recap on Euler Angles to handle the rotation properly.

### Step 1

Create a `Camera` class. Let the input function apart for now and implement the others functions.
```cpp
class Camera
{
public:
    enum class Direction
    {
        Forward,
        Backward,
        Right,
        Left
    };

    Camera();
    Camera(const glm::vec3& pos, 
        const glm::vec3& worldUp,
        float pitch,
        float yaw);

    // use glm::lookAt
    glm::mat4 GetMatrix() const;

    // Input
    void ProcessKeyboard(Direction direction, float deltaTime);
    void ProcessMouse(float xoffset, float yoffset);
    void ProcessMouseScroll(float yoffset);

private:
    // Compute the Front and Right vector using the euler angles
    void UpdateCameraRotation();

    // Translation
    glm::vec3 Position;

    // Rotation - Must be normalized
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Euler Angles
    float Yaw;
    float Pitch;
    
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Fov;
};
```

### Step 2

To process the keyboard input, we will need the delta time between two frames.
Update the `main.cpp` file to compute the deltaTime.

Then, by modifying the `processInput` function, you can send the right event to you camera class if the right input is pressed.

Implement the `ProcessKeyboard` function in the `Camera` class.

Here are a list of useful functions (that you will need to use):
- glfwGetTime
- glfwGetKey

### Step 3

To process the mouse event, implement the `mouse_callback` function and call the `ProcessMouse` function (that you must implement too).

Do the same for the scroll callback by implementing the `scroll_callback` and the `ProcessMouseScroll` functions.