#pragma once

#include "Vectors.hpp"
#include "VulkanDevice.hpp"
#include "VulkanDescriptors.hpp"
#include "VulkanObject.hpp"
#include "VulkanRenderer.hpp"
#include "VulkanRenderSystem.hpp"
#include "VulkanTexture.hpp"
#include "VulkanUtils.hpp"
#include "VulkanWindow.hpp"
#include "Config.hpp"

#include <array>
#include <memory>
#include <vector>

namespace rts {

class CatsVsDogs
{
	public:

	CatsVsDogs();
	~CatsVsDogs();
	CatsVsDogs(const CatsVsDogs&) = delete;
	CatsVsDogs& operator=(const CatsVsDogs&) = delete;

	void	run();
	bool	initialize();
	void	shutdown() {};

	private:

	ve::VulkanWindow	vulkanWindow{config::DEFAULT_WINDOW_HEIGHT, config::DEFAULT_WINDOW_WIDTH, "CatsVsDogs"};
	ve::VulkanDevice	vulkanDevice{vulkanWindow};
	ve::VulkanRenderer	vulkanRenderer{vulkanWindow, vulkanDevice};
	std::unique_ptr<ve::VulkanDescriptorPool>	globalDescriptorPool{};

	ve::VulkanObject::Map		objects;
	std::vector<ve::VulkanTexture>	textures;

	std::vector<VkDescriptorSet>	createGlobalDescriptorSets(
		ve::VulkanDescriptorSetLayout& descriptorSetLayout,
		const std::vector<std::unique_ptr<ve::VulkanBuffer>>& uboBuffers);
};

vec3	generateRandomColor();
vec3	generateRandomGreyscale();
vec3	generateSoftGreyscale();

}	// namespace rts