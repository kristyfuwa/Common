#include <windows.h>
#include "TGAImage.h"
#include "Vector3.h"


int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	constexpr int width = 800; // output image size
	constexpr int height = 800;

	const Vector3		light_dir(1, 1, 1); // light source
	const Vector3       eye(1, 1, 3); // camera position
	const Vector3		center(0, 0, 0); // camera direction
	const Vector3       up(0, 1, 0); // camera up vector
	TGAImage framebuffer(width, height, TGAImage::RGB);


	return 0;
}