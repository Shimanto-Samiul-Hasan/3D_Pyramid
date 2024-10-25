#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

struct CUSTOMVERTEX
{
    FLOAT x, y, z; // Vertex position
    D3DCOLOR color; // Vertex color
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

// Global Variables
LPDIRECT3D9             g_pD3D = NULL;           // Pointer to the Direct3D interface
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;     // Pointer to the Direct3D device
LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;   // Pointer to the vertex buffer
LPDIRECT3DINDEXBUFFER9  g_pIndexBuffer = NULL;    // Pointer to the index buffer
LPD3DXFONT              g_pFont = NULL;           // Pointer to the font
HWND                    hwnd;                      // Window handle

// Forward declarations of functions
HRESULT Objects_Init(HWND hwnd);
void Render();
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Function to create and show the window
void CreateMainWindow(HINSTANCE hInstance)
{
    // Register the window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = _T("Direct3DWindowClass");

    RegisterClassEx(&wc);

    // Create the window
    hwnd = CreateWindowEx(0, _T("Direct3DWindowClass"), _T("3D Pyramid"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOW);
}

// Initialize Objects
HRESULT Objects_Init(HWND hwnd)
{
    // Create a font for rendering text
    if (FAILED(D3DXCreateFont(g_pd3dDevice, 36, 0, 0, 1, false, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("Arial"), &g_pFont)))
        return E_FAIL;

    // Create the vertex buffer
    if (FAILED(g_pd3dDevice->CreateVertexBuffer(5 * sizeof(CUSTOMVERTEX),
        0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVertexBuffer, NULL)))
    {
        return E_FAIL;
    }

    // Create the index buffer
    if (FAILED(g_pd3dDevice->CreateIndexBuffer(18 * sizeof(WORD), 0,
        D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIndexBuffer, NULL)))
    {
        return E_FAIL;
    }

    // Define vertices for a square pyramid
    CUSTOMVERTEX Vertices[] =
    {
        { -20.0f, -20.0f,  20.0f, D3DCOLOR_XRGB(255, 0, 0) },  // Base 1
        {  20.0f, -20.0f,  20.0f, D3DCOLOR_XRGB(0, 255, 0) },  // Base 2
        {  20.0f, -20.0f, -20.0f, D3DCOLOR_XRGB(0, 0, 255) },  // Base 3
        { -20.0f, -20.0f, -20.0f, D3DCOLOR_XRGB(255, 255, 0) }, // Base 4
        {  0.0f,  20.0f,   0.0f,  D3DCOLOR_XRGB(255, 0, 255) }  // Apex
    };

    VOID* pVertices = nullptr; // Pointer to hold vertex buffer
    if (FAILED(g_pVertexBuffer->Lock(0, sizeof(Vertices), &pVertices, 0)))
        return E_FAIL;

    memcpy(pVertices, Vertices, sizeof(Vertices)); // Copy vertices to vertex buffer
    g_pVertexBuffer->Unlock(); // Unlock the vertex buffer

    // Define indices for the square pyramid
    WORD Indices[] =
    {
        // Base (two triangles)
        0, 1, 2,
        0, 2, 3,
        // Sides (four triangles)
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    VOID* pIndices = nullptr; // Pointer to hold index buffer
    if (FAILED(g_pIndexBuffer->Lock(0, sizeof(Indices), &pIndices, 0)))
        return E_FAIL;

    memcpy(pIndices, Indices, sizeof(Indices)); // Copy indices to index buffer
    g_pIndexBuffer->Unlock(); // Unlock the index buffer

    return S_OK; // Success
}

// Rendering function
void Render()
{
    // Clear the back buffer
    g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    // Begin the scene
    if (SUCCEEDED(g_pd3dDevice->BeginScene()))
    {
        // Set the vertex buffer
        g_pd3dDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(CUSTOMVERTEX));
        g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

        // Set the index buffer
        g_pd3dDevice->SetIndices(g_pIndexBuffer);

        // Draw the cube
        g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 5, 0, 6); // 6 triangles

        // End the scene
        g_pd3dDevice->EndScene();
    }

    // Present the back buffer to the screen
    g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

// Window procedure to handle messages
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    CreateMainWindow(hInstance);

    // Initialize Direct3D
    g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (g_pD3D == NULL)
        return 0;

    D3DPRESENT_PARAMETERS d3dpp = {};
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hwnd;

    // Create the Direct3D device
    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
    {
        return 0;
    }

    // Call Objects_Init to initialize objects
    if (FAILED(Objects_Init(hwnd)))
    {
        // Handle error
        return 0;
    }

    // Main message loop
    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        Render(); // Call the render function
    }

    // Clean up Direct3D and other resources
    if (g_pd3dDevice) g_pd3dDevice->Release();
    if (g_pD3D) g_pD3D->Release();
    if (g_pVertexBuffer) g_pVertexBuffer->Release();
    if (g_pIndexBuffer) g_pIndexBuffer->Release();
    if (g_pFont) g_pFont->Release();

    return static_cast<int>(msg.wParam);
}
