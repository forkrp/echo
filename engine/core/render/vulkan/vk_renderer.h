#pragma once

#include "engine/core/render/interface/Renderer.h"
#include "vk_render_base.h"
#include "vk_swap_chain.h"

namespace Echo
{
    class GPUBuffer;
	class VKRenderer: public Renderer
	{
		typedef vector<VkExtensionProperties>::type     ExtensionProperties;
		typedef vector<VkLayerProperties>::type		    LayerProperties;
        typedef vector<VkQueueFamilyProperties>::type   QueueFamilies;

	public:
		VKRenderer();
		virtual ~VKRenderer();

		// initialize
        virtual bool initialize(const Config& config) override;

        // create buffer
        virtual GPUBuffer*	createVertexBuffer(Dword usage, const Buffer& buff) override;
        virtual GPUBuffer*	createIndexBuffer(Dword usage, const Buffer& buff) override;

        // create texture
        virtual Texture*     createTexture2D(const String& name) override { return nullptr; }
        virtual TextureCube* createTextureCube(const String& name) override {return nullptr; }

        // create views
        virtual RenderTarget* createRenderTarget(ui32 _id, ui32 _width, ui32 _height, PixelFormat _pixelFormat, const RenderTarget::Options& option) override {return nullptr;}

        // create states
        virtual RasterizerState* createRasterizerState(const RasterizerState::RasterizerDesc& desc) override;
        virtual DepthStencilState* createDepthStencilState(const DepthStencilState::DepthStencilDesc& desc)override;
        virtual BlendState* createBlendState(const BlendState::BlendDesc& desc) override;
        virtual const SamplerState* getSamplerState(const SamplerState::SamplerDesc& desc) override;

        // create shaders
        virtual ShaderProgram* createShaderProgram() override;

		// create renderable
        virtual Renderable* createRenderable(const String& renderStage, ShaderProgram* material) override;

        // convert matrix
        virtual void convertMatOrho(Matrix4& mat, const Matrix4& matOrth, Real zn, Real zf) override {}
        virtual void convertMatProj(Matrix4& mat, const Matrix4& matProj) override {}

		// scissor operate
		virtual void scissor(ui32 left, ui32 top, ui32 width, ui32 height) override {}
		virtual void endScissor() override {}

		// on size
		virtual void onSize(int width, int height) override {}

		// draw
		virtual void draw(Renderable* program) override {}

		// present
		virtual bool present() override { return false; }

    public:
        // set texture
        virtual void setTexture(ui32 index, Texture* texture, bool needUpdate = false) override;

        // view port
        virtual void setViewport(Viewport* pViewport) override;

    public:
        // get max stage number
        virtual ui32 getMaxStageNum() const override { return 32;}

        // get depth range
        virtual void getDepthRange(Vector2& vec) override {}

        // get screen width and height
        virtual ui32 getScreenWidth() override { return m_screenWidth;}
        virtual ui32 getScreenHeight() override { return m_screenHeight;}

		// get view port
		virtual void getViewportReal(Viewport& pViewport) override {}

	public:
		// get physical device
		VkPhysicalDevice getVkPhysicalDevice() { return m_vkPhysicalDevice; }

		// get windows surface
		VkSurfaceKHR getVkSurface() { return m_vkWindowSurface; }

		// get queue family index
		const ui32 getGraphicsQueueFamilyIndex();
		const ui32 getPresentQueueFamilyIndex();

	private:
		// create vk instance
		void createVkInstance();

        // create window surface
        void createVkSurface(void* handle);

		// vk extensions
		void enumerateVkExtensions();
		void prepareVkExtensions(vector<const char*>::type& extensions);

		// vk validation layers
		void enumerateVkValidationLayers();
		void prepareVkValidationLayers(vector<const char*>::type& validationLayers);

        // choose a physical device
        void pickVkPhysicalDevice();
        i32  calcVkPhysicalDeviceScore(const VkPhysicalDevice& device);

        // queue famalies
        void enumerateQueueFamalies();

        // create vk logical device
        void createVkLogicalDevice();

        // create swapChain
        void createVkSwapChain();

    private:
        ui32				m_screenWidth = 640;
        ui32				m_screenHeight = 480;
		VkInstance			m_vkInstance;
		ExtensionProperties	m_vkExtensions;
		LayerProperties		m_vkLayers;
        VkPhysicalDevice    m_vkPhysicalDevice = VK_NULL_HANDLE;
        QueueFamilies       m_vkQueueFamilies;
        VkDevice            m_vkDevice;
        VkQueue             m_vkGraphicsQueue;
        VkSurfaceKHR        m_vkWindowSurface;
        VkQueue             m_vkPresentQueue;
		VKSwapChain			m_swapChain;
	};
}
