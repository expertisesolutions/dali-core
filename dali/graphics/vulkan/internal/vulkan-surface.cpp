/*
 * Copyright (c) 2017 Samsung Electronics Co., Ltd.
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

// INTERNAL INCLUDES
#include <dali/graphics/vulkan/internal/vulkan-surface.h>
#include <dali/graphics/vulkan/vulkan-graphics.h>
#include <dali/integration-api/graphics/vulkan/vk-surface-factory.h>

namespace Dali
{
namespace Graphics
{
namespace Vulkan
{

struct Surface::Impl
{
  Impl( Surface& owner, Graphics& graphics, std::unique_ptr< SurfaceFactory > surfaceFactory ) :
          mOwner( owner ), mGraphics( graphics ), mSurfaceFactory( std::move( surfaceFactory ) )
  {
    mVulkanSurfaceFactory = dynamic_cast<Dali::Integration::Graphics::Vulkan::VkSurfaceFactory*>(mSurfaceFactory.get());
  }

  ~Impl()
  {

  }

  bool Initialise()
  {
    if( !mVulkanSurfaceFactory )
    {
      return false;
    }

    // fixme: should avoid const cast :(
    auto* allocatorCallbacks = const_cast<vk::AllocationCallbacks*>(&mGraphics.GetAllocator());
    mSurface = mVulkanSurfaceFactory
            ->Create( mGraphics.GetInstance(), allocatorCallbacks, mGraphics.GetPhysicalDevice() );

    if( !mSurface )
    {
      return false;
    }

    mCapabilities = VkAssert( mGraphics.GetPhysicalDevice().getSurfaceCapabilitiesKHR( mSurface ) );

    return true;
  }

  vk::SurfaceCapabilitiesKHR GetCapabilities() const
  {
    return VkAssert( mGraphics.GetPhysicalDevice().getSurfaceCapabilitiesKHR( mSurface ) );
  }

  Surface& mOwner;
  Graphics& mGraphics;
  std::unique_ptr< SurfaceFactory > mSurfaceFactory;
  Dali::Integration::Graphics::Vulkan::VkSurfaceFactory* mVulkanSurfaceFactory;
  vk::SurfaceKHR mSurface;
  vk::SurfaceCapabilitiesKHR mCapabilities;
};

/**
 * Surface
 */

RefCountedSurface Surface::New( Graphics& graphics, std::unique_ptr< SurfaceFactory > surfaceFactory )
{
  return RefCountedSurface( new Surface( graphics, std::move( surfaceFactory ) ) );
}

Surface::Surface( Graphics& graphics, std::unique_ptr< SurfaceFactory > surfaceFactory )
{
  mImpl = std::make_unique< Impl >( *this, graphics, std::move( surfaceFactory ) );
}

Surface::~Surface() = default;

bool Surface::Create()
{
  return mImpl->Initialise();
}

vk::SurfaceKHR Surface::GetSurfaceKHR() const
{
  return mImpl->mSurface;
}

vk::SurfaceCapabilitiesKHR Surface::GetCapabilities() const
{
  return mImpl->GetCapabilities();
}

} // namespace Vulkan
} // namespace Graphics
} // namespace Dali