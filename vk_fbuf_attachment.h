#ifndef CHIMERA_VK_FBUF_ATTACHMENT_H
#define CHIMERA_VK_FBUF_ATTACHMENT_H

#define USE_VOLK
#include "vk_include.h"
#include "vk_swapchain.h"
#include <vector>


namespace vk_utils
{
  struct FbufAttachment
  {
    VkImage image = VK_NULL_HANDLE;
    VkImageView view = VK_NULL_HANDLE;
    VkFormat format = VK_FORMAT_UNDEFINED;
    VkImageSubresourceRange subresourceRange{};
    VkAttachmentDescription description{};
    uint32_t layerCount = 0;

    VkMemoryRequirements mem_req{};
    VkDeviceMemory mem = VK_NULL_HANDLE;
    VkDeviceSize mem_offset = 0;
  };

  struct AttachmentInfo
  {
    VkFormat format = VK_FORMAT_UNDEFINED;
    VkImageUsageFlags usage = VK_IMAGE_USAGE_SAMPLED_BIT;
    VkSampleCountFlagBits imageSampleCount = VK_SAMPLE_COUNT_1_BIT;
    VkImageLayout initial_layout = VK_IMAGE_LAYOUT_UNDEFINED;
  };

  struct RenderTarget
  {
    VkDevice m_device = VK_NULL_HANDLE;
    VkExtent2D m_resolution{};
    std::vector<VkFramebuffer> m_framebuffers;
    VkRenderPass m_renderPass = VK_NULL_HANDLE;
    VkSampler m_sampler = VK_NULL_HANDLE;
    std::vector<FbufAttachment> m_attachments;

    explicit RenderTarget(const VkExtent2D &a_resolution) : m_resolution(a_resolution){}
    ~RenderTarget();

    uint32_t getNumColorAttachments() const {return m_numColorAttachments;}
    uint32_t createAttachment(const AttachmentInfo &info);
//    uint32_t addAttachment(const AttachmentInfo &info, VkImage img);
    void createViewAndBindMemory(VkDeviceMemory mem, const std::vector<VkDeviceSize> &offsets);
    VkResult createDefaultSampler();
    VkResult createDefaultRenderPass();
    VkResult createRenderPassWithSwapchainOut(VulkanSwapChain &a_swapchain);
  private:
    uint32_t m_numColorAttachments = 0;
  };
}
#endif//CHIMERA_VK_FBUF_ATTACHMENT_H

