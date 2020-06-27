#pragma once

#include "Rosewood/Core.h"
#include "Rosewood/Video.h"

struct ID3D11Device;
struct ID3D11DeviceContext1;
struct IDXGISwapChain1;
struct ID3D11RenderTargetView;
struct ID3D11BlendState;

#ifdef RW_DEBUG
struct ID3D11Debug;
struct ID3D11InfoQueue;
#endif

namespace rw
{
	class Window;

	class D3D11Video : public Video
	{
	public:
		explicit D3D11Video(const Window& window);
		virtual ~D3D11Video();
		
		virtual void SetClearColor(unsigned short red, unsigned short green, unsigned short blue) override;

		virtual void BeginRender() override;
		virtual void EndRender() override;

	private:
		const Window& mWindow;

		ID3D11Device* mDevice;
		ID3D11DeviceContext1* mDeviceContext1;
		IDXGISwapChain1* mSwapChain1;
		ID3D11RenderTargetView* mBackBuffer;
		ID3D11BlendState* mBlendState;

		float mClearColor[4];

#ifdef RW_DEBUG
		ID3D11Debug* mDebug;
		ID3D11InfoQueue* mInfoQueue;
#endif
	};
}
