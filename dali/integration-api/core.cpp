/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd.
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

// CLASS HEADER
#include <dali/integration-api/core.h>

// INTERNAL INCLUDES
#include <dali/integration-api/events/event.h>
#include <dali/integration-api/gl-context-helper-abstraction.h>
#include <dali/integration-api/gl-sync-abstraction.h>
#include <dali/integration-api/processor-interface.h>
#include <dali/internal/common/core-impl.h>
#include <dali/public-api/actors/layer.h>
#include <dali/public-api/common/dali-common.h>
#include <dali/public-api/render-tasks/render-task-list.h>

namespace Dali
{
namespace Integration
{
Core* Core::New(RenderController&           renderController,
                PlatformAbstraction&        platformAbstraction,
                GlAbstraction&              glAbstraction,
                GlSyncAbstraction&          glSyncAbstraction,
                GlContextHelperAbstraction& glContextHelperAbstraction,
                RenderToFrameBuffer         renderToFboEnabled,
                DepthBufferAvailable        depthBufferAvailable,
                StencilBufferAvailable      stencilBufferAvailable,
                PartialUpdateAvailable      partialUpdateAvailable)
{
  Core* instance  = new Core;
  instance->mImpl = new Internal::Core(renderController,
                                       platformAbstraction,
                                       glAbstraction,
                                       glSyncAbstraction,
                                       glContextHelperAbstraction,
                                       renderToFboEnabled,
                                       depthBufferAvailable,
                                       stencilBufferAvailable,
                                       partialUpdateAvailable);

  return instance;
}

Core::~Core()
{
  delete mImpl;
}

void Core::Initialize()
{
  mImpl->Initialize();
}

ContextNotifierInterface* Core::GetContextNotifier()
{
  return mImpl->GetContextNotifier();
}

void Core::ContextCreated()
{
  mImpl->ContextCreated();
}

void Core::ContextDestroyed()
{
  mImpl->ContextDestroyed();
}

void Core::RecoverFromContextLoss()
{
  mImpl->RecoverFromContextLoss();
}

void Core::SceneCreated()
{
  mImpl->SceneCreated();
}

void Core::QueueEvent(const Event& event)
{
  mImpl->QueueEvent(event);
}

void Core::ProcessEvents()
{
  mImpl->ProcessEvents();
}

uint32_t Core::GetMaximumUpdateCount() const
{
  return mImpl->GetMaximumUpdateCount();
}

void Core::Update(float elapsedSeconds, uint32_t lastVSyncTimeMilliseconds, uint32_t nextVSyncTimeMilliseconds, UpdateStatus& status, bool renderToFboEnabled, bool isRenderingToFbo)
{
  mImpl->Update(elapsedSeconds, lastVSyncTimeMilliseconds, nextVSyncTimeMilliseconds, status, renderToFboEnabled, isRenderingToFbo);
}

void Core::PreRender(RenderStatus& status, bool forceClear, bool uploadOnly)
{
  mImpl->PreRender(status, forceClear, uploadOnly);
}

void Core::PreRender(Integration::Scene& scene, std::vector<Rect<int>>& damagedRects)
{
  mImpl->PreRender(scene, damagedRects);
}

void Core::RenderScene(RenderStatus& status, Integration::Scene& scene, bool renderToFbo)
{
  mImpl->RenderScene(status, scene, renderToFbo);
}

void Core::RenderScene(RenderStatus& status, Integration::Scene& scene, bool renderToFbo, Rect<int>& clippingRect)
{
  mImpl->RenderScene(status, scene, renderToFbo, clippingRect);
}

void Core::PostRender(bool uploadOnly)
{
  mImpl->PostRender(uploadOnly);
}

void Core::RegisterProcessor(Processor& processor)
{
  mImpl->RegisterProcessor(processor);
}

void Core::UnregisterProcessor(Processor& processor)
{
  mImpl->UnregisterProcessor(processor);
}

ObjectRegistry Core::GetObjectRegistry() const
{
  return ObjectRegistry(&mImpl->GetObjectRegistry());
}

Core::Core()
: mImpl(nullptr)
{
}

} // namespace Integration

} // namespace Dali
