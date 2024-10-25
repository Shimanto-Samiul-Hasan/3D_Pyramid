
# 3D Pyramid Application

## Overview
The **3D Pyramid Application** is a simple graphical program developed using Direct3D to render a pyramid in a 3D environment. This project serves as a fundamental introduction to graphics programming, leveraging the DirectX API for rendering 3D objects.

## Features
- Renders a square pyramid using vertex and index buffers.
- Utilizes a black background with colored lines for the pyramid structure.
- Displays a basic user interface utilizing DirectX fonts.
- Simple structure suitable for beginners in game programming and graphics development.

## Prerequisites
Before you begin, ensure you have the following installed:
- **Windows OS** (Windows 10 or later recommended)
- **Visual Studio** (2019 or later preferred)
- **DirectX SDK** (DirectX 9 or later)

## Getting Started

### Installation
1. **Clone the Repository**
   Open your terminal and clone the repository using:
   ```bash
   git clone https://github.com/username/3D-Pyramid.git
   ```

2. **Open the Project**
   Navigate to the project directory:
   ```bash
   cd 3D-Pyramid
   ```
   Open the solution file (`.sln`) in Visual Studio.

3. **Build the Project**
   - In Visual Studio, select `Build` from the top menu, then choose `Build Solution`.
   - Ensure that there are no errors during the build process.

4. **Run the Application**
   - Press `F5` or select `Debug > Start Debugging` to run the application.
   - A window should appear displaying the 3D pyramid.

## Code Structure
The application is organized as follows:

```
3D-Pyramid/
│
├── 3d_pyramid.cpp          # Main application code
├── README.md               # Project documentation
└── ...                     # Other resources and assets
```

### Key Code Components

#### Main Application Logic
```cpp
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    CreateMainWindow(hInstance);

    // Initialize Direct3D
    g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    ...
}
```
- This function initializes the application and creates the main window using the Win32 API. It also sets up Direct3D for rendering.

#### Object Initialization
```cpp
HRESULT Objects_Init(HWND hwnd)
{
    // Create the vertex buffer
    if (FAILED(g_pd3dDevice->CreateVertexBuffer(5 * sizeof(CUSTOMVERTEX),
        0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVertexBuffer, NULL)))
    {
        return E_FAIL;
    }
    ...
}
```
- This function initializes the vertex and index buffers used for rendering the pyramid. The vertex buffer holds the vertices, and the index buffer defines the order in which vertices are connected to form triangles.

#### Rendering Function
```cpp
void Render()
{
    g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    ...
}
```
- The `Render` function clears the screen and draws the pyramid. It sets the buffers and uses `DrawIndexedPrimitive` to render the shape based on the defined vertices and indices.

## Errors and Debugging
While developing the application, we encountered several issues, such as:
- **Undefined Identifiers**: We had to ensure all necessary headers were included, such as `d3dx9.h`.
- **L-value Required Errors**: These errors were typically resolved by ensuring correct variable references in function calls.
- **Black Screen Issues**: Adjustments to the rendering pipeline and ensuring the correct order of operations resolved these issues.

Each error provided an opportunity to learn more about Direct3D and debugging practices.

## Contributing
We welcome contributions to the project! If you have suggestions or enhancements, please follow these steps:
1. Fork the repository.
2. Create a new branch for your feature or bug fix.
   ```bash
   git checkout -b feature/my-new-feature
   ```
3. Commit your changes.
   ```bash
   git commit -m "Add some feature"
   ```
4. Push to the branch.
   ```bash
   git push origin feature/my-new-feature
   ```
5. Create a pull request.

## Final Output of the Program
![Alt text](assests/gif.gif)

## Acknowledgments
- Thanks to the DirectX community and documentation for invaluable resources.
- Special thanks to all contributors who have helped improve this project.

---

For further information or inquiries, feel free to contact the project maintainer at [samiulhasan6730@gmail.com](mailto:samiulhasan6730@gmail.com).
```
