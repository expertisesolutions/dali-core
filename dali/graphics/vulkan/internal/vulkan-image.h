#ifndef DALI_GRAPHICS_VULKAN_IMAGE
#define DALI_GRAPHICS_VULKAN_IMAGE

/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <dali/graphics/vulkan/internal/vulkan-types.h>

namespace Dali
{
namespace Graphics
{
namespace Vulkan
{

class Graphics;
class Memory;

class Image : public VkManaged
{
  friend class Graphics;

public:

  /**
   * Returns underlying Vulkan object
   * @return
   */
  vk::Image GetVkHandle() const;

  /**
   * Returns VkImageLayout associated with the image
   * @return
   */
  vk::ImageLayout GetImageLayout() const;

  /**
   * Returns width in pixels
   * @return
   */
  uint32_t GetWidth() const;

  /**
   * Returns height in pixels
   * @return
   */
  uint32_t GetHeight() const;

  /**
   * Returns number of layers
   * @return
   */
  uint32_t GetLayerCount() const;

  /**
   * Returns number of mipmap levels
   * @return
   */
  uint32_t GetMipLevelCount() const;

  /**
   * Returns pixel format
   * @return
   */
  vk::Format GetFormat() const;

  /**
   * returns image type ( VkImageType)
   * @return
   */
  vk::ImageType GetImageType() const;

  /**
   * Returns used image tiling mode
   * @return
   */
  vk::ImageTiling GetImageTiling() const;

  vk::ImageAspectFlags GetAspectFlags() const;

  /**
   *
   * @return
   */
  vk::ImageUsageFlags GetUsageFlags() const;

  vk::SampleCountFlagBits GetSampleCount() const;

  void SetImageLayout( vk::ImageLayout imageLayout );

  const Image& ConstRef();

  Image& Ref();

  bool OnDestroy() override;

  Memory* GetMemory() const
  {
    return mDeviceMemory.get();
  }

  /**
   * Destroys underlying Vulkan resources on the caller thread.
   *
   * @note Calling this function is unsafe and makes any further use of
   * image invalid.
   */
  void DestroyNow();

private:

  /**
   * Creates new VkImage with given specification, it doesn't
   * bind the memory.
   * @param graphics
   * @param createInfo
   */
  Image( Graphics& graphics, const vk::ImageCreateInfo& createInfo, vk::Image externalImage = nullptr );

  /**
   * Destroys used Vulkan resource objects
   * @param device Vulkan device
   * @param image Vulkan image
   * @param memory Vulkan device memory
   * @param allocator Pointer to the Vulkan allocator callbacks
   */
  static void DestroyVulkanResources( vk::Device device, vk::Image image, vk::DeviceMemory memory, const vk::AllocationCallbacks* allocator );

private:
  Graphics* mGraphics;
  vk::ImageCreateInfo mCreateInfo;
  vk::Image mImage;
  vk::ImageLayout mImageLayout;
  vk::ImageAspectFlags mAspectFlags;

  std::unique_ptr<Memory> mDeviceMemory;
  bool mIsExternal;
};

} // namespace Vulkan

} // namespace Graphics

} // namespace Dali

#endif // DALI_GRAPHICS_VULKAN_IMAGE