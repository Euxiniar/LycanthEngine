#include <VulkanLoader.h>

namespace Ly 
{
	VulkanLoader::VulkanLoader(std::unique_ptr<Window>& window)
		: m_window(window)
	{
		initVulkan();
	}

	VulkanLoader::~VulkanLoader()
	{
		cleanupSwapChain();

		m_descriptorPool.reset();
		m_descriptorSetLayout.reset();

		for (size_t i = 0; i < m_swapChainImages.size(); i++) {
			m_uniformBuffers.at(i).reset();
		}

		m_indexBuffer.reset();
		m_vertexBuffer.reset();

		for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++){
			m_syncObjects.at(i).reset();
		}

		for (int i = 0; i < m_commandPools.size(); i++)
		{
			m_commandPools.at(i).reset();
		}
		
		m_device.reset();

		if (Ly::ValidationLayers::areEnabled()) {
			m_callback.reset();
		}
		vkDestroySurfaceKHR(m_instance->get(), m_surface, nullptr);
		m_instance.reset();
	}

	void VulkanLoader::cleanupSwapChain()
	{
		m_swapChainFramebuffers.reset();
		m_commandBuffers.reset();
		m_graphicsPipeline.reset();
		m_pipelineLayout.reset();
		m_renderPass.reset();
		m_swapChainImageViews.reset();
		m_swapChain.reset();
	}

	void VulkanLoader::recreateSwapchain()
	{
		int width = 0, height = 0;
		while (width == 0 || height == 0) {
			m_window->updateWindowSize();
			width = m_window->m_width;
			height = m_window->m_height;
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(m_device->get());

		cleanupSwapChain();

		createSwapChain();
		createImageViews();
		createRenderPass();
		createPipelineLayout();
		createGraphicsPipeline();
		createFramebuffers();
		createCommandBuffers();
	}

	void VulkanLoader::initVulkan()
	{
		createValidationLayers();
		createInstance();
		setupDebugCallback();
		createSurface();
		createPhysicalDevice();
		createLogicalDevice();
		createSwapChain();
		createImageViews();
		createRenderPass();
		createDescriptorSetLayout();
		createPipelineLayout();
		createGraphicsPipeline();
		createFramebuffers();
		createCommandPool();
		createVertexBuffer();
		createIndexBuffer();
		createUniformBuffer();
		createDescriptorPool();
		createDescriptorSet();
		createCommandBuffers();
		createSyncObjects();
	}

	void VulkanLoader::createValidationLayers()
	{
		m_validationLayers = std::make_unique<Ly::ValidationLayers>("VK_LAYER_LUNARG_standard_validation");
	}

	void VulkanLoader::createInstance()
	{
		m_instance = std::make_unique<Ly::Instance>(m_appName.c_str(), m_engineName.c_str(), m_validationLayers->get());
	}

	void VulkanLoader::setupDebugCallback()
	{
		if (!Ly::ValidationLayers::areEnabled()) {
			return;
		}
		else {
			m_callback = std::make_unique<DebugCallback>(m_instance->get());
		}
	}

	void VulkanLoader::createSurface()
	{
		if (glfwCreateWindowSurface(m_instance->get(), m_window->m_window, nullptr, &m_surface) != VK_SUCCESS) {
			Ly::Log::error("Failed to create Window Surface !");
		}
	}

	void VulkanLoader::createPhysicalDevice()
	{
		m_physicalDevice = std::make_unique<Ly::PhysicalDevice>(m_instance->get(), m_surface);
	}

	void VulkanLoader::createLogicalDevice()
	{
		m_device = std::make_unique<Ly::LogicalDevice>(m_physicalDevice->get(), 
			m_surface, m_validationLayers->get(), 
			m_deviceExtensions, m_graphicsQueue, m_presentQueue, m_transferQueue);
	}

	void VulkanLoader::createSwapChain()
	{
		m_swapChain = std::make_unique<Swapchain>(m_window, m_physicalDevice->get(), 
			m_surface, m_device->get(), m_swapChainImages, m_swapChainImageFormat, 
			m_swapChainExtent);
	}

	void VulkanLoader::createImageViews()
	{
		m_swapChainImageViews = std::make_unique<Ly::ImageViews>(m_device->get(), m_swapChainImages, m_swapChainImageFormat);
	}

	void VulkanLoader::createRenderPass()
	{
		m_renderPass = std::make_unique<Ly::RenderPass>(m_device->get(), m_swapChainImageFormat);
	}

	void VulkanLoader::createDescriptorSetLayout()
	{
		m_descriptorSetLayout = std::make_unique<Ly::DescriptorSetLayout>(m_device->get());
	}

	void VulkanLoader::createPipelineLayout()
	{
		m_pipelineLayout = std::make_unique<Ly::PipelineLayout>(m_device->get(), m_descriptorSetLayout->get());
	}

	void VulkanLoader::createGraphicsPipeline()
	{
		m_graphicsPipeline = std::make_unique<Ly::GraphicsPipeline>(m_device->get(), m_swapChainExtent, 
			m_pipelineLayout->get(), m_renderPass->get());
	}

	void VulkanLoader::createFramebuffers()
	{
		m_swapChainFramebuffers = std::make_unique<Ly::Framebuffers>(m_device->get(), 
			m_swapChainImageViews->get(), m_renderPass->get(), m_swapChainExtent);
	}

	void VulkanLoader::createCommandPool()
	{
		QueueFamilyIndices queueFamilyIndices = QueueFamily::findQueueFamilies(m_physicalDevice->get(), m_surface);
		m_commandPools.push_back(std::make_unique<Ly::CommandPool>(m_device->get(), queueFamilyIndices.graphicsFamily));
		m_commandPools.push_back(std::make_unique<Ly::CommandPool>(m_device->get(), queueFamilyIndices.presentFamily));
	}

	void VulkanLoader::createVertexBuffer()
	{
		Ly::Buffer stagingBuffer(m_device->get(), m_physicalDevice->get(), sizeof(m_vertices[0]) * m_vertices.size(),
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		void* data;
		vkMapMemory(m_device->get(), stagingBuffer.getMemory(), 0, stagingBuffer.getSize(), 0, &data);
		memcpy(data, m_vertices.data(), (size_t)stagingBuffer.getSize());
		vkUnmapMemory(m_device->get(), stagingBuffer.getMemory());

		m_vertexBuffer = std::make_unique<Ly::VertexBuffer>(m_device->get(),
			m_physicalDevice->get(), stagingBuffer.getSize());

		copyBuffer(stagingBuffer.get(), m_vertexBuffer->get());
	}

	void VulkanLoader::createIndexBuffer()
	{
		Ly::Buffer stagingBuffer(m_device->get(), m_physicalDevice->get(), sizeof(m_indices[0]) * m_indices.size(),
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		void* data;
		vkMapMemory(m_device->get(), stagingBuffer.getMemory(), 0, stagingBuffer.getSize(), 0, &data);
		memcpy(data, m_indices.data(), (size_t)stagingBuffer.getSize());
		vkUnmapMemory(m_device->get(), stagingBuffer.getMemory());

		m_indexBuffer = std::make_unique<Ly::IndexBuffer>(m_device->get(),
			m_physicalDevice->get(), stagingBuffer.getSize());

		copyBuffer(stagingBuffer.get(), m_indexBuffer->get());
	}

	void VulkanLoader::createUniformBuffer()
	{
		VkDeviceSize bufferSize = sizeof(UniformBufferObject);
		for (int i = 0; i < m_swapChainImages.size(); i++)
		{
			m_uniformBuffers.push_back(std::make_unique<Ly::UniformBuffer>(m_device->get(), m_physicalDevice->get(), bufferSize));
		}
	}

	void VulkanLoader::createDescriptorPool()
	{
		m_descriptorPool = std::make_unique<Ly::DescriptorPool>(m_device->get(), static_cast<uint32_t>(m_swapChainImages.size()), static_cast<uint32_t>(m_swapChainImages.size()));
	}

	void VulkanLoader::createDescriptorSet()
	{
		std::vector<VkDescriptorSetLayout> layouts(m_swapChainImages.size(), m_descriptorSetLayout->get());
		VkDescriptorSetAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = m_descriptorPool->get();
		allocInfo.descriptorSetCount = static_cast<uint32_t>(m_swapChainImages.size());
		allocInfo.pSetLayouts = layouts.data();

		m_descriptorSets.resize(m_swapChainImages.size());
		if (vkAllocateDescriptorSets(m_device->get(), &allocInfo, &m_descriptorSets[0]) != VK_SUCCESS) {
			Ly::Log::error("Failed to allocate descriptor sets!");
		}

		for (size_t i = 0; i < m_swapChainImages.size(); i++) {
			VkDescriptorBufferInfo bufferInfo = {};
			bufferInfo.buffer = m_uniformBuffers[i]->get();
			bufferInfo.offset = 0;
			bufferInfo.range = sizeof(UniformBufferObject);

			VkWriteDescriptorSet descriptorWrite = {};
			descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet = m_descriptorSets[i];
			descriptorWrite.dstBinding = 0;
			descriptorWrite.dstArrayElement = 0;
			descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptorWrite.descriptorCount = 1;
			descriptorWrite.pBufferInfo = &bufferInfo;

			vkUpdateDescriptorSets(m_device->get(), 1, &descriptorWrite, 0, nullptr);
		}
	}

	void VulkanLoader::createCommandBuffers()
	{
		m_commandBuffers = std::make_unique<Ly::CommandBuffers>(m_device->get(), m_commandPools.at(0)->get(), 
			m_swapChainFramebuffers->get(), m_pipelineLayout->get(), m_graphicsPipeline->get(), m_renderPass->get(), m_swapChainExtent,
			m_vertexBuffer->get(), m_indexBuffer->get(), static_cast<uint32_t>(m_indices.size()), m_descriptorSets);
	}

	void VulkanLoader::createSyncObjects()
	{
		for(int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		m_syncObjects.push_back(std::make_unique<Ly::SyncObject>(m_device->get()));
	}

	void VulkanLoader::drawFrame()
	{
		vkWaitForFences(m_device->get(), 1, &m_syncObjects.at(currentFrame)->getInFlightFence(), VK_TRUE, std::numeric_limits<uint64_t>::max());

		uint32_t imageIndex;
		VkResult result = vkAcquireNextImageKHR(m_device->get(), m_swapChain->get(), std::numeric_limits<uint64_t>::max(), 
			m_syncObjects.at(currentFrame)->getImageAvailableSemaphore(), VK_NULL_HANDLE, &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapchain();
			return;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			Ly::Log::error("Failed to acquire swap chain image !");
		}

		m_uniformBuffers.at(imageIndex)->update(m_swapChainExtent.width, m_swapChainExtent.height);

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore waitSemaphores[] = { m_syncObjects.at(currentFrame)->getImageAvailableSemaphore() };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_commandBuffers->get(imageIndex);

		VkSemaphore signalSemaphores[] = { m_syncObjects.at(currentFrame)->getRenderFinishedSemaphore() };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		vkResetFences(m_device->get(), 1, &m_syncObjects.at(currentFrame)->getInFlightFence());

		if (vkQueueSubmit(m_graphicsQueue, 1, &submitInfo, m_syncObjects.at(currentFrame)->getInFlightFence()) != VK_SUCCESS) {
			Ly::Log::error("Failed to submit draw command buffer!");
		}

		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR swapChains[] = { m_swapChain->get() };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;

		presentInfo.pImageIndices = &imageIndex;

		result = vkQueuePresentKHR(m_presentQueue, &presentInfo);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_window->framebufferResized) {
			m_window->framebufferResized = false;
			recreateSwapchain();
		}
		else if (result != VK_SUCCESS) {
			Ly::Log::error("Failed to present swap chain image!");
		}

		currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
	}

	void VulkanLoader::waitIdle()
	{
		vkDeviceWaitIdle(m_device->get());
	}

	void VulkanLoader::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer)
	{
		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = m_commandPools.at(1)->get();
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(m_device->get(), &allocInfo, &commandBuffer);

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &beginInfo);

		VkBufferCopy copyRegion = {};
		copyRegion.srcOffset = 0; 
		copyRegion.dstOffset = 0; 
		copyRegion.size = m_vertexBuffer->getSize();
		vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

		vkEndCommandBuffer(commandBuffer);

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(m_graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(m_graphicsQueue);

		vkFreeCommandBuffers(m_device->get(), m_commandPools.at(1)->get(), 1, &commandBuffer);
	}
}
